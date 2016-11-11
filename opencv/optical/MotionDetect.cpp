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
#include "camerathread.h"


//#define USE_CAMERA_THREAD
using namespace cv;

int maxLevelNum = 1;//��������������0��ʼ
float g_ofpyrThreshold = 0.001f;//������������У�G�����С����ֵ�Ƚ�
double g_ofAffineThreshold = 2.;//���԰�һ���㿴���ڵ��������
double g_ofAffineQuality = 0.96;//����任���Ŷȣ�������������

float g_cameraHeight = 0.0f; //��λcm
float g_cameraShiftX = 0.0f;
float g_cameraShiftY = 0.0f;
float cameraShiftSumX = 0.0f, cameraShiftSumY = 0.0f;
double sumTime;

int xtofOpticalFlow(Mat &imgPrev);
void debugDrawCurve(float x, float y);

int main()
{
	string videoName;
	Mat frame, image;

#ifdef USE_CAMERA_THREAD
	camera_thread();
	while(imSrc.empty()) ;
	imSrc.copyTo(frame);
#else
	//string videoName{ "D:\\2016\\��ͼ\\��Ƶ\\�������Ե�����20160824\\�Ե�\\544305398.h264" };
	//VideoCapture cap(videoName);

	VideoCapture cap(0);
	if (!cap.isOpened()) 
	{
		printf("can not open cap!\n");
		return 0;
	}
	cap >> frame;
#endif
	//�����㷨��ʼ�����֣���һ֡ͼƬ�Ļ�ȡ
	int imgSelectX1 = (frame.cols - IMG_SELECT_AREA) / 2;
	int imgSelectY1 = (frame.rows - IMG_SELECT_AREA) / 2;

#ifdef DEBUG
	//cout�ض���
	ofstream out("out.txt");
	cout.rdbuf(out.rdbuf());

	//�������ʱ��
	time_t rawTime = time(&rawTime);
	struct tm timeInfo;
	char asctimeChar[50];

	localtime_s(&timeInfo, &rawTime);
	asctime_s(asctimeChar, &timeInfo);
	cout << asctimeChar;

	//���������Ƶ��Ϣ��ʽ
	cout << "video_name: " << videoName << endl;
	int frameH = (int)cap.get(CV_CAP_PROP_FRAME_HEIGHT);
	int frameW = (int)cap.get(CV_CAP_PROP_FRAME_WIDTH);
	int nframes = (int)cap.get(CV_CAP_PROP_FRAME_COUNT);
	int framesR = (int)cap.get(CV_CAP_PROP_FPS);

	cout << "cap nframes: " << nframes << "\tfps: " << framesR << "\tcols: " << frameW << "\trows: " << frameH << "\n";
	std::cout << "franeNum\tpointsNum" << "\tout(0,0)\tout(0,1)\tdx\tout(1,0)\tout(1,1)\tdy";
	std::cout << "\tfindFea" << "\ttyrlk" << "\transac" << "\tfunTime\n";
#endif

	char cKey = 0;
	int frameflg;
	while (1)
	{
		double funTime = (double)getTickCount();
#ifdef USE_CAMERA_THREAD
		//sem_wait(&bin_sem);
		//pthread_mutex_lock(&bin_mut);
		
		cameraNum--;
		while(cameraNum < 0) ;
		imSrc.copyTo(frame);
		//pthread_mutex_unlock(&bin_mut);
#else
		cap >> frame;
#endif
		printf("cameratime%f\t", ((double)getTickCount() - funTime) / getTickFrequency() * 1000);

		if (frame.empty() || (cKey == 's'))
		{
			break;
		}
		frame = frame(Rect(imgSelectX1, imgSelectY1, IMG_SELECT_AREA, IMG_SELECT_AREA));

		resize(frame, frame, Size(), IMG_SCALE, IMG_SCALE);
		//remap(image, image, cameraMapX, cameraMapY, INTER_LINEAR);//ͼ��������������
		cvtColor(frame, image, COLOR_BGR2GRAY);

		//equalizeHist(image,image);
		//GaussianBlur(image,image,Size(3,3),0,0);
		imshow("image",image);
		xtofOpticalFlow(image);
		
		printf("funtime%f\n", ((double)getTickCount() - funTime) / getTickFrequency() * 1000);

		cKey = waitKey(1);
	}
#ifdef DEBUG
	cout << "sumShiftX: " << cameraShiftSumX << '\n' << "sumShiftY: "<< cameraShiftSumY << endl;
	cout << "sumTime: " << sumTime / 1000 << "s" << endl;
	std::cout << "resize-cols: " << image.cols << "\tresize-rows: " << image.rows << "\n\n";

	localtime_s(&timeInfo, &rawTime);
	asctime_s(asctimeChar, &timeInfo);
	cout << asctimeChar;
#endif
	system("pause.\n");
	return 0;
}

