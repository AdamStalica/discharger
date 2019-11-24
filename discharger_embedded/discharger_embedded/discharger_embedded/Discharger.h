/* 
* Discharger.h
*
* Created: 07.10.2019 21:42:03
* Author: domin
*/

#define BAUDRATE 57600UL
#define F_CPU 10240000UL

#include <avr/io.h>
#include <util/delay.h>

#include "SimulationData.h"
#include "MCP4725.h"
#include "AnalogMeasurement.h"
#include "CurrentDriver.h"
#include "MillisecsCounter.h"

#ifndef __DISCHARGER_H__
#define __DISCHARGER_H__


class Discharger : private SimulationData
{
//variables
public:
	AnalogMeasurement adc;
	MCP4725 dac;
	//SimulationData data;
	UsartHolder & uart;
	CurrentDriver driver;
	MillisecsCounter ms;

//functions
public:
	Discharger();
	~Discharger() {}
	void run();
	void aboutToSendNewData() override;
};

#endif
