#ifndef _XTOFGLOBAL_H_
#define _XTOFGLOBAL_H_

#include <opencv2/opencv.hpp>

#define  CAMERA_WIDTH 640 //��Ƶ���
#define  CAMERA_LENGTH 480 //��Ƶ����

#define  IMG_SELECT_AREA 200  //��Ƶ��ȡ����߳�
#define  IMG_SCALE 0.5 //��Ƶ��ȡͼ�����ű���
#define  IMG_SELECT_X 220	//��Ƶ��ȡͼ�����Ͻ�x����
#define  IMG_SELECT_Y 140  //��Ƶ��ȡͼ�����Ͻ�y����
#define  IMG_SELECT_WIDTH 200  //��Ƶ��ȡͼ����
#define  IMG_SELECT_LENGTH 200 //��Ƶ��ȡͼ�񳤶�


#define  CAMERA_FOCAL_X 665.4535
#define  CAMERA_FOCAL_Y 661.4893
#define  CAMERA_PRINCIPLE_X 312.4918
#define  CAMERA_PRINCIPLE_Y 225.6335

#define PI 3.1416
#define MAX_CORNER_NUM			20		//�ǵ�������Ŀ

//�����mine �������
//#define CAMERA_FOCAL_X 624  //3.6mm�����࣬6um��Ԫ�ߴ�.�õ��ĵ�λ������
//#define CAMERA_FOCAL_Y 625  //3.6mm�����࣬6um��Ԫ�ߴ�
//#define FACTOR_DISTORTION1 -0.43133
//#define FACTOR_DISTORTION2 0.14725
//#define FACTOR_DISTORTION3 -0.00087
//#define FACTOR_DISTORTION4 -0.0089

//�����2�������
#define FACTOR_DISTORTION1 0
#define FACTOR_DISTORTION2 0
#define FACTOR_DISTORTION3 0
#define FACTOR_DISTORTION4 0

#define LINUX_DEBIAN

//#define DEBUG
//#define CV_SSE2 true
//#define USEBLOCK
#define TRUE 1
#define FALSE 0

enum global_param_id
{
	PARAM_SEND_OPTICAL_MAVLINK,
	PARAM_SEND_VIDEO_MAVLINK,
	PARAM_SENSOR_ID,
	ON_BOARD_PARAM_COUNT
};
//image destination size
struct img_struct
{
	int width;
	int height;
	int leftupX;
	int leftupY;
};
struct global_struct
{
	int param[ON_BOARD_PARAM_COUNT];
	struct img_struct img;
};


#endif