#include "accessTime.h"
#include <iostream>
#include <stdio.h>

using namespace std;

int dataMat(Mat c, uchar x);
int ptrMat(Mat c, uchar x);
int ptrMatArray(Mat c, uchar x);
int lookuptableMat(Mat im, uchar x);
int iteraterMat(Mat c, uchar x);
int atMat(Mat im, uchar x);

item matItem[10];

int structInit()
{
	matItem[0].name = "dataMat";
	matItem[1].name = "ptr_and_*++";
	matItem[2].name = "iteraterMat";
	matItem[3].name = "lookuptableMat";
	matItem[4].name = "atMat";
	matItem[5].name = "ptr_and_[]";
}
//Mat类形参传递默认是引用类型的吗？
int scanTime(Mat img)
{
	uchar x = 0;
	int flg = 0;

	for(int flg = 0; flg < 5; flg++)
	{
		Mat im = img.clone();
		double t = (double)getTickCount();

		for (int i = 0; i < 10; i++)
		{
			switch (flg)
			{
			case 0:
				dataMat(im, x);
				break;
			case 1://最快
				ptrMat(im, x);
				break;
			case 2:
				iteraterMat(im, x);
				break;
			case 3:
				lookuptableMat(im, x);
				break;
			case 4:
				atMat(im, x);
				break;
			case 5:
				ptrMatArray(im, x);
				break;
			default:
				break;
			}
		}

		char str[10];
		sprintf(str, "%d_", flg);
		string strC = str;
		imshow(strC + matItem[flg].name, im);
		cout <<"flg:" << flg << "\ttime:" << ((double)getTickCount() - t) / getTickFrequency() * 1000 
			<< "ms" << "\tusing "<< matItem[flg].name << endl;
	}
	return 1;
}

//Mat类的
//Mat类的data成员访问
int dataMat(Mat c, uchar x)
{
	int cols = c.cols;
	int channel = c.channels();
	int rows = c.rows;
	uchar *p;

	cols = cols * channel;
	p = c.data;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			p[i * rows * 3 + j] = x;//还要乘以3才是行首地址
		}
	}
	return 1;
}

//用ptr和指针对Mat数据进行遍历,
int ptrMat(Mat c, uchar x)
{
	int cols = c.cols;
	int channel = c.channels();
	int rows = c.rows;
	uchar *p;

	cols = cols * channel;

	for (int i = 0; i < rows; ++i)
	{
		p = c.ptr<uchar>(i);//乘以三已经计算在内
		for (int j = 0; j < cols; ++j)
		{
			*p = x;
			++p;
		}
	}
	return 1;
}
//用ptr和数组访问方式，对Mat数据进行遍历,
int ptrMatArray(Mat c, uchar x)
{
	int cols = c.cols;
	int channel = c.channels();
	int rows = c.rows;
	uchar *p;

	cols = cols * channel;

	for (int i = 0; i < rows; ++i)
	{
		p = c.ptr<uchar>(i);//乘以三已经计算在内
		for (int j = 0; j < cols; ++j)
		{
			p[j] = x;
		}
	}
	return 1;
}
//用迭代器对Mat元素进行遍历
int iteraterMat(Mat c, uchar x)
{
	int channel = c.channels();

	MatIterator_<Vec4b> it;
	for (it = c.begin<Vec4b>(); it != c.end<Vec4b>(); ++it)
	{
		for (int i = 0; i < channel; ++i)
		{
			(*it)[i] = x;
		}
	}
	return 1;
}
//查找表的方法
int lookuptableMat(Mat im, uchar x)
{
	Mat lookUpTable(1, 256, CV_8U);
	uchar *pt = lookUpTable.data;

	for (int i = 0; i < 256; ++i)
	{
		pt[i] = i;
	}
	Mat I = (Mat_<int>(3, 3) << 1, 2, 3, 4, 5, 6, 7, 8, 9);
	Mat J(3, 3, CV_8U);

	return 1;
}

//at成员函数访问
int atMat(Mat im, uchar x)
{
	int cols = im.cols;
	int rows = im.rows;
	int channels = im.channels();

	cols = cols * channels;

	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < cols; j++)
		{
			im.at<uchar>(i,j) = x;
		}
	}
}