/****************************************************************************************
* File: main.cpp
* Name: xtofOpticalFlow
* Input:imgPrev//ǰһ֡ͼ�����´���Ƶ����ȡ������ǰ��
* Output:
* Function:
* Date: 2016/07/04 23:41
*****************************************************************************************/
int xtofOpticalFlow(Mat &imgPrev)
{
	static Mat imgPost; //��һ֡ͼ��
	static vector<Mat> imgPyrPrev;
	static vector<Mat> imgPyrPost;
	static vector<Point2f> cornerPostMask;
	vector<Point2f> cornerPrevC, cornerPostC;
	Mat affine2D(2, 3, CV_64F);
	Mat affineInlier;

	affine2D.setTo(0.f);
	g_cameraShiftX = 0.f;
	g_cameraShiftY = 0.f;


	//���¸߶�	
	xtofCameraHeight(g_cameraHeight);

	//�������нǵ�����mask
	Mat mask = Mat::ones(imgPrev.size(), CV_8U) * 255;//0������
	//xtofMaskCreate(mask, cornerPostMask);
	//cornerPostMask.clear();

	if (imgPost.empty())
	{
		imgPrev.copyTo(imgPost);
		buildOpticalFlowPyramid(imgPost, imgPyrPost, Size(WIN_SIZE, WIN_SIZE), maxLevelNum, false);
	}
	
	vector<Point2f> cornerPrev, cornerPost;

	xtofCornerToTrack(imgPost, cornerPost, mask, WIN_SIZE);//blockSize = 21  �ҽǵ�ļ�������ֵģ��Ĵ�С
	maxLevelNum = buildOpticalFlowPyramid(imgPrev, imgPyrPrev, Size(WIN_SIZE, WIN_SIZE), maxLevelNum, false);

	if (cornerPost.size() > 6)
	{
		vector<uchar> cornerStatus;
		vector<float> cornerErr; 

		TermCriteria cornerTermcrit(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, 0.03);//���������͵�������
		//g_ofpyrThreshold�жϸ���ʧ�ܵ���ֵ������g_ofpyrThreshold���ж�Ϊ����ʧ��,��G�����С������ֵ���бȽ�
		xtofCalcPyrlk(imgPyrPost, imgPyrPrev, cornerPost, cornerPrev, cornerStatus, cornerErr, cornerTermcrit, g_ofpyrThreshold, maxLevelNum);

		/*�ɹ����ٽǵ���ȡ*///����ǵ�֮��λ�ƹ��󣬿��ж�Ϊ����ʧ��
		for (int cornerNum = 0; cornerNum < cornerStatus.size(); cornerNum++)
		{
			if ((cornerStatus[cornerNum]) || (cornerErr[cornerNum] > 40))
			{
				cornerPrevC.push_back(cornerPrev[cornerNum]);
				cornerPostC.push_back(cornerPost[cornerNum]);
				cornerPostMask.push_back(cornerPrev[cornerNum]);//prev�Ľǵ�����һѭ������ͼ����,��Ҫ�жϽǵ�֮��ľ���������
			}
		}

		affineInlier.create(1,cornerPrevC.size(),CV_8U);
		affineInlier.setTo(1);

		if (cornerPrevC.size() > 4)
		{
			/*����任������ȡ*/
			if (xtofAffine2D(cornerPrevC, cornerPostC, affine2D, affineInlier, g_ofAffineThreshold, g_ofAffineQuality))
			{
				if ((affine2D.at<double>(0, 0) < -2) || (affine2D.at<double>(0, 0) > 2)
					|| (affine2D.at<double>(1, 1) < -2) || (affine2D.at<double>(1, 1) > 2)
					|| (affine2D.at<double>(0, 1) < -1) || (affine2D.at<double>(0, 1) > 1)
					|| (affine2D.at<double>(1, 0) < -1) || (affine2D.at<double>(1, 0) > 1))
				{
					affine2D.setTo(0);
				}

				/*����ʵ��λ��*/
				//����һ
				g_cameraShiftX = (float)(affine2D.at<double>(0, 2) / CAMERA_FOCAL_X * g_cameraHeight / IMG_SCALE);
				g_cameraShiftY = (float)(affine2D.at<double>(1, 2) / CAMERA_FOCAL_Y * g_cameraHeight / IMG_SCALE);
				//distanceSumX += distanceX;
				//distanceSumY += distanceY;
				//������
				//�����ӳ��ǡ��߶���Ϣ����д
				//λ���˲�
			}
		}
	}
	swap(imgPyrPost, imgPyrPrev);
	swap(imgPost, imgPrev);

	//debugDrawCurve(g_cameraShiftX, g_cameraShiftY);
#ifdef DEBUG
	static int imgNum{ 0 };//ͼ�����

	++imgNum;//ͼ�����

	printf("%d\t%f\t%f\n", imgNum, g_cameraShiftX, g_cameraShiftY);
	debugDrawCurve(g_cameraShiftX, g_cameraShiftY);
	cout << imgNum << "\t" << cornerPostC.size() << '\t';

	cout.precision(4);
	cout.setf(ios::fixed);//С�����ȷ��λ
	//cout << tSum / (cvGetTickFrequency() * 1000 << endl;
	cout << affine2D.at<double>(0, 0) << '\t' << affine2D.at<double>(0, 1) << '\t' << g_cameraShiftX << '\t'
		<< affine2D.at<double>(1, 0) << "\t" << affine2D.at<double>(1, 1) << "\t" << g_cameraShiftY << "\t";

	cameraShiftSumX += g_cameraShiftX;
	cameraShiftSumY += g_cameraShiftY;
	
	//�Ȱ����ݸ��Ƴ���,���⻭����ĵ�Ӱ��������
	Mat imgPostTmp;
	imgPost.copyTo(imgPostTmp);
	for (int i = 0; i < cornerPostC.size(); i++)
	{
		if (1 == affineInlier.at<unsigned char>(i))
		{
			circle(imgPrev, cornerPostC[i], 1, Scalar(255, 0, 0), -1, 8);//��Ϊswap����imgpPrevʵΪpost
			circle(imgPostTmp, cornerPrevC[i], 1, Scalar(255, 0, 0), -1, 8);//��Ϊswap����imgPostʵΪPrev
		}
		else
		{
			circle(imgPrev, cornerPostC[i], 2, Scalar(255, 0, 0), -1, 8);//��Ϊswap����imgpPrevʵΪpost
			circle(imgPostTmp, cornerPrevC[i], 2, Scalar(255, 0, 0), -1, 8);//��Ϊswap����imgPostʵΪPrev
		}
	}
	//����ʱ����ͼƬ
	char str1[30], str2[30];
	if ((g_cameraShiftY < -20) || (g_cameraShiftY > 20) 
		|| (g_cameraShiftX < -20) || (g_cameraShiftX > 20))
	{
		sprintf_s(str1, "img\\img_%d_Post.bmp", imgNum);
		cv::imwrite(str1, imgPrev);
		sprintf_s(str2, "img\\img_%d_Prev.bmp", imgNum);
		cv::imwrite(str2, imgPostTmp);
	}

	cv::imshow("camera",imgPrev);
#else
	printf("%f\t%f\t", g_cameraShiftX, g_cameraShiftY);
#endif
	return 1;
}

#define DEBUGARRAYLENGTH 201

void debugDrawCurve(float x, float y)
{
	Size winSize(700, 400);
	Mat im = Mat::zeros(winSize, CV_8UC3);
	
	
	static int imX[DEBUGARRAYLENGTH];
	static int imY[DEBUGARRAYLENGTH];

	int arrayLength = DEBUGARRAYLENGTH - 1;
	int max = 150, min = -150;

	x *= 10;//�Ŵ�10��
	y *= 10;
	if (x > max) x = max;
	if (x < min) x = min;
	if (y > max) y = max;
	if (y < min) y = min;

	imX[arrayLength] = (int)(x + winSize.height / 2);
	imY[arrayLength] = (int)(y + winSize.height / 2);//����ƽ��100

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
	imshow("curve", im);
}
