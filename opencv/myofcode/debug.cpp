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
VideoWriter g_savecap;
FileStorage g_fs;

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


    g_savecap.open("/home/lxg-/video/tmp.avi", codec, fps, Size(300, 300));
    if(!g_savecap.isOpened())
    {
        printf("can not open save video\n");
        return -1;
    }
}
int saveVideo(Mat &im)
{
    g_savecap << im;
}
int closeSaveVideo()
{
    g_savecap.release();
}
void xmlInit(void)
{
    g_fs.open("tmp.xml", FileStorage::WRITE);

}
int saveXmlData(float x, float y)
{
    g_fs << "{:";
    g_fs << x;
    g_fs << y;
    g_fs << ":}";
}
void xmlClose()
{
    g_fs.release();
}