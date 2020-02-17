/* 
* SimulationData.h
*
* Created: 15.10.2019 19:25:52
* Author: domin
*/


#ifndef __SIMULATIONDATA_H__
#define __SIMULATIONDATA_H__

#include "UsartHolder.h"
#include "GlobalDefs.h"

class SimulationData : public UsartHolder
{
	static Device::Error lastError;
	static Device::Warning lastWarn;
	static uint16_t voltLimit, 
					radiatorTempLimit,
					measuredCurrent,
					measuredBLV,
					measuredBRV,
					measuredBLT,
					measuredBRT,
					measuredRT;
	
	uint16_t currentId = 0, 
			 currentCurrent = 0;
	uint8_t	 inProgress = 0;
	uint8_t _comm_established = 0;

//functions
public:
	SimulationData() {};
	~SimulationData() {};
		
	virtual void aboutToSendNewData() = 0;
	virtual void stopDevice() = 0;
	virtual void communicationEstablished() = 0;
	
	uint16_t getCurrentCurrent() { return currentCurrent; }
	
	void setMeauredCurrent(uint16_t current) { measuredCurrent = current; }
	void setBattLeftVolt(uint16_t bLV) { measuredBLV = bLV; }
	void setBattRightVolt(uint16_t bRV) { measuredBRV = bRV; }
	void setBattLeftTemp(uint16_t bLT) { measuredBLT = bLT; }
	void setBattRightTemp(uint16_t bRT) { measuredBRT = bRT; }
	void setRadiatorTemp(uint16_t RT) { measuredRT = RT; }
	
	void sendDeviceHasStopped();
	uint8_t simulationInProgress();
	void run();
	
	static void logError(Device::Error errno) { lastError = errno; }
	static void logWarning(Device::Warning warnNo) { lastWarn = warnNo; }
	
	static uint16_t getVoltageLimit()		{ return voltLimit; }
	static uint16_t getRadiatorTempLimit()	{ return radiatorTempLimit; }
	static uint16_t getMeasuredCurrent()	{ return measuredCurrent; }	
	static uint16_t getBattLeftVolt()		{ return measuredBLV; }
	static uint16_t getBattRightVolt()		{ return measuredBRV; }
	static uint16_t getBattLeftTemp()		{ return measuredBLT; }
	static uint16_t getBattRightTemp()		{ return measuredBRT; }
	static uint16_t getRadiatorTemp()		{ return measuredRT; }

private:
	SimulationData( const SimulationData &c );
	SimulationData& operator=( const SimulationData &c );
	void processNewData();
	void sendResponse();
	void sendHandshake();
	void sendError();
	void sendWarning();
	
	uint8_t doesStrContainParam(char * str, char * param);
	uint16_t getUIntValueFromStr(char * str, char * name);
};

#endif
