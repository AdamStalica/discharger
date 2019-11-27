/*
* CurrentDriver.cpp
*
* Created: 21.11.2019 11:31:53
* Author: domin
*/


#include "CurrentDriver.h"

CurrentDriver::CurrentDriver()
{
	chPoints[pointsEnum::MIDDLE].millivolt = 3502;
	chPoints[pointsEnum::MIDDLE].current = 351;
	chPoints[pointsEnum::MAX].millivolt = DAC_VREF_mV;
	chPoints[pointsEnum::MAX].current = DEAFULT_MAX_CURRENT_E2mA;
}

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
	return (uint32_t(dacVolt * DAC_VREF_mV) / DAC_MAX);
}

uint16_t CurrentDriver::getDACFromMillivolts(uint16_t millivolts) {
	return (uint32_t(millivolts) * DAC_MAX / DAC_VREF_mV);
}

void CurrentDriver::setMaxCurrent(uint16_t max) {
	chPoints[pointsEnum::MAX].current = max;
}

void CurrentDriver::setSimulatedCurrent(uint16_t current) {
	if (current > 0 && current < chPoints[pointsEnum::MAX].current) {
		
		chPoints[pointsEnum::MIDDLE].current = current;
		chPoints[pointsEnum::MIDDLE].millivolt = lastEstimatedMillivolts;
	}
	currentlySimulatedCurrent = current;
} 

uint16_t CurrentDriver::getEstimatedMillivoltsToBeSet(uint16_t requestedCurrent) {

	uint16_t estimatedMillivolt = getInterpolatedValue(
		requestedCurrent
	);
	// currentlySimulatedCurrent + (requestedCurrent - currentlySimulatedCurrent) / interpolationDiv

	if (requestedCurrent == 0) estimatedMillivolt = 0;
	
	lastEstimatedMillivolts = estimatedMillivolt;
	if (estimatedMillivolt >= DAC_VREF_mV) estimatedMillivolt = DAC_VREF_mV - 1;

	return estimatedMillivolt;
}

uint16_t CurrentDriver::getInterpolatedValue(int16_t x) {

	float xx0 = (x - x0);
	float xx1 = (x - x1);
	float xx2 = (x - x2);
	int16_t x1x0 = (x1 - x0);
	int16_t x1x2 = (x1 - x2);
	int16_t x2x0 = (x2 - x0);
	int16_t x2x1 = (x2 - x1);

	int16_t L1 = int16_t(y1 * ((xx0 / x1x0) * (xx2 / x1x2)));
	int16_t L2 = int16_t(y2 * ((xx0 / x2x0) * (xx1 / x2x1)));
	
	return uint16_t(L1 + L2);
}