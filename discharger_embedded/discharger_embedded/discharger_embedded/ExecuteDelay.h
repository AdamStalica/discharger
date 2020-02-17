/*
 * ExecuteDelay.h
 *
 * Created: 17.02.2020 20:59:24
 *  Author: domin
 */ 


#ifndef EXECUTEDELAY_H_
#define EXECUTEDELAY_H_
#include "Millis.h"

class ExecuteDelay {
	uint16_t period_;
	uint8_t canHandle_;
public:
	ExecuteDelay(uint16_t period, uint8_t executeImieditly = 0) {
		period_ = period;
		canHandle_ = executeImieditly;
	}
	
	uint8_t skipThisTime() {
		if((Millis::get() % period_) < (period_ / 2)) {
			if(canHandle_) {
				canHandle_ = 0;
				return 0;
			}
		}
		else canHandle_ = 1;
		return 1;
	}
};


#endif /* EXECUTEDELAY_H_ */