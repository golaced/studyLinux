#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;
int imshowTest();
int videoTest();
int preprocessIm(Mat &srcIm, int delta);
int readIm(Mat &im);
int ranColor();
int writeVideo();
int showVideo();


int main(int argc, char *argv[])
{
	int flg = 6;

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
		preprocessIm(im, 1);
		imshow("binary1", im);

		readIm(im);
		preprocessIm(im, 2);
		imshow("binary2", im);

		readIm(im);
		preprocessIm(im, 3);
		imshow("binary3", im);
		
		readIm(im);
		preprocessIm(im, 4);
		imshow("binary4", im);

		readIm(im);
		preprocessIm(im, 5);
		imshow("binary5", im);
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
	case 6://显示两段视频
		showVideo();
		break;
	default:
		printf("arg is not right\n");
		break;
	}	
	waitKey(0);
	return 0;
}
int showVideo()
{
	Mat imo;
	VideoCapture capo;
	capo.open("/home/lxg-/video/tmp_o.avi");
	//cap.open("test.avi");
	if(!capo.isOpened())
	{
		printf("can not open tmp_o\n");
		return -1;
	}
	namedWindow("tmp_o");
	moveWindow("tmp_o", 20,15);

	Mat imb;
	VideoCapture capb;
	capb.open("/home/lxg-/video/tmp_b.avi");
	if(!capb.isOpened())
	{
		printf("can not open tmp_b\n");
		return -1;
	}
	namedWindow("tmp_b");
	moveWindow("tmp_b", 350, 15);

	char c;
	while(1)
	{
		capo >> imo;
		if(imo.empty())
		{
			printf("tmp_o end\n");
			break;
		}
		
		imshow("tmp_o", imo);

		capb >> imb;
		if(imb.empty())
		{
			printf("tmp_b end\n");
			break;
		}
		
		imshow("tmp_b", imb);
		c = waitKey(40);
		if(c == 's')
		{
			waitKey(0);
		}
	}
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
	im = imread("/home/lxg-/video/leina.jpg");
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

int preprocessIm(Mat &srcIm, int delta)
{
	int cols = srcIm.cols;
	int rows = srcIm.rows;
	uchar *p = NULL;

	for(int i = 0; i < rows; i++)
	{
		p = srcIm.ptr<uchar>(i);
		for(int j = 0; j < cols - delta; ++j)
		{
			if(*p > *(p + delta))
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
