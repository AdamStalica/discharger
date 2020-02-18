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
#include "ExecuteDelay.h"

inline uint16_t mathAbsDiff(uint16_t a, uint16_t b) {
	return (a < b ? (b - a) : (a - b));
}

class DS18B20 : private OneWireHolder
{
	ExecuteDelay runDelay;
	Device::Warning _warnCrc;
	Device::Error _errorCrc;
	Device::Error _errorNotAvaliable;
	
	uint8_t _crcNoMatchCounter = 0;
	uint8_t _isNewValue = 0;
	uint16_t temperature = 0;
	
	//https://www.elektroda.pl/rtvforum/topic1087331.html
	uint8_t CRC8(uint8_t *inData, uint8_t len);
	
public:
	DS18B20(uint8_t physicalPin, 
			Device::Warning warnCrc = Device::Warning::NO_WARNING, 
			Device::Error errorCrc = Device::Error::NO_ERROR,
			Device::Error errorNotAvaliable = Device::Error::NO_ERROR
			) : 
			OneWireHolder(physicalPin),
			runDelay(TEMP_READ_INTERVAL, 1),
			_warnCrc(warnCrc),
			_errorCrc(errorCrc),
			_errorNotAvaliable(errorNotAvaliable)
			
	{};
	~DS18B20() {};
	
	uint8_t deviceAvaliable();
	uint8_t startConversion();
	int16_t getTemperature();
	uint8_t isNewValueAvaliable() { return _isNewValue; };
	
	void run();
	
}; 

#endif //__DS18B20_H__
