/* 
* DS18B20.h
*
* Created: 26.11.2019 23:43:50
* Author: domin
*/


#ifndef __DS18B20_H__
#define __DS18B20_H__

#include "GlobalDefs.h"
#include "OneWireHolder.h"
#include <avr/io.h>

inline uint16_t mathAbsDiff(uint16_t a, uint16_t b) {
	return (a < b ? (b - a) : (a - b));
}

class DS18B20 : private OneWireHolder
{
	uint8_t valueIsUnchecked = 0;
	uint16_t temperature = 0;
	uint32_t lastReadTimestamp = 0;
	
public:
	DS18B20(uint8_t physicalPin) : OneWireHolder(physicalPin) {};
	~DS18B20() {};
	
	uint8_t deviceAvaliable();
	uint8_t startConversion();
	int16_t getTemperature();
	uint8_t isNewValueAvaliable() {
		uint8_t tmp = valueIsUnchecked;
		valueIsUnchecked = 0;
		return tmp;
	};
	
	void run();
	
}; 

#endif //__DS18B20_H__
