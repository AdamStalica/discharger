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

class DS18B20 : private OneWireHolder
{
	
public:
	DS18B20(uint8_t physicalPin) : OneWireHolder(physicalPin) {};
	~DS18B20() {};
	
	uint8_t deviceAvaliable();
	uint8_t startConversion();
	int16_t getTemperature();
	
}; 

#endif //__DS18B20_H__
