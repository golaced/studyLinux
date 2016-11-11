#ifndef _XTOF_CAMERACORRECT_H_
#define _XTOF_CAMERACORRECT_H_

#include <opencv2/opencv.hpp>

void xtofCameraCorrect(cv::Size imSrcSize, cv::Mat &mapxMat, cv::Mat &mapyMat);
void readRotation();

#endif
