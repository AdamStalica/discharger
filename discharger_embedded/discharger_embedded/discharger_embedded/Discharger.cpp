/* 
* Discharger.cpp
*
* Created: 07.10.2019 21:42:02
* Author: domin
*/


#include "Discharger.h"

#define CURRENT_ACCURACY 15
#define TESTS 0


Discharger::Discharger() 
	:	uart(static_cast<UsartHolder&>(*this)),
		therm1(THERMOMETR_1_PIN),
		therm2(THERMOMETR_2_PIN)
{
	sei();
	wdt_enable(WDTO_1S);
	
	MillisecsCounter::init();
	SafetyGuard::init();
	
	adc.startConversion();
	
	therm1.startConversion();
	therm2.startConversion();
	
	SafetyGuard::setThermometerToObserve(&therm1);
	
	logError(DeviceError::DEVICE_STARTED);
	
	dac.writeDACValue(0);
}


void Discharger::run() {
	
	wdt_reset();
	
	SimulationData::run();
	SafetyGuard::run();
	adc.run();
	therm1.run();
	therm2.run();
	
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

void Discharger::aboutToSendNewData() {
	
	SimulationData::setMeauredBLT(therm1.getTemperature());
	SimulationData::setMeauredBRT(therm2.getTemperature());
}

void Discharger::simulationDriver() {
	
	static uint8_t canHandle100msTimeOut = 1;
	if(MillisecsCounter::getMillisecs() % SIMULATION_INTERVAL == 0) {
		if(canHandle100msTimeOut) {
			if(adc.isNewValueAvailable(AnalogMeasurement::LEM)) {
				
				adc.countAverages();
				int16_t currentlySimulatedCurrentAdc = adc.getAvgADC(AnalogMeasurement::LEM);
				int16_t currentlySimulatedCurrent = driver.getCurrentFormADC(currentlySimulatedCurrentAdc);
				driver.setSimulatedCurrent(currentlySimulatedCurrent);
				
				SimulationData::setMeauredCurrent(currentlySimulatedCurrent);
	
				SimulationData::setMeauredBLV(
					AnalogMeasurement::convertAdcToMillivolts(
						adc.getAvgADC(AnalogMeasurement::BLV)
					)
				);
	
				SimulationData::setMeauredBRV(
					AnalogMeasurement::convertAdcToMillivolts(
						adc.getAvgADC(AnalogMeasurement::BRV)
					)
				);
			}
						
			uint16_t newCurrent = getCurrentCurrent();
			uint16_t millivoltsToSet = driver.getEstimatedMillivolts(newCurrent);
			uint16_t dacToSet = driver.getDACFromMillivolts(millivoltsToSet);
			
			dac.writeDACValue(dacToSet);
			
			canHandle100msTimeOut = 0;
		}
	}
	else canHandle100msTimeOut = 1;
}

void Discharger::dangerEvent() {
	logError(getDeviceError());
	sendDeviceHasStopped();
}