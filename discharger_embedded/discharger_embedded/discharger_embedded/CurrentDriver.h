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

#endif //__CURRENTDRIVER_H__