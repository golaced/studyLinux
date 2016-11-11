#include <stdio.h>
#include "readSonar.h"

int main()
{
	float sonar = 0;
	int fd;
	
	fd = open(SONAR_DEVICE,O_RDWR);
	if(-1 == fd)
	{
		printf("can not open ttyUSB0\n");
	}
	setSpeed(fd, SONAR_BAUDRATE);
	if(setParity(fd,8,1,'N') == FALSE)
	{
		printf("set parity error\n");
	}


	while(1)
	{
		sleep(0.5);
		sonar = readSonar(fd);
		printf("%f\n",sonar);
	}
	close(fd);
	return 0;
}
