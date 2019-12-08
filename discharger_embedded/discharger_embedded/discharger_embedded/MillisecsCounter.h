/* 
* MillisecsCounter.h
*
* Created: 24.11.2019 09:58:59
* Author: domin
*/


#ifndef __MILLISECSCOUNTER_H__
#define __MILLISECSCOUNTER_H__

#include <avr/io.h>
#include "GlobalDefs.h"

class MillisecsCounter
{
	volatile static uint32_t msSinceDeviceHasStarted;
	
public:
	~MillisecsCounter() {};
	MillisecsCounter() {};
	static void init() {
	
		TCCR0A = (1 << WGM01);
		TCCR0B = (1 << CS02) | (1 << CS00);
		
		OCR0A = F_CPU / 1024 / 1000;
		TIMSK0 = (1 << OCIE0A);	
	};
	
	static void isrTimer0CompBVect() {
		++msSinceDeviceHasStarted;
	}
	
	static uint32_t getMillisecs() {
		return msSinceDeviceHasStarted;
	}
};


#endif //__MILLISECSCOUNTER_H__
