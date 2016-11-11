#ifndef _XTOF_AFFINE2D_H_
#define _XTOF_AFFINE2D_H_

#include <opencv2/opencv.hpp>

class Affine2DEstimator
{
public:
	Affine2DEstimator();
	int runKernel(const CvMat* m1, const CvMat* m2, CvMat* model);
	bool runRANSAC(const CvMat* m1, const CvMat* m2, CvMat* model,
		CvMat* mask, double threshold,
		double confidence = 0.99, int maxIters = 60);//最大迭代次数
	bool getSubset(const CvMat* m1, const CvMat* m2,
		CvMat* ms1, CvMat* ms2, int maxAttempts = 1000);
	bool checkSubset(const CvMat* ms1, int count);
	int findInliers(const CvMat* m1, const CvMat* m2,
		const CvMat* model, CvMat* error,
		CvMat* mask, double threshold);
	void computeReprojError(const CvMat* m1, const CvMat* m2, const CvMat* model, CvMat* error);
protected:
	CvRNG rng;// CvRNG uint64;  cvRNG(-1)随机数
	int modelPoints;////modelPoints = 3，即点数最少为3
	CvSize modelSize;//3*2
	int maxBasicSolutions;//1
	bool checkPartialSubsets;//true
};

/****************************************************************************************
* File: xtofAffine2D.h
* Name: xtofAffine2D
* Input:    param1把一个点看作内点的最大误差，param2置信率，太大，迭代次数过多，速度减慢；
* Input:	太小，迭代次数过少，结果不可信，3和0.99为默认值，调用时被覆盖
* Output:
* Function:  
* Date: 2016/07/08 23:11
*****************************************************************************************/
int xtofAffine2D(cv::InputArray _from, cv::InputArray _to,
	cv::OutputArray _out, cv::OutputArray _inliers,
	double param1 = 3, double param2 = 0.99);

void affineTest();


#endif
