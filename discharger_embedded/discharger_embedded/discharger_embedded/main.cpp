/*
 * discharger_embedded.cpp
 *
 * Created: 06.10.2019 23:03:45
 * Author : domin
 */ 

#include "Discharger.h"

Discharger discharger;

#ifdef DEBUG_MODE
void debugLog(char * string, int32_t digit) {
	discharger.debugerUartFunction(string, digit);
}
#endif

int main(void)
{	
    while (1) 
    {
		discharger.run();	
    }
}

ISR(USART0_RX_vect) {
	discharger.isrUsart0RxHandler();
}

ISR(USART0_UDRE_vect) {
	discharger.isrUsart0UdreHandler();
}

ISR(ADC_vect) {
	discharger.isrADCVect();
}

ISR(TIMER0_COMPA_vect) {
	discharger.isrTimer0CompBVect();
}

ISR(WDT_vect) {
	discharger.isrWDT();
}
