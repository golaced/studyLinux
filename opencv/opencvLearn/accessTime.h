#ifndef _ACCESSTIME_H_
#define _ACCESSTIME_H_

#include "opencv2/opencv.hpp"

using namespace cv;

struct item{
    string name;
    int num;
};

int scanTime(Mat im);
int structInit();

#endif