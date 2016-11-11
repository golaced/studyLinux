#ifndef _MAVLINK_BRIDGE_H_
#define _MAVLINK_BRIDGE_H_

#include <mavlink_types.h>

#define MAVLINK_SEND_UART_BYTES mavlink_send_bytes

extern void mavlink_send_bytes(mavlink_channel_t chan, const uint8_t * ch, uint16_t length);

#endif