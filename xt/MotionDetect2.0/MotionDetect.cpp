#include <stdio.h>
#include <stdlib.h>
using namespace std;
#include <vector>
#include "xtofglobal.h"
#include "xtofFindCorner.h"
#include "xtofCalcPyrlk.h"
#include "xtofAffine2D.h"
#include "xtofCameraHeight.h"
#include "xtofCameraCorrect.h"
#include <opencv/highgui.h>
#include <opencv2/opencv.hpp>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <time.h>

extern "C"{
#include "PilotData.h"
};

using namespace cv;

#define  CAMERA_WIDTH   640
#define  CAMERA_HEIGHT  480

#define  IMG_SELECT_X 90	//视频截取图像左上角x坐标
#define  IMG_SELECT_Y 60        //视频截取图像左上角y坐标
#define  IMG_SELECT_WIDTH 400   //视频截取图像宽度
#define  IMG_SELECT_LENGTH 400  //视频截取图像长度
#define  IMG_SCALE 0.5          //视频截取图像缩放比例

TermCriteria cornerTermcrit(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, 0.03);//迭代次数和迭代精度
Mat imgPrev;                    //前一帧图像，最新从视频流获取到的在前面
Mat imgPost;                    //后一帧图像
Mat affine2D;
Mat affineInlier;
vector<Mat> imgPyrPrev;
vector<Mat> imgPyrPost;
int maxLevelNum = 3;

float g_cameraHeight = 0.0f; //单位cm
float g_cameraShiftX = 0.0f;
float g_cameraShiftY = 0.0f;

float cameraShiftSumX = 0.0f, cameraShiftSumY = 0.0f;
double sumTime;


int xtofOpticalFlow();

int main(int argc, char **argv)
{
	/* init camera */
	float roll,pitch,yaw;
	unsigned long msgTime;
	VideoCapture capture;
	capture = VideoCapture(-1);
	
	if(!capture.isOpened())
	{
		fprintf(stderr, "Can't initialize webcam!\n");
		return -1;
	}

	int listening = ListenForPilotData();
	if(listening<0)
	{
		fprintf(stderr,"Can't get AHRS from pilot.\n");
	}

	/* Get first frame */	
	Mat frame,image;
	capture >> frame;
	if(frame.empty()){
		fprintf(stderr,"Get frame failed.\n");
		return -1;
	}

	image = frame(Rect(IMG_SELECT_X, IMG_SELECT_Y, IMG_SELECT_WIDTH, IMG_SELECT_LENGTH));
	Mat cameraMapX, cameraMapY;
	xtofCameraCorrect(image.size(), cameraMapX, cameraMapY);//矫正矩阵求解
	remap(image, image, cameraMapX, cameraMapY, INTER_LINEAR);//图像摄像机畸变矫正

	resize(image, image, Size(), IMG_SCALE, IMG_SCALE);
	cvtColor(image, imgPost, COLOR_BGR2GRAY);//准备后一张图片
	maxLevelNum = buildOpticalFlowPyramid(imgPost, imgPyrPost, Size(WIN_SIZE, WIN_SIZE), maxLevelNum, false);
	while (1)
	{
		
		capture >> frame;
		if (frame.empty())
		{
			break;
		}
		image = frame(Rect(IMG_SELECT_X, IMG_SELECT_Y, IMG_SELECT_WIDTH, IMG_SELECT_LENGTH));
		remap(image, image, cameraMapX, cameraMapY, INTER_LINEAR);//图像摄像机畸变矫正
		resize(image, image, Size(), IMG_SCALE, IMG_SCALE);
		cvtColor(image, imgPrev, COLOR_BGR2GRAY);

		xtofOpticalFlow();
	}

	return 0;
}



