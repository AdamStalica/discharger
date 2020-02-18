/*
 * Led.cpp
 *
 * Created: 17.02.2020 20:00:23
 *  Author: domin
 */ 
#include "Led.h"

Led led;

void Led::setLedBit(uint8_t ledBit) {
	lastBlink_ = blink_;
	lastLedBit_ = ledBit_;
	ledBit_ = ledBit;
	blink_ = 0;
	LED_OFF;
	LED_ON(ledBit);
}

void Led::run() {
	if(!blink_) return;
	if(runDelay.skipThisTime()) return;
			
	if(LED_IS_OFF) {
		LED_ON(ledBit_);
	}
	else {
		LED_OFF;
	}
}

void Led::previousState() {
	blink_ = lastBlink_;
	setLedBit(lastLedBit_);
	blink_ = lastBlink_;
}