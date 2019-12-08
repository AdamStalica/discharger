/*
 * GlobalDefs.h
 *
 * Created: 26.11.2019 23:26:05
 *  Author: domin
 */ 


#ifndef GLOBALDEFS_H_
#define GLOBALDEFS_H_

#include <avr/io.h>
#include <DeviceErrorEnum.h>

#define F_CPU 10240000UL

#define BAUDRATE 57600UL

#define THERMOMETR_1_PIN PC6
#define THERMOMETR_2_PIN PC7
#define ONE_WIRE_PIN PINC
#define ONE_WIRE_PORT PORTC
#define ONE_WIRE_DDR DDRC

#define LED_BLUE PB0
#define LED_GREEN PB1
#define LED_RED PB2
#define LED_DDR DDRB
#define LED_PORT PORTB

#define STP_BTN PB3
#define STP_BTN_DDR DDRB
#define STP_BTN_PORT PORTB
#define STP_BTN_PIN PINB

#define MAX_TEMPERAUTRE_mCE1 3000
#define SAFETY_GUARD_INTERVAL_MS 500
#define STOP_BTN_DURATION_MS 4000

#define DEBUG_MODE

#define SKIP_SECOND_PARAM 0xFFFFFFFF
#ifdef DEBUG_MODE

extern void debugLog(char * string, int32_t digit = SKIP_SECOND_PARAM);

#else

static void debugLog(char * string, int32_t digit = SKIP_SECOND_PARAM) { return; }
	
#endif

#endif /* GLOBALDEFS_H_ */