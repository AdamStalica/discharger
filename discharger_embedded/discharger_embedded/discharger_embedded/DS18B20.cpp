/* 
* DS18B20.cpp
*
* Created: 26.11.2019 23:43:50
* Author: domin
*/


#include "DS18B20.h"
#include "MillisecsCounter.h"

#define SKIP_ROM 0xCC
#define CONVERT_T 0x44
#define READ_SCRATCHPAD 0xBE

#define MAX_DIFFERENCE 150

#define READ_INTERVAL_MS 800

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
	return temperature;
}

void DS18B20::run() {
	
	if((MillisecsCounter::getMillisecs() - lastReadTimestamp) > READ_INTERVAL_MS) {
		
		lastReadTimestamp = MillisecsCounter::getMillisecs();
		
		if(deviceAvaliable()) {
			
			writeByte(SKIP_ROM);
			writeByte(READ_SCRATCHPAD);
			
			temperature = readByte();
			temperature |= (readByte() << 8);
			temperature *= 100;
			temperature /= 16;
			
			valueIsUnchecked = 1;
			
			startConversion();
			
		}	
		else {
			debugLog("Can't read T: ", getPhysicalPin());
		}
	}
}

