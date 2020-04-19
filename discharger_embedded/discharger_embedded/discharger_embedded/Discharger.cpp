/* 
* Discharger.cpp
*
* Created: 07.10.2019 21:42:02
* Author: domin
*/

/*
	TODO: New driving algorithm
	TODO: determination of chtic
	TODO: Storing chtic in EEPROM memory
*/

#include "Discharger.h"
#include <util/delay.h>

#define wdt_interrput_enable() (	\
	WDTCSR |= (1 << WDIE)			\
)

Discharger::Discharger() 
	:	therm1(THERMOMETER_3_PIN),				// swap therm1 with therm 3 !
		therm2(THERMOMETER_2_PIN),
		therm3(THERMOMETER_1_PIN),
		simDelay(SIMULATION_INTERVAL),
		chticDetermDelay(2000)
{
	wdt_enable(WDTO_1S);
	wdt_interrput_enable();
	sei();
		
	Millis::init();
	SafetyGuard::init();
	led.init();
	driver.setChticData(static_cast<ChticData*>(&chDeterm));
	 
	adc.startConversion();
	therm1.startConversion();
	therm2.startConversion();
	therm3.startConversion();
	wdt_reset();
	dac.writeDACValue(0);
	
	led.green().blink();
	
	therm1.setOnCrcNoMatchWarning(Device::Warning::HEAT_SINK_THERM_CRC);
	therm2.setOnCrcNoMatchWarning(Device::Warning::BATT_LEFT_THERM_CRC);
	therm3.setOnCrcNoMatchWarning(Device::Warning::BATT_RIGHT_THERM_CRC);
	therm1.setOnCrcNoMatchError(Device::Error::STOPPED_HEAT_SINK_THERM_CRC);
	therm1.setOnNotAvaliableError(Device::Error::STOPPED_HEAT_SINK_THERM_NOT_AVALIABLE);
	
	chDeterm.loadFromEEPROM();
	deviceDriver.setCallbacks(static_cast<DeviceDriverCallbacks*>(this));
}



void Discharger::run() {
	wdt_reset();
	
	deviceDriver.run();
	SafetyGuard::run();
	adc.run();
	therm1.run();
	therm2.run();
	therm3.run();
	led.run();
	
	if(chDeterm.isInProgress() && !chticDetermDelay.skipThisTime()) {
		detemineCharacteristic();
		return;
	}
	
	if(simData.isSimulationInProgress() && !simDelay.skipThisTime()) {
		simulationDriver();	
	}
}


void Discharger::handleHanshake() {
	led.green();
	deviceDriver.sendHandshakeReply();
}

void Discharger::handleStop() {
	dac.writeDACValue(0);
	if(simData.isSimulationInProgress()) {
		deviceDriver.sendSimulationData();
		_delay_ms(20);
	}
	simData.clear();
	led.green().blink();
	deviceDriver.sendDeviceHasStopped();
}

void Discharger::handleChticDetermStart() {
	led.blue().blink();
	chDeterm.start();
	dac.writeMillivolts(chDeterm.getMilivolts());
}

void Discharger::handleChticRead() {
	uint8_t id = 0;
	int16_t mV, I;
	while(chDeterm.readPointAt(id, mV, I)) {
		deviceDriver.sendCharacteristicData(id, mV, I);
		++id;
		_delay_ms(10);
		wdt_reset();
	}
	deviceDriver.sendCharacteristicDone();
}

void Discharger::handleSimNewData(const DrivingData & data) {
	if(!simData.isSimulationInProgress()) {
		led.blue();
	}
	else {
		deviceDriver.sendSimulationData();
	}
	simData.setDrivingData(data);
}

void Discharger::deviceStopRequest() {
	dac.writeDACValue(0);
	simData.clear();
}

void Discharger::detemineCharacteristic() {	
	if(adc.isNewValueAvailable(AnalogMeasurement::LEM)) {
		
		adc.countAverages();
		int16_t currentlySimulatedCurrentAdc = adc.getAvgADC(AnalogMeasurement::LEM);
		int16_t currentlySimulatedCurrent = CurrentDriver::getCurrentFormADC(currentlySimulatedCurrentAdc);
		deviceDriver.sendCharacteristicData(
			chDeterm.getId(), 
			chDeterm.getMilivolts(), 
			currentlySimulatedCurrent
		);
		
		if(chDeterm.setCurrent(currentlySimulatedCurrent) == CHTIC_DONE) {
			dac.writeMillivolts(0);
			led.previousState();
			chDeterm.storeInEEPROM();
			chDeterm.clear();
			deviceDriver.sendCharacteristicDone();
			return;
		}
		dac.writeMillivolts(chDeterm.getMilivolts());
	}	
}

void Discharger::simulationDriver() {
	/*
	static uint16_t i = 0;
	dac.writeMillivolts(i);
	i += 50;
	i %= 5000;
	debugLog("I ", i);
	return;
	*/
	
	
	//dac.writeMillivolts(1000);
	/*
	uint16_t newCurrent1 = getCurrentCurrent();
	dac.writeMillivolts(newCurrent1);
	
	
	if(adc.isNewValueAvailable(AnalogMeasurement::LEM)) {
		adc.countAverages();
		uint16_t currAdc = adc.getAvgADC(AnalogMeasurement::LEM);
		
		debugLog(
			"I =", 
			driver.getCurrentFormADC(currAdc)
		);
	}
	return;
	*/
	
	//debugLog("Hello World!");
	deviceDriver.sendDebug("Hi");
	
	if(adc.isNewValueAvailable(AnalogMeasurement::LEM)) {
				
		adc.countAverages();
		int16_t currentlySimulatedCurrentAdc = adc.getAvgADC(AnalogMeasurement::LEM);
		int16_t currentlySimulatedCurrent = CurrentDriver::getCurrentFormADC(currentlySimulatedCurrentAdc);
		driver.setMeasuredCurrent(currentlySimulatedCurrent);
			
		simData.setMeasuredCurrent(currentlySimulatedCurrent);	
		//SimulationData::setMeauredCurrent(currentlySimulatedCurrent);
	}						
	if(adc.isNewValueAvailable(AnalogMeasurement::BRV)) {
		simData.setMeasuredBLV(
			AnalogMeasurement::convertAdcToMillivolts(
				adc.getAvgADC(AnalogMeasurement::BLV)
			)
		);
	}
	if(adc.isNewValueAvailable(AnalogMeasurement::BLV)) {
		simData.setMeasuredBRV(
			AnalogMeasurement::convertAdcToMillivolts(
				adc.getAvgADC(AnalogMeasurement::BRV)
			)
		);
	}
	if(therm1.isNewValueAvaliable()) {
		simData.setMeasuredHST(therm1.getTemperature());
	}
	if(therm2.isNewValueAvaliable()) {
		simData.setMeasuredBLT(therm2.getTemperature());
	}
	if(therm3.isNewValueAvaliable()) {
		simData.setMeasuredBRT(therm3.getTemperature());
	}
			
	uint16_t newCurrent = simData.getDrivingCurrent();
	uint16_t millivoltsToSet = driver.getEstimatedMillivolts(newCurrent);
	//debugLog("mV=", millivoltsToSet);
	
//#define DIRECT
#ifdef DIRECT
	dac.writeMillivolts(newCurrent/10);
#else
	dac.writeMillivolts(millivoltsToSet);
#endif
}

void Discharger::isrWDT() {
	deviceDriver.sendWarning(Device::Warning::WDT_RESET);
	_delay_ms(10);
}
