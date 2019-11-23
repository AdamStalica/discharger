/*
* CurrentDriver.cpp
*
* Created: 21.11.2019 11:31:53
* Author: domin
*/


#include "CurrentDriver.h"


CurrentDriver::CurrentDriver()
{
	chPoints[pointsEnum::MIN].millivolt = 10;
	chPoints[pointsEnum::MIN].current = 1;
	chPoints[pointsEnum::MIDDLE].millivolt = 1250;
	chPoints[pointsEnum::MIDDLE].current = 1003;
	chPoints[pointsEnum::MAX].millivolt = 2500;
	chPoints[pointsEnum::MAX].current = 2007;
}

CurrentDriver::~CurrentDriver()
{
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
	return (uint32_t(millivolts * DAC_MAX) / DAC_VREF_mV);
}

void CurrentDriver::setSimulatedCurrent(uint16_t current) {
	if (current > 0) {
		uint8_t index;

		if (current < UPPER_MIN_CURRENT_E2mA) {
			index = pointsEnum::MIN;
		}
		else if (current > chPoints[pointsEnum::MAX].current) {
			index = pointsEnum::MAX;
		}
		else {
			index = pointsEnum::MIDDLE;
		}
		chPoints[index].current = current;
		chPoints[index].millivolt = lastEstimatedMillivolts;
	}
	currentlySimulatedCurrent = current;
	iterationDiv = 1;
	interpolationDiv = 4;
}

void CurrentDriver::setCurrentToBeSimulated(uint16_t current) {
	currentlyNextCurrent = current;


	if (!isInterpolationReady()) {
		
	}
}

uint16_t CurrentDriver::getEstimatedMillivoltsToBeSet(uint16_t requestedCurrent) {
	uint16_t estimatedMillivolt = 0;

	if (isInterpolationReady()) {
		estimatedMillivolt = getInterpolatedValue(
		currentlySimulatedCurrent + (requestedCurrent - currentlySimulatedCurrent) / interpolationDiv
		);

		if (requestedCurrent == 0) estimatedMillivolt = 0;

		interpolationDiv = (interpolationDiv == 1 ? interpolationDiv : (interpolationDiv / 2));
	}
	else {
		uint16_t delta = currentlySimulatedCurrent > requestedCurrent ? (currentlySimulatedCurrent - requestedCurrent) : (requestedCurrent - currentlySimulatedCurrent);
		if (delta < ITERATION_CHANGE_DIV_UNDER_E2mA) {
			iterationDiv *= 2;
		}
		if (delta >= CURRENT_EPS_E3mA) {
			if (currentlySimulatedCurrent < requestedCurrent) {
				estimatedMillivolt = lastEstimatedMillivolts + DEFAULT_VOLT_STEP_mV / interpolationDiv;
			}
			else {
				estimatedMillivolt = lastEstimatedMillivolts - DEFAULT_VOLT_STEP_mV / interpolationDiv;
			}
		}
	}
	lastEstimatedMillivolts = estimatedMillivolt;
	return estimatedMillivolt;
}

uint8_t CurrentDriver::isInterpolationReady() {
	return (
	chPoints[pointsEnum::MIN].current != 0 &&
	chPoints[pointsEnum::MIDDLE].current != 0 &&
	chPoints[pointsEnum::MAX].current != 0
	);
}

uint16_t CurrentDriver::getInterpolatedValue(uint16_t x) {

	uint16_t y = 0;
	for (uint8_t i = 0; i < POINTS_SIZE; ++i) {
		float t = 1;

		for (uint8_t j = 0; j < POINTS_SIZE; ++j) {
			if (i != j) {
				t *= (float((int16_t)x - (int16_t)chPoints[j].current) / ((int16_t)chPoints[i].current - (int16_t)chPoints[j].current));
			}
		}

		y += uint16_t(t * chPoints[i].millivolt);
	}
	return y;
}