/* 
* SafetyGuard.h
*
* Created: 08.12.2019 19:25:50
* Author: domin
*/


#ifndef __SAFETYGUARD_H__
#define __SAFETYGUARD_H__

#include "GlobalDefs.h"
#include "DS18B20.h"

#define TEMPERATURE_ARRAY_SIZE 6



class SafetyGuard
{
	
	DS18B20 * thermometer;
	uint16_t tempsArray[TEMPERATURE_ARRAY_SIZE] = { 0 };
	uint8_t deviceError = DeviceError::DEVICE_STARTED;
	
	void review();
	void reset() { while(1); };
	
public:
	SafetyGuard() {};
	~SafetyGuard() {};
	
	void init();
	
protected:

	void setThermometerToObserve(DS18B20 * therm) { thermometer = therm; }
	uint8_t getDeviceError() { return deviceError; }
	void run();
	
	virtual void dangerEvent() = 0;
};

#endif //__SAFETYGUARD_H__
