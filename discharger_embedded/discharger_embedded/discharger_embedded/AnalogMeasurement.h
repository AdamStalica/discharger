/* 
* AnalogMeasurement.h
*
* Created: 20.11.2019 10:11:48
* Author: domin
*/


#ifndef __ANALOGMEASUREMENT_H__
#define __ANALOGMEASUREMENT_H__

#include <avr/io.h>
#include "GlobalDefs.h"

#define ADC_CH_NO 1
#define ADC_MEASURE_F 200UL

class AnalogMeasurement
{
//variables
public:

	enum adcChannels {
		LEM	
	};
	
private:
	
	const uint8_t INPUT_CHANNELS[ADC_CH_NO] = {
		((1 << MUX4) | (0 << MUX4) | (0 << MUX3) | (0 << MUX2) | (0 << MUX1) | (0 << MUX0))	// ADC0 Single ended input.
	};
	
	uint8_t currentChannel = 0;
	volatile uint8_t rawADCFull = 0;
	volatile uint16_t rawADC[ADC_CH_NO] = { 0 };
		
	uint16_t avgADC[ADC_CH_NO] = { 0 };
	uint32_t sumADC[ADC_CH_NO] = { 0 };
	uint16_t nAvgAdc = 0;
	
	uint16_t newValsFlags[ADC_CH_NO] = { 0 };
	
//functions
public:
	AnalogMeasurement();
	~AnalogMeasurement();
	
	void startConversion();
	void run();
	void isrADCVect();
	void countAverages();
	uint8_t isNewValueAvailable(adcChannels channel);
	
	uint16_t getAvgADC(adcChannels channel);
	uint16_t getADC(adcChannels channel);

};

#endif //__ANALOGMEASUREMENT_H__
