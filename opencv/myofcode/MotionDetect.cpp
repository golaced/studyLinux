#include <cstdio>
//#include <stdio.h>
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
#include <math.h>
#include "debug.h"

#include "mavlink/common/mavlink.h"
#include "xtofmavlinktest.h"

extern "C"
{
	#include "xtofReadSonar.h"
	#include "PilotData.h"
};
using namespace cv;


int maxLevelNum = 4;//金字塔层数，从0开始
float g_ofpyrThreshold = 0.0003f;//0.001f;//解算光流过程中，G矩阵较小特征值比较
double g_ofAffineThreshold = 2;//可以把一个点看作内点的最大误差
double g_ofAffineQuality = 0.96;//仿射变换置信度，与迭代次数相关

float g_cameraHeight = 0.0f; //单位cm
float g_cameraShiftX = 0.0f;
float g_cameraShiftY = 0.0f;
float cameraShiftSumX = 0.0f, cameraShiftSumY = 0.0f;
double sumTime;
struct global_struct global_data;
vector<Point2f> cornerPost;

int xtofOpticalFlow(Mat &imgPrev, Mat &imgDisplay);
void debugDrawCurve(float x, float y, string s);
void globalDataInit();
int ofFilterMediam(float &x, float &y, float a);
void quick_sort(float s[], int l, int r);

