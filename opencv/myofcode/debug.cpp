#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>  
#include <sys/stat.h>  
#include <fcntl.h>  
#include <termios.h>  
#include <unistd.h>
#include "debug.h"    

extern "C"
{
    #include "xtofReadSonar.h"
};

#define FALSE -1
#define TRUE 0

int g_nrfFd;
VideoWriter cap;

int usbNrfInit()
{
    int fd ;
    //fd = open("ttyUSB0");
    fd = open(NRF_DEVICE,O_RDWR);
    if(-1 == fd)
    {
        fprintf(stderr,"can not open usb NRF\n");
    }
    setSpeed(fd, NRF_BAUDRATE);
    if(setParity(fd,8,1,'N') == FALSE)
    {
        fprintf(stderr, "set NRF parity error\n");
    }
    fprintf(stderr, "open NRF usb  ");
    
    g_nrfFd = fd;
    return fd;
}

int nrfSend(float x, float y)
{
    char buf[30] = {0};

    sprintf(buf, "%2.3f,%2.3f\n", x, y);
    write(g_nrfFd, buf, strlen(buf));
}
int saveVideoInit()
{
    int codec = CV_FOURCC('M', 'J', 'P', 'G');
    double fps = 25.0;


    cap.open("/home/lxg-/code/video/tmp.avi", codec, fps, Size(300, 300));
    if(!cap.isOpened())
    {
        printf("can not open video\n");
        return -1;
    }
}
int saveVideo(Mat &im)
{
    cap << im;
}