/* 
* Discharger.cpp
*
* Created: 07.10.2019 21:42:02
* Author: domin
*/


#include "Discharger.h"

Discharger::Discharger() 
	:	therm1(	THERMOMETER_1_PIN, Device::Warning::RADIATOR_THERM_CRC, 
				Device::Error::STOPPED_RADIATOR_THERM_CRC, 
				Device::Error::STOPPED_RADIATOR_THERM_NOT_AVALIABLE),
		therm2(THERMOMETER_2_PIN, Device::Warning::BATT_LEFT_THERM_CRC),
		therm3(THERMOMETER_2_PIN, Device::Warning::BATT_RIGHT_THERM_CRC),
		simDelay(SIMULATION_INTERVAL)
{
	sei();
	wdt_enable(WDTO_1S);
	
	
	//logError(Device::DEVICE_STARTED);
	
	Millis::init();
	SafetyGuard::init();
	led.init();
	 
	adc.startConversion();
	therm1.startConversion();
	therm2.startConversion();
	therm3.startConversion();
	
	dac.writeDACValue(0);

	led.green().blink();
	//debugLog("OK");
}


void Discharger::run() {
	
	wdt_reset();
	debugLog("OK");
	SimulationData::run();
	SafetyGuard::run();
	adc.run();
	therm1.run();
	therm2.run();
	led.run();
	
	if(SimulationData::isSimulationInProgress()) {
		simulationDriver();	
	}
}

void Discharger::simHasStarted() {
	led.blue();
}

void Discharger::raceivedStopDevice() {
	SafetyGuard::reset();
}

void Discharger::communicationEstablished() {
	led.green();
}

void Discharger::deviceStopRequest() {
	dac.writeDACValue(0);
	setDeviceHasStopped();	
}

void Discharger::aboutToSendNewData() {
	//debugLog("T", SimulationData::getRadiatorTempLimit());
	//led.blue();
}

void Discharger::simulationDriver() {
	
	if(simDelay.skipThisTime()) return;
	
	if(adc.isNewValueAvailable(AnalogMeasurement::LEM)) {
				
		adc.countAverages();
		int16_t currentlySimulatedCurrentAdc = adc.getAvgADC(AnalogMeasurement::LEM);
		int16_t currentlySimulatedCurrent = driver.getCurrentFormADC(currentlySimulatedCurrentAdc);
		driver.setSimulatedCurrent(currentlySimulatedCurrent);
				
		SimulationData::setMeauredCurrent(currentlySimulatedCurrent);
	}						
	if(adc.isNewValueAvailable(AnalogMeasurement::BRV)) {
		SimulationData::setBattLeftVolt(
			AnalogMeasurement::convertAdcToMillivolts(
				adc.getAvgADC(AnalogMeasurement::BLV)
			)
		);
	}
	if(adc.isNewValueAvailable(AnalogMeasurement::BLV)) {
		SimulationData::setBattRightVolt(
			AnalogMeasurement::convertAdcToMillivolts(
				adc.getAvgADC(AnalogMeasurement::BRV)
			)
		);
	}
	if(therm1.isNewValueAvaliable()) {
		SimulationData::setBattLeftTemp(therm1.getTemperature());
	}
	if(therm2.isNewValueAvaliable()) {
		SimulationData::setBattRightTemp(therm2.getTemperature());
	}
			
	uint16_t newCurrent = getCurrentCurrent();
	uint16_t millivoltsToSet = driver.getEstimatedMillivolts(newCurrent);
			
	dac.writeMillivolts(millivoltsToSet);
}
/*
void Discharger::isrWDT() {

}
*/