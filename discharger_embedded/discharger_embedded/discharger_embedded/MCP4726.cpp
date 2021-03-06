/* 
* MCP4725.cpp
*
* Created: 15.10.2019 10:31:32
* Author: domin
*/


#include "MCP4726.h"

uint16_t MCP4726::readDACValue() {
	
	uint8_t data[5];
	
	uint8_t ans = this->receive(DEVICE_ADDRESS, data, sizeof(data[5]));	
	
	if(!ans) {
		uint16_t dac = (data[1] << 8) | data[2];
		return dac;
	}
	return 0xFFFF;
}

uint8_t MCP4726::writeDACValue(uint16_t dacValue) {

	dacValue = dacValue << 4;
	uint8_t data[3] = {
		DATA_WRITE_FIRST_BYTE,
		uint8_t(dacValue >> 8),
		(uint8_t)dacValue
	};
	
	uint8_t ans = this->transmit(DEVICE_ADDRESS, data, sizeof(data));	
	return ans;
}

uint16_t MCP4726::convertMillivoltsToDAC(uint16_t millivolts) {
	return (uint32_t(millivolts) * MCP4725_MAX_DAC / MCP4725_VREF);
}

uint8_t MCP4726::writeMillivolts(uint16_t millivolts) {
	return writeDACValue(convertMillivoltsToDAC(millivolts));
}
