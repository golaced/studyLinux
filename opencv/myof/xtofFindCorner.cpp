#include "xtofFindCorner.h"
#include "xtofglobal.h"

#include <iostream>
using namespace std;
using namespace cv;
#define CORNER_QUALITY			0.001	//角点置信度，与最大值的乘积作为寻找符合角点特征值大小的阈值
#define MIN_CORNER_DISTANCE		10		//角点之间的最小分布距离

#define MINEIGENVAL				0		//最小的特征值



static void mycornerEigenValsVecs(const Mat &mask, const Mat& src, Mat& eigenv, int block_size,
	int aperture_size, int op_type, double k );

static void mycalcMinEigenVal(const Mat& _cov, Mat& _dst, const Mat &mask);
void mycornerMinEigenVal(InputArray _mask, InputArray _src, OutputArray _dst, int blockSize, int ksize, int borderType = BORDER_DEFAULT);
void cornerBlockGet(Mat &eig, Size imgsize, Mat mask, vector<const float *> &tmpCorners);

template<typename T> struct greaterThanPtr
{
	bool operator()(const T* a, const T* b) const { return *a > *b; }
};

/****************************************************************************************
* File: findCorner.cpp
* Name: xtofCornerToTrack
* Input: _mask 屏蔽检测的位置 blockSize 梯度检测核大小定义   
* Output:
* Function:  
* Date: 2016/07/03 21:06
*****************************************************************************************/
int xtofCornerToTrack(cv::InputArray _image, cv::OutputArray _corners, cv::InputArray _mask, int blockSize)
{
	Mat image = _image.getMat(), mask = _mask.getMat();

	
	//CV_Assert(qualityLevel > 0 && minDistance >= 0 && maxCorners >= 0);
	CV_Assert(mask.empty() || (mask.type() == CV_8UC1 && mask.size() == image.size()));

	Mat eig, tmp;

	mycornerMinEigenVal(mask, image, eig, blockSize, 3);//blockSize寻找角点时计算的, kSize = 3只是作为Sobel梯度的核大小
	
	vector<const float *> tmpCorners;
#ifdef USEBLOCK
	cornerBlockGet(eig, image.size(), mask, tmpCorners);

#else	
	double maxVal;
	
	
	cv::minMaxLoc(eig, 0, &maxVal, 0, 0, Mat());//计算最小，最大值，并返回最大值及位置,这里的mask只是用作屏蔽吗，没有使对应的eig=0
	cv::threshold(eig, eig, maxVal*CORNER_QUALITY, 0, THRESH_TOZERO);//可信度这么用的乘以最大值做固定阈值

	//使用形态学膨胀，姜还是老的辣，比较节省时间
	cv::dilate(eig, tmp, Mat());//形态学膨胀，膨胀就是求局部最大值的操作 第三个参数缺失时，使用默认的3*3核 0.7ms

	Size imgsize = image.size();


	// collect list of pointers to features - put them into temporary image
	for (int y = 1; y < imgsize.height - 1; y++)
	{
		const float* eig_data = (const float*)eig.ptr(y);//阈值操作后的特征值
		const float* tmp_data = (const float*)tmp.ptr(y);//形态学膨胀
		const uchar* mask_data = mask.data ? mask.ptr(y) : 0;

		for (int x = 1; x < imgsize.width - 1; x++)
		{
			float val = eig_data[x];
			if (val != 0 && val == tmp_data[x] && (mask_data && mask_data[x]))
				tmpCorners.push_back(eig_data + x);
		}
	}//使用形态学膨胀结束

	/*//不使用膨胀操作
	Size imgsize = image.size();
	// collect list of pointers to features - put them into temporary image
	for (int y = 1; y < imgsize.height - 1; y++)
	{
		const float* eig_data = (const float*)eig.ptr(y);//阈值操作后的特征值
		//const float* tmp_data = (const float*)tmp.ptr(y);//形态学膨胀
		const uchar* mask_data = mask.data ? mask.ptr(y) : 0;

		for (int x = 1; x < imgsize.width - 1; x++)
		{
			float val = eig_data[x];
			if (val != 0 && (!mask_data || mask_data[x]))
				tmpCorners.push_back(eig_data + x);
		}
	}//不使用膨胀操作结束*/
	
	cv::sort(tmpCorners, greaterThanPtr<float>());//对角点排序
#endif
	vector<Point2f> corners;
	size_t i, j, total = tmpCorners.size(), ncorners = 0;

	if (MIN_CORNER_DISTANCE >= 1)//根据距离原则，删除一部分角点
	{
		// Partition the image into larger grids
		int w = image.cols;
		int h = image.rows;

		const int cell_size = cvRound(MIN_CORNER_DISTANCE);
		const int grid_width = (w + cell_size - 1) / cell_size;
		const int grid_height = (h + cell_size - 1) / cell_size;

		std::vector<std::vector<Point2f> > grid(grid_width*grid_height);

		int minDistance = MIN_CORNER_DISTANCE;
		minDistance *= minDistance;

		for (i = 0; i < total; i++)
		{
			int ofs = (int)((const uchar*)tmpCorners[i] - eig.data);
			int y = (int)(ofs / eig.step);
			int x = (int)((ofs - y*eig.step) / sizeof(float));

			bool good = true;

			int x_cell = x / cell_size;
			int y_cell = y / cell_size;

			int x1 = x_cell - 1;
			int y1 = y_cell - 1;
			int x2 = x_cell + 1;
			int y2 = y_cell + 1;

			// boundary check
			x1 = std::max(0, x1);
			y1 = std::max(0, y1);
			x2 = std::min(grid_width - 1, x2);
			y2 = std::min(grid_height - 1, y2);

			for (int yy = y1; yy <= y2; yy++)
			{
				for (int xx = x1; xx <= x2; xx++)
				{
					vector <Point2f> &m = grid[yy*grid_width + xx];

					if (m.size())
					{
						for (j = 0; j < m.size(); j++)
						{
							float dx = x - m[j].x;
							float dy = y - m[j].y;

							if (dx*dx + dy*dy < minDistance)
							{
								good = false;
								goto break_out;
							}
						}
					}
				}
			}

			break_out:

			if (good)
			{
				// printf("%d: %d %d -> %d %d, %d, %d -- %d %d %d %d, %d %d, c=%d\n",
				//    i,x, y, x_cell, y_cell, (int)minDistance, cell_size,x1,y1,x2,y2, grid_width,grid_height,c);
				grid[y_cell*grid_width + x_cell].push_back(Point2f((float)x, (float)y));

				corners.push_back(Point2f((float)x, (float)y));
				++ncorners;

				if (MAX_CORNER_NUM > 0 && (int)ncorners == MAX_CORNER_NUM)
					break;
			}
		}
	}
	else
	{
		for (i = 0; i < total; i++)
		{
			int ofs = (int)((const uchar*)tmpCorners[i] - eig.data);
			int y = (int)(ofs / eig.step);
			int x = (int)((ofs - y*eig.step) / sizeof(float));

			corners.push_back(Point2f((float)x, (float)y));
			++ncorners;
			if (MAX_CORNER_NUM > 0 && (int)ncorners == MAX_CORNER_NUM)
				break;
		}
	}

	Mat(corners).convertTo(_corners, _corners.fixedType() ? _corners.type() : CV_32F);

	return 1;
	/*
	for( i = 0; i < total; i++ )
	{
	int ofs = (int)((const uchar*)tmpCorners[i] - eig.data);
	int y = (int)(ofs / eig.step);
	int x = (int)((ofs - y*eig.step)/sizeof(float));

	if( minDistance > 0 )
	{
	for( j = 0; j < ncorners; j++ )
	{
	float dx = x - corners[j].x;
	float dy = y - corners[j].y;
	if( dx*dx + dy*dy < minDistance )
	break;
	}
	if( j < ncorners )
	continue;
	}

	corners.push_back(Point2f((float)x, (float)y));
	++ncorners;
	if( maxCorners > 0 && (int)ncorners == maxCorners )
	break;
	}
	*/
}
/****************************************************************************************
* File: xtofFindCorner.cpp
* Name: 
* Input:    
* Output:
* Function:  
* Date: 2016/09/08 21:57
*****************************************************************************************/
void xtofMaskCreate(Mat &im, vector<Point2f> seed)
{
	int seedWin = 8;

	for (int k = 0; k < seed.size(); ++k)
	{
		int x, y;

		x = cvRound(seed[k].x);
		y = cvRound(seed[k].y);

		int xMin = x < seedWin ? 0 : x - seedWin;
		int yMin = y < seedWin ? 0 : y - seedWin;
		int xMax = x > (im.cols - seedWin) ? im.cols : x + seedWin;
		int yMax = y > (im.rows - seedWin) ? im.rows : y + seedWin;

		for (int i = yMin; i < yMax; ++i)
		{
			uchar *p = im.ptr<uchar>(i) +xMin;
			for (int j = xMin; j < xMax; ++j)
			{
				*p = 0;
				++p;
			}
		}
	}
}
/****************************************************************************************
* File: xtofFindCorner.cpp
* Name: cornerBlockGet
* Input:    
* Output:
* Function: 寻找角点时限制角点的分布
* Date: 2016/07/07 22:38
*****************************************************************************************/
void cornerBlockGet(Mat &img, Size imgsize, Mat mask, vector<const float *> &tmpCorners)
{
	double maxVal = 0;
	int cellSizeH = imgsize.height / 3; //图像结构块划分
	int cellSizeW = imgsize.width / 3;

	int imgH[4] = { 1, cellSizeH, 2 * cellSizeH, imgsize.height };
	int imgW[4] = { 1, cellSizeW, 2 * cellSizeW, imgsize.width };
	vector<vector<const float *> > corners;
	
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			vector<const float *> cornerTmp;

			Mat &eig = img.adjustROI(imgW[i], imgH[j], imgW[i + 1], imgH[j + 1]);

			cv::minMaxLoc(eig, 0, &maxVal, 0, 0, Mat());//计算最小，最大值，并返回最大值及位置
			cv::threshold(eig, eig, maxVal*CORNER_QUALITY, 0, THRESH_TOZERO);//可信度这么用的乘以最大值做固定阈值
			//imshow("eigen", eig);//
			Mat tmp;
			cv::dilate(eig, tmp, Mat());//形态学膨胀

			//imshow("tmp", tmp);//

			vector<const float*> tmpCorners;

			// collect list of pointers to features - put them into temporary image
			for (int y = imgH[j]; y < imgH[j + 1] - 1; y++)
			{
				const float* eig_data = (const float*)eig.ptr(y);//阈值操作后的特征值
				const float* tmp_data = (const float*)tmp.ptr(y);//形态学膨胀
				const uchar* mask_data = mask.data ? mask.ptr(y) : 0;

				for (int x = imgW[i]; x < imgW[i + 1] - 1; x++)
				{
					float val = eig_data[x];
					if (val != 0 && val == tmp_data[x] && (!mask_data || mask_data[x]))
						cornerTmp.push_back(eig_data + x);
						
				}
			}

			cv::sort(cornerTmp, greaterThanPtr<float>());//对角点排序
			
			corners.push_back(cornerTmp);
			
		}
	}
	
	size_t maxSize = corners[0].size();
	for (int i = 1; i < 9; i++ )
	{
		if (maxSize < corners[i].size())
		{
			maxSize = corners[i].size();
		}
	}
	for (int j = 0; j < maxSize; j++)
	{
		for (int i = 0; i < 9; i++)
		{
			if (j < corners[i].size())
			{
				tmpCorners.push_back(corners[i][j]);
			}
		}
	}
}



