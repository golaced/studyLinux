#include <stdio.h>
#include "testcv.h"
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
void quick_sort(int s[], int l, int r);

int main(int argc, char *argv[])
{
	int flg = 8;

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
	case 7:
		{
			myVideo firstone;
			string name = "tmp.avi";

			if(argc == 2)
			{
				name = argv[1];
			}
			firstone.openVideo(name);
			firstone.controlVideo();
			break;
		}
	case 8:
		{
			int data[5] = {5, 6, 3, 2, 7};
			quick_sort(data, 0, 4);
			for(int i = 0; i < 5 ;i++)
				printf("%d\n", data[i]);
			break;
		}
	default:
		printf("arg is not right\n");
		break;
	}	
	waitKey(0);
	return 0;
}
/*
快速排序
l:数组最小下标,
r：数组最大下标
*/
void quick_sort(int s[], int l, int r)
{
    if (l < r)
    {
		//Swap(s[l], s[(l + r) / 2]); //将中间的这个数和第一个数交换 参见注1
        int i = l, j = r, x = s[l];
        while (i < j)
        {
            while(i < j && s[j] >= x) // 从右向左找第一个小于x的数
				j--;  
            if(i < j) 
				s[i++] = s[j];
			
            while(i < j && s[i] < x) // 从左向右找第一个大于等于x的数
				i++;  
            if(i < j) 
				s[j--] = s[i];
        }
        s[i] = x;
        quick_sort(s, l, i - 1); // 递归调用 
        quick_sort(s, i + 1, r);
    }
}

void myVideo::openVideo(string name)
{
    string path("/home/lxg-/video/");
    
    videoName = name;
    cap.open(path + name);
    if(!cap.isOpened())
    {
        printf("cano not open video\n");
        exit(0);
    }
}

void myVideo::controlVideo()
{
	char key = 0;
	int count = 0;
	int flg = 9000;

	while(1)
	{
		if(flg > 0)
		{
			cap >> im;
			if(im.empty())
			{
				exit(0);
			}
			printf("count:%d\n", count);
			count ++;
			imshow(videoName, im);
			flg --;
		}
		key = waitKey(33);
		switch(key)
		{
		case 's':
			flg = 0;
			break;
		case 'a':
			count -= 2;
			cap.set(CV_CAP_PROP_POS_FRAMES, count);
			flg = 1;
			break;
		case 'd':
			flg = 1;
			break;
		case 'w':
			flg = 9000;
			break;
		case 0x1b:
			exit(0);
		default :
			break;
		}
	}
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
