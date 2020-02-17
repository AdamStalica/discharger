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


#define SIM_EPS 1
#define SIM_MAX_CURRENT 300
#define SIM_MIN_CURRENT 9
#define SIM_MAX_VOLT 5000

#define BTN_ACTIVE 0

#define SAFETY_TIMEOUT 10 // s
#define SAFETY_BTN_PRESS_TIMEOUT 5000 // s
#define BATT_VOLT_LIMIT 10000 // mV
#define RADIATOR_TEMP_LIMIT 8000 // 100 * °C
#define SAFETY_MAX_CURRENT (SIM_MAX_CURRENT + 50) // A


#define THERMOMETR_1_PIN PC6
#define THERMOMETR_2_PIN PC7
#define ONE_WIRE_PIN PINC
#define ONE_WIRE_PORT PORTC
#define ONE_WIRE_DDR DDRC

#define BLINKING_PERIOD 500 // ms
#define LED_BLUE PB0
#define LED_GREEN PB1
#define LED_RED PB2
#define LED_DDR DDRB
#define LED_PORT PORTB

#define STP_BTN PB3
#define STP_BTN_DDR DDRB
#define STP_BTN_PORT PORTB
#define STP_BTN_PIN PINB

#define MAX_TEMPERAUTRE_mCE1 5000
#define SAFETY_GUARD_INTERVAL 500
#define STOP_BTN_DURATION_MS 4000

#define DEBUG_MODE

#define SKIP_SECOND_PARAM 0xFFFFFFFF
#ifdef DEBUG_MODE

extern void debugLog(char * string, int32_t digit = SKIP_SECOND_PARAM);

#else

static void debugLog(char * string, int32_t digit = SKIP_SECOND_PARAM) { return; }
	
#endif

#endif /* GLOBALDEFS_H_ */