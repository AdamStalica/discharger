/* 
* DS18B20.cpp
*
* Created: 26.11.2019 23:43:50
* Author: domin
*/

#include "DS18B20.h"
#include "Millis.h"
#include "SafetyGuard.h"
#include "SimulationData.h"

#define SKIP_ROM 0xCC
#define CONVERT_T 0x44
#define READ_SCRATCHPAD 0xBE

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
	_isNewValue = 0;
	return temperature;
}

void DS18B20::run() {
	
	if(runDelay.skipThisTime()) return;

	if(deviceAvaliable()) {
			
		writeByte(SKIP_ROM);
		writeByte(READ_SCRATCHPAD);
			
		uint8_t tab[9] = { 0 };
		for(uint8_t i = 0; i < 9; ++i) {
			tab[i] = readByte();
		}
			
		if(tab[8] == CRC8(tab, 8)) {
			temperature = tab[0];
			temperature |= (tab[1] << 8);
			temperature *= 100;
			temperature /= 16;
			_isNewValue = 1;
			_crcNoMatchCounter = 0;
		}
		else {
			if(_crcNoMatchCounter == THERM_CRC_NO_MATCH_MAX_ERR) {
				if(_errorCrc != Device::Error::NO_DEV_ERROR)
					SafetyGuard::stopDevice(_errorCrc);
				_crcNoMatchCounter = 0;
			}
			else if(_crcNoMatchCounter == THERM_CRC_NO_MATCH_MAX_WARN) { 
				if(_warnCrc != Device::Warning::NO_WARNING) 
					SimulationData::logWarning(_warnCrc);
			}
			++_crcNoMatchCounter;
		}
		
		startConversion();
	}	
	else if(_errorNotAvaliable != Device::Error::NO_DEV_ERROR) {
		SafetyGuard::stopDevice(_errorNotAvaliable);
	}
}

 uint8_t DS18B20::CRC8(uint8_t *inData, uint8_t len) {
	 uint8_t crc;
	 crc = 0;
	 for(; len; len--)
	 {
		 crc ^= *inData++;
		 crc ^= (crc << 3) ^ (crc << 4) ^ (crc << 6);
		 crc ^= (crc >> 4) ^ (crc >> 5);
	 }
	 return crc;
 }