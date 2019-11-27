/*
 * GlobalDefs.h
 *
 * Created: 26.11.2019 23:26:05
 *  Author: domin
 */ 


#ifndef GLOBALDEFS_H_
#define GLOBALDEFS_H_

#include <avr/io.h>

#define F_CPU 10240000UL

#define BAUDRATE 57600UL

#define THERMOMETR_1_PIN PB0
#define THERMOMETR_2_PIN PB1
#define ONE_WIRE_PIN PINB
#define ONE_WIRE_PORT PORTB
#define ONE_WIRE_DDR DDRB


#define DEBUG_MODE

#define SKIP_SECOND_PARAM 0xFFFFFFFF
#ifdef DEBUG_MODE

extern void debugLog(char * string, int32_t digit = SKIP_SECOND_PARAM);

#else

static void debugLog(char * string, int32_t digit = SKIP_SECOND_PARAM) { return; }
	
#endif

#endif /* GLOBALDEFS_H_ */