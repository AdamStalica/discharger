/*
 * MillisecsCounter.cpp
 *
 * Created: 08.12.2019 20:06:42
 *  Author: domin
 */ 
#include "MillisecsCounter.h"

volatile uint32_t MillisecsCounter::msSinceDeviceHasStarted = 0;