#ifndef _XTOFGLOBAL_H_
#define _XTOFGLOBAL_H_

#include "mavlink/common/mavlink.h"



#define  CAMERA_WIDTH 640 //视频宽度
#define  CAMERA_LENGTH 480 //视频长度

#define  IMG_SELECT_AREA 200  //视频截取区域边长
#define  IMG_SCALE 0.5 //视频截取图像缩放比例
#define  IMG_SELECT_X 220	//视频截取图像左上角x坐标
#define  IMG_SELECT_Y 140  //视频截取图像左上角y坐标
#define  IMG_SELECT_WIDTH 200  //视频截取图像宽度
#define  IMG_SELECT_LENGTH 200 //视频截取图像长度


#define  CAMERA_FOCAL_X 665.4535
#define  CAMERA_FOCAL_Y 661.4893
#define  CAMERA_PRINCIPLE_X 312.4918
#define  CAMERA_PRINCIPLE_Y 225.6335

#define PI 3.1416
#define MAX_CORNER_NUM			20		//角点的最大数目

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

#define MAVLINK_COMM_NET MAVLINK_COMM_0
#define MAVLINK_COMM_UART MAVLINK_COMM_1


//#define DEBUG
//#define CV_SSE2 true
//#define USEBLOCK
#define TRUE 1
#define FALSE 0

enum send_data
{
	SEND_DATA_UART = 1,
	SEND_DATA_MAVLINK,
};

enum global_param_id
{
	PARAM_SEND_DATA,
	PARAM_SEND_OPTICAL_MAVLINK,
	PARAM_SEND_VIDEO_MAVLINK,
	PARAM_SEND_SONAR_MAVLINK,
	
	PARAM_SONAR_RAW,
	PARAM_SENSOR_ID,
	PARAM_PREPROCESS_ISC,

	PARAM_FIX_POINT,
	PARAM_SAVE_TEST_VIDEO,

	PARAM_FILTER_MEDIAM,
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
	mavlink_channel_t mavlink;
};


#endif