int main(int argc, char *argv[])
{
	globalDataInit();

	string videoName;
	VideoCapture cap;

	if(argc != 1) 
	{
		string path = "/home/lxg-/video/";
		videoName = path + argv[1];
		cap.open(videoName);
	} 
	else 
	{
		printf("try to open cap 1\n");
		cap.open(1);
	}


	if (!cap.isOpened()) {
		printf("can not open cap 1!\n");
		cap.open(0);
		if(!cap.isOpened())
		{
			printf("can not open cap 0\n");
			return 0;
		}
	}

	//光流算法初始化部分，第一帧图片的获取
	Mat frame, image, imgDisplay;
	cap >> frame;
	if (frame.empty()) return -1;
	if(frame.cols < IMG_SELECT_AREA)
	{
		printf("select area is larger than camera\n");
		return 1;
	}
	global_data.img.leftupX = (frame.cols - IMG_SELECT_AREA) / 2;
	global_data.img.leftupY = (frame.rows - IMG_SELECT_AREA) / 2;

	if(global_data.param[PARAM_SEND_DATA])
	{
		if(global_data.param[PARAM_SEND_DATA] == SEND_DATA_MAVLINK)
		{
			printf("mavlink example program running\n");
			if(global_data.mavlink == MAVLINK_COMM_NET)
			{
				//mavlink_example();
				mavlinkNetInit();
			}
			else if(global_data.mavlink == MAVLINK_COMM_UART)
			{
				mavlinkUartInit();
			}
			printf("mavlink example program finish\n");
		}
		else if(global_data.param[PARAM_SEND_DATA] == SEND_DATA_UART)
		{
			printf("uart init\n");
			usbNrfInit();
		}

	}
#ifndef DEBIAN
	if(global_data.param[PARAM_SAVE_TEST_VIDEO])
	{
		saveVideoInit();
	}
#endif

#ifdef DEBUG
	//cout重定向
	ofstream out("out.txt");
	cout.rdbuf(out.rdbuf());

	//输出调试时间
	time_t rawTime = time(&rawTime);
	struct tm timeInfo;
	char asctimeChar[50];

	localtime_s(&timeInfo, &rawTime);
	asctime_s(asctimeChar, &timeInfo);
	cout << asctimeChar;

	//输出调试视频信息格式
	cout << "video_name: " << videoName << endl;

	int nframes = (int)cap.get(CV_CAP_PROP_FRAME_COUNT);
	int framesR = (int)cap.get(CV_CAP_PROP_FPS);

	cout << "cap nframes: " << nframes << "\tfps: " << framesR << "\tcols: " << frameW << "\trows: " << frameH << "\n";
	std::cout << "franeNum\tpointsNum" << "\tout(0,0)\tout(0,1)\tdx\tout(1,0)\tout(1,1)\tdy";
	std::cout << "\tfindFea" << "\ttyrlk" << "\transac" << "\tfunTime\n";
#endif

	char cKey=0;
	while (1)
	{
		double funTime = (double)getTickCount();
		cap >> frame; 
		printf("cameraT %3.2f\t", ((double)getTickCount() - funTime) / getTickFrequency() * 1000);
		if (frame.empty()||(cKey == 's'))
		{
			break;
		}
		frame = frame(Rect(global_data.img.leftupX, global_data.img.leftupY, IMG_SELECT_AREA, IMG_SELECT_AREA));
		cvtColor(frame, frame, COLOR_BGR2GRAY);
		resize(frame, image, Size(), IMG_SCALE, IMG_SCALE);
		if(global_data.param[PARAM_FILTER_IMG])
		{
			//GaussianBlur(image, image, Size(3,3), 0, 0);//对初始图像滤波
			blur(image, image, Size(3,3));
		}
		image.copyTo(imgDisplay);
		//remap(image, image, cameraMapX, cameraMapY, INTER_LINEAR);//图像摄像机畸变矫正,浪费时间
		if(global_data.param[PARAM_PREPROCESS_ISC])
		{
			preprocessImISC(image);
		}


		double localTime = (double)getTickCount();
		xtofOpticalFlow(image, imgDisplay);
		//printf("cameratime%3.2f\t", ((double)getTickCount() - funTime) / getTickFrequency() * 1000);

		funTime = ((double)getTickCount() - funTime) / getTickFrequency() * 1000;
		printf("funT %3.2f\t", funTime);
		cKey=waitKey(1);
	}

#ifdef DEBUG
	cout << "sumShiftX: " << cameraShiftSumX << '\n' << "sumShiftY: "<< cameraShiftSumY << endl;
	cout << "sumTime: " << sumTime / 1000 << "s" << endl;
	std::cout << "resize-cols: " << image.cols << "\tresize-rows: " << image.rows << "\n\n";

	localtime_s(&timeInfo, &rawTime);
	asctime_s(asctimeChar, &timeInfo);
	cout << asctimeChar;
#endif

#ifndef DEBIAN
	if(global_data.param[PARAM_SAVE_TEST_VIDEO])
	{
		closeSaveVideo();
	}
#endif

	return 0;
}
/****************************************************************************************
* File: main.cpp
* Name: xtofOpticalFlow
* Input:imgPrev//前一帧图像，最新从视频流获取到的在前面
* Output:
* Function:
* Date: 2016/07/04 23:41
*****************************************************************************************/
int xtofOpticalFlow(Mat &imgPrev, Mat &imgDisplay)
{
	static Mat imgPost; //后一帧图像，
	static vector<Mat> imgPyrPrev;
	static vector<Mat> imgPyrPost;
	//static vector<Point2f> cornerPostMask;
	vector<Point2f> cornerPrevC, cornerPostC;
	Mat affine2D(2, 3, CV_64F);
	Mat affineInlier;
	float of_quality;


	affine2D.setTo(0.f);
	g_cameraShiftX = 0.f;
	g_cameraShiftY = 0.f;
	of_quality = 0;
	//更新高度	
	xtofCameraHeight(g_cameraHeight);

	//根据已有角点生成mask
	Mat mask = Mat::ones(imgPrev.size(), CV_8U) * 255;//0被屏蔽
	//xtofMaskCreate(mask, cornerPostMask);
	//cornerPostMask.clear();

	if (imgPost.empty())
	{
		imgPrev.copyTo(imgPost);
		buildOpticalFlowPyramid(imgPost, imgPyrPost, Size(WIN_SIZE, WIN_SIZE), maxLevelNum, false);
	}
	
	vector<Point2f> cornerPrev;//6*6=36个固定点
	if(!global_data.param[PARAM_FIX_POINT]) 
	{
		cornerPost.clear();
		xtofCornerToTrack(imgPost, cornerPost, mask, WIN_SIZE);// 找角点的计算特征值模板的大小
	}
	maxLevelNum = buildOpticalFlowPyramid(imgPrev, imgPyrPrev, Size(WIN_SIZE, WIN_SIZE), maxLevelNum, false);
	//printf("levelNum:%d ", maxLevelNum);
	int inlierNum = 0;

	if (cornerPost.size() > 6)
	{
		vector<uchar> cornerStatus;
		vector<float> cornerErr; 
		
		//光流迭代条件设置
		TermCriteria cornerTermcrit(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 15, 0.1);//迭代次数和迭代精度
		//g_ofpyrThreshold判断跟踪失败的阈值，大于g_ofpyrThreshold会判断为跟踪失败,与G矩阵较小的特征值进行比较
		xtofCalcPyrlk(imgPyrPost, imgPyrPrev, cornerPost, cornerPrev, cornerStatus, cornerErr, cornerTermcrit, g_ofpyrThreshold, maxLevelNum);

		/*成功跟踪角点提取*///如果角点之间位移过大，可判断为跟踪失败
		for (int cornerNum = 0; cornerNum < cornerStatus.size(); cornerNum++)
		{
			if ((cornerStatus[cornerNum]) || (cornerErr[cornerNum] > 40))
			{
				// float x = floor(cornerPrev[cornerNum].x + 0.5);
				// float y = floor(cornerPrev[cornerNum].y + 0.5);
				// cornerPrevC.push_back(Point2f(x,y));

				cornerPrevC.push_back(cornerPrev[cornerNum]);
				cornerPostC.push_back(cornerPost[cornerNum]);
				//cornerPostMask.push_back(cornerPrev[cornerNum]);//prev的角点在下一循环的新图像上,需要判断角点之间的距离来生成
			}
		}

		affineInlier.create(1,cornerPrevC.size(),CV_8U);
		affineInlier.setTo(1);

		printf("cornerSize:%d\t", (int)cornerPrevC.size());

		if (cornerPrevC.size() > 10)
		{
			/*仿射变换矩阵求取*/
			
			if (xtofAffine2D(inlierNum, cornerPrevC, cornerPostC, affine2D, affineInlier, g_ofAffineThreshold, g_ofAffineQuality))
			{
				if ((affine2D.at<double>(0, 0) < -2) || (affine2D.at<double>(0, 0) > 2)
					|| (affine2D.at<double>(1, 1) < -2) || (affine2D.at<double>(1, 1) > 2)
					|| (affine2D.at<double>(0, 1) < -1) || (affine2D.at<double>(0, 1) > 1)
					|| (affine2D.at<double>(1, 0) < -1) || (affine2D.at<double>(1, 0) > 1))
				{
					affine2D.setTo(0);
				}
				/*计算实际位移*/
				//方案一
				g_cameraShiftX = 0 - (float)(affine2D.at<double>(0, 2) / CAMERA_FOCAL_X * g_cameraHeight / IMG_SCALE);
				g_cameraShiftY = 0 - (float)(affine2D.at<double>(1, 2) / CAMERA_FOCAL_Y * g_cameraHeight / IMG_SCALE);
				//distanceSumX += distanceX;
				//distanceSumY += distanceY;
				//方案二
				//利用视场角、高度信息，待写
				//位移滤波
				of_quality = (float)inlierNum / cornerPrev.size();

				if(global_data.param[PARAM_FILTER_MEDIAM])//中值滤波
				{
					ofFilterMediam(g_cameraShiftX, g_cameraShiftY, 0.8);
				}
			}
		}
	}
	swap(imgPyrPost, imgPyrPrev);
	swap(imgPost, imgPrev);

#ifndef DEBIAN
	debugDrawCurve(g_cameraShiftX,g_cameraShiftY, "curve1");
	cvtColor(imgDisplay, imgDisplay, CV_GRAY2BGR);
	
	for (int i = 0; i < cornerPostC.size(); i++)
	{
		if (1 == affineInlier.at<unsigned char>(i))
		{
			circle(imgDisplay, cornerPostC[i], 1, Scalar(255, 0, 0), -1, 8);//因为swap函数imgpPrev实为post
			circle(imgDisplay, cornerPrevC[i], 1, Scalar(255, 0, 0), -1, 8);//因为swap函数imgPost实为Prev
			line(imgDisplay,cornerPrevC[i],cornerPostC[i],Scalar(255, 0, 0));
		}
		else
		{
			// circle(imgDisplay, cornerPostC[i], 2, Scalar(0, 0, 255), -1, 8);//因为swap函数imgpPrev实为post
			// circle(imgDisplay, cornerPrevC[i], 2, Scalar(0, 0, 255), -1, 8);//因为swap函数imgPost实为Prev
			// line(imgDisplay,cornerPrevC[i],cornerPostC[i],Scalar(0, 0, 255));
		}
	}

	resize(imgDisplay,imgDisplay,Size(300,300));
	cv::imshow("camera",imgDisplay);

	if(global_data.param[PARAM_SAVE_TEST_VIDEO])
	{
		 saveVideo(imgDisplay);//函数内Size要和视频大小相同
	}
#endif
	if(global_data.param[PARAM_SEND_DATA])
	{
		if(global_data.param[PARAM_SEND_DATA] == SEND_DATA_MAVLINK)
		{
			if(global_data.param[PARAM_SEND_OPTICAL_MAVLINK])
			{
				mavlink_msg_heartbeat_send(global_data.mavlink, MAV_TYPE_HELICOPTER, MAV_AUTOPILOT_GENERIC
					, MAV_MODE_GUIDED_ARMED, 0, MAV_STATE_ACTIVE);
				mavlink_msg_optical_flow_send(global_data.mavlink, microsSinceEpoch(), global_data.param[PARAM_SENSOR_ID]
					, 0 - affine2D.at<double>(0, 2) / CAMERA_FOCAL_X * g_cameraHeight / IMG_SCALE * 20
					, affine2D.at<double>(1, 2) //对应qgroundcontrol上的flow_x,flow_y,需要是整数类型
					, g_cameraShiftX * 20 //对应flow_comp_m_x
					, g_cameraShiftY * 20, of_quality * 100, g_cameraHeight);
					//, affine2D.at<double>(0, 2), affine2D.at<double>(1, 2), of_quality, g_cameraHeight);
				//printf("send optical\n");
			}

			if(global_data.param[PARAM_SEND_VIDEO_MAVLINK])
			{
				uint16_t image_size_send;

				image_size_send = global_data.img.width * global_data.img.height;//100*100;//image_size;
				mavlink_msg_data_transmission_handshake_send(
					global_data.mavlink,
					MAVLINK_DATA_STREAM_IMG_RAW8U,
					image_size_send,
					global_data.img.width,
					global_data.img.height,
					image_size_send / MAVLINK_MSG_ENCAPSULATED_DATA_FIELD_DATA_LEN + 1,
					MAVLINK_MSG_ENCAPSULATED_DATA_FIELD_DATA_LEN,
					100);
				uint16_t frame = 0;
				for (frame = 0; frame < image_size_send / MAVLINK_MSG_ENCAPSULATED_DATA_FIELD_DATA_LEN + 1; frame++)
				{
					mavlink_msg_encapsulated_data_send(global_data.mavlink, frame, 
						&((uint8_t *) imgPrev.data)[frame * MAVLINK_MSG_ENCAPSULATED_DATA_FIELD_DATA_LEN]);
				}
			}
		}
		if(global_data.param[PARAM_SEND_DATA] == SEND_DATA_UART)
		{
			printf("send uart\n");
			nrfSend(g_cameraShiftX, g_cameraShiftY);
		}
	}	
#ifdef DEBUG
	static int imgNum{ 0 };//图像序号

	++imgNum;//图像序号

	printf("%d\t%1.3f\t%1.3f\t", imgNum, g_cameraShiftX, g_cameraShiftY);
	debugDrawCurve(g_cameraShiftX, g_cameraShiftY);
	cout << imgNum << "\t" << cornerPostC.size() << '\t';

	cout.precision(4);
	cout.setf(ios::fixed);//小数点后精确几位
	//cout << tSum / (cvGetTickFrequency() * 1000 << endl;
	cout << affine2D.at<double>(0, 0) << '\t' << affine2D.at<double>(0, 1) << '\t' << g_cameraShiftX << '\t'
		<< affine2D.at<double>(1, 0) << "\t" << affine2D.at<double>(1, 1) << "\t" << g_cameraShiftY << "\t";

	cameraShiftSumX += g_cameraShiftX;
	cameraShiftSumY += g_cameraShiftY;
	
	//先把数据复制出来,以免画上面的点影响后续检测
	//调试时保存图片
	//char str1[30], str2[30];
	//if ((g_cameraShiftY < -20) || (g_cameraShiftY > 20) 
	//	|| (g_cameraShiftX < -20) || (g_cameraShiftX > 20))
	//{
	//	sprintf_s(str1, "img\\img_%d_Post.bmp", imgNum);
	//	cv::imwrite(str1, imgPrev);
	//	sprintf_s(str2, "img\\img_%d_Prev.bmp", imgNum);
	//	cv::imwrite(str2, imgPostTmp);
	//}
#else
	printf("%2.3f\t%2.3f\n", g_cameraShiftX, g_cameraShiftY);
#endif

	return 1;
}

