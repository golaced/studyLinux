#include "xtofAffine2D.h"
using namespace cv;
using namespace std;

int myGetAffineTransform(const CvMat* m1, const CvMat* m2, CvMat* model, int m);

/****************************************************************************************
* File: xtofAffine2D.cpp
* Name: xtofAffine2D
* Input:    
* Output:
* Function:  
* Date: 2016/07/04 21:50
*****************************************************************************************/
/*Parameters:
src – First input 3D point set.
dst – Second input 3D point set.
out – Output 3D affine transformation matrix  3 \times 4 .
inliers – Output vector indicating which points are inliers.
可以把一个点看作内点的最大误差
ransacThreshold – Maximum reprojection error in the RANSAC algorithm to consider a point as an inlier.
置信度，太大速度会慢，太小，迭代次数会太少，结果不可信
confidence – Confidence level, between 0 and 1, for the estimated transformation.
Anything between 0.95 and 0.99 is usually good enough.
Values too close to 1 can slow down the estimation significantly.
Values lower than 0.8 - 0.9 can result in an incorrectly estimated transformation.*/
int xtofAffine2D(InputArray _from, InputArray _to,
	OutputArray _out, OutputArray _inliers,
	double param1, double param2)
{
	Mat from = _from.getMat(), to = _to.getMat();
	Mat out = _out.getMat();
	Mat inliers = _inliers.getMat();

	int count = from.checkVector(2, CV_32F);//可能返回负数
	if (count < 5)
	{
		return false;
	}

	Mat dFrom, dTo;
	from.convertTo(dFrom, CV_64F);//两者的数据区域不同。
	to.convertTo(dTo, CV_64F);

	CvMat F2x3 = out;
	CvMat mask = inliers;
	CvMat m1 = dFrom;//两者指向同一个数据区域
	CvMat m2 = dTo;

	//const double epsilon = numeric_limits<double>::epsilon();//运行编译程序的计算机所能识别的最小非零浮点数。
	double epsilon = 0.00001;
	param1 = param1 <= 0 ? 3 : param1;
	param2 = (param2 < epsilon) ? 0.99 : (param2 > 1 - epsilon) ? 0.99 : param2;
	
	return Affine2DEstimator().runRANSAC(&m1, &m2, &F2x3, &mask, param1, param2);
}
#ifdef _DEBUG_AFFINE
/*****************************************************************************************
* name：affine
* input：
* output：
* function：放射变化矩阵求解，ransac
* Date：
*****************************************************************************************/
void affineTest()
{
	//int estimateAffine2D(cv::InputArray _from, cv::InputArray _to,
	//	cv::OutputArray _out, cv::OutputArray _inliers,
	//	double param1 = 3, double param2 = 0.99);
	ifstream file1, file2;
	string txtRoad = "texture//";
	string txtName = "testc_";
	file1.open(txtRoad + txtName + "last.txt");
	file2.open(txtRoad + txtName + "next.txt");
	if (!file1 || !file2)
	{
		cout << "fail" << endl;
	}
	vector<Point2f> from, to, between;
	Point Ptemp;
	char str[31];
	float x, y;
	int i = 0;
	Mat img(500, 500, CV_8UC1);

	while (!file1.eof())
	{
		file1.getline(str, 30);
		sscanf_s(str, "%f, %f", &x, &y);	//Ptemp.x >> Ptemp.y;
		Ptemp.x = x;
		Ptemp.y = y;
		from.push_back(Ptemp);

		file2.getline(str, 30);
		sscanf_s(str, "%f, %f", &x, &y);	//Ptemp.x >> Ptemp.y;
		Ptemp.x = x;
		Ptemp.y = y;
		to.push_back(Ptemp);

		Ptemp = from[i] - to[i];
		between.push_back(Ptemp);
		circle(img, from[i], 1, Scalar(0, 255, 0));
		line(img, from[i], to[i], Scalar(0, 0, 255));
		i++;
	}
	writetxt("file33.txt", between, between);
	imshow("image", img);
	Mat out1, out2;
	double t = (double)cvGetTickCount();
	estimateAffine2D(from, to, out1, out2, 1, 0.95);
	t = (double)cvGetTickCount() - t;
	cout << "ransac time: " << t / (cvGetTickFrequency() * 1000) << "gms\n";
	cout << "out1:\n" << out1 << endl;
	cout << "point num: " << from.size() << endl;
	cout << "inliers num: " << out2.cols << endl;
	cout << "out2:" << out2 << endl;
	cvWaitKey(0);
}
#endif

