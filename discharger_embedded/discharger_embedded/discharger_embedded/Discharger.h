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

#ifndef __DISCHARGER_H__
#define __DISCHARGER_H__


class Discharger
{
//variables
public:
	MCP4725 dac;
	SimulationData data;
	UsartHolder & uart;

//functions
public:
	Discharger();
	~Discharger() {}
	void run();

};

#endif
