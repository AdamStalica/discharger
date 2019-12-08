/* 
* SafetyGuard.cpp
*
* Created: 08.12.2019 19:25:50
* Author: domin
*/


#include "SafetyGuard.h"
#include "MillisecsCounter.h"

#define LEDS_OFF (LED_PORT |= (1 << LED_RED) | (1 << LED_GREEN) | (1 << LED_BLUE))
#define LED_ON(LED_) (LED_PORT = (LED_PORT & ~(1 << LED_)))

#define STP_PRESSED ((STP_BTN_PIN & (1 << STP_BTN)) == 0)

#define STP_BTN_PRESSED_N (STOP_BTN_DURATION_MS / SAFETY_GUARD_INTERVAL_MS)

void SafetyGuard::init()
{
	LED_DDR |= (1 << LED_RED) | (1 << LED_GREEN) | (1 << LED_BLUE);
	LEDS_OFF;
	LED_ON(LED_GREEN);
	STP_BTN_DDR = (STP_BTN_DDR & ~(1 << STP_BTN));
	STP_BTN_PORT |= (1 << STP_BTN);
} 


void SafetyGuard::run() {
	
	static uint8_t handled = 0;
	if((MillisecsCounter::getMillisecs() % SAFETY_GUARD_INTERVAL_MS) == 0) {
	
		if(handled == 0) {
			handled = 1;
			review();
		}		
	}	
	else {
		handled = 0;
	}
}

void SafetyGuard::review() {
	
	static uint8_t tempsArrayIte = 0;
	if(thermometer->isNewValueAvaliable()) {
		
		tempsArray[tempsArrayIte] = thermometer->getTemperature();
		tempsArrayIte = (++tempsArrayIte % TEMPERATURE_ARRAY_SIZE);
		
		uint32_t sum = 0;
		for(uint8_t i = 0; i < TEMPERATURE_ARRAY_SIZE; ++i) {
			sum += tempsArray[i];
		}
		
		if((sum / TEMPERATURE_ARRAY_SIZE) > MAX_TEMPERAUTRE_mCE1) {
			
			if(deviceError == DeviceError::DEVICE_STARTED) {
				deviceError = DeviceError::STOPPED_OVER_TEMP;
				LEDS_OFF;
				LED_ON(LED_RED);
				dangerEvent();	
			}
		}
	}
	
	static uint8_t stpPressesCounter = 0;
	if(STP_PRESSED) {
		if(stpPressesCounter == 0) {
			LEDS_OFF;
			LED_ON(LED_BLUE);
			
			if(deviceError != DeviceError::DEVICE_STARTED) reset();
		}
		if(stpPressesCounter == STP_BTN_PRESSED_N) {
			LEDS_OFF;
			LED_ON(LED_RED);
			deviceError = DeviceError::STOPPED_BY_BTN;
			dangerEvent();
		}
		++stpPressesCounter;
	}
	else if(stpPressesCounter != 0) {
		
		stpPressesCounter = 0;
		if(deviceError == DeviceError::DEVICE_STARTED) {
			LEDS_OFF;
			LED_ON(LED_GREEN);
		}
		
	}
	
}
