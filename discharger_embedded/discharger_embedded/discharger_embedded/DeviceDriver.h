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
	void sendError(Device::Error errno);
	void sendWarning(Device::Warning warnno);
	void sendDebug(char * str, int32_t num);
	void sendDebug(char * str);
	void sendSimulationData();
	void sendSimulationData(
		uint16_t id, 
		int16_t I, 
		uint16_t bLV, 
		uint16_t bLT, 
		uint16_t bRV, 
		uint16_t bRT, 
		uint16_t HST
	);
	void sendCharacteristicData(uint8_t id, int16_t mV, int16_t I);
	void sendCharacteristicDone();
	
	void setCallbacks(DeviceDriverCallbacks * callbacks) {
		this->callbacks = callbacks;
	}
	
	//friend void Discharger::isrUsart0RxHandler();
	//friend void Discharger::isrUsart0UdreHandler();
	friend class Discharger;
}; //DeviceDriver

extern DeviceDriver deviceDriver;

#endif //__DEVICEDRIVER_H__
