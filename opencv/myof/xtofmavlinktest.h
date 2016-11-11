#ifndef _XTOFMAVLINKTEST_H_
#define _XTOFMAVLINKTEST_H_

#include "xtofReadSonar.h"


#define BUFFER_LENGTH 1024
uint64_t microsSinceEpoch();
int mavlink_example();
int mavlinkNetInit();
#endif
