#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;
int imshowTest();
int videoTest();
int preprocessIm(Mat &srcIm);
int readIm(Mat &im);
int ranColor();
int writeVideo();

int main(int argc, char *argv[])
{
	int flg = 1;

	if(argc > 1)
	{
		sscanf(argv[1], "%d", &flg);
	}
	printf("welcome to opencv\n");


	switch (flg)
	{
	case 1:
		imshowTest();
		break;
	case 2://读视频
		videoTest();
		break;
	case 3://图像预处理
	{
		Mat im;

		readIm(im);
		preprocessIm(im);
		imshow("binary", im);

		break;
	}
	case 4://随机颜色
	{
		ranColor();
		break;
	}
	case 5://写视频
		writeVideo();
		break;
	default:
		printf("arg is not right\n");
		break;
	}	
	waitKey(0);
	return 0;
}

int writeVideo()
{
	VideoCapture cap;

	cap.open(0);
	if(!cap.isOpened())
	{
		printf("can not open cap\n");
		return -1;
	}

	Mat im;
	cap >> im;
	VideoWriter video;
	int codec = CV_FOURCC('M','J','P','G');
	video.open("test.avi", codec, 25, im.size(), 1);
	if(!video.isOpened())
	{
		printf("video can not open\n");
		return -1;
	}
	while(1)
	{
		cap >> im;
		imshow("srcIm",im);

		video << im;
		char c = waitKey(1);
		if(c == 's')
		{
			break;
		}
	}
	cap.release();
	video.release();
}
int ranColor()
{
	RNG rng(0xffffffff);

	int icolor = (unsigned)rng;
	Scalar color(icolor & 0xff, (icolor >> 8) & 0xff, (icolor >> 16) & 0xff);
	int a = 0;
}
int readIm(Mat &im)
{
	im = imread("/home/lxg-/code/video/test.jpg");
	if(im.data == NULL) 
	{
		printf("can not open test.jpg\n");
		return -1;
	}
	if(im.type() == CV_8UC3)//不是灰度转灰度
	{
		cvtColor(im, im, CV_BGR2GRAY);
	}
	if(!im.isContinuous())
	{
		printf("im is not continuous\n");
		return -1;
	}
	imshow("read_img",im);
	printf("can imshow\n");
}

int preprocessIm(Mat &srcIm)
{
	int cols = srcIm.cols;
	int rows = srcIm.rows;
	uchar *p = NULL;

	for(int i = 0; i < rows; i++)
	{
		p = srcIm.ptr<uchar>(i);
		for(int j = 0; j < cols - 1; ++j)
		{
			if(*p > *(p+1))
			{
				*p |= 0xff;
			}
			else
			{
				*p &= 0;
			}
			++p;
		}
	}
}


int imshowTest()
{
	Mat im;
	im = imread("/home/lxg-/code/video/test.jpg");
	if(im.data == NULL) 
	{
		printf("can not open test.jpg\n");
		return -1;
	}
	imshow("linux-img",im);
	printf("can imshow\n");
}
int videoTest()
{
	Mat im;
	VideoCapture cap;
	cap.open("/home/lxg-/code/video/video.avi");
	//cap.open("test.avi");
	if(!cap.isOpened())
	{
		printf("can not open video\n");
		return -1;
	}
	int fps = cap.get(CV_CAP_PROP_FPS);
	int fourcc = cap.get(CV_CAP_PROP_FOURCC);
	printf("fps:%d", fps);
	printf("fourcc:%d", fourcc);

	while(1)
	{
		cap >> im;
		if(im.empty())
		{
			printf("video end >>\n");
			break;
		}
		imshow("video", im);
		waitKey(1);
	}
}
