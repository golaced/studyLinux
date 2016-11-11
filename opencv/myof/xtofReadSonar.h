#ifndef _READSONAR_H_
#define _READSONAR_H_

#include <sys/types.h>  
      
#include <sys/stat.h>  
#include <fcntl.h>  
#include <termios.h>  

#define SONAR_BAUDRATE 115200
#define SONAR_DEVICE "/dev/ttyUSB0"


float readSonar(int fd);
void setSpeed(int fd, int speed);
int setParity(int fd, int databits, int stopbits, int parity);
int sonarInit();

#endif