void mycornerMinEigenVal(InputArray _mask, InputArray _src, OutputArray _dst, int blockSize, int ksize, int borderType)
{
	Mat src = _src.getMat();
	_dst.create(src.size(), CV_32F);
	Mat dst = _dst.getMat();
	Mat mask = _mask.getMat();
	
	mycornerEigenValsVecs(mask, src, dst, blockSize, ksize, MINEIGENVAL, 0);
}

static void mycornerEigenValsVecs(const Mat &mask, const Mat& src, Mat& eigenv, int block_size,
	int aperture_size, int op_type, double k = 0.)
{

#ifdef HAVE_TEGRA_OPTIMIZATION
	if (tegra::cornerEigenValsVecs(src, eigenv, block_size, aperture_size, op_type, k, borderType))
		return;
#endif

	int depth = src.depth();
	double scale = (double)(1 << ((aperture_size > 0 ? aperture_size : 3) - 1)) * block_size;
	if (aperture_size < 0)
		scale *= 2.;
	if (depth == CV_8U)
		scale *= 255.;
	scale = 1. / scale;

	CV_Assert(src.type() == CV_8UC1 || src.type() == CV_32FC1);

	

	Mat Dx, Dy;
	int borderType = BORDER_DEFAULT;

	if (aperture_size > 0)
	{
		
		Sobel(src, Dx, CV_32F, 1, 0, aperture_size, scale, 0, borderType);
		Sobel(src, Dy, CV_32F, 0, 1, aperture_size, scale, 0, borderType);

		//下面的相对比较费时间
		//Mat kx, ky;
		//kx.create(src.size(), CV_MAKETYPE(src.depth(), src.channels()));
		//ky.create(src.size(), CV_MAKETYPE(src.depth(), src.channels()));
		//kx = (Mat_<float>(1, 3) << -1, 0, 1);
		//ky = (Mat_<float>(1, 3) << 1, 2, 1);
		//ky *= scale;
		//sepFilter2D(src, Dx, 5, kx, ky, Point(-1, -1), 0, borderType);
		//ky = (Mat_<float>(1, 3) << -1, 0, 1);
		//kx = (Mat_<float>(1, 3) << 1, 2, 1);
		//kx *= scale;
		//sepFilter2D(src, Dy, 5, kx, ky, Point(-1, -1), 0, borderType);
	}
	else
	{
		Scharr(src, Dx, CV_32F, 1, 0, scale, 0, borderType);
		Scharr(src, Dy, CV_32F, 0, 1, scale, 0, borderType);
	}


	Size size = src.size();
	Mat cov(size, CV_32FC3);
	int i, j;

	for (i = 0; i < size.height; i++)
	{
		float* cov_data = (float*)(cov.data + i*cov.step);
		const float* dxdata = (const float*)(Dx.data + i*Dx.step);
		const float* dydata = (const float*)(Dy.data + i*Dy.step);

		for (j = 0; j < size.width; j++)
		{
			float dx = dxdata[j];
			float dy = dydata[j];

			cov_data[j * 3] = dx*dx;
			cov_data[j * 3 + 1] = dx*dy;
			cov_data[j * 3 + 2] = dy*dy;
		}
	}

	boxFilter(cov, cov, cov.depth(), Size(block_size, block_size),
		Point(-1, -1), false, borderType);//对每个像素都进行特征值的计算，即是滤波
	mycalcMinEigenVal(cov, eigenv, mask);//0.3ms

}

