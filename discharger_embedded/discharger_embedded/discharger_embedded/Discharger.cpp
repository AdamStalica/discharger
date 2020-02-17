/* 
* Discharger.cpp
*
* Created: 07.10.2019 21:42:02
* Author: domin
*/


#include "Discharger.h"

#define CURRENT_ACCURACY 15
#define TESTS 0

/*
	TODO:
		- terms,
		- communication,
		
*/


Discharger::Discharger() 
	:	uart(static_cast<UsartHolder&>(*this)),
		therm1(THERMOMETR_1_PIN),
		therm2(THERMOMETR_2_PIN)
{
	sei();
	wdt_enable(WDTO_1S);
	
	Millis::init();
	SafetyGuard::init();
	led.init();
	
	adc.startConversion();
	
	therm1.startConversion();
	therm2.startConversion();
	
	SafetyGuard::setThermometerToObserve(&therm1);
	
	//logError(DeviceError::DEVICE_STARTED);
	
	dac.writeDACValue(0);
	
	led.green().blink();
}


void Discharger::run() {
	
	wdt_reset();
	
	SimulationData::run();
	SafetyGuard::run();
	adc.run();
	therm1.run();
	therm2.run();
	led.run();
	
	if(SimulationData::simulationInProgress() || TESTS) {
		simulationDriver();	
	}
	
	
	
	/*
	static uint8_t canHandle1000msTimeout = 1;
	if(ms.getMillisecs() % 1000 == 0) {
		if(canHandle1000msTimeout) {
			
			if(therm1.deviceAvaliable()) {
				
				debugLog("Temp1 ", therm1.getTemperature());
				therm1.startConversion();
			}
			if(therm2.deviceAvaliable()) {
				
				debugLog("Temp1 ", therm2.getTemperature());
				therm2.startConversion();
			}
			canHandle1000msTimeout = 0;
		}
	}
	else canHandle1000msTimeout = 1;
	/**/
}


void Discharger::stopDevice()
{
	dac.writeDACValue(0);
}

void Discharger::communicationEstablished() {
	led.green();
}

void Discharger::deviceStopRequest() {
	//logError(getDeviceError());
	sendDeviceHasStopped();
}

void Discharger::aboutToSendNewData() {
	debugLog("T", SimulationData::getRadiatorTempLimit());
	led.blue();
	SimulationData::setBattLeftTemp(therm1.getTemperature());
	SimulationData::setBattRightTemp(therm2.getTemperature());
}

void Discharger::simulationDriver() {
	
	static uint8_t canHandle100msTimeOut = 1;
	if(Millis::get() % SIMULATION_INTERVAL == 0) {
		if(canHandle100msTimeOut) {
			if(adc.isNewValueAvailable(AnalogMeasurement::LEM)) {
				
				adc.countAverages();
				int16_t currentlySimulatedCurrentAdc = adc.getAvgADC(AnalogMeasurement::LEM);
				int16_t currentlySimulatedCurrent = driver.getCurrentFormADC(currentlySimulatedCurrentAdc);
				driver.setSimulatedCurrent(currentlySimulatedCurrent);
				
				SimulationData::setMeauredCurrent(currentlySimulatedCurrent);
	
				SimulationData::setBattLeftVolt(
					AnalogMeasurement::convertAdcToMillivolts(
						adc.getAvgADC(AnalogMeasurement::BLV)
					)
				);
	
				SimulationData::setBattRightVolt(
					AnalogMeasurement::convertAdcToMillivolts(
						adc.getAvgADC(AnalogMeasurement::BRV)
					)
				);
			}
						
			uint16_t newCurrent = getCurrentCurrent();
			uint16_t millivoltsToSet = driver.getEstimatedMillivolts(newCurrent);
			
			dac.writeMillivolts(millivoltsToSet);
			
			canHandle100msTimeOut = 0;
		}
	}
	else canHandle100msTimeOut = 1;
}