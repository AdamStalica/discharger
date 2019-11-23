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
		uart(static_cast<UsartHolder&>(*this))
{
	adc.startConversion();
}

void Discharger::run() {
		
	SimulationData::run();
	adc.run();
	
	if(adc.isNewValueAvailable(AnalogMeasurement::adcChannels::LEM)) {
		
		uint16_t lemAdc = adc.getADC(AnalogMeasurement::adcChannels::LEM);
		
		//logError(lemAdc);
		
		uint16_t simulatedCurrent = driver.getCurrentFormADC(lemAdc);
		
		driver.setSimulatedCurrent(simulatedCurrent);
		
		
		uint16_t millivoltsToSet = driver.getEstimatedMillivoltsToBeSet(getCurrentCurrent());
		
		uint16_t dacToSet = driver.getDACFromMillivolts(millivoltsToSet);
		
		dac.writeDACValue(dacToSet << 4);
		
		logError(simulatedCurrent);
		 
		 //_delay_ms(100);
		
		/*
		// 1.0A -> 10
		uint16_t dacToSet = (4 * getCurrentCurrent()) / 5;
		
		dac.writeDACValue(dacToSet << 3);
		
		//
		//uint16_t lemCurrent = lemAdc;
		*/
		
	}
}


void Discharger::aboutToSendNewData() {
	adc.countAverages();
	
	uint16_t simulatedCurrentADC = adc.getAvgADC(AnalogMeasurement::adcChannels::LEM);
	
	uint16_t simulatedCurrent = driver.getCurrentFormADC(simulatedCurrentADC);
	
	SimulationData::setMeauredCurrent(simulatedCurrent);
}