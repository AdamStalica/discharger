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
#include "DrivingData.h"

#define M_CURRENT_SAMPLES 5

class SimulationData {

	DrivingData drivingData;
	int16_t mCurrent[M_CURRENT_SAMPLES];
	uint8_t mCurrId = 0;
	uint16_t mBLV = 0xFFFF,
		mBLT = 0xFFFF,
		mBRV = 0xFFFF,
		mBRT = 0xFFFF,
		mHST = 0xFFFF;

public:

	uint8_t isSimulationInProgress() {
		return drivingData.id != 0xFFFF;
	}
	
	void clear() {
		for(uint8_t i = 0; i < M_CURRENT_SAMPLES; ++i)
			mCurrent[i] = 0;
		mBLV = 0xFFFF;
		mBLT = 0xFFFF;
		mBRV = 0xFFFF;
		mBRT = 0xFFFF;
		mHST = 0xFFFF;
		drivingData.clear();
	}

	void setDrivingData(const DrivingData & data) {
		drivingData = data;
	}
	
	void setMeasuredCurrent(int16_t current) {
		mCurrId = (++mCurrId % M_CURRENT_SAMPLES);
		mCurrent[mCurrId] = current;
	}
	
	void setMeasuredBLV(uint16_t blv) {
		mBLV = blv;
	}
	
	void setMeasuredBLT(uint16_t blt) {
		mBLT = blt;
	}
	
	void setMeasuredBRV(uint16_t brv) {
		mBRV = brv;
	}
	
	void setMeasuredBRT(uint16_t brt) {
		mBRT = brt;
	}
	
	void setMeasuredHST(uint16_t hst) {
		mHST = hst;
	}
	
	uint16_t getDrivingId() {
		return drivingData.id;
	}
	
	uint16_t getDrivingCurrent() {
		return drivingData.current;
	}
	
	uint16_t getVoltageLimit() {
		return drivingData.voltLimit;
	}
	
	uint16_t getHeatSinkTempLimit() {
		return drivingData.tempLimit;
	}
	
	int16_t getMeasuredCurrent() {
		return mCurrent[mCurrId];
	}
	
	uint16_t getMeasuredBLV() {
		return mBLV;
	}
	
	uint16_t getMeasuredBLT() {
		return mBLT;
	}
	
	uint16_t getMeasuredBRV() {
		return mBRV;
	}
	
	uint16_t getMeasuredBRT() {
		return mBRT;
	}
	
	uint16_t getMeasuredHST() {
		return mHST;
	}
	
	int16_t getMeasuredCurrentQuantileMean();
};

extern SimulationData simData;

/*
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
	virtual void startCharacteristicDetermination() = 0;
	
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
*/
#endif
