#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
	Mat im =imread("test.bmp");
	imshow("win",im);
}
