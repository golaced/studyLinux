#ifndef _TESTCV_H_
#define _TESTCV_H_

#include <opencv2/opencv.hpp>
using namespace cv;

class myVideo
{
    public:
    
    VideoCapture cap;
    Mat im;
    string videoName;

    void openVideo(string name);
    void controlVideo();

};

#endif