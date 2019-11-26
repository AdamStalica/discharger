/* 
* MillisecsCounter.h
*
* Created: 24.11.2019 09:58:59
* Author: domin
*/


#ifndef __MILLISECSCOUNTER_H__
#define __MILLISECSCOUNTER_H__

#include <avr/io.h>

class MillisecsCounter
{
	volatile uint32_t msSinceDeviceHasStarted = 0;
	
public:
	~MillisecsCounter();
	MillisecsCounter(unsigned long fCpu);
	void isrTimer0CompBVect();
	uint32_t getMillisecs();
	

}; //MillisecsCounter

#endif //__MILLISECSCOUNTER_H__
