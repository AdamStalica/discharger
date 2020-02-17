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
#include "Button.h"

#define TEMPERATURE_ARRAY_SIZE 6



class SafetyGuard : ExecuteDelay
{
	uint8_t _safety_btn_was_pressed = 0;
	uint32_t _safety_event_start = 0;
	
	
	Button safetyBtn;
	
	DS18B20 * thermometer;
	uint16_t tempsArray[TEMPERATURE_ARRAY_SIZE] = { 0 };
	uint8_t deviceError = Device::Error::DEVICE_STARTED;
	
	void review();
	void reset() { while(1); };
	
public:
	SafetyGuard() : ExecuteDelay(SAFETY_GUARD_INTERVAL) {};
	~SafetyGuard() {};
		
	
	void init();
	
protected:

	void setThermometerToObserve(DS18B20 * therm) { thermometer = therm; }
	uint8_t getDeviceError() { return deviceError; }
	void run();
	
	virtual void deviceStopRequest() = 0;
};

#endif //__SAFETYGUARD_H__
