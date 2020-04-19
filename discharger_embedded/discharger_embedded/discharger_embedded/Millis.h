/* 
* Millis.h
*
* Created: 24.11.2019 09:58:59
* Author: domin
*/


#ifndef __MILLIS_H__
#define __MILLIS_H__

#include <avr/io.h>
#include "GlobalDefs.h"


class Millis
{
	volatile static uint32_t msSinceDeviceHasStarted;
	
public:	
	static uint32_t get() {
		return msSinceDeviceHasStarted;
	}

	static void init() {
	
		TCCR0A = (1 << WGM01);
		TCCR0B = (1 << CS02); // prescaler /256 -> F_CPU / 256 = 18,432,000 / 256 = 72,000 Hz
		
		OCR0A = F_CPU / 256 / 1000;
		TIMSK0 = (1 << OCIE0A);	
	};
	
	static void isrTimer0CompBVect() {
		++msSinceDeviceHasStarted;
	}
	
	static uint32_t getMillisecs() {
		return msSinceDeviceHasStarted;
	}
};

#endif //__MILLIS_H__
