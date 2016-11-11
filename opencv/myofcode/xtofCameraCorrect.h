#ifndef _XTOF_CAMERACORRECT_H_
#define _XTOF_CAMERACORRECT_H_

#include "opencv2/opencv.hpp"
using namespace cv;

void xtofCameraCorrect(cv::Size imSrcSize, cv::Mat &mapxMat, cv::Mat &mapyMat);
void readRotation();
int preprocessImISC(Mat &srcIm);
Scalar randomColor(RNG &rng);

#endif