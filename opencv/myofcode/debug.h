#ifndef _DEBUG_H_
#define _DEBUG_H_

#define NRF_DEVICE "/dev/ttyUSB1"
#define NRF_BAUDRATE 9600

int usbNrfInit();
int nrfSend(float x, float y);

#endif