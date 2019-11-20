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
	
	static uint8_t i = 0;
	
	SimulationData::run();
	adc.run();
	
	static uint16_t dacValue = 0;

	uint8_t status = dac.writeDACValue(getCurrentCurrent() << 2);
	
	//data.setMeauredCurrent(adc.getAvgADCCh(AnalogMeasurement::adcChannels::LEM));
	
	//dacValue += 500;
	
	//uart.println(i++);
	
	//data.logError(adc.getAvgADCCh(AnalogMeasurement::adcChannels::LEM));
	
	//_delay_ms(500);
}


void Discharger::aboutToSendNewData() {
	adc.countAverages();
	SimulationData::setMeauredCurrent(adc.getAvgADCCh(AnalogMeasurement::adcChannels::LEM));
}