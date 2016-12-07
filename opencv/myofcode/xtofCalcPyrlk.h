#ifndef _XTOF_CALCPYRLK_H_
#define _XTOF_CALCPYRLK_H_

#include <opencv2/opencv.hpp>

#define WIN_SIZE  31 //建立光流金字塔时用到，在光流解算时是G矩阵的求和范围，相当于光流的搜索范围 //opencv自带是31

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

int xtofCalcPyrlk(std::vector<cv::Mat> &prevPyr, std::vector<cv::Mat> &nextPyr,
	cv::InputArray _prevPts, cv::InputOutputArray _nextPts,
	cv::OutputArray _status, cv::OutputArray _err, cv::TermCriteria criteria,
	double minEigThreshold, int maxLevel);
#endif