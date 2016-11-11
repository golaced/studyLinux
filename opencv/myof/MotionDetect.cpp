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

#include "mavlink/common/mavlink.h"
#include "xtofmavlinktest.h"

extern "C"
{
	#include "xtofReadSonar.h"
};
using namespace cv;

//#define  DEBIAN

int maxLevelNum = 1;//��������������0��ʼ
float g_ofpyrThreshold = 0.001f;//������������У�G�����С����ֵ�Ƚ�
double g_ofAffineThreshold = 2.;//���԰�һ���㿴���ڵ��������
double g_ofAffineQuality = 0.96;//����任���Ŷȣ�������������

float g_cameraHeight = 0.0f; //��λcm
float g_cameraShiftX = 0.0f;
float g_cameraShiftY = 0.0f;
float cameraShiftSumX = 0.0f, cameraShiftSumY = 0.0f;
double sumTime;

struct global_struct global_data;

int xtofOpticalFlow(Mat &imgPrev);
void debugDrawCurve(float x, float y);
void globalDataInit();

int main(void)
{
	globalDataInit();
	//string videoName{ "D:\\2016\\��ͼ\\��Ƶ\\�в��ĶԵ���Ƶ\\2881307025.h264" };
	//string videoName{ "D:\\2016\\��ͼ\\��Ƶ\\�������Ե�����20160824\\�Ե�\\544305398.h264" };
	//string videoName{ "D:\\2016\\��ͼ\\��Ƶ\\�в�������Ƶ20160816\\3114994239.h264" };
	string videoName;
	//VideoCapture cap(videoName);
	VideoCapture cap(0);

	if (!cap.isOpened()) 
	{
		printf("can not open cap!\n");
		return 0;
	}

	//�����㷨��ʼ�����֣���һ֡ͼƬ�Ļ�ȡ
	Mat frame, image;
	cap >> frame;
	if (frame.empty()) return -1;
	global_data.img.leftupX = (frame.cols - IMG_SELECT_AREA) / 2;
	global_data.img.leftupY = (frame.rows - IMG_SELECT_AREA) / 2;

	if(global_data.param[PARAM_SEND_OPTICAL_MAVLINK] || global_data.param[PARAM_SEND_VIDEO_MAVLINK])
	{
		printf("mavlink example program running\n");
		//mavlink_example();
		mavlinkNetInit();
		printf("mavlink example program finish\n");
	}

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
		printf("cameratime%3.2f\t", ((double)getTickCount() - funTime) / getTickFrequency() * 1000);
		if (frame.empty()||(cKey == 's'))
		{
			break;
		}
		frame = frame(Rect(global_data.img.leftupX, global_data.img.leftupY, IMG_SELECT_AREA, IMG_SELECT_AREA));
		cvtColor(frame, frame, COLOR_BGR2GRAY);
		resize(frame, image, Size(), IMG_SCALE, IMG_SCALE);
		//remap(image, image, cameraMapX, cameraMapY, INTER_LINEAR);//ͼ��������������,�˷�ʱ��

		double localTime = (double)getTickCount();
		xtofOpticalFlow(image);
		//printf("cameratime%3.2f\t", ((double)getTickCount() - funTime) / getTickFrequency() * 1000);

		funTime = ((double)getTickCount() - funTime) / getTickFrequency() * 1000;
		printf("funtime%3.2f\t", funTime);
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
	// cornerPost.clear();
	// for (int i = 0; i < 6; i++)
	// {
	// 	for (int j = 0; j < 6; j++)
	// 		cornerPost.push_back(Point(j * 16 + 9, i * 16 + 9));
	// }
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
	if(global_data.param[PARAM_SEND_OPTICAL_MAVLINK])
	{
		mavlink_msg_heartbeat_send(MAVLINK_COMM_0, MAV_TYPE_HELICOPTER, MAV_AUTOPILOT_GENERIC, 
			MAV_MODE_GUIDED_ARMED, 0, MAV_STATE_ACTIVE);
		mavlink_msg_optical_flow_send(MAVLINK_COMM_0, microsSinceEpoch(), global_data.param[PARAM_SENSOR_ID],
			(int16_t)(g_cameraShiftX * 100), (int16_t)(g_cameraShiftY * 100), 0, 0, 0, 100);
		printf("send optical\n");
	}
	if(global_data.param[PARAM_SEND_VIDEO_MAVLINK])
	{
		printf("send video\n");
		uint16_t image_size_send;

		image_size_send = global_data.img.width * global_data.img.height;//100*100;//image_size;
		mavlink_msg_data_transmission_handshake_send(
			MAVLINK_COMM_0,
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
			mavlink_msg_encapsulated_data_send(MAVLINK_COMM_0, frame, 
				&((uint8_t *) imgPrev.data)[frame * MAVLINK_MSG_ENCAPSULATED_DATA_FIELD_DATA_LEN]);
		}
	}
#ifndef DEBIAN
	//debugDrawCurve(g_cameraShiftX,g_cameraShiftY);
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
	cv::imshow("camera1",imgPrev);
	cv::imshow("camera2",imgPostTmp);
#endif
	
#ifdef DEBUG
	static int imgNum{ 0 };//ͼ�����

	++imgNum;//ͼ�����

	printf("%d\t%1.3f\t%1.3f\t", imgNum, g_cameraShiftX, g_cameraShiftY);
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
	//����ʱ����ͼƬ
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
	printf("%1.4f    %1.4f    \n", g_cameraShiftX, g_cameraShiftY);
#endif
	return 1;
}

void globalDataInit()
{
	mavlink_system.sysid = 1;
	mavlink_system.compid = 200;

	global_data.param[PARAM_SEND_OPTICAL_MAVLINK] = TRUE;
	global_data.param[PARAM_SENSOR_ID] = 200;
	global_data.param[PARAM_SEND_VIDEO_MAVLINK] = FALSE;

	global_data.img.width =  IMG_SELECT_AREA * IMG_SCALE;
	global_data.img.height =  IMG_SELECT_AREA * IMG_SCALE;
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
