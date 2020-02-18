/* 
* UsartHolder.h
*
* Created: 07.10.2019 22:59:58
* Author: domin
*/

#include <avr/pgmspace.h>
#include "GlobalDefs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#ifndef __USARTHOLDER_H__
#define __USARTHOLDER_H__

#define TX_BUFFER_SIZE 100
#define RX_BUFFER_SIZE 100

#define END_LINE_CHAR1 '\r'
#define END_LINE_CHAR2 '\n'
#define STR_END_CHAR '\0'


class UsartHolder
{
//variables
public:
protected:
private:

	char _txBuffer[TX_BUFFER_SIZE];
	uint8_t _txDataEnd = 0;
	uint8_t _txDataPtr = 0;

	char _rxBuffer[RX_BUFFER_SIZE];
	uint8_t _rxDataEnd = 0;
	uint8_t _rxDataReady = 0;

//functions
public:
	UsartHolder();
	~UsartHolder() {};
	
	void writeByte(uint8_t data);
	
	//virtual void rxDataReady() {};
	uint8_t isRxDataReady() { return _rxDataReady; }
	uint8_t getRxDataSize() { return _rxDataEnd; }
	char * getRxData() {  
		_rxDataEnd = 0;
		_rxDataReady = 0;
		return _rxBuffer; 
	}
	
	void print(const char * data, ...);
	void printP(const PROGMEM char * data, ...);
	void print(int32_t data);
	void endl();
	
	void isrUsart0RxHandler();
	void isrUsart0UdreHandler();

#ifdef DEBUG_MODE
	void debuger(char * string, int32_t digit);
#endif
	
protected:
private:
	UsartHolder( const UsartHolder &c );
	UsartHolder& operator=( const UsartHolder &c );
	void readData();
	void putBuffer();
	

}; //UsartHolder

#endif //__USARTHOLDER_H__
