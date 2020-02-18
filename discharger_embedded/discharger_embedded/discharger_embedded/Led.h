/*
 * Led.h
 *
 * Created: 17.02.2020 19:10:12
 *  Author: domin
 */ 


#ifndef LED_H_
#define LED_H_

#include "GlobalDefs.h"
#include "ExecuteDelay.h"

#define LED_OFF (LED_PORT |= (1 << LED_RED) | (1 << LED_GREEN) | (1 << LED_BLUE))
#define LED_ON(LED_) (LED_PORT = (LED_PORT & ~(1 << LED_)))
#define LED_IS_OFF ( \
	(LED_PORT & ((1 << LED_RED) | (1 << LED_GREEN) | (1 << LED_BLUE))) == \
	((1 << LED_RED) | (1 << LED_GREEN) | (1 << LED_BLUE)) \
) 

class Led {
		
public: 
	Led() : runDelay(BLINKING_PERIOD) {};

	void init() {
		LED_DDR |= (1 << LED_RED) | (1 << LED_GREEN) | (1 << LED_BLUE);
		LED_OFF;
	}
	void blink() { blink_ = 1; };
	void run();
	void previousState();
	
	Led & green() {
		setLedBit(LED_GREEN);
		return *this;	
	}
	Led & blue() {
		setLedBit(LED_BLUE);
		return *this;
	}
	Led & red() {
		setLedBit(LED_RED);
		return *this;
	}

private:
	void setLedBit(uint8_t ledBit);
	uint8_t blink_;
	uint8_t lastBlink_;
	uint8_t ledBit_;
	uint8_t lastLedBit_;
	ExecuteDelay runDelay;
};

extern Led led;

#endif /* LED_H_ */