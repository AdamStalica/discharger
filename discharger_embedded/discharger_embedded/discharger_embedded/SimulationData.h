/* 
* SimulationData.h
*
* Created: 15.10.2019 19:25:52
* Author: domin
*/


#ifndef __SIMULATIONDATA_H__
#define __SIMULATIONDATA_H__

#include "UsartHolder.h"

class SimulationData : public UsartHolder
{
	uint16_t currentId, 
			 currentCurrent, 
			 currentTemp;
	uint8_t	 inProgress = 0;
	uint16_t measuredCurrent,
			 measuredBLV,
			 measuredBRV,
			 measuredBLT,
			 measuredBRT;
	char buff[70];

//functions
public:
	SimulationData(unsigned long baudrate, unsigned long fCpu)
		: UsartHolder(baudrate, fCpu)
	{};
	~SimulationData() {};
		
	virtual void aboutToSendNewData() = 0;
	
	uint16_t getCurrentCurrent() { return currentCurrent; }
	uint16_t getCurrentTemp() { return currentTemp; }
	
	void setMeauredCurrent(uint16_t current) { measuredCurrent = current; }
	void setMeauredBLV(uint16_t bLV) { measuredBLV = bLV; }
	void setMeauredBRV(uint16_t bRV) { measuredBRV = bRV; }
	void setMeauredBLT(uint16_t bLT) { measuredBLT = bLT; }
	void setMeauredBRT(uint16_t bRT) { measuredBRT = bRT; }
	void logError(uint8_t errno);
	void run();

private:
	SimulationData( const SimulationData &c );
	SimulationData& operator=( const SimulationData &c );
	void processNewData();
	void sendResponse();
};

#endif
