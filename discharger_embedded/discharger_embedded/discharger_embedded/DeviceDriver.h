/* 
* DeviceDriver.h
*
* Created: 18.04.2020 17:16:03
* Author: domin
*/


#ifndef __DEVICEDRIVER_H__
#define __DEVICEDRIVER_H__

#include "UsartHolder.h"
#include "GlobalDefs.h"
#include "DeviceDriverCallbacks.h"

class Discharger;

class StringProcessor;

class DeviceDriver : 
	private UsartHolder
{	
	DeviceDriverCallbacks * callbacks;
	
	void processNewData();
	void parseSimParams(StringProcessor * sp);
	
public:
	void run();	
	void sendHandshakeReply();
	void sendDeviceHasStopped();
	void sendError(dischargerDevice::Error errno);
	void sendWarning(dischargerDevice::Warning warnno);
	void sendDebug(char * str, int32_t num);
	void sendDebug(char * str);
	void sendSimulationData();
	void sendCharacteristicData(uint8_t id, int16_t mV, int16_t I);
	void sendCharacteristicDone();
	void sendDeviceInfo();
	void setDeviceId(uint8_t id);
	
	void setCallbacks(DeviceDriverCallbacks * callbacks) {
		this->callbacks = callbacks;
	}
	
	friend class Discharger;
}; //DeviceDriver

extern DeviceDriver deviceDriver;

#endif //__DEVICEDRIVER_H__