void globalDataInit()
{
	mavlink_system.sysid = 1;
	mavlink_system.compid = 200;

	global_data.mavlink= MAVLINK_COMM_NET;//MAVLINK_COMM_NET, MAVLINK_COMM_NRF
	global_data.param[PARAM_SEND_DATA] = SEND_DATA_MAVLINK;//SEND_DATA_UART,SEND_DATA_MAVLNK,FALSE

	global_data.param[PARAM_SENSOR_ID] = 200;

	global_data.param[PARAM_SEND_OPTICAL_MAVLINK] = TRUE;
	global_data.param[PARAM_SEND_VIDEO_MAVLINK] = TRUE;//是否发送mavlink视频
	global_data.param[PARAM_SEND_SONAR_MAVLINK] = TRUE;

	global_data.img.width =  IMG_SELECT_AREA * IMG_SCALE;//最终图像大小
	global_data.img.height =  IMG_SELECT_AREA * IMG_SCALE;

	global_data.param[PARAM_SONAR_RAW] = FALSE;//输出超声波距离
	global_data.param[PARAM_FIX_POINT] = TRUE;//固定点，指不计算容易跟踪的点

	global_data.param[PARAM_PREPROCESS_ISC] = FALSE;//是否用ISC预处理
	global_data.param[PARAM_SAVE_TEST_VIDEO] = TRUE;//保存视频
	global_data.param[PARAM_FILTER_IMG] = FALSE;//是否对原图像滤波
	global_data.param[PARAM_FILTER_MEDIAM] = TRUE;//对光流输出滤波

	if(global_data.param[PARAM_FIX_POINT])
	{
		setCorner(cornerPost);
	}

}