/****************************************************************************************
* File: main.cpp
* Name: xtofOpticalFlow
* Input:
* Output:
* Function:
* Date: 2016/07/04 23:41
*****************************************************************************************/
int xtofOpticalFlow()
{
	vector<Point2f> cornerPrev, cornerPost;
	vector<uchar> cornerStatus;//
	vector<float> cornerErr; //

#ifdef DEBUG
	static int imgNum = 0;//图像序号
	double findTime = (double)cvGetTickCount();
#endif


	//寻找易跟踪的角点
	xtofCornerToTrack(imgPost, cornerPost, Mat(), 3);



#ifdef DEBUG
	findTime = ((double)cvGetTickCount() - findTime) / (cvGetTickFrequency() * 1000);
	double pyrTime = (double)cvGetTickCount();
#endif


	//光流跟踪
	maxLevelNum = buildOpticalFlowPyramid(imgPrev, imgPyrPrev, Size(WIN_SIZE,WIN_SIZE), maxLevelNum, false);
	//0.001这个参数非常重要，太大了会判断为跟踪失败	
	xtofCalcPyrlk(imgPyrPost, imgPyrPrev, cornerPost, cornerPrev, cornerStatus, cornerErr, cornerTermcrit, 0, 0.001L, maxLevelNum);
	swap(imgPyrPost, imgPyrPrev);


#ifdef DEBUG
	pyrTime = ((double)cvGetTickCount() - pyrTime) / (cvGetTickFrequency() * 1000);
#endif


	//成功跟踪角点提取
	vector<Point2f> cornerPrevC, cornerPostC;
	int cornerNum;
	for (cornerNum = 0; cornerNum < cornerStatus.size(); cornerNum++)
	{
		if (cornerStatus[cornerNum])
		{
			cornerPrevC.push_back(cornerPrev[cornerNum]);
			cornerPostC.push_back(cornerPost[cornerNum]);
		}
	}


#ifdef DEBUG
	double affineTime = (double)cvGetTickCount();
#endif

	//仿射变换矩阵求取	
	xtofAffine2D(cornerPrevC, cornerPostC, affine2D, affineInlier, 2, 0.96);


#ifdef DEBUG
	affineTime = ((double)cvGetTickCount() - affineTime) / (cvGetTickFrequency() * 1000);
#endif

	//更新高度，激光高度获取	
	xtofCameraHeight(g_cameraHeight);


	//计算实际位移
	//方案一
	g_cameraShiftX = (float)(affine2D.at<double>(0, 2) / CAMERA_FOCAL_X * g_cameraHeight / IMG_SCALE);
	g_cameraShiftY = (float)(affine2D.at<double>(1, 2) / CAMERA_FOCAL_Y * g_cameraHeight / IMG_SCALE);
	//distanceSumX += distanceX;
	//distanceSumY += distanceY;
	//方案二
	//利用视场角、高度信息，待写
	//位移滤波

	//按电子罗盘方向分解x,y方向位移并求和，视频调试
	//static int i = 0;
	//++i;

	swap(imgPost, imgPrev);
	

#ifdef DEBUG
	++ imgNum;//图像序号
	cout << imgNum << "\t" << cornerNum << '\t';
	
	cout.precision(4);
	cout.setf(ios::fixed);//小数点后精确几位
	//cout << tSum / (cvGetTickFrequency() * 1000 << endl;
	cout << affine2D.at<double>(0, 0) << '\t' << affine2D.at<double>(0, 1) << '\t' << g_cameraShiftX << '\t'
		<< affine2D.at<double>(1, 0) << "\t" << affine2D.at<double>(1, 1) << "\t" << g_cameraShiftY << "\t";

	cameraShiftSumX += g_cameraShiftX;
	cameraShiftSumY += g_cameraShiftY;
	
	cout <<findTime << "\t" << pyrTime << '\t' << affineTime << '\t';

	//先把数据复制出来,以免画上面的点影响后续检测
	Mat imgPostTmp;
	imgPost.copyTo(imgPostTmp);
	for (int i = 0; i < cornerPostC.size(); i++)
	{
		if (1 == affineInlier.at<unsigned char>(i))
		{
			circle(imgPrev, cornerPostC[i], 1, Scalar(255, 0, 0), -1, 8);//因为swap函数imgpPrev实为post
			circle(imgPostTmp, cornerPrevC[i], 1, Scalar(255, 0, 0), -1, 8);//因为swap函数imgPost实为Prev
		}
		else
		{
			circle(imgPrev, cornerPostC[i], 2, Scalar(255, 0, 0), -1, 8);//因为swap函数imgpPrev实为post
			circle(imgPostTmp, cornerPrevC[i], 2, Scalar(255, 0, 0), -1, 8);//因为swap函数imgPost实为Prev
		}
	}
	//调试时保存图片
	//char str1[30],str2[30];
	//sprintf_s(str1, "img\\img_%d_Post.bmp", imgNum);
	//cv::imwrite(str1, imgPrev);
	//sprintf_s(str2, "img\\img_%d_Prev.bmp", imgNum);
	//cv::imwrite(str2, imgPostTmp);

	//cv::imshow("win1",imgPrev);
	//cvWaitKey(1);
#endif

	return 1;
}
