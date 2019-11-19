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
	DDRA = 0xFF;
	
}

void Discharger::run() {
	
	static uint8_t i = 0;
	
	data.run();
	
	static uint16_t dacValue = 0;

	//uint8_t status = dac.writeDACValue(dacValue);
	dacValue += 500;
	
	//uart.println(i++);
	
	//data.logError(i++);
	
	//_delay_ms(500);
}