static void mycalcMinEigenVal(const Mat& _cov, Mat& _dst, const Mat &mask)
{
	int i, j;
	Size size = _cov.size();
#if CV_SSE
	volatile bool simd = checkHardwareSupport(CV_CPU_SSE);
#endif

	if (_cov.isContinuous() && _dst.isContinuous())
	{
		size.width *= size.height;
		size.height = 1;
	}

	for (i = 0; i < size.height; i++)
	{
		const float* cov = (const float*)(_cov.data + _cov.step*i);
		float* dst = (float*)(_dst.data + _dst.step*i);
		uchar *mdata = (uchar *)(mask.data + mask.step*i);
		j = 0;
#if CV_SSE
		if (simd)
		{
			__m128 half = _mm_set1_ps(0.5f);
			for (; j <= size.width - 5; j += 4)
			{
				__m128 t0 = _mm_loadu_ps(cov + j * 3); // a0 b0 c0 x
				__m128 t1 = _mm_loadu_ps(cov + j * 3 + 3); // a1 b1 c1 x
				__m128 t2 = _mm_loadu_ps(cov + j * 3 + 6); // a2 b2 c2 x
				__m128 t3 = _mm_loadu_ps(cov + j * 3 + 9); // a3 b3 c3 x
				__m128 a, b, c, t;
				t = _mm_unpacklo_ps(t0, t1); // a0 a1 b0 b1
				c = _mm_unpackhi_ps(t0, t1); // c0 c1 x x
				b = _mm_unpacklo_ps(t2, t3); // a2 a3 b2 b3
				c = _mm_movelh_ps(c, _mm_unpackhi_ps(t2, t3)); // c0 c1 c2 c3
				a = _mm_movelh_ps(t, b);
				b = _mm_movehl_ps(b, t);
				a = _mm_mul_ps(a, half);
				c = _mm_mul_ps(c, half);
				t = _mm_sub_ps(a, c);
				t = _mm_add_ps(_mm_mul_ps(t, t), _mm_mul_ps(b, b));
				a = _mm_sub_ps(_mm_add_ps(a, c), _mm_sqrt_ps(t));
				_mm_storeu_ps(dst + j, a);
			}
		}
#endif
		for (; j < size.width; j++)
		{
			if (!mdata[j])//比较省时间大概0.3ms
			{
				dst[j] = 0;
				continue;
			}
			float a = cov[j * 3] * 0.5f;
			float b = cov[j * 3 + 1];
			float c = cov[j * 3 + 2] * 0.5f;
			dst[j] = (float)((a + c) - std::sqrt((a - c)*(a - c) + b*b));
		}
	}
}