#define DEBUGARRAYLENGTH 201

void debugDrawCurve(float x, float y, string s)
{
	Size winSize(700, 400);
	Mat im = Mat::zeros(winSize, CV_8UC3);
	
	
	static int imX[DEBUGARRAYLENGTH];
	static int imY[DEBUGARRAYLENGTH];

	int arrayLength = DEBUGARRAYLENGTH - 1;
	int max = 150, min = -150;

	x *= 20;//放大倍数
	y *= 20;
	if (x > max) x = max;
	if (x < min) x = min;
	if (y > max) y = max;
	if (y < min) y = min;

	imX[arrayLength] = (int)(x + winSize.height / 2);
	imY[arrayLength] = (int)(y + winSize.height / 2);//向上平移100

	for (int i = 0; i < arrayLength; ++i)
	{
		imX[i] = imX[i + 1];
		imY[i] = imY[i + 1];
	}
	
	line(im, Point2d(0, winSize.height / 2), Point2d(winSize.width, winSize.height / 2), Scalar(255,255,255));
	line(im, Point2d(0, winSize.height / 2 + max), Point2d(winSize.width, winSize.height / 2 + max), Scalar(255, 255, 255));
	line(im, Point2d(0, winSize.height / 2 + min), Point2d(winSize.width, winSize.height / 2 + min), Scalar(255, 255, 255));

	for (int i = arrayLength; i > 0; --i)
	{
		line(im, Point2d(i * 3, imX[i]), Point2d((i - 1) * 3, imX[i - 1]), Scalar(0, 0, 255), 1);
		line(im, Point2d(i * 3, imY[i]), Point2d((i - 1) * 3, imY[i - 1]), Scalar(0, 255, 0), 1);
		circle(im, Point2d(i * 3, imX[i]), 2, Scalar(0, 0, 255), -1, 8);
		circle(im, Point2d(i * 3, imY[i]), 2, Scalar(0, 255, 0), -1, 8);
	}
	imshow(s, im);
	//saveVideo(im);//函数内Size要和视频大小相同
}

