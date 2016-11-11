#ifndef _XTOF_CALCPYRLK_H_
#define _XTOF_CALCPYRLK_H_
#include <stdio.h>
#include <stdlib.h>
#include <opencv2/opencv.hpp>

#define WIN_SIZE  21 
using namespace std;

namespace cv
{
	namespace detail
	{

		typedef short deriv_type;

		struct LKTrackerInvoker : ParallelLoopBody
		{
			LKTrackerInvoker(const Mat& _prevImg, const Mat& _prevDeriv, const Mat& _nextImg,
				const Point2f* _prevPts, Point2f* _nextPts,
				uchar* _status, float* _err,
				Size _winSize, TermCriteria _criteria,
				int _level, int _maxLevel, int _flags, float _minEigThreshold);

			void operator()(const Range& range) const;

			const Mat* prevImg;
			const Mat* nextImg;
			const Mat* prevDeriv;
			const Point2f* prevPts;
			Point2f* nextPts;
			uchar* status;
			float* err;
			Size winSize;
			TermCriteria criteria;
			int level;
			int maxLevel;
			int flags;
			float minEigThreshold;
		};

	}// namespace detail
	
}// namespace cv

using namespace cv;
int xtofCalcPyrlk(vector<Mat> &prevPyr, vector<Mat> &nextPyr,
	InputArray _prevPts, InputOutputArray _nextPts,
	OutputArray _status, OutputArray _err, TermCriteria criteria,
	int flags, double minEigThreshold, int maxLevel);
#endif
