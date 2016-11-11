#include <opencv2/opencv.hpp>
#include <stdio.h>
#include "camerathread.h"

//#define USE_THREAD

using namespace cv;
int main()
{
#ifndef USE_THREAD
	VideoCapture cap;

	cap.open(0);
	if(!cap.isOpened())
	{
		printf("can not open cap\n");
		return -1;
	}
#else
	camera_thread();
#endif

	Mat imDst;
	char c = 0;
	double cameraTime;
	Size imsize(50,50);

	while(1)
	{
		cameraTime = (double)getTickCount();
#ifndef USE_THREAD
		cap >> imSrc;
#endif
		printf("time:%f\nms", ((double)getTickCount() - cameraTime) / getTickFrequency() * 1000);
  		
		if(!imSrc.empty())
		{
			resize(imSrc,imDst,imsize);
			imshow("camera",imDst);
		}

		c = waitKey(1);
		if(c == 's')
		{
			break;
		}
	}

	return 0;
}
