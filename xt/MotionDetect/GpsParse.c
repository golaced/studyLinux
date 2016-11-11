#include <stdio.h>   
#include <stdlib.h>
#include <sys/types.h>   
#include <sys/ipc.h>     
#include <errno.h>
#include <sys/time.h>
#include <pthread.h>
#include "GpsParse.h"

uint8_t step,cls,ck_a,ck_b,msg_id;
uint16_t payload_length,payload_counter;
bool new_speed,new_pos;
uint32_t last_vel_time,last_pos_time;
uint32_t last_update_gps_time;

union UBX_MSGDATA _buffer;
Gps_Status gps_status;
pthread_mutex_t mutex_gps;


bool Parse_Gps(){
	if (cls == CLASS_ACK){
		return false;
	}
	pthread_mutex_lock(&mutex_gps);
	switch(msg_id){
		case MSG_POSLLH:
			last_pos_time = _buffer.posllh.time;
			gps_status.pos_time = _buffer.posllh.time;
      gps_status.lng    = _buffer.posllh.longitude;
      gps_status.lat    = _buffer.posllh.latitude;
      gps_status.alt    = _buffer.posllh.altitude_msl / 10;
		  new_pos = true;
			break;
		case MSG_STATUS:
			if (_buffer.status.fix_status & NAV_STATUS_FIX_VALID){
				if( (_buffer.status.fix_type == FIX_3D) &&
                (_buffer.status.fix_status & NAV_STATUS_DGPS_USED)) {
                gps_status.fix = GPS_OK_FIX_3D_DGPS;
            }else if( _buffer.status.fix_type == FIX_3D) {
                gps_status.fix = GPS_OK_FIX_3D;
            }else if (_buffer.status.fix_type == FIX_2D) {
                gps_status.fix = GPS_OK_FIX_2D;
            }else{
                gps_status.fix = NO_FIX;
            }
			}else{
				gps_status.fix = NO_FIX;
			}
			break;
		case MSG_SOL:
			if (_buffer.solution.fix_status & NAV_STATUS_FIX_VALID) {
            if( (_buffer.solution.fix_type == FIX_3D) &&
                (_buffer.solution.fix_status & NAV_STATUS_DGPS_USED)) {
                gps_status.fix = GPS_OK_FIX_3D_DGPS;
            }else if( _buffer.solution.fix_type == FIX_3D) {
                gps_status.fix = GPS_OK_FIX_3D;
            }else if (_buffer.solution.fix_type == FIX_2D) {
                gps_status.fix = GPS_OK_FIX_2D;
            }else{
                gps_status.fix = NO_FIX;
            }
        }else{
            gps_status.fix = NO_FIX;
        }
			gps_status.hdop = _buffer.solution.position_DOP;
			gps_status.num_sats = _buffer.solution.satellites;
			break;
		case MSG_VELNED:
			last_vel_time = _buffer.velned.time;
			gps_status.ground_speed = _buffer.velned.speed_2d*0.01f;  //m/s
		  gps_status.velned_x = _buffer.velned.ned_north * 0.01f;
      gps_status.velned_y = _buffer.velned.ned_east * 0.01f;
      gps_status.velned_z = _buffer.velned.ned_down * 0.01f;
		  gps_status.heading_2d  =_buffer.velned.heading_2d;
		  new_speed = true;
			break;
		default:
			return false;
	}
	if (new_pos && new_speed && last_vel_time == last_pos_time){
		new_pos = new_speed = false;
		return true;
	}
	pthread_mutex_unlock(&mutex_gps);
	return false;
}

void Update_Gps()
{
	uint8_t data;
  	int16_t numc,i;
  
	numc = USART2available();
	if(numc<=0)
		return;
	
	for (i = 0; i < numc; i++){
		data = USART2Read();
reset:
		switch(step){
			case 0:
				if(PREAMBLE1 == data)
          step++;
				break;
			case 1:
				if(PREAMBLE2 == data) {
           step++;
           break;
        }
        step = 0;
			  break;
			case 2:
				step ++;
			  cls = data;
			  ck_a = ck_b = data;
				break;
			case 3:
				step ++;
			  ck_b += (ck_a += data);
			  msg_id =data;
				break;
			case 4:
				step ++;
			  ck_b += (ck_a += data);
			  payload_length = data;
				break;
			case 5:
				step ++;
			  ck_b += (ck_a += data);
			  payload_length += (uint16_t)(data<<8);
			  if (payload_length > sizeof(_buffer)) {
           // assume any payload bigger then what we know about is noise
           payload_length = 0;
           step = 0;
				   goto reset;
        }
        payload_counter = 0;
				break;
			case 6:
				ck_b += (ck_a += data);                   // checksum byte
        if (payload_counter < sizeof(_buffer)) {
           _buffer.bytes[payload_counter] = data;
        }
        if (++payload_counter == payload_length)
           step++;
				break;
			case 7:
				step++;
        if (ck_a != data) {
          step = 0;
				  goto reset;
        }
				break;
			case 8:
				step = 0;
        if (ck_b != data) {      
           break;   // bad checksum
        }
				if(Parse_Gps()) {
					 last_update_gps_time = systemTickMs;
           gps_status.gps_new_data = true;
					 gps_status.gps_new_display = true;
        }
				break;
		}
	}
}

void *threadFunc(void *ptr)
{
	while(1)
	{
		Update_Gps();
	}
}

int ListenForGpsData(void)
{
	pthread_t id;
	int ret;
	
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

void GetRawGps(Gps_Status* pGps)
{
	pthread_mutex_lock(&mutex_gps);
	
	pthread_mutex_unlock(&mutex_gps);
}
