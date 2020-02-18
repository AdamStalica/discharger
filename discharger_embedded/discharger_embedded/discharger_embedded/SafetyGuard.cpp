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

Device::Error SafetyGuard::error = Device::Error::NO_ERROR;

void SafetyGuard::init()
{
	STP_BTN_DDR = (STP_BTN_DDR & ~(1 << STP_BTN));
	STP_BTN_PORT |= (1 << STP_BTN);
	safetyBtn.init(&STP_BTN_PIN, STP_BTN);
} 


void SafetyGuard::run() {
	
	safetyBtn.run();
	if(safetyBtn.isPressed()) {
		if(!SimulationData::isSimulationInProgress()) {
			led.red();
			//reset();
		}
		
		SimulationData::logWarning(Device::Warning::SAFETY_BTN_PRESSED);
		safetyEventStart(SafetyEvents::SAFETY_BTN);
		
		safetyBtn.setHandled();
	}
	
	if(!SimulationData::isSimulationInProgress()) return;

	if(error != Device::Error::NO_ERROR) {
		SimulationData::logError(error);
		safetyEventTimeout();
		error = Device::Error::NO_ERROR;
		return;
	}

	if(runDelay.skipThisTime()) return;
	
	
	if(_safetyEvent == SafetyEvents::SAFETY_BTN) {
		if(hasTimeoutOccured(SAFETY_BTN_PRESS_TIMEOUT)) {
			SimulationData::logError(Device::Error::STOPPED_BY_SAFETY_BTN);
			safetyEventTimeout();
		}
		else if(safetyBtn.isRelesed()) {
			safetyEventStop();
		}
		return;
	}
	
	if(safetyCheckEvent(
			OVER_TEMP, 
			Device::Warning::RADIATOR_TEMP_TOO_HIGH, 
			Device::Error::STOPPED_RADIATOR_TEMP_TOO_HIGH, 
			SAFETY_TIMEOUT, 
			(SimulationData::getRadiatorTemp() > SimulationData::getRadiatorTempLimit())
		)
	) return;

	if(safetyCheckEvent(
			OVER_CURR, 
			Device::Warning::CURRENT_TOO_HIGH, 
			Device::Error::STOPPED_CURRENT_TOO_HIGH, 
			SAFETY_TIMEOUT, 
			(SimulationData::getMeasuredCurrent() > SAFETY_MAX_CURRENT)
		)
	) return;

	if(safetyCheckEvent(
			UNDER_VOLT, 
			Device::Warning::VOLTAGE_TOO_LOW, 
			Device::Error::STOPPED_VOLTAGE_TOO_LOW, 
			SAFETY_TIMEOUT, 
			(
				SimulationData::getBattLeftVolt() < SimulationData::getVoltageLimit() ||
				SimulationData::getBattRightVolt() < SimulationData::getVoltageLimit()
			)
		)
	) return;
}

uint8_t SafetyGuard::safetyCheckEvent(
	SafetyEvents event, 
	Device::Warning warn, 
	Device::Error error,
	uint32_t timeout,
	uint8_t logicState) 
{
	if(logicState) {
		if(_safetyEvent == NONE) {
			SimulationData::logWarning(warn);
			safetyEventStart(event);
		}
		else if(_safetyEvent == event) {
			if(hasTimeoutOccured(timeout)) {
				SimulationData::logError(error);
				safetyEventTimeout();
			}
		}
		return 1;
	}
	else if(_safetyEvent == event) {
		safetyEventStop();
	}	
	return 0;
}

void SafetyGuard::safetyEventStart(SafetyEvents event) {
	led.red().blink();
	_safetyEvent = event;
	_safetyEventStart = Millis::get();
}

void SafetyGuard::safetyEventStop() {
	led.previousState();
	_safetyEvent = NONE;
}

void SafetyGuard::safetyEventTimeout() {
	led.red();
	_safetyEvent = NONE;
	deviceStopRequest();
}

uint8_t SafetyGuard::hasTimeoutOccured(uint32_t limit) {
	return ((Millis::get() - _safetyEventStart) > limit);
}