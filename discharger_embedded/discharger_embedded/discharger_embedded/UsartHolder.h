/* 
* UsartHolder.h
*
* Created: 07.10.2019 22:59:58
* Author: domin
*/

#include <avr/io.h>

#ifndef __USARTHOLDER_H__
#define __USARTHOLDER_H__

#define TX_INT_ENABLED

#define TX_BUFFER_SIZE 100
#define RX_BUFFER_SIZE 100

#define END_LINE_CHAR1 '\n'
#define END_LINE_CHAR2 '\r'
#define STR_END_CHAR '\0'

/*
#ifndef F_CPU
	# warning "F_CPU has not been defined!"
	#define F_CPU 1000000
#endif
*/

class UsartHolder
{
//variables
public:
protected:
private:
	uint8_t _txBuffer[TX_BUFFER_SIZE];
	uint8_t _txDataEnd = 0;
	uint8_t _txDataPtr = 0;

	uint8_t _rxBuffer[RX_BUFFER_SIZE];
	uint8_t _rxDataEnd = 0;
	uint8_t _rxDataReady = 0;

//functions
public:
	UsartHolder(unsigned long baudRate, unsigned long fCpu);
	~UsartHolder() {};
	
	void writeByte(uint8_t data);
	
	//virtual void rxDataReady() {};
	uint8_t isRxDataReady() { return _rxDataReady; }
	uint8_t getRxDataSize() { return _rxDataEnd; }
	uint8_t * getRxData() {  
		_rxDataEnd = 0;
		_rxDataReady = 0;
		return _rxBuffer; 
	}
	
	void print(uint8_t * data);
	void print(const char * data);
	void println(const char * data);
	
	void isrUsart0RxHandler();
	void isrUsart0UdreHandler();
	
	
protected:
private:
	UsartHolder( const UsartHolder &c );
	UsartHolder& operator=( const UsartHolder &c );
	void readData();
	void putBuffer();
	

}; //UsartHolder

#endif //__USARTHOLDER_H__
