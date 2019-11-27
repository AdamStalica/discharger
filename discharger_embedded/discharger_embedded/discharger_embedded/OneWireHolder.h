/* 
* OneWireHolder.h
*
* Created: 26.11.2019 21:16:15
* Author: domin
*/


#ifndef __ONEWIREHOLDER_H__
#define __ONEWIREHOLDER_H__

#include "GlobalDefs.h"
#include <avr/io.h>

class OneWireHolder
{
private:
	void writeBit(uint8_t bit_);
	uint8_t readBit();
	
	uint8_t physicalPin_;
	
public:

	void writeByte(uint8_t byte_);
	uint8_t readByte();
	uint8_t resetPulse();

	OneWireHolder(uint8_t physicalPin) : physicalPin_(physicalPin) {};
	~OneWireHolder() {};
};

#endif //__ONEWIREHOLDER_H__
