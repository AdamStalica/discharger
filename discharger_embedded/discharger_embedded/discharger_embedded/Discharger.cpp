/* 
* Discharger.cpp
*
* Created: 07.10.2019 21:42:02
* Author: domin
*/


#include "Discharger.h"

Discharger::Discharger() 
	:	uart(static_cast<UsartHolder&>(*this)),
		therm1(THERMOMETR_1_PIN),
		therm2(THERMOMETR_2_PIN)
{
	sei();
	wdt_enable(WDTO_1S);
	
	adc.startConversion();
	
	therm1.startConversion();
	therm2.startConversion();
	
	logError(DEVICE_STARTED);
}


void Discharger::run() {
	
	wdt_reset();
	
	SimulationData::run();
	adc.run();
	
	simulationDriver();
	
	/*
	static uint8_t canHandle1000msTimeout = 1;
	if(ms.getMillisecs() % 1000 == 0) {
		if(canHandle1000msTimeout) {
			
			if(therm1.deviceAvaliable()) {
				
				logError(therm1.getTemperature());
				therm1.startConversion();
			}
			if(therm2.deviceAvaliable()) {
				
				logError(therm2.getTemperature());
				therm2.startConversion();
			}
			
			canHandle1000msTimeout = 0;
		}
	}
	else canHandle1000msTimeout = 1;
	/**/
}


void Discharger::aboutToSendNewData() {
	
	if(therm1.deviceAvaliable()) {
		SimulationData::setMeauredBLT(therm1.getTemperature());
		therm1.startConversion();
	}
	
	if(therm2.deviceAvaliable()) {
		SimulationData::setMeauredBRT(therm2.getTemperature());
		therm2.startConversion();
	}
	
	adc.countAverages();
	
	uint16_t simulatedCurrentADC = adc.getAvgADC(AnalogMeasurement::adcChannels::LEM);
	uint16_t simulatedCurrent = driver.getCurrentFormADC(simulatedCurrentADC);
	driver.setSimulatedCurrent(simulatedCurrent);
	
	SimulationData::setMeauredCurrent(simulatedCurrent);
}

void Discharger::simulationDriver() {
	
	static uint8_t canHandle100msTimeOut = 1;
	if(ms.getMillisecs() % SIMULATION_INTERVAL == 0) {
		if(canHandle100msTimeOut) {
			
			uint16_t newCurrent = getCurrentCurrent();
			
			uint16_t millivoltsToSet = driver.getEstimatedMillivoltsToBeSet(newCurrent);
			
			uint16_t dacToSet = driver.getDACFromMillivolts(millivoltsToSet);
			
			dac.writeDACValue(dacToSet);
			
			canHandle100msTimeOut = 0;
		}
	}
	else canHandle100msTimeOut = 1;
}