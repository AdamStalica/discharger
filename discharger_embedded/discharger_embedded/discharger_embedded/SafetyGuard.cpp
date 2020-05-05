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
#include "DeviceDriver.h"

dischargerDevice::Error SafetyGuard::error = dischargerDevice::Error::NO_DEV_ERROR;

void SafetyGuard::init()
{
	STP_BTN_DDR = (STP_BTN_DDR & ~(1 << STP_BTN));
	STP_BTN_PORT |= (1 << STP_BTN);
	safetyBtn.init(&STP_BTN_PIN, STP_BTN);
} 


void SafetyGuard::run() {
	
	if(error != dischargerDevice::Error::NO_DEV_ERROR) {
		deviceDriver.sendError(error);
		safetyEventTimeout();
		error = dischargerDevice::Error::NO_DEV_ERROR;
		return;
	}
	
	safetyBtn.run();
	if(safetyBtn.isPressed()) {
		if(!simData.isSimulationInProgress()) {
			led.red();
			reset();
		}
		
		deviceDriver.sendWarning(dischargerDevice::Warning::SAFETY_BTN_PRESSED);
		safetyEventStart(SafetyEvents::SAFETY_BTN);
		
		safetyBtn.setHandled();
	}
	
	if(!simData.isSimulationInProgress()) return;
	if(runDelay.skipThisTime()) return;
	
	
	if(_safetyEvent == SafetyEvents::SAFETY_BTN) {
		if(hasTimeoutOccured(SAFETY_BTN_PRESS_TIMEOUT)) {
			deviceDriver.sendError(dischargerDevice::Error::STOPPED_BY_SAFETY_BTN);
			safetyEventTimeout();
		}
		else if(safetyBtn.isRelesed()) {
			safetyEventStop();
		}
		return;
	}
	
	if(safetyCheckEvent(
			OVER_TEMP, 
			dischargerDevice::Warning::HEAT_SINK_TEMP_TOO_HIGH, 
			dischargerDevice::Error::STOPPED_HEAT_SINK_TEMP_TOO_HIGH, 
			SAFETY_TIMEOUT, 
			(simData.getMeasuredHST() > simData.getHeatSinkTempLimit())
		)
	) return;

	if(safetyCheckEvent(
			OVER_CURR, 
			dischargerDevice::Warning::CURRENT_TOO_HIGH, 
			dischargerDevice::Error::STOPPED_CURRENT_TOO_HIGH, 
			SAFETY_TIMEOUT, 
			(abs(simData.getMeasuredCurrent()) > SAFETY_MAX_CURRENT)
		)
	) return;

	if(safetyCheckEvent(
			UNDER_VOLT, 
			dischargerDevice::Warning::VOLTAGE_TOO_LOW, 
			dischargerDevice::Error::STOPPED_VOLTAGE_TOO_LOW, 
			SAFETY_TIMEOUT, 
			(
				simData.getMeasuredBLV() < simData.getVoltageLimit() ||
				simData.getMeasuredBRV() < simData.getVoltageLimit()
			)
		)
	) return;
}

uint8_t SafetyGuard::safetyCheckEvent(
	SafetyEvents event, 
	dischargerDevice::Warning warn, 
	dischargerDevice::Error error,
	uint32_t timeout,
	uint8_t logicState) 
{
	if(logicState) {
		if(_safetyEvent == NONE) {
			deviceDriver.sendWarning(warn);
			safetyEventStart(event);
		}
		else if(_safetyEvent == event) {
			if(hasTimeoutOccured(timeout)) {
				deviceDriver.sendError(error);
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