/****************************************************************************************
* File: xtofAffine2D.cpp
* Name: 
* Input:    
* Output:
* Function:  根据阈值寻找符合模型的内点
* Date: 2016/08/22 13:59
*****************************************************************************************/
int Affine2DEstimator::findInliers(const CvMat* m1, const CvMat* m2,
	const CvMat* model, CvMat* _err,
	CvMat* _mask, double threshold)
{
	int i, count = _err->rows*_err->cols, goodCount = 0;
	const float* err = _err->data.fl;
	uchar* mask = _mask->data.ptr;

	computeReprojError(m1, m2, model, _err);
	threshold *= threshold;
	for (i = 0; i < count; i++)
		goodCount += mask[i] = err[i] <= threshold;
	return goodCount;
}

/****************************************************************************************
* File: xtofAffine2D.cpp
* Name: 
* Input:    
* Output:
* Function:  计算点与模型的误差
* Date: 2016/08/22 14:01
*****************************************************************************************/
void Affine2DEstimator::computeReprojError(const CvMat* m1, const CvMat* m2, const CvMat* model, CvMat* error)
{
	int count = m1->rows * m1->cols;
	const CvPoint2D64f* from = reinterpret_cast<const CvPoint2D64f*>(m1->data.ptr);
	const CvPoint2D64f* to = reinterpret_cast<const CvPoint2D64f*>(m2->data.ptr);
	const double* F = model->data.db;
	float* err = error->data.fl;

	for (int i = 0; i < count; i++)
	{
		const CvPoint2D64f& f = from[i];
		const CvPoint2D64f& t = to[i];

		double a = F[0] * f.x + F[1] * f.y + F[2] - t.x;
		double b = F[3] * f.x + F[4] * f.y + F[5] - t.y;

		//err[i] = (float)sqrt(a*a + b*b);
		err[i] = float(a*a + b*b);//误差的平方
	}
}
/*****************************************************************************************
* name：runRANSAC
* input：mask0 点是否为内点的标志量
* output：model 输出放射变换参数
* function：
* Date：
*****************************************************************************************/
bool Affine2DEstimator::runRANSAC(const CvMat* m1, const CvMat* m2, CvMat* model,
	CvMat* mask0, double reprojThreshold,
	double confidence, int maxIters)
{
	bool result = false;
	cv::Ptr<CvMat> mask = cvCloneMat(mask0);//深复制？？
	cv::Ptr<CvMat> models, err, tmask;
	cv::Ptr<CvMat> ms1, ms2;

	int iter, niters = maxIters;
	int count = m1->rows*m1->cols, maxGoodCount = 0;
	int flag = CV_ARE_SIZES_EQ(m1, m2);
	flag = CV_ARE_SIZES_EQ(m1, mask);
	CV_Assert(CV_ARE_SIZES_EQ(m1, m2) && CV_ARE_SIZES_EQ(m1, mask));

	models = cvCreateMat(modelSize.height*maxBasicSolutions, modelSize.width, CV_64FC1);
	err = cvCreateMat(1, count, CV_32FC1);
	tmask = cvCreateMat(1, count, CV_8UC1);

	if (count > modelPoints)
	{
		ms1 = cvCreateMat(1, modelPoints, m1->type);//1*3
		ms2 = cvCreateMat(1, modelPoints, m2->type);//1*3
	}
	else
	{
		niters = 1;
		ms1 = cvCloneMat(m1);
		ms2 = cvCloneMat(m2);
	}
	//runsac迭代开始
	for (iter = 0; iter < niters; iter++)
	{

		int i, goodCount, nmodels;
		if (count > modelPoints)
		{
			bool found = getSubset(m1, m2, ms1, ms2, 300);//ms1源点，ms2目的点
			if (!found)
			{
				if (iter == 0)
					return false;
				break;
			}
		}

		nmodels = runKernel(ms1, ms2, models);//nmodels结算出模型nmodels为1，未解算出模型nmodels为0
		if (nmodels <= 0)
			continue;

		for (i = 0; i < nmodels; i++)//可以尝试多生成几个模型，然后选出最好的
		{
			CvMat model_i;
			cvGetRows(models, &model_i, i*modelSize.height, (i + 1)*modelSize.height);//从modles获取model_i模型
			goodCount = findInliers(m1, m2, &model_i, err, tmask, reprojThreshold);//err记录误差，tmask是否为内点的标志变量

			if (goodCount > MAX(maxGoodCount, modelPoints - 1))//有判断如果获取到的模型比原来的较好就保留
			{
				std::swap(tmask, mask);
				cvCopy(&model_i, model);
				maxGoodCount = goodCount;
				niters = cvRANSACUpdateNumIters(confidence,
					(double)(count - goodCount) / count, modelPoints, niters);//迭代次数重新计算，可以去掉
			}//外点的比例
		}
	}//ransac迭代结束

	/*把内点带入进行解算仿射变换矩阵*/
	if (maxGoodCount > 3)
	{
		if (mask != mask0)
		{
		//	cvCopy(mask, mask0);
			mask0 = cvCloneMat(mask);
		}
		result = true;

		//用最小二乘法重新计算放射变换矩阵
		Mat maskTmp = cvCloneMat(mask0);
		cv::Mat_<cv::Vec<uchar,1> >::iterator it = maskTmp.begin<cv::Vec<uchar,1> >();
		cv::Mat_<cv::Vec<uchar,1> >::iterator itend = maskTmp.end<cv::Vec<uchar,1> >();

		cv::Ptr<CvMat> myMs1, myMs2;//原点、目的点

		myMs1 = cvCreateMat(1, maxGoodCount, m2->type);
		myMs2 = cvCreateMat(1, maxGoodCount, m2->type);

		const int *m1ptr = m1->data.i, *m2ptr = m2->data.i;
		int *ms1ptr = myMs1->data.i, *ms2ptr = myMs2->data.i;


		int type = CV_MAT_TYPE(m1->type), elemSize = CV_ELEM_SIZE(type);
		elemSize /= sizeof(int);

		int idx_i = 0, i = 0;

		for (; it != itend; ++it)
		{
			bool flagTmp = (*it)[0];
			if (flagTmp)
			{
				for (int k = 0; k < elemSize; ++k)
				{
					ms1ptr[i*elemSize + k] = m1ptr[idx_i*elemSize + k];//源点复制
					ms2ptr[i*elemSize + k] = m2ptr[idx_i*elemSize + k];//目的点复制
				}
				++i;
			}
			++idx_i;
		}
		myGetAffineTransform(myMs1, myMs2, model, maxGoodCount);//存在对矩阵求逆
	}

	return result;
}
/*****************************************************************************************
* name：getAffineTransform64f
* input：
* output：
* function：求解仿射变换矩阵
* Date：
*****************************************************************************************/
Mat getAffineTransform64f(const Point2d src[], const Point2d dst[])
{
	Mat M(2, 3, CV_64F), X(6, 1, CV_64F, M.data);
	double a[6 * 6], b[6];
	Mat A(6, 6, CV_64F, a), B(6, 1, CV_64F, b);

	for (int i = 0; i < 3; i++)
	{
		int j = i * 12;
		int k = i * 12 + 6;
		a[j] = a[k + 3] = src[i].x;
		a[j + 1] = a[k + 4] = src[i].y;
		a[j + 2] = a[k + 5] = 1;
		a[j + 3] = a[j + 4] = a[j + 5] = 0;
		a[k] = a[k + 1] = a[k + 2] = 0;
		b[i * 2] = dst[i].x;
		b[i * 2 + 1] = dst[i].y;
	}
	//所以它得到的最终是用三个点计算出来的仿射变换矩阵M.data
	solve(A, B, X);//! solves linear system or a least-square problem//lapack.cpp文件
	//cout << "A: " << A << endl;
	//cout << "B: " << B << endl;
	//cout << "X: " << X << endl;

	/*只有位移参数的模型*/
	//M = (Mat_<float>(2, 3) << 1, 0, src[0].x - dst[1].x, 0, 1, src[0].y - dst[1].y);
	return M;
}

