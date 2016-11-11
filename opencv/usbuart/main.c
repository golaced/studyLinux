#include "readSonar.h"
#include <string.h>
#include <stdio.h>

int usbInit();

int main(int argc, char *argv[])
{
    int fd;
    char buf[256];
    
    fd = usbInit();
    while(1)
    {
        uartRead(fd, buf);
        printf("%s\n", buf);
    }
}


int uartRead(int fd, char *buf)
{
    char str[256];

    read(fd, str, 255);
    strcpy(buf, str + 1);
}
int usbInit()
{
    int fd;

    fd = open(SONAR_DEVICE, O_RDWR);
    if(-1 == fd)
    {
        printf("can not open UART_USB\n");
        return -1;
    }
    setSpeed(fd, SONAR_BAUDRATE );
    if(setParity(fd,8,1,'N') == FALSE)
    {
        printf("can not set parity\n");
        return -1;
    }
    return fd;
}