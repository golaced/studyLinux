#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <opencv2/opencv.hpp>
#include "camerathread.h"
Mat imSrc;

void *thread_function(void *arg);

int camera_thread()
{
	pthread_t id;
	int res;

	res = pthread_create(&id,NULL,thread_function,NULL);

}

void *thread_function(void *arg)
{
	VideoCapture cap(0);

	if(!cap.isOpened())
	{
		printf("can not open camera\n");
//		pthread_exit("can not open camera\n");
	}

	double timeT;
	while(1)
	{
		timeT = (double)getTickCount();

		cap >> imSrc;

		printf("camera time %f\n", ((double)getTickCount() - timeT) / getTickFrequency() * 1000);
	}
}