int ofFilterMediam(float &x, float &y, float a)
{
	//中值滤波
	static float xx[7];
	static float yy[7];
	float xtmp[7];
	float ytmp[7];

	for(int i = 5; i > -1; i--)
	{
		xx[i + 1] = xx[i];
		xtmp[i + 1] = xx[i + 1];
	//	printf(" %f ", xx[i]);
	}
	xx[0] = x;
	xtmp[0] = xx[0];	
	quick_sort(xtmp, 0, 5);
	x = xtmp[3];
	// for(int i = 0; i < 6; i++)
	// {
	// 	printf("%f\t", xtmp[i]);
	// }

	// yy[2] = yy[1]; 
	// yy[1] = yy[0];
	// if(yy[2] > yy[1])
	// {
	// 	if(y > yy[2])
	// 	{
	// 		y = yy[2];
	// 	}
	// 	else if(y < yy[1])
	// 	{
	// 		y = yy[1];
	// 	}
	// }
	
	// //限幅滤波
	// int max = 20;//单位cm
	// int min = 0 - max;
	// if(x > max)
	// { 
	// 	x = max;
	// }
	// else if(x < min)
	// {
	// 	x = min;
	// }
	// if(y > max)
	// {
	// 	y = max;
	// }
	// else if(y < min)
	// {
	// 	y = min;
	// }

	// //低通滤波
	// static float xxx[4];
	// static float yyy[4];
	
	// x = x * a + xxx[0] * (1 - a);
	// // x = (xxx[3] + xxx[2] + xxx[1] + xxx[0] + x) / 5;
	// // xxx[3] = xxx[2];
	// // xxx[2] = xxx[1];
	// // xxx[1] = xxx[0];
	// xxx[0] = x;

	// y = y * a + yyy[0] * (1 - a);
	// // y = (yyy[3] + yyy[2] + yyy[1] + yyy[0] + y) / 5;
	// // yyy[3] = yyy[2];
	// // yyy[2] = yyy[1];
	// // yyy[1] = yyy[0];
	// yyy[0] = y;

	//消抖滤波法,其实就是对信号进行了降采样
	// static int count;
	// static float xlast, ylast;
	// //if(((x - xlast) < 0.1)&&((x - xlast) > -0.1))
	// if(x == xlast)
	// {
	// 	count = 0;
	// }
	// else 
	// {
	// 	count ++;
	// }
	// if(count < 3)
	// {
	// 	x = xlast;
	// }
	// else
	// {
	// 	xlast = x;
	// 	count = 0;
	// }

}

/*
快速排序
l:数组最小下标,
r：数组最大下标
*/
void quick_sort(float s[], int l, int r)
{
    if (l < r)
    {
		//Swap(s[l], s[(l + r) / 2]); //将中间的这个数和第一个数交换 参见注1
        int i = l, j = r;
		float x = s[l];
        while (i < j)
        {
            while(i < j && s[j] >= x) // 从右向左找第一个小于x的数
				j--;  
            if(i < j) 
				s[i++] = s[j];
			
            while(i < j && s[i] < x) // 从左向右找第一个大于等于x的数
				i++;  
            if(i < j) 
				s[j--] = s[i];
        }
        s[i] = x;
        quick_sort(s, l, i - 1); // 递归调用 
        quick_sort(s, i + 1, r);
    }
}