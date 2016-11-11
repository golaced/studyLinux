#include <opencv2/opencv.hpp>
#include <stdio.h>

using namespace cv;
int main()
{
	VideoCapture cap;

	cap.open(-1);
	if(!cap.isOpened())
	{
		printf("can not open cap\n");
		return -1;
	}

	Mat imDst;
	char c = 0;
	double cameraTime;

	while(1)
	{
		cameraTime = (double)getTickCount();
		cap >> imDst;
		printf("time:%f\n", ((double)getTickCount() - cameraTime) / getTickFrequency() * 1000);
  		
		imshow("camera",imDst);

		c = waitKey(1);
		if(c == 's')
		{
			break;
		}
	}

	return 0;
}
