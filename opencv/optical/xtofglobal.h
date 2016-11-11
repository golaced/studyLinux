#ifndef _XTOFGLOBAL_H_
#define _XTOFGLOBAL_H_

#include <opencv2/opencv.hpp>

#define  CAMERA_WIDTH 640 //视频宽度
#define  CAMERA_LENGTH 480 //视频长度

#define IMG_SELECT_AREA 400  //视频截取区域边长
#define  IMG_SCALE 0.225 //视频截取图像缩放比例
#define  IMG_SELECT_X 220	//视频截取图像左上角x坐标
#define  IMG_SELECT_Y 140  //视频截取图像左上角y坐标
#define  IMG_SELECT_WIDTH 200  //视频截取图像宽度
#define  IMG_SELECT_LENGTH 200 //视频截取图像长度

#define  CAMERA_FOCAL_X 665.4535
#define  CAMERA_FOCAL_Y 661.4893
#define  CAMERA_PRINCIPLE_X 312.4918
#define  CAMERA_PRINCIPLE_Y 225.6335

#define PI 3.1416
#define MAX_CORNER_NUM			30		//角点的最大数目

//摄像机mine 畸变参数
//#define CAMERA_FOCAL_X 624  //3.6mm物理焦距，6um像元尺寸.得到的单位是像素
//#define CAMERA_FOCAL_Y 625  //3.6mm物理焦距，6um像元尺寸
//#define FACTOR_DISTORTION1 -0.43133
//#define FACTOR_DISTORTION2 0.14725
//#define FACTOR_DISTORTION3 -0.00087
//#define FACTOR_DISTORTION4 -0.0089

//摄像机2畸变参数
#define FACTOR_DISTORTION1 0
#define FACTOR_DISTORTION2 0
#define FACTOR_DISTORTION3 0
#define FACTOR_DISTORTION4 0

#define LINUX_DEBIAN
//#define DEBUG
//#define CV_SSE2 true
//#define USEBLOCK


#endif
