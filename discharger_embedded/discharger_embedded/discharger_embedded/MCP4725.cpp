/* 
* MCP4725.cpp
*
* Created: 15.10.2019 10:31:32
* Author: domin
*/


#include "MCP4725.h"

// default constructor
MCP4725::MCP4725(unsigned long fCpu) : I2CMaster(fCpu)
{
} //MCP4725

// default destructor
MCP4725::~MCP4725()
{
} //~MCP4725

uint8_t MCP4725::readData(uint8_t * tab, uint8_t size) {
	uint8_t ans = 0x00;
	
	for(uint8_t i = 0; i < 0x08; i++) {
		ans |= this->receive((DEVICE_ADDRESS | ((i << 1) & 0x0E)), tab, size);	
	}
	
	return ans;
}

uint8_t MCP4725::writeDACData(uint16_t dacValue) {

	uint8_t data[3] = {
		DATA_WRITE_FIRST_BYTE,
		uint8_t(dacValue >> 8),
		(uint8_t)dacValue
	};

	uint8_t ans;	
	ans =	this->transmit((DEVICE_ADDRESS | (0 << 3) | (0 << 2)), data, sizeof(data));
	ans |=	this->transmit((DEVICE_ADDRESS | (0 << 3) | (1 << 2)), data, sizeof(data));
	ans |=	this->transmit((DEVICE_ADDRESS | (1 << 3) | (0 << 2)), data, sizeof(data));
	ans |=	this->transmit((DEVICE_ADDRESS | (1 << 3) | (1 << 2)), data, sizeof(data));
	
	return ans;
}