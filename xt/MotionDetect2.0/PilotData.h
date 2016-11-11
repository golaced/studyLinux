#ifndef _PILOT_DATA_H_
#define _PILOT_DATA_H_

#define MSGKEY  1024
#define MSG_TYPE_AHRS          0x01
#define MSG_TYPE_GPS           0x02

struct AHRS{
	unsigned long time;
	float roll;
	float pitch;
	float yaw;
};

struct GPSDATA{
	int status;
	float speed;
	long lat;
	long lng;
	long alt;
};

typedef union{
	struct AHRS ahrs;
	struct GPSDATA gps;
}MSG_BODY;

struct msg_packet{
	int msgType;
	MSG_BODY body;
};

int ListenForPilotData(void);
int GetAHRS(float* roll,float* pitch,float* yaw,unsigned long* t);
int GetGps(struct GPSDATA* pGps);

#endif
