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
	static int16_t measuredCurrent;
	static uint16_t voltLimit, 
					radiatorTempLimit,
					measuredBLV,
					measuredBRV,
					measuredBLT,
					measuredBRT,
					measuredHST;
					
	static uint8_t inProgress;
	
	uint16_t currentId = 0, 
			 currentCurrent = 0;
			 
//functions
public:
	SimulationData() {};
	~SimulationData() {};
		
	virtual void simHasStarted() = 0;
	virtual void aboutToSendNewData() = 0;
	virtual void raceivedStopDevice() = 0;
	virtual void communicationEstablished() = 0;
	
	uint16_t getCurrentCurrent() { return currentCurrent; }
	
	void setMeauredCurrent(int16_t current) { measuredCurrent = current; }
	void setBattLeftVolt(uint16_t bLV) { measuredBLV = bLV; }
	void setBattRightVolt(uint16_t bRV) { measuredBRV = bRV; }
	void setBattLeftTemp(uint16_t bLT) { measuredBLT = bLT; }
	void setBattRightTemp(uint16_t bRT) { measuredBRT = bRT; }
	void setHeatSinkTemp(uint16_t RT) { measuredHST = RT; }
	void setDeviceHasStopped();
	
	void sendDeviceHasStopped();
	void run();
	
	static void logError(Device::Error errno) { lastError = errno; }
	static void logWarning(Device::Warning warnNo) { lastWarn = warnNo; }
	
	static uint16_t getVoltageLimit()		{ return voltLimit; }
	static uint16_t getHeatSinkTempLimit()	{ return radiatorTempLimit; }
	static int16_t getMeasuredCurrent()	{ return measuredCurrent; }	
	static uint16_t getBattLeftVolt()		{ return measuredBLV; }
	static uint16_t getBattRightVolt()		{ return measuredBRV; }
	static uint16_t getBattLeftTemp()		{ return measuredBLT; }
	static uint16_t getBattRightTemp()		{ return measuredBRT; }
	static uint16_t getHeatSinkTemp()		{ return measuredHST; }
		
	static uint8_t isSimulationInProgress() { return inProgress; };

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
