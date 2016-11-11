#ifndef _XTOFMAVLINKTEST_H_
#define _XTOFMAVLINKTEST_H_


#define BUFFER_LENGTH 1024
#define MAVLINK_UART_BAUDRATE 9600
#define MAVLINK_UART_DEVICE "/dev/ttyUSB0"

uint64_t microsSinceEpoch();
int mavlink_example();
int mavlinkNetInit();
int mavlinkUartInit();
#endif
