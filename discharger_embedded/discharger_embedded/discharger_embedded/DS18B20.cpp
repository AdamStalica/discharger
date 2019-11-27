/* 
* DS18B20.cpp
*
* Created: 26.11.2019 23:43:50
* Author: domin
*/


#include "DS18B20.h"

#define SKIP_ROM 0xCC
#define CONVERT_T 0x44
#define READ_SCRATCHPAD 0xBE

#define MAX_DIFFERENCE 150

uint8_t DS18B20::deviceAvaliable() {
	return resetPulse();
}

uint8_t DS18B20::startConversion() {
	
	uint8_t deviceAvailable = resetPulse();
	writeByte(SKIP_ROM);
	writeByte(CONVERT_T);
	
	return deviceAvailable;
}


int16_t DS18B20::getTemperature() {
	
	writeByte(SKIP_ROM);
	writeByte(READ_SCRATCHPAD);
		
	uint16_t temperature = readByte();
	temperature |= (readByte() << 8);
	temperature *= 100;
	temperature /= 16;
	
	static uint8_t firstRun = 1;
	if(!firstRun && mathAbsDiff(lastTemperature, temperature) > MAX_DIFFERENCE) {
		temperature = lastTemperature;
	}
	else {
		lastTemperature = temperature;
		firstRun = 0;	
	}
		
	return temperature;
}
