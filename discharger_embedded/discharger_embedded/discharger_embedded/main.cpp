/*
 * discharger_embedded.cpp
 *
 * Created: 06.10.2019 23:03:45
 * Author : domin
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "Discharger.h"

Discharger discharger;

int main(void)
{	
	sei();
    while (1) 
    {
		discharger.run();	
    }
}

ISR(USART0_RX_vect) {
	discharger.uart.isrUsart0RxHandler();
}

ISR(USART0_UDRE_vect) {
	discharger.uart.isrUsart0UdreHandler();
}

ISR(ADC_vect) {
	discharger.adc.isrADCVect();
}

ISR(TIMER0_COMPA_vect) {
	discharger.ms.isrTimer0CompBVect();
}