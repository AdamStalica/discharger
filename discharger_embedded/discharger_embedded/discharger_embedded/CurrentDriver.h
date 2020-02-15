/*
* CurrentDriver.h
*
* Created: 21.11.2019 11:31:53
* Author: domin
*/


#ifndef __CURRENTDRIVER_H__
#define __CURRENTDRIVER_H__

#include <avr/io.h>
#include "SimulationData.h"

#define POINTS_SIZE 3

#define DEAFULT_MAX_CURRENT_E2mA 500
#define DAC_VREF_mV 5000
#define DAC_MAX 0x0FFF

#define INTERPOLATION_mV_MAX_DIFFERENCE 3000

#define x0 ((int16_t)chPoints[0].current)
#define x1 ((int16_t)chPoints[1].current)
#define x2 ((int16_t)chPoints[2].current)
#define y0 ((int16_t)chPoints[0].millivolt)
#define y1 ((int16_t)chPoints[1].millivolt)
#define y2 ((int16_t)chPoints[2].millivolt)


class CurrentDriver
{
	struct simulatedPoint {
		uint16_t current = 0;
		uint16_t millivolt = 0;
	};

	enum pointsEnum {
		MIN,
		MIDDLE,
		MAX
	};
	simulatedPoint chPoints[3];
	
	uint16_t currentlySimulatedCurrent = 0;
	uint16_t lastEstimatedMillivolts = 0;
	
	
	uint16_t getInterpolatedValue(int16_t x);
	
	public:
	CurrentDriver();
	~CurrentDriver() {};

	uint16_t getCurrentFormADC(uint16_t adcCurrent);
	uint16_t getMillivoltsFromDAC(uint16_t dacVolt);
	uint16_t getDACFromMillivolts(uint16_t millivolts);
	int16_t getCurrentFromDifferentianlADC(uint16_t diffAdc);

	void setMaxCurrent(uint16_t max);
	void setSimulatedCurrent(uint16_t current);

	uint16_t getEstimatedMillivoltsToBeSet(uint16_t requestedCurrent);
};

#endif //__CURRENTDRIVER_H__
