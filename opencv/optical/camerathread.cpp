#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <opencv2/opencv.hpp>
#include "camerathread.h"

Mat imSrc;
sem_t bin_sem;
pthread_mutex_t bin_mut;
int cameraNum = 0;

void *thread_function(void *arg);

int camera_thread()
{
	pthread_t id;
	int res;

	res = pthread_create(&id,NULL,thread_function,NULL);
	if(res != 0)
	{
		printf("thread create fail\n");
	}
	/*res = sem_init(&bin_sem,0,0);
	if(res != 0)
	{
		printf("semaphore init fail\n");
	}*/
	
	res = pthread_mutex_init(&bin_mut,NULL);
	if(res != 0)
	{
		printf("mutex init fail\n");
	}
}

void *thread_function(void *arg)
{
	VideoCapture cap(0);

	if(!cap.isOpened())
	{
		printf("can not open camera\n");
//		pthread_exit("can not open camera\n");
	}

	Mat imTmp;
	double timeT;

	while(1)
	{
		timeT = (double)getTickCount();

//		cap >> imSrc;
		cap >> imTmp;
		
		//pthread_mutex_lock(&bin_mut);
		imTmp.copyTo(imSrc);
		cameraNum++;
		//pthread_mutex_unlock(&bin_mut);
//		sem_post(&bin_sem);

		printf("camera time:%f\n", ((double)getTickCount() - timeT) / getTickFrequency() * 1000);
	}
}
