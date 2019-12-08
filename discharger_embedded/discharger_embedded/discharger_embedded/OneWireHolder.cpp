/* 
* OneWireHolder.cpp
*
* Created: 26.11.2019 21:16:15
* Author: domin
*/


#include "OneWireHolder.h"

#include <util/delay.h>

#define ONE_WIRE_RESET 0
#define ONE_WIRE_WRITE 1
#define ONE_WIRE_READ 2

#define SET_BIT(byte, bit) \
(byte |= (1 << bit))

#define CLR_BIT(byte, bit) \
(byte &= ~(1 << bit))

#define BIT_IS_CLR(byte, bit) \
((byte & (1 << bit)) == 0)

#define BIT_IS_SET(byte, bit) \
((byte & (1 << bit)) != 0)

#define ONE_WIRE_LOW(pin_) CLR_BIT(ONE_WIRE_PORT, pin_)
#define ONE_WIRE_HIGH(pin_) SET_BIT(ONE_WIRE_PORT, pin_)
#define ONE_WIRE_IN(pin_) CLR_BIT(ONE_WIRE_DDR, pin_)
#define ONE_WIRE_OUT(pin_) SET_BIT(ONE_WIRE_DDR, pin_)

#define ONE_WIRE_SLV_CLRD(pin_) BIT_IS_CLR(ONE_WIRE_PIN, pin_)
#define ONE_WIRE_SLV_SET(pin_) BIT_IS_SET(ONE_WIRE_PIN, pin_)

uint8_t OneWireHolder::resetPulse() {
	
	uint8_t presenceImpulse = 0;
	
	ONE_WIRE_LOW(physicalPin_);
	ONE_WIRE_OUT(physicalPin_);
	_delay_us(500);
	ONE_WIRE_IN(physicalPin_);
	_delay_us(45);
	
	if(ONE_WIRE_SLV_CLRD(physicalPin_)) {
		presenceImpulse = 1;
	}
	
	_delay_us(470);
	return presenceImpulse;
}

void OneWireHolder::writeBit(uint8_t bit_) {
	
	ONE_WIRE_OUT(physicalPin_);
	_delay_us(5);
	
	if(bit_)
		ONE_WIRE_IN(physicalPin_);
		
	_delay_us(80);
	ONE_WIRE_IN(physicalPin_);
}

uint8_t OneWireHolder::readBit() {
	
	uint8_t bit_ = 0;
	ONE_WIRE_OUT(physicalPin_);
	_delay_us(2);
	ONE_WIRE_IN(physicalPin_);
	_delay_us(15);
	
	if(ONE_WIRE_SLV_SET(physicalPin_)) 
		bit_ = 1;
		
	return bit_;
}

void OneWireHolder::writeByte(uint8_t byte_) {
	
	uint8_t bitToSend = 0;
	for(uint8_t i = 0; i < 8; ++i) {
		bitToSend = (byte_ >> i) & 0x01;
		writeBit(bitToSend);
	}
	_delay_us(100);
}

uint8_t OneWireHolder::readByte() {
	
	uint8_t readByte_ = 0;
	for(uint8_t i = 0; i < 8; ++i) {
		if(readBit())
			readByte_ |= (0x01 << i);
		_delay_us(15);
	}
	return readByte_;
}