int Affine2DEstimator::runKernel(const CvMat* m1, const CvMat* m2, CvMat* model)
{
	const Point2d* from = reinterpret_cast<const Point2d*>(m1->data.ptr);
	const Point2d* to = reinterpret_cast<const Point2d*>(m2->data.ptr);
	Mat M0 = cv::cvarrToMat(model);
	Mat M = getAffineTransform64f(from, to);
	CV_Assert(M.size() == M0.size());
	M.convertTo(M0, M0.type());

	return model != NULL ? 1 : 0;//只是用来判断是否解算出模型
}


bool Affine2DEstimator::getSubset(const CvMat* m1, const CvMat* m2,
	CvMat* ms1, CvMat* ms2, int maxAttempts)
{
	cv::AutoBuffer<int> _idx(modelPoints);
	int* idx = _idx;
	int i = 0, j, k, idx_i, iters = 0;
	int type = CV_MAT_TYPE(m1->type), elemSize = CV_ELEM_SIZE(type);
	const int *m1ptr = m1->data.i, *m2ptr = m2->data.i;
	int *ms1ptr = ms1->data.i, *ms2ptr = ms2->data.i;
	int count = m1->cols*m1->rows;

	assert(CV_IS_MAT_CONT(m1->type & m2->type) && (elemSize % sizeof(int) == 0));
	elemSize /= sizeof(int);
	//生成随机子集，最大尝试次数循环
	for (; iters < maxAttempts; iters++)
	{
		for (i = 0; i < modelPoints && iters < maxAttempts;)
		{
			idx[i] = idx_i = cvRandInt(&rng) % count;///* Return random 32-bit unsigned integer: */
			for (j = 0; j < i; j++)
				if (idx_i == idx[j])
					break;
			if (j < i)//j不小于i说明数组中还没有当前生成的随机数
				continue;
			for (k = 0; k < elemSize; k++)
			{
				ms1ptr[i*elemSize + k] = m1ptr[idx_i*elemSize + k];//源点复制
				ms2ptr[i*elemSize + k] = m2ptr[idx_i*elemSize + k];//目的点复制
			}
			if (checkPartialSubsets && (!checkSubset(ms1, i + 1) || !checkSubset(ms2, i + 1)))
			{//检测子集，检测新添加的点与原来的点不在一条线上
				iters++;
				continue;
			}
			i++;
		}
		if (!checkPartialSubsets && i == modelPoints &&
			(!checkSubset(ms1, i) || !checkSubset(ms2, i)))
			continue;
		break;
	}

	return i == modelPoints && iters < maxAttempts;
}


