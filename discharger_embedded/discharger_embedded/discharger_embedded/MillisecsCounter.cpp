/* 
* MillisecsCounter.cpp
*
* Created: 24.11.2019 09:58:59
* Author: domin
*/


#include "MillisecsCounter.h"


MillisecsCounter::MillisecsCounter(unsigned long fCpu)
{
	TCCR0A = (1 << WGM01);
	TCCR0B = (1 << CS02) | (1 << CS00);
	
	OCR0A = fCpu / 1024 / 1000;
	TIMSK0 = (1 << OCIE0A);
}


MillisecsCounter::~MillisecsCounter()
{
}


void MillisecsCounter::isrTimer0CompBVect() {
	++msSinceDeviceHasStarted;
}

uint32_t MillisecsCounter::getMillisecs() {
	return msSinceDeviceHasStarted;
}