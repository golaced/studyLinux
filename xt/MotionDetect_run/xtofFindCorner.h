#ifndef _XTOFFINDCORNER_H_
#define _XTOFFINDCORNER_H_

#include <opencv2/opencv.hpp>

int xtofCornerToTrack(cv::InputArray _image, cv::OutputArray _corners, cv::InputArray _mask, int blockSize);

#endif