bool Affine2DEstimator::checkSubset(const CvMat* ms1, int count)
{
	int j, k, i, i0, i1;
	CvPoint2D64f* ptr = (CvPoint2D64f*)ms1->data.ptr;

	assert(CV_MAT_TYPE(ms1->type) == CV_64FC2);

	if (checkPartialSubsets)
		i0 = i1 = count - 1;
	else
		i0 = 0, i1 = count - 1;

	for (i = i0; i <= i1; i++)
	{
		// check that the i-th selected point does not belong
		// to a line connecting some previously selected points
		for (j = 0; j < i; j++)
		{
			double dx1 = ptr[j].x - ptr[i].x;
			double dy1 = ptr[j].y - ptr[i].y;
			for (k = 0; k < j; k++)
			{
				double dx2 = ptr[k].x - ptr[i].x;
				double dy2 = ptr[k].y - ptr[i].y;
				if (fabs(dx2*dy1 - dy2*dx1) <= FLT_EPSILON*(fabs(dx1) + fabs(dy1) + fabs(dx2) + fabs(dy2)))
					break;
			}
			if (k < j)
				break;
		}
		if (j < i)
			break;
	}

	return i >= i1;
}
/****************************************************************************************
* File: xtofAffine2D.cpp
* Name: 
* Input:    
* Output:
* Function:  仿射变换模型，线性回归，正规方程求解参数矩阵的方法
* Date: 2016/08/22 16:19
*****************************************************************************************/
int myGetAffineTransform(const CvMat* m1, const CvMat* m2, CvMat* model, int m)
{
	const Point2d* src = reinterpret_cast<const Point2d*>(m1->data.ptr);
	const Point2d* dst = reinterpret_cast<const Point2d*>(m2->data.ptr);
	Mat M0 = cv::cvarrToMat(model);
	

	cv::Mat_<float> X = cv::Mat(m, 3, CV_32FC1, cv::Scalar(0));
	cv::Mat_<float> Y = cv::Mat(m, 2, CV_32FC1, cv::Scalar(0));

	for (int i = 0; i < m; i++)
	{
		float x0 = src[i].x, x1 = src[i].y;
		float y0 = dst[i].x, y1 = dst[i].y;

		X(i, 0) = x0;
		X(i, 1) = x1;
		X(i, 2) = 1;

		Y(i, 0) = y0;
		Y(i, 1) = y1;
	}

	cv::Mat_<float> F = (X.t()*X).inv()*(X.t()*Y);

	Mat M = F.t();
	// cout << F << endl;
	CV_Assert(M.size() == M0.size());
	M.convertTo(M0, M0.type());

	return model != NULL ? 1 : 0;//只是用来判断是否解算出模型
}
Affine2DEstimator::Affine2DEstimator() : modelPoints(3), modelSize(cvSize(3, 2)), maxBasicSolutions(1)
{
	checkPartialSubsets = true;
	rng = cvRNG(-1);
}

