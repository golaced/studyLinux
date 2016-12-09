#ifndef _DEBUG_H_
#define _DEBUG_H_

#include "opencv2/opencv.hpp"
using namespace cv;

#ifdef __arm__//gcc预设的宏定义
    #define  DEBIAN
#endif

#define NRF_DEVICE "/dev/ttyUSB1"
#define NRF_BAUDRATE 9600

int usbNrfInit();
int nrfSend(float x, float y);
int saveVideoInit();
int saveVideo(Mat &im);
int closeSaveVideo();

void xmlClose();
void xmlInit(void);
int saveXmlData(float x, float y);


#endif