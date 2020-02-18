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

class SafetyGuard
{
	ExecuteDelay runDelay;
	Button safetyBtn;
	
	static Device::Error error;
	
	enum SafetyEvents {
		NONE,
		SAFETY_BTN,
		OVER_TEMP,
		OVER_CURR,
		UNDER_VOLT	
	} _safetyEvent = NONE;
	uint32_t _safetyEventStart = 0;
		
	uint8_t safetyCheckEvent(SafetyEvents event, Device::Warning warn, Device::Error error, uint32_t timeout, uint8_t logicState);
	void safetyEventStart(SafetyEvents event);
	void safetyEventStop();
	void safetyEventTimeout();
	uint8_t hasTimeoutOccured(uint32_t limit);
	
public:
	SafetyGuard() : runDelay(SAFETY_GUARD_INTERVAL) {};
	~SafetyGuard() {};
	
	static void reset() { while(1); };
	static void stopDevice(Device::Error err) { error = err; }
	
protected:
	void init();
	void run();	
	virtual void deviceStopRequest() = 0;
};

#endif //__SAFETYGUARD_H__
