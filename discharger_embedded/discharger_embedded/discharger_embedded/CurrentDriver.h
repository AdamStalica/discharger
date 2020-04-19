/*
* CurrentDriver.h
*
* Created: 21.11.2019 11:31:53
* Author: domin
*/


#ifndef __CURRENTDRIVER_H__
#define __CURRENTDRIVER_H__

#include <avr/io.h>
#include "GlobalDefs.h"

#include "GlobalDefs.h"
#include "ChticData.h"

class CurrentDriver
{
	ChticData * chData;

	//lastReqCurrent = -1,
	int16_t lastMv = -1,
	lastMeasuredCurrent = -1;

	int16_t computeCorrection() {
		if (lastMv == -1 || lastMeasuredCurrent == -1)
			return 0;
		if (chData->moveRangeTo(lastMeasuredCurrent) == CHTIC_TOO_HIGH_CURRENT)
			return 0;
		int16_t correction = (lastMv - computeMv(lastMeasuredCurrent));
		correction *= CURR_DRIVER_CORRECTION_RATIO;
		correction += 5;
		correction /= 10;
		return correction;
	}
	
	int16_t computeMv(int16_t current) {
		int32_t result = current - chData->getRangeBeginCurrent();
		result *= CHTIC_NON_ZERO_STEP;
		result /= (chData->getRangeEndCurrent() - chData->getRangeBeginCurrent());
		result += chData->getRangeBeginMv();
		return result;
	}

public:
	static int16_t getCurrentFormADC(int16_t adcVolt) {
		if(adcVolt == 0) return 0;
		int16_t current = adcVolt;
		current *= 19;
		current -= 74;
		current += current < 0 ? -5 : 5;
		current /= 10;
		return current;
	}

	void setChticData(ChticData * chData) {
		this->chData = chData;
	}

	void setMeasuredCurrent(int16_t current) {
		lastMeasuredCurrent = current;
	}

	int16_t getEstimatedMillivolts(int16_t reqCurrent, uint8_t useCorrection = 1) {
		int16_t correction = (useCorrection == 1 ? computeCorrection() : 0);

		if (chData->moveRangeTo(reqCurrent) == CHTIC_TOO_HIGH_CURRENT)
			return CURR_DRIVER_ERROR;
		
		int32_t result = computeMv(reqCurrent);
		result += correction;

		lastMeasuredCurrent = -1;
		lastMv = result;
		return result;
	}
/*
	
	int16_t getEstimatedMillivolts(int16_t reqCurrent) {
		int16_t correction = computeCorrection();

		if (chData->moveRangeTo(reqCurrent) == CHTIC_TOO_HIGH_CURRENT)
			return (CURR_DRIVER_ERROR + 1);

		int16_t interpolated = getInterpolatedValue(reqCurrent);

		lastMv = interpolated;
		
		return interpolated;
	}

private:

	uint16_t getInterpolatedValue(uint16_t x) {

		#define x0 (lastMeasuredCurrent)
		#define y0 (lastMv)
		#define x1 (chData->getRangeBeginCurrent())
		#define y1 (chData->getRangeBeginMv())
		#define x2 (chData->getRangeEndCurrent())
		#define y2 (chData->getRangeEndMv())

		float xx0 = (x - x0);
		float xx1 = (x - x1);
		float xx2 = (x - x2);
		int16_t x0x1 = (x0 - x1);
		int16_t x0x2 = (x0 - x2);
		int16_t x1x0 = (x1 - x0);
		int16_t x1x2 = (x1 - x2);
		int16_t x2x0 = (x2 - x0);
		int16_t x2x1 = (x2 - x1);

		int16_t L0 = (y0 * ((xx1 / x0x1) * (xx2 / x0x2)));
		int16_t L1 = (y1 * ((xx0 / x1x0) * (xx2 / x1x2)));
		int16_t L2 = (y2 * ((xx0 / x2x0) * (xx1 / x2x1)));

		return abs(L0 + L1 + L2);
	}
*/
};


/*
#ifdef INTERPOLATION
#define SIM_INTPOL_POINT_NUM 3
#define SIM_INTPOL_REC_CYC_NUM 10
#define SIM_INTPOL_DEFAULT_SETEP 300
#define SIM_INTPOL_CURR_MAX_DIFF 50
#define SIM_PURE_INTPOL_MIN 10
#define SIM_INTPOL_P1_MAX 10
#define SIM_INTPOL_P3_MIN (SIM_MAX_CURRENT - 20)
#else
#define SIM_ITE_VOLT_DELTA 100
#define SIM_ITE_TAB_SIZE (SIM_MAX_VOLT / SIM_ITE_VOLT_DELTA)
#define SIM_ITE_GET_VOLT(id) (id * SIM_ITE_VOLT_DELTA)
#endif //INTERPOLATION

class CurrentDriver {
	public:
	CurrentDriver();
	~CurrentDriver() {};

	static int16_t getCurrentFormADC(int16_t adcCurrent);

	void setSimulatedCurrent(int16_t current);
	uint16_t getEstimatedMillivolts(int16_t requestedCurrent);

	private:
	struct LastParams
	{
		int16_t volt = 0,
		reqCurr = 0,
		simCurr = 0;

	} lastParams;

	#ifdef INTERPOLATION
	struct simulatedPoint {
		int16_t current = 0;
		int16_t millivolt = 0;
	};

	enum PointsEnum {
		MIN,
		MIDDLE,
		MAX
	};
	simulatedPoint chPoints[SIM_INTPOL_POINT_NUM];
	uint8_t noInterpolation = 0;
	uint8_t noInterpolCounter = 0;

	uint16_t getInterpolatedValue(int16_t x);
	void turnOffInterpolation();
	void turnOnInterpolation();
	#else
	struct Currents
	{
		int16_t _tab_[SIM_ITE_TAB_SIZE] = { 0 };
		uint8_t back = 0xFF;

		int16_t & operator[](uint8_t id) { return _tab_[id]; }

	} currents;
	uint8_t setupFinished = 0;

	uint8_t getLowerVoltIdForCurr(int16_t curr);
	#endif //INTERPOLATION

}; //CurrentDriver
*/
#endif //__CURRENTDRIVER_H__