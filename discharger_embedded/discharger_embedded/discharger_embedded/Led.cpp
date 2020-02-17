/*
 * Led.cpp
 *
 * Created: 17.02.2020 20:00:23
 *  Author: domin
 */ 
#include "Led.h"

Led led;

void Led::setLedBit(uint8_t ledBit) {
	ledBit_ = ledBit;
	blink_ = 0;
	LED_OFF;
	LED_ON(ledBit);
}

void Led::run() {
	if(!blink_) return;
	static uint8_t canHandle = 1;
	if((Millis::get() % BLINKING_PERIOD) < 50) {
		if(canHandle) {
			if(LED_IS_OFF) {
				LED_ON(ledBit_);
			}
			else {
				LED_OFF;
			}
			canHandle = 0;
		}
	}
	else {
		canHandle = 1;
	}
}