#ifndef _XTOFFINDCORNER_H_
#define _XTOFFINDCORNER_H_

#include <opencv2/opencv.hpp>
using namespace cv;

int xtofCornerToTrack(cv::InputArray _image, cv::OutputArray _corners, cv::InputArray _mask, int blockSize);
void xtofMaskCreate(Mat &im, vector<Point2f> seed);
void setCorner(vector<Point2f> &src);

#endif