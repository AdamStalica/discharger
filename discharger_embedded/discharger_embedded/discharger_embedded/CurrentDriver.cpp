/*
* CurrentDriver.cpp
*
* Created: 21.11.2019 11:31:53
* Author: domin
*/


#include "CurrentDriver.h"
#include <stdlib.h>

/**
*	adcVolt 0..1023
*	I = adcVolt*2 + 7 [E2mA]
*/
uint16_t CurrentDriver::getCurrentFormADC(uint16_t adcVolt) {
	return (adcVolt ? (adcVolt * 2 + 7) : 0);
}

/**
*	dac 12 bits
*	U = dacVolt * DAC_VREF_mV / 2 ^ 12
*/
uint16_t CurrentDriver::getMillivoltsFromDAC(uint16_t dacVolt) {
	return (uint32_t(dacVolt) * DAC_VREF_mV / DAC_MAX);
}

uint16_t CurrentDriver::getDACFromMillivolts(uint16_t millivolts) {
	return (uint32_t(millivolts) * DAC_MAX / DAC_VREF_mV);
}

void CurrentDriver::setSimulatedCurrent(uint16_t current) {
	
	if (!setupFinished) {
		currents[currents.back] = current;
		if (current > MAX_CURRENT || GET_VOLT(currents.back) == MAX_VOLT_mV) {
			setupFinished = 1;
		}
		return;
	}

	lastParams.simCurr = current;
}

uint16_t CurrentDriver::getEstimatedMillivolts(int16_t requestedCurrent) {
	
	if (!setupFinished) {
		return GET_VOLT(++currents.back);
	}

	uint8_t u1Id = getLowerVoltIdForCurr(requestedCurrent);
	uint8_t isNewVal = (u1Id != (lastParams.volt / VOLT_DELTA_mV));

	if (((currents[u1Id] + EPS) >= requestedCurrent && (currents[u1Id] - EPS) <= requestedCurrent) || requestedCurrent < MIN_CURRENT) {
		lastParams.volt = GET_VOLT(u1Id);
	}
	else {
		int16_t deltaCurr = currents[u1Id + 1] - currents[u1Id];

		if (isNewVal) {
			int16_t deltaReqCurr = requestedCurrent - currents[u1Id];
			int16_t deltaReqVolt = (VOLT_DELTA_mV * deltaReqCurr) / deltaCurr;
			lastParams.volt = (GET_VOLT(u1Id) + deltaReqVolt);
		}
		else {
			int16_t deltaSim = requestedCurrent - lastParams.simCurr;
			if (abs(deltaSim) > EPS) {
				int16_t deltaReqCurr = lastParams.reqCurr - currents[u1Id];
				int16_t deltaReqVolt = (VOLT_DELTA_mV * deltaReqCurr) / deltaCurr;

				if (deltaSim > 0) {
					deltaReqVolt = VOLT_DELTA_mV - deltaReqVolt;
					deltaReqCurr = deltaCurr - deltaReqCurr;
				}

				lastParams.volt += ((deltaReqVolt * deltaSim) / deltaReqCurr);
			}
		}
	}
	lastParams.reqCurr = requestedCurrent;
	return lastParams.volt;
}