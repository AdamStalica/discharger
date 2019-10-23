/* 
* Discharger.cpp
*
* Created: 07.10.2019 21:42:02
* Author: domin
*/


#include "Discharger.h"

Discharger::Discharger() 
	:	data(BAUDRATE, F_CPU), 
		dac(F_CPU),
		uart(data)
{
	dac.setSerial(&uart);
	//uart.println("Device ready!");
}


void Discharger::run() {
	
	static uint16_t i = 0;
	
	data.run();
	
	/*
	if(i++ == 0)
		data.logError(12);
	_delay_us(30);
	*/
	
	/*
	static uint16_t dacValue = 0;
	
	uint8_t data[7];
	uint8_t status = dac.readData(data, sizeof(data));
	uart.println(status ? "I've got an error while reading." : "I've got data.");
	
	/*
	status = dac.writeDACData(dacValue);
	this->println(status ? "I've got an error while writing." : "I've got data.");
	dacValue += 1000;
	*/
}
