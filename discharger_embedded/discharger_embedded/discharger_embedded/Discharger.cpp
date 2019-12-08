/* 
* Discharger.cpp
*
* Created: 07.10.2019 21:42:02
* Author: domin
*/


#include "Discharger.h"

#define CURRENT_ACCURACY 15

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
}


void Discharger::run() {
	
	wdt_reset();
	
	SimulationData::run();
	SafetyGuard::run();
	adc.run();
	therm1.run();
	therm2.run();
	
	simulationDriver();
	
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


void Discharger::aboutToSendNewData() {
	
	SimulationData::setMeauredBLT(therm1.getTemperature());
	SimulationData::setMeauredBRT(therm2.getTemperature());
		
	adc.countAverages();
	
	uint16_t simulatedCurrentADC = adc.getAvgADC(AnalogMeasurement::adcChannels::LEM);
	uint16_t simulatedCurrent = driver.getCurrentFormADC(simulatedCurrentADC);
	
	/*
	if(!simulationCurrentAlreadySet)
		driver.setSimulatedCurrent(simulatedCurrent);
	else
	*/ 
	
	uint16_t difference = mathAbsDiff(simulatedCurrent, getCurrentCurrent());
	
	
	
	static uint16_t lastDifference = 0xFFFF;
	static uint8_t counter = 0;
	if( difference < lastDifference || difference > CURRENT_ACCURACY ) {
		driver.setSimulatedCurrent(simulatedCurrent);
		lastDifference = difference;
	}
	
	
	/*
	static uint8_t noAccuracyFittedCounter = 7;
	static uint8_t gotAccuracy = 1;
	if(difference < CURRENT_ACCURACY) {
		if(!gotAccuracy) {
			
			driver.setSimulatedCurrent(simulatedCurrent);
			debugLog("Accuracy fitted.", difference);
			gotAccuracy = 1;
		}
		noAccuracyFittedCounter = 0;
	}
	else {
		if(noAccuracyFittedCounter = 1) gotAccuracy = 0;
		if((++noAccuracyFittedCounter % 10) == 0) {
			
			driver.setSimulatedCurrent(simulatedCurrent);
			debugLog("Over 10.", noAccuracyFittedCounter);
			
			noAccuracyFittedCounter = 0;
		}
	}
	*/
	SimulationData::setMeauredCurrent(simulatedCurrent);
}

void Discharger::simulationDriver() {
	
	static uint8_t canHandle100msTimeOut = 1;
	if(MillisecsCounter::getMillisecs() % SIMULATION_INTERVAL == 0) {
		
		
		if(canHandle100msTimeOut) {

			/*
			uint16_t currentlySimulatedCurrentAdc = adc.getADC(AnalogMeasurement::adcChannels::LEM);
			
			uint16_t currentlySimulatedCurrent = driver.getCurrentFormADC(currentlySimulatedCurrentAdc);
			
			
			uint16_t diff = mathAbsDiff(currentlySimulatedCurrent, newCurrent);
			//debugLog("Diff: ", diff);
			if(	!simulationCurrentAlreadySet && 
				(diff < CURRENT_ACCURACY)) 
			{
				
				simulationCurrentAlreadySet = 1;
			}
			*/
			
			//#define ADC_TEST
			
			#ifndef ADC_TEST
			
			uint16_t newCurrent = getCurrentCurrent();
						
			uint16_t millivoltsToSet = driver.getEstimatedMillivoltsToBeSet(newCurrent);
			
			uint16_t dacToSet = driver.getDACFromMillivolts(millivoltsToSet);
			
			dac.writeDACValue(dacToSet);
			
			#else
			
			adc.countAverages();
			
			debugLog("ADC ", adc.getAvgADC(AnalogMeasurement::LEM));
			
			#endif
			
			canHandle100msTimeOut = 0;
		}
	}
	else canHandle100msTimeOut = 1;
}

void Discharger::dangerEvent() {
	logError(getDeviceError());
	sendDeviceHasStopped();
}