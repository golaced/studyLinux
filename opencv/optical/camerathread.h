#ifndef _CAMERATHREAD_H_
#define _CAMERATHREAD_H_

#include <semaphore.h>
#include <opencv2/opencv.hpp>


using namespace cv;

int camera_thread();
extern Mat imSrc;
extern sem_t bin_sem;
extern pthread_mutex_t bin_mut;
extern int cameraNum;
#endif
