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

#define DAC_VREF_mV 5000
#define DAC_MAX 0x1000

#define EPS 1

#define MAX_VOLT_mV 5000
#define MAX_CURRENT 300 // 300 = 30A
#define MIN_CURRENT 9
#define VOLT_DELTA_mV 100
#define CURR_TAB_SIZE (MAX_VOLT_mV / VOLT_DELTA_mV)
#define GET_VOLT(id) (id * VOLT_DELTA_mV)

class CurrentDriver
{
	struct Currents
	{
		uint16_t _tab_[CURR_TAB_SIZE] = { 0 };
		uint8_t back = 0xFF;

		uint16_t & operator[](uint8_t id) { return _tab_[id]; }

	} currents;

	struct LastParams
	{
		int16_t volt = 0,
		reqCurr = 0,
		simCurr = 0;

	} lastParams;
	uint8_t setupFinished = 0;

public:
	CurrentDriver() {};
	~CurrentDriver() {};

	uint16_t getCurrentFormADC(uint16_t adcCurrent);
	uint16_t getMillivoltsFromDAC(uint16_t dacVolt);
	uint16_t getDACFromMillivolts(uint16_t millivolts);

	void setSimulatedCurrent(uint16_t current);
	uint16_t getEstimatedMillivolts(int16_t requestedCurrent);

private:

	uint8_t getLowerVoltIdForCurr(int16_t curr) {
		if (curr >= MAX_CURRENT)
		return (currents.back - 1);
		for (uint8_t i = 0; i < currents.back; ++i) {
			if (currents[i + 1] > curr && currents[i] <= curr) {
				return i;
			}
		}
		return 0;
	}


}; //CurrentDriver

#endif //__CURRENTDRIVER_H__
