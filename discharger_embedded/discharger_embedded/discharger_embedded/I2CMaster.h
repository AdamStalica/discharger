/* 
* I2CMaster.h
*
* Created: 14.10.2019 11:55:10
* Author: domin
*/


#ifndef __I2CMASTER_H__
#define __I2CMASTER_H__

#define I2C_READ 0x01
#define I2C_WRITE 0x00

#include <avr/io.h>
#include "UsartHolder.h"
#include "GlobalDefs.h"

class I2CMaster
{
protected:
	//UsartHolder * uart;
	
public:
	I2CMaster(unsigned long fScl = 100000UL, uint8_t prescaler = 1);
	
	/**
	*	Method to transmit data into addressed device
	*	@param address - Address of the device to transmit data.
	*	@param data - Data vector.
	*	@param length - Number of bits to be written.
	*	@return 0 if the transmition is successful.
	*/
	uint8_t transmit(uint8_t, uint8_t*, uint16_t);
	
	/**
	*	Method to receive data from  the device.
	*	@param address - Address of the device to request data.
	*	@param data - Data vector.
	*	@param length - Number of bits to receive.
	*	@return 0 if received correctly.
	*/
	uint8_t receive(uint8_t, uint8_t*, uint16_t);
	uint8_t writeReg(uint8_t, uint8_t, uint8_t*, uint16_t);
	uint8_t readReg(uint8_t, uint8_t, uint8_t*, uint16_t);
	~I2CMaster() {};
	
	//void setSerial(UsartHolder * uart) { this->uart = uart; } 
	
protected:
private:
	I2CMaster( const I2CMaster &c );
	I2CMaster& operator=( const I2CMaster &c );
	
	uint8_t write(uint8_t);
	uint8_t readAck();
	uint8_t readNack();
	void stop();
	uint8_t start(uint8_t);

};

#endif
