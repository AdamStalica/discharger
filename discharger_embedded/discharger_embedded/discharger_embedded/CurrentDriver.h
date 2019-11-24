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


#define F_CPU 10240000UL
#include <util/delay.h>

#define POINTS_SIZE 3

#define DAC_VREF_mV 5000
#define DAC_MAX 0x1000

#define UPPER_MIN_CURRENT_E2mA 10

#define DEFAULT_VOLT_STEP_mV 1000
#define ITERATION_CHANGE_DIV_UNDER_E2mA 50
#define CURRENT_EPS_E3mA 5

#define INTERPOLATION_mV_MAX_DIFFERENCE 3000


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


	uint8_t iterationDiv = 1;
	uint8_t interpolationDiv = 1;

	uint16_t lastEstimatedMillivolts = 0;

	uint16_t currentlyNextCurrent = 0;
	
	SimulationData & uart;

	//functions
	public:
	CurrentDriver(SimulationData & uart_);
	~CurrentDriver();

	uint16_t getCurrentFormADC(uint16_t adcCurrent);
	uint16_t getMillivoltsFromDAC(uint16_t dacVolt);
	uint16_t getDACFromMillivolts(uint16_t millivolts);


	void setSimulatedCurrent(uint16_t current);
	void setCurrentToBeSimulated(uint16_t current);

	uint16_t getEstimatedMillivoltsToBeSet(uint16_t requestedCurrent);

	private:

	uint8_t isInterpolationReady();
	uint16_t getInterpolatedValue(uint16_t x);


}; //CurrentDriver

#endif //__CURRENTDRIVER_H__
