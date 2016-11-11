#include <stdio.h>   
#include <stdlib.h>
#include <sys/types.h>   
#include <sys/ipc.h>   
#include <sys/msg.h>   
#include <errno.h>
#include <sys/time.h>
#include <pthread.h>
#include "PilotData.h"

struct AHRS ahrs;
struct GPSDATA gps;
pthread_mutex_t mutex_ahrs;
pthread_mutex_t mutex_gps;

void *threadFunc(void *ptr)
{
	struct msg_packet packet;
	int ret,msgid;

	
	while(1){
		msgid = msgget(MSGKEY,IPC_EXCL);
		if(msgid<0)
		{
			continue;
		}
		ret = msgrcv(msgid,&packet,sizeof(struct msg_packet),0,IPC_NOWAIT);
		if(ret == sizeof(struct msg_packet))
		{
			switch(packet.msgType)
			{
				case MSG_TYPE_AHRS:
					pthread_mutex_lock(&mutex_ahrs);
					ahrs.time = packet.body.ahrs.time;
					ahrs.roll = packet.body.ahrs.roll;
					ahrs.pitch = packet.body.ahrs.pitch;
					ahrs.yaw = packet.body.ahrs.yaw;
					pthread_mutex_unlock(&mutex_ahrs);
				break;
				case MSG_TYPE_GPS:
					pthread_mutex_lock(&mutex_gps);
					gps.status = packet.body.gps.status;
					gps.speed = packet.body.gps.speed;
					gps.lat = packet.body.gps.lat;
					gps.lng = packet.body.gps.lng;
					gps.alt = packet.body.gps.alt;
					pthread_mutex_unlock(&mutex_gps);
				break;
			}
		}
	}
}

int ListenForPilotData(void)
{
	pthread_t id;
	int ret;
	
	if(pthread_mutex_init(&mutex_ahrs,NULL) != 0)
	{
		return -1;
	}
	if(pthread_mutex_init(&mutex_gps,NULL) != 0)
	{
		return -1;
	}
	ret=pthread_create(&id,NULL,threadFunc,NULL);
	if(ret!=0){
		return -1;
	}
	return 0;
}


int GetAHRS(float* roll,float* pitch,float* yaw,unsigned long* t)
{
	struct  timeval    tv;
	struct  timezone   tz;
	gettimeofday(&tv,&tz);
	
	//if(tv.tv_sec - ahrs.time < 2)
	{
		pthread_mutex_lock(&mutex_ahrs);
		*roll = ahrs.roll;
		*pitch = ahrs.pitch;
		*yaw = ahrs.yaw;
		*t = tv.tv_sec;
		pthread_mutex_unlock(&mutex_ahrs);
		return 0;
	}
	return -1;
} 

int GetGps(struct GPSDATA* pGps)
{
	struct  timeval    tv;
	struct  timezone   tz;
	gettimeofday(&tv,&tz);
	
	if(pGps == NULL)
		return -1;
	//if(tv.tv_sec - ahrs.time < 2)
	{
		pthread_mutex_lock(&mutex_gps);
		pGps->status = gps.status;
		pGps->speed = gps.speed;
		pGps->lat = gps.lat;
		pGps->lng = gps.lng;
		pGps->alt = gps.alt;
		pthread_mutex_unlock(&mutex_gps);
		return 0;
	}
	return -1;
}
