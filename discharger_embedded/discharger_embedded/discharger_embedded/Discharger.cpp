/* 
* Discharger.cpp
*
* Created: 07.10.2019 21:42:02
* Author: domin
*/


#include "Discharger.h"
#include <util/delay.h>

#define wdt_interrput_enable() (	\
	WDTCSR |= (1 << WDIE)			\
)

Discharger::Discharger() 
	:	uart(static_cast<UsartHolder&>(*this)),
		therm1(THERMOMETER_3_PIN),				// swap therm1 with therm 3 !
		therm2(THERMOMETER_2_PIN),
		therm3(THERMOMETER_1_PIN),
		simDelay(SIMULATION_INTERVAL)
{
	wdt_enable(WDTO_1S);
	wdt_interrput_enable();
	sei();
		
	Millis::init();
	SafetyGuard::init();
	led.init();
	 
	adc.startConversion();
	therm1.startConversion();
	therm2.startConversion();
	therm3.startConversion();
	wdt_reset();
	dac.writeDACValue(0);
	
	led.green().blink();
	
	therm1.setOnCrcNoMatchWarning(Device::Warning::RADIATOR_THERM_CRC);
	therm2.setOnCrcNoMatchWarning(Device::Warning::BATT_LEFT_THERM_CRC);
	therm3.setOnCrcNoMatchWarning(Device::Warning::BATT_RIGHT_THERM_CRC);
	therm1.setOnCrcNoMatchError(Device::Error::STOPPED_RADIATOR_THERM_CRC);
	therm1.setOnNotAvaliableError(Device::Error::STOPPED_RADIATOR_THERM_NOT_AVALIABLE);
}

void Discharger::run() {
	
	wdt_reset();
	
	SimulationData::run();
	SafetyGuard::run();
	adc.run();
	therm1.run();
	therm2.run();
	therm3.run();
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
		SimulationData::setRadiatorTemp(therm1.getTemperature());
	}
	if(therm2.isNewValueAvaliable()) {
		SimulationData::setBattLeftTemp(therm2.getTemperature());
	}
	if(therm3.isNewValueAvaliable()) {
		SimulationData::setBattRightTemp(therm3.getTemperature());
	}
			
	uint16_t newCurrent = getCurrentCurrent();
	uint16_t millivoltsToSet = driver.getEstimatedMillivolts(newCurrent);
			
	dac.writeMillivolts(millivoltsToSet);
}

void Discharger::isrWDT() {
	logWarning(Device::Warning::WDT_RESET);
	SimulationData::run();
	_delay_ms(10);
}
