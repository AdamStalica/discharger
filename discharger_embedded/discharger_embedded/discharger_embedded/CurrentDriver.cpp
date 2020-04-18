/*
* CurrentDriver.cpp
*
* Created: 21.11.2019 11:31:53
* Author: domin
*/
/*

#include "CurrentDriver.h"
#include <stdlib.h>

/**
*	adcVolt 0..1023
*	I = adcVolt * 0.19 - 0.74 [A] -> adcVolt * 1.9 - 7.4 [E2mA]
*
int16_t CurrentDriver::getCurrentFormADC(int16_t adcVolt) {
	if(adcVolt == 0) return 0;
	int16_t current = adcVolt;
	current *= 19;
	current -= 74;
	current += current < 0 ? -5 : 5;
	current /= 10;
	return current;
}

#ifdef INTERPOLATION

CurrentDriver::CurrentDriver() {
	chPoints[MIN].millivolt = 0;
	chPoints[MIN].current = 0;
	chPoints[MIDDLE].millivolt = SIM_MAX_VOLT / 2;
	chPoints[MIDDLE].current = SIM_MAX_CURRENT / 2;
	chPoints[MAX].millivolt = SIM_MAX_VOLT;
	chPoints[MAX].current = SIM_MAX_CURRENT;
}

void CurrentDriver::setSimulatedCurrent(int16_t current) {
	uint16_t diff_abs = abs(current - lastParams.reqCurr);
	if (diff_abs > SIM_INTPOL_CURR_MAX_DIFF && !noInterpolation) {
		turnOffInterpolation();
		return;
	}

	if (current <= SIM_EPS) return;

	uint8_t index;
	if (current <= SIM_INTPOL_P1_MAX) {
		index = PointsEnum::MIN;
	}
	else if (current >= SIM_INTPOL_P3_MIN) {
		index = PointsEnum::MAX;
	}
	else {
		index = PointsEnum::MIDDLE;
	}

	lastParams.simCurr = current;
	chPoints[index].current = current;
	chPoints[index].millivolt = lastParams.volt;
}

uint16_t CurrentDriver::getEstimatedMillivolts(int16_t requestedCurrent) {
	lastParams.reqCurr = requestedCurrent;
	if (requestedCurrent == 0) return 0;
	if (requestedCurrent < SIM_INTPOL_P1_MAX) return 5;

	uint16_t delta_abs = abs(requestedCurrent - lastParams.simCurr);

	if (delta_abs <= SIM_EPS) return lastParams.volt;

	if (noInterpolation) {
		if (noInterpolCounter < SIM_INTPOL_REC_CYC_NUM && lastParams.simCurr < SIM_MAX_CURRENT) {
			++noInterpolCounter;
			lastParams.volt += SIM_INTPOL_DEFAULT_SETEP;
			return lastParams.volt;
		}
		else {
			turnOnInterpolation();
		}
	}

	int16_t t = getInterpolatedValue(requestedCurrent);
	if (delta_abs <= SIM_PURE_INTPOL_MIN) {
		t = lastParams.volt + (t - lastParams.volt) / 2;
	}
	lastParams.volt = t;

	if (lastParams.volt > chPoints[MAX].millivolt && requestedCurrent < chPoints[MAX].current) {
		turnOffInterpolation();
	}

	return lastParams.volt;
}

uint16_t CurrentDriver::getInterpolatedValue(int16_t x) {

	float xx0 = (x - chPoints[0].current);
	float xx1 = (x - chPoints[1].current);
	float xx2 = (x - chPoints[2].current);
	int16_t x0x1 = (chPoints[0].current - chPoints[1].current);
	int16_t x0x2 = (chPoints[0].current - chPoints[2].current);
	int16_t x1x0 = (chPoints[1].current - chPoints[0].current);
	int16_t x1x2 = (chPoints[1].current - chPoints[2].current);
	int16_t x2x0 = (chPoints[2].current - chPoints[0].current);
	int16_t x2x1 = (chPoints[2].current - chPoints[1].current);

	int16_t L0 = (chPoints[0].millivolt * ((xx1 / x0x1) * (xx2 / x0x2)));
	int16_t L1 = (chPoints[1].millivolt * ((xx0 / x1x0) * (xx2 / x1x2)));
	int16_t L2 = (chPoints[2].millivolt * ((xx0 / x2x0) * (xx1 / x2x1)));

	return abs(L0 + L1 + L2);
}

void CurrentDriver::turnOffInterpolation() {
	noInterpolation = 1;
	noInterpolCounter = 0;
	lastParams.volt = 0;
}

void CurrentDriver::turnOnInterpolation() {
	noInterpolation = 0;
}

#else

CurrentDriver::CurrentDriver() {}

void CurrentDriver::setSimulatedCurrent(int16_t current) {
	if (!setupFinished) {
		currents[currents.back] = current;
		if (current > SIM_MAX_CURRENT || SIM_ITE_GET_VOLT(currents.back) == SIM_MAX_VOLT) {
			setupFinished = 1;
		}
		return;
	}
	lastParams.simCurr = current;
}

uint16_t CurrentDriver::getEstimatedMillivolts(int16_t requestedCurrent) {
	if (!setupFinished) {
		return SIM_ITE_GET_VOLT(++currents.back);
	}

	uint8_t u1Id = getLowerVoltIdForCurr(requestedCurrent);
	uint8_t isNewVal = (u1Id != (lastParams.volt / SIM_ITE_VOLT_DELTA));

	if (((currents[u1Id] + SIM_EPS) >= requestedCurrent && (currents[u1Id] - SIM_EPS) <= requestedCurrent) ||
	requestedCurrent < SIM_MIN_CURRENT) {
		lastParams.volt = SIM_ITE_GET_VOLT(u1Id);
	}
	else {
		int16_t deltaCurr = currents[u1Id + 1] - currents[u1Id];

		if (isNewVal) {
			int16_t deltaReqCurr = requestedCurrent - currents[u1Id];
			int16_t deltaReqVolt = (SIM_ITE_VOLT_DELTA * deltaReqCurr) / deltaCurr;
			lastParams.volt = (SIM_ITE_GET_VOLT(u1Id) + deltaReqVolt);
		}
		else {
			int16_t deltaSim = requestedCurrent - lastParams.simCurr;
			if (abs(deltaSim) > SIM_EPS) {
				int16_t deltaReqCurr = lastParams.reqCurr - currents[u1Id];
				int16_t deltaReqVolt = (SIM_ITE_VOLT_DELTA * deltaReqCurr) / deltaCurr;

				if (deltaSim > 0) {
					deltaReqVolt = SIM_ITE_VOLT_DELTA - deltaReqVolt;
					deltaReqCurr = deltaCurr - deltaReqCurr;
				}

				lastParams.volt += ((deltaReqVolt * deltaSim) / deltaReqCurr);
			}
		}
	}
	lastParams.reqCurr = requestedCurrent;
	return lastParams.volt;
}

uint8_t CurrentDriver::getLowerVoltIdForCurr(int16_t curr) {
	if (curr >= SIM_MAX_CURRENT)
	return (currents.back - 1);
	for (uint8_t i = 0; i < currents.back; ++i) {
		if (currents[i + 1] > curr && currents[i] <= curr) {
			return i;
		}
	}
	return 0;
}

#endif //INTERPOLATION
*/