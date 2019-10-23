/* 
* UsartHolder.cpp
*
* Created: 07.10.2019 22:59:58
* Author: domin
*/


#include "UsartHolder.h"
#include <avr/io.h>
#include <avr/interrupt.h>

UsartHolder::UsartHolder(unsigned long baudRate, unsigned long fCpu)
{
	baudRate = (fCpu / baudRate / 16UL - 1);
	
	UBRR0H = (unsigned char)(baudRate >> 8);
	UBRR0L = (unsigned char)baudRate;		UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);	UCSR0B |= (1 << RXCIE0); 
}

void UsartHolder::isrUsart0RxHandler() {
	readData();
}

void UsartHolder::isrUsart0UdreHandler() {
	#ifdef TX_INT_ENABLED		if(_txDataPtr != _txDataEnd) {			writeByte(_txBuffer[_txDataPtr++]);		}		else {			UCSR0B &= ~(1 << UDRIE0);
			_txDataPtr = 0;
			_txDataEnd = 0;		}	#endif
}

void UsartHolder::writeByte(uint8_t data) {
	#ifndef TX_INT_ENABLED
		while ( !( UCSR0A & (1<<UDRE0)) );
	#endif
	
	UDR0 = data;
};

void UsartHolder::readData() {
	uint8_t byte = UDR0;
	if(	byte != END_LINE_CHAR1 && byte != END_LINE_CHAR2) {
		
		_rxBuffer[_rxDataEnd++] = byte;
		
		if(_rxDataEnd != (RX_BUFFER_SIZE - 1))
			return;
	}
	
	_rxBuffer[_rxDataEnd] = STR_END_CHAR;
	_rxDataReady = 1;
}

void UsartHolder::putBuffer() {
	#ifdef TX_INT_ENABLED
		UCSR0B |= (1 << UDRIE0); 
	#else
		while (_txDataPtr != _txDataEnd) {
			writeByte(_txBuffer[_txDataPtr++]);
		}
		_txDataPtr = 0;
		_txDataEnd = 0;
	#endif
}

void UsartHolder::print(uint8_t * data) {
	
	while(*data != STR_END_CHAR && _txDataEnd < TX_BUFFER_SIZE) {
		_txBuffer[_txDataEnd++] = *(data++);
	}
	putBuffer();
}

void UsartHolder::print(const char * data) {
	
	while(*data != STR_END_CHAR && _txDataEnd < TX_BUFFER_SIZE) {
		_txBuffer[_txDataEnd++] = *(data++);
	}
	putBuffer();
}

void UsartHolder::println(const char * data) {
	while(*data != STR_END_CHAR && _txDataEnd < (TX_BUFFER_SIZE - 1)) {
		_txBuffer[_txDataEnd++] = *(data++);
	}
	_txBuffer[_txDataEnd++] = END_LINE_CHAR1;
	putBuffer();
}