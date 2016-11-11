#include <opencv2/opencv.hpp>
#include "xtofCameraCorrect.h"
#include "xtofglobal.h"
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

float g_roll, g_pitch, g_yaw;
float g_gestureArray[3][200];

/****************************************************************************************
* File: xtofCameraCorrect.cpp
* Name: xtofCameraCorrect
* Input:    
* Output:
* Function:  
* Date: 2016/07/13 21:06
*****************************************************************************************/
void xtofCameraCorrect(Size imSrcSize, Mat &mapxMat, Mat &mapyMat)
{
	//内矩阵
	double m[3][3] = { { CAMERA_FOCAL_X, 0, CAMERA_PRINCIPLE_X }, { 0, CAMERA_FOCAL_Y, CAMERA_PRINCIPLE_Y }, { 0, 0, 1 } };
	Mat cameraMatrix(3, 3, CV_64F, m);
	CvMat mCv = cameraMatrix;
	//外矩阵
	double n[4] = { FACTOR_DISTORTION1, FACTOR_DISTORTION2, FACTOR_DISTORTION3, FACTOR_DISTORTION4 };//畸变系数

	Mat distCoeff(1, 4, CV_64F, n);
	CvMat nCv = distCoeff;

	IplImage *mapx = cvCreateImage(imSrcSize, IPL_DEPTH_32F, 1);
	IplImage *mapy = cvCreateImage(imSrcSize, IPL_DEPTH_32F, 1);

	cvInitUndistortMap(&mCv, &nCv, mapx, mapy);
	mapxMat = cvarrToMat(mapx);
	mapyMat = cvarrToMat(mapy);
}


/****************************************************************************************
* File: xtofCameraCorrect.cpp
* Name: xtofCameraRotation
* Input:    
* Output:
* Function:  
* Date: 2016/07/13 21:40
*****************************************************************************************/
void xtofCameraRotation(Size srcSize, Mat src, Mat &dest)
{
	double f = 500, dist = 500;//焦距和高度？两者一样大就可以避免缩放
	double alpha = 90, beta = 90, gamma = 90;

	alpha = ((double)alpha - 90)*PI / 180;
	beta = ((double)beta - 90)*PI / 180;
	gamma = ((double)gamma - 90)*PI / 180;

	double w = srcSize.width, h = srcSize.height;
	//projection 2D->3D matrix???
	Mat A1 = (Mat_<double>(4, 3) <<
		1, 0, -w / 2,
		0, 1, -h / 2,
		0, 0, 1);
	//Rotation matrix
	Mat RX = (Mat_<double>(4, 4) <<
		1, 0, 0, 0,
		0, cos(alpha), -sin(alpha), 0,
		0, sin(alpha), cos(alpha), 0,
		0, 0, 0, 1);
	Mat RY = (Mat_<double>(4, 4) << 
		cos(beta), 0, -sin(beta), 0,
		0, 1, 0, 0,
		sin(beta), 0, cos(beta), 0,
		0, 0, 0, 1);
	Mat RZ = (Mat_<double>(4, 4) <<
		cos(gamma), -sin(gamma), 0, 0,
		sin(gamma), cos(gamma), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);

	// Composed rotation matrix with (RX,RY,RZ)
	Mat R = RX * RY * RZ;

	// Translation matrix on the Z axis change dist will change the height//why is translation
	Mat T = (Mat_<double>(4, 4) <<
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, dist,
		0, 0, 0, 1);

	// Camera Intrisecs matrix 3D -> 2D
	Mat A2 = (Mat_<double>(3, 4) <<
		f, 0, w / 2, 0,
		0, f, h / 2, 0,
		0, 0, 1, 0);

	// Final and overall transformation matrix
	Mat transfo = A2 * (T * (R * A1));

	// Apply matrix transformation
	warpPerspective(src, dest, transfo, srcSize, INTER_LINEAR | WARP_INVERSE_MAP);//why is inverse transformation
	//cvPerspectiveTransform()
}



/****************************************************************************************
* File: xtofCameraCorrect.cpp
* Name: 
* Input:    
* Output:
* Function:read txt along its video  
* Date: 2016/07/25 15:54
*****************************************************************************************/
void readRotation()
{
	FILE* fp;
        char* line = NULL;
	size_t len = 0;
	ssize_t read = 0;
	int i = 0;
	char str[256];
	
	fp = fopen("/simtoo/video3.txt","r");
	if (fp == NULL)
	{
		printf("*.txt is not opened\n");
		return;
	}
	
	while ((read = getline(&line, &len, fp)) != -1)
	{
		sscanf(str, "ROLL: %f PITCH: %f YAW: %f", &g_gestureArray[0][i], &g_gestureArray[1][i], &g_gestureArray[2][i]);
		++i;
	}
}
