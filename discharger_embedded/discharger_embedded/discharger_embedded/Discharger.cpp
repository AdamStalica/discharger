/* 
* Discharger.cpp
*
* Created: 07.10.2019 21:42:02
* Author: domin
*/


#include "Discharger.h"

Discharger::Discharger() 
	:	SimulationData(BAUDRATE, F_CPU), 
		dac(F_CPU),
		adc(F_CPU),
		uart(static_cast<UsartHolder&>(*this)),
		ms(F_CPU)
{
	sei();
	wdt_enable(WDTO_1S);
	
	adc.startConversion();
	
	logError(DEVICE_STARTED);
}


void Discharger::run() {
	
	wdt_reset();
	
	SimulationData::run();
	adc.run();
	
	simulationDriver();
}


void Discharger::aboutToSendNewData() {
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