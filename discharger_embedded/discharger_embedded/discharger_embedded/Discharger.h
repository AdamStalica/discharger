/* 
* Discharger.h
*
* Created: 07.10.2019 21:42:03
* Author: domin
*/

#define BAUDRATE 57600UL
#define F_CPU 10240000UL

#define DEVICE_STARTED 0
#define SIMULATION_INTERVAL 100

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/wdt.h>

#include "SimulationData.h"
#include "MCP4725.h"
#include "AnalogMeasurement.h"
#include "CurrentDriver.h"
#include "MillisecsCounter.h"

#ifndef __DISCHARGER_H__
#define __DISCHARGER_H__


class Discharger : private SimulationData
{
	AnalogMeasurement adc;
	MCP4725 dac;
	UsartHolder & uart;
	CurrentDriver driver;
	MillisecsCounter ms;

	
	void aboutToSendNewData() override;
	void simulationDriver();

public:
	Discharger();
	~Discharger() {}
	void run();
	
	
// ISR vecs
	void isrUsart0RxHandler() { uart.isrUsart0RxHandler(); }
	void isrUsart0UdreHandler() { uart.isrUsart0UdreHandler(); }
	void isrADCVect() { adc.isrADCVect(); }
	void isrTimer0CompBVect() { ms.isrTimer0CompBVect(); }
};

#endif
