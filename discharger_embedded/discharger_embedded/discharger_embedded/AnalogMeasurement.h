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


class AnalogMeasurement
{
//variables
public:
	enum AdcChannels {
		LEM,
		BLV,
		BRV
	};
	
private:
	
	volatile const uint8_t INPUT_CHANNELS[ADC_CH_NUM] = {
		ADC_CH1_CONF,	// ADC0 Differential pair input.
		ADC_CH2_CONF,	// ADC1 Single ended input.
		ADC_CH3_CONF	// ADC1 Single ended input.
	};
	
	uint8_t currentChannel = 0;
	volatile uint8_t rawADCFull = 0;
	volatile uint16_t rawADC[ADC_CH_NUM] = { 0 };
		
	int16_t avgADC[ADC_CH_NUM] = { 0 };
	int32_t sumADC[ADC_CH_NUM] = { 0 };
	uint16_t nAvgAdc = 0;
	
	uint16_t newValsFlags[ADC_CH_NUM] = { 0 };
		
	uint8_t isDiffrentialChannel(AdcChannels channel);
	
//functions
public:
	AnalogMeasurement();
	~AnalogMeasurement() {};
	
	void startConversion();
	void run();
	void isrADCVect();
	void countAverages();
	uint8_t isNewValueAvailable(AdcChannels channel);
	
	int16_t getAvgADC(AdcChannels channel);
	int16_t getADC(AdcChannels channel);

	static int16_t convertAdcToMillivolts(int16_t adc_);

};

#endif //__ANALOGMEASUREMENT_H__
