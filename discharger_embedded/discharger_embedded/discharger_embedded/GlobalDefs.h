/*
 * GlobalDefs.h
 *
 * Created: 26.11.2019 23:26:05
 *  Author: domin
 */ 


#ifndef GLOBALDEFS_H_
#define GLOBALDEFS_H_

#include <avr/io.h>
#include <DeviceEventsDef.h>


/****************************************************************************************************/
/*												 SYS												*/
/****************************************************************************************************/
#define F_CPU 10240000UL
#define DEBUG_MODE


/****************************************************************************************************/
/*											   IO USAGE												*/
/*																									*/
/*		PA0		BATTERY LEFT	SINGLE ENDED INPUT													*/
/*		PA1		BATTERY RIGHT	SINGLE ENDED INPUT													*/
/*		PA2		LEM				NEGATIVE INPUT					100nF CONNECTED TO THE PA3			*/
/*		PA3		LEM				POSITIVE INPUT														*/
/*																									*/
/*		PB0		LED BLUE		ACTIVE LOW															*/
/*		PB1		LED GREEN		ACTIVE LOW															*/
/*		PB2		LED RED			ACTIVE LOW															*/
/*		PB3		STOP BUTTON		CONNECTED TO THE GND												*/
/*		PB5		MOSI			USB ASP - KANDA														*/
/*		PB6		MISO			USB ASP - KANDA														*/
/*		PB7		SCK				USB ASP	- KANDA														*/
/*																									*/
/*		RESET	RESET			USB ASP - KANDA														*/
/*																									*/
/*		PC0		SCL				I2C - MCP4725 					4.7k PULL UP						*/
/*		PC1		SDA				I2C - MCP4725 					4.7k PULL UP						*/
/*		PC5		1Wire			THERMOMETER	1 - HEAT SINK		4.7k PULL UP						*/
/*		PC6		1Wire			THERMOMETER 2 - BATTERY LEFT	4.7k PULL UP						*/
/*		PC7		1Wire			THERMOMETER 3 - BATTERY RIGHT	4.7k PULL UP						*/
/*																									*/
/*		PD0		RX0				INCOMING DATA FROM PC												*/
/*		PD1		TX0				OUTGOING DATA TO PC													*/
/*																									*/
/*		XTAL1	EXTERNAL CRYSTAL OSCILLATOR						22pF CONNECTED TO THE GND			*/
/*		XTAL2	EXTERNAL CRYSTAL OSCILLATOR						22pF CONNECTED TO THE GND			*/
/*		AVREF													100nF CONNECTED TO THE GND			*/
/*																									*/
/****************************************************************************************************/


/****************************************************************************************************/
/*											    USART												*/
/*																									*/
/*	Data size: 8 bit																				*/
/*	Stop bits: 2 bit																				*/
/*																									*/
/****************************************************************************************************/
#define BAUDRATE 57600UL
#define TX_INT_ENABLED


/****************************************************************************************************/
/*											  SIMULATION											*/
/****************************************************************************************************/
#define INTERPOLATION
#define SIM_EPS			1		// 10^-1 A
#define SIM_MAX_CURRENT 400		// 10^-1 A
#define SIM_MIN_CURRENT 9		// 10^-1 A
#define SIM_MAX_VOLT	5000	// mV


/****************************************************************************************************/
/*					    						SAFETY												*/
/****************************************************************************************************/
#define SAFETY_GUARD_INTERVAL			500						// ms
#define SAFETY_TIMEOUT					10000					// ms
#define SAFETY_BTN_PRESS_TIMEOUT		5000					// ms
#define BATT_VOLT_LIMIT_DEFAULT			10000					// mV
#define HEAT_SINK_TEMP_LIMIT_DEFAULT	8000					// 10^-2 �C
#define SAFETY_MAX_CURRENT				(SIM_MAX_CURRENT + 50)	// 10^-1A
#define BTN_ACTIVE						0
#define STP_BTN							PB3
#define STP_BTN_DDR						DDRB
#define STP_BTN_PORT					PORTB
#define STP_BTN_PIN						PINB


/****************************************************************************************************/
/*											   ONE WIRE												*/
/****************************************************************************************************/
#define ONE_WIRE_PIN	PINC
#define ONE_WIRE_PORT	PORTC
#define ONE_WIRE_DDR	DDRC


/****************************************************************************************************/
/*												DS18B20												*/
/****************************************************************************************************/
#define TEMP_READ_INTERVAL			800		// ms
#define THERM_CRC_NO_MATCH_MAX_WARN	10
#define THERM_CRC_NO_MATCH_MAX_ERR	60
#define THERMOMETER_1_PIN			PC5
#define THERMOMETER_2_PIN			PC6
#define THERMOMETER_3_PIN			PC7
#define THERMOMETER_NUM				3


/****************************************************************************************************/
/*												LED RGB												*/
/****************************************************************************************************/
#define BLINKING_PERIOD		500			// ms
#define LED_DDR				DDRB
#define LED_PORT			PORTB
#define LED_BLUE			PB0
#define LED_GREEN			PB1
#define LED_RED				PB2


/****************************************************************************************************/
/*												  ADC												*/
/****************************************************************************************************/
#define ADC_DIFF_3_2_10X	1
#define ADC_CH_NUM			3
#define ADC_MEASURE_FREQ	200UL	// Hz
// Channel 1, differential - PA0 positive, PA1 negative input
#define ADC_CH1_CONF		(((1 << MUX4) | (1 << MUX3) | (0 << MUX2) | (1 << MUX1) | (0 << MUX0)) >> ADC_DIFF_3_2_10X)
// Channel 2, PA2 - single ended input
#define ADC_CH2_CONF		((0 << MUX4) | (0 << MUX3) | (1 << MUX2) | (1 << MUX1) | (0 << MUX0))
// Channel 3, PA3 - single ended input
#define ADC_CH3_CONF		((0 << MUX4) | (0 << MUX3) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0))


/****************************************************************************************************/
/*												DEBUGING											*/
/****************************************************************************************************
#define SKIP_SECOND_PARAM 0xFFFFFFFF
#ifdef DEBUG_MODE
extern void debugLog(char * string, int32_t digit = SKIP_SECOND_PARAM);
#else
static void debugLog(char * string, int32_t digit = SKIP_SECOND_PARAM) { return; }
#endif
*/

















#define CHTIC_ZERO_STEP 100
#define CHTIC_NON_ZERO_STEP 10

#define CHTIC_ZERO_CURRENT 0

#define CHTIC_VOLT_LIM 5000
#define CHTIC_CURRENT_LIM 800
#define CHTIC_CURRENT_POINTS 50
#define CHTIC_OUT_OF_RANGE 1
#define CHTIC_DONE 1
#define CHTIC_TOO_HIGH_CURRENT 1

#define CHTIC_EEPROM_FLAG_ADDR 0
#define CHTIC_EEPROM_BEG 1
#define CHTIC_EEPROM_SIZE ((CHTIC_CURRENT_POINTS + 1) * 2)

#define CURR_DRIVER_ERROR -1
#define CURR_DRIVER_CORRECTION_RATIO 7 // 0 - 10





























#endif /* GLOBALDEFS_H_ */