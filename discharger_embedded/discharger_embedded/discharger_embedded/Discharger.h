/* 
* Discharger.h
*
* Created: 07.10.2019 21:42:03
* Author: domin
*/

//#define DEVICE_STARTED 0
#define SIMULATION_INTERVAL 100

#include "GlobalDefs.h"
#include "SimulationData.h"
#include "MCP4725.h"
#include "AnalogMeasurement.h"
#include "CurrentDriver.h"
#include "DS18B20.h"
#include "Millis.h"
#include "SafetyGuard.h"
#include "Led.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>

#ifndef __DISCHARGER_H__
#define __DISCHARGER_H__


class Discharger : public SimulationData, SafetyGuard
{
	AnalogMeasurement adc;
	MCP4725 dac;
	UsartHolder & uart;
	CurrentDriver driver;
	DS18B20 therm1;
	DS18B20 therm2;
	
	uint8_t simulationCurrentAlreadySet = 0;
	
	uint8_t stoppedByBtn = 0;

	void aboutToSendNewData() override;
	void stopDevice() override;
	void communicationEstablished() override;
	void deviceStopRequest() override;
	
	void simulationDriver();

public:
	Discharger();
	~Discharger() {}
	void run();
	
	
// ISR vecs
	void isrUsart0RxHandler() { uart.isrUsart0RxHandler(); }
	void isrUsart0UdreHandler() { uart.isrUsart0UdreHandler(); }
	void isrADCVect() { adc.isrADCVect(); }
	void isrTimer0CompBVect() { Millis::isrTimer0CompBVect(); }
		
		
#ifdef DEBUG_MODE
	void debugerUartFunction(char * string, int32_t digit) {
		uart.debuger(string, digit);
	};
#endif
};

#endif
