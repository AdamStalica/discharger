/* 
* UsartHolder.cpp
*
* Created: 07.10.2019 22:59:58
* Author: domin
*/


#include "UsartHolder.h"
#include <avr/io.h>
#include <avr/interrupt.h>

UsartHolder::UsartHolder()
{
	uint16_t baudRate = (F_CPU / BAUDRATE / 16UL - 1);
	
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
	if(byte != END_LINE_CHAR2) {
		
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

void UsartHolder::print(const char * data, ...) {
	va_list arglist;
	va_start( arglist, data );
	_txDataEnd += vsprintf(&_txBuffer[_txDataEnd], data, arglist);	
	va_end( arglist );
	putBuffer();
}

void UsartHolder::printP(const PROGMEM char * data, ...) {
	va_list arglist;
	va_start( arglist, data );
	_txDataEnd += vsprintf_P(&_txBuffer[_txDataEnd], data, arglist);
	va_end( arglist );
	putBuffer();
}

void UsartHolder::print(int32_t data) {
	_txDataEnd += sprintf_P(&_txBuffer[_txDataEnd], PSTR("%ld"), data);
	putBuffer();
}

void UsartHolder::endl() {
	_txBuffer[_txDataEnd++] = END_LINE_CHAR1;
	_txBuffer[_txDataEnd++] = END_LINE_CHAR2;
	putBuffer();
}



#ifdef DEBUG_MODE
void UsartHolder::debuger(char * string, int32_t digit) {
	
	if(digit == SKIP_SECOND_PARAM)
		printP(PSTR("{\"debug\":\"%s\"}"), string);
	else 
		printP(PSTR("{\"debug\":\"%s %ld\"}"), string, digit);
	endl();
}
#endif