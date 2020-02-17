/* 
* SafetyGuard.cpp
*
* Created: 08.12.2019 19:25:50
* Author: domin
*/

#include "SimulationData.h"
#include "SafetyGuard.h"
#include "Millis.h"
#include "Led.h"

void SafetyGuard::init()
{
	STP_BTN_DDR = (STP_BTN_DDR & ~(1 << STP_BTN));
	STP_BTN_PORT |= (1 << STP_BTN);
	safetyBtn.init(&STP_BTN_PIN, STP_BTN);
} 


void SafetyGuard::run() {
	
	safetyBtn.run();
	if(safetyBtn.isPressed()) {
		SimulationData::logWarning(Device::Warning::SAFETY_BTN_PRESSED);
		led.red().blink();
		_safety_btn_was_pressed = 1;
		_safety_event_start = Millis::get();
		safetyBtn.setHandled();
	}
		
	if(skipThisTime()) return;
	
	if(_safety_btn_was_pressed) {
		if((Millis::get() - _safety_event_start) > SAFETY_BTN_PRESS_TIMEOUT) {
			SimulationData::logError(Device::Error::STOPPED_BY_SAFETY_BTN);
			led.red();
			_safety_btn_was_pressed = 0;
		}
		else {
			if(safetyBtn.isRelesed()) {
				led.green().blink();
				_safety_btn_was_pressed = 0;
			}
		}
		return;
	}
	
	
	
	/*
	
	
	
	static uint8_t handled = 0;
	if((Millis::get() % SAFETY_GUARD_INTERVAL_MS) == 0) {
	
		if(handled == 0) {
			handled = 1;
			review();
		}		
	}	
	else {
		handled = 0;
	}
	
	*/
}

void SafetyGuard::review() {
	/*
	
	static uint8_t tempsArrayIte = 0;
	if(thermometer->isNewValueAvaliable()) {
		
		tempsArray[tempsArrayIte] = thermometer->getTemperature();
		tempsArrayIte = (++tempsArrayIte % TEMPERATURE_ARRAY_SIZE);
		
		uint32_t sum = 0;
		for(uint8_t i = 0; i < TEMPERATURE_ARRAY_SIZE; ++i) {
			sum += tempsArray[i];
		}
		
		if((sum / TEMPERATURE_ARRAY_SIZE) > MAX_TEMPERAUTRE_mCE1) {
			
			if(deviceError == Device::Error::DEVICE_STARTED) {
				deviceError = Device::Error::STOPPED_RADIATOR_TEMP_TOO_HIGH;
				//LEDS_OFF;
				//LED_ON(LED_RED);
				deviceStopRequest();	
			}
		}
	}
	
	static uint8_t stpPressesCounter = 0;
	if(STP_PRESSED) {
		if(stpPressesCounter == 0) {
			//LEDS_OFF;
			//LED_ON(LED_BLUE);
			
			if(deviceError != Device::Error::DEVICE_STARTED) reset();
		}
		if(stpPressesCounter == STP_BTN_PRESSED_N) {
			//LEDS_OFF;
			//LED_ON(LED_RED);
			deviceError = Device::Error::STOPPED_BY_SAFETY_BTN;
			deviceStopRequest();
		}
		++stpPressesCounter;
	}
	else if(stpPressesCounter != 0) {
		
		stpPressesCounter = 0;
		if(deviceError == Device::Error::DEVICE_STARTED) {
			//LEDS_OFF;
			//LED_ON(LED_GREEN);
		}
		
	}
	*/
}
