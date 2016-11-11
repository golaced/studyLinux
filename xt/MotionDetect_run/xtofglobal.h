#ifndef _XTOFGLOBAL_H_
#define _XTOFGLOBAL_H_

#define  CAMERA_FOCAL_X 665.4535
#define  CAMERA_FOCAL_Y 661.4893
#define  CAMERA_PRINCIPLE_X 312.4918
#define  CAMERA_PRINCIPLE_Y 225.6335

#define PI 3.1416
//摄像机mine 畸变参数
//#define FACTOR_DISTORTION1 -0.43133
//#define FACTOR_DISTORTION2 0.14725
//#define FACTOR_DISTORTION3 -0.00087
//#define FACTOR_DISTORTION4 -0.0089

//摄像机2畸变参数
#define FACTOR_DISTORTION1 0
#define FACTOR_DISTORTION2 0
#define FACTOR_DISTORTION3 0
#define FACTOR_DISTORTION4 0

//#define DEBUG
//#define CV_SSE2 true
//#define USEBLOCK

extern float g_roll, g_pitch, g_yaw;
extern float g_gestureArray[3][200];

#endif
