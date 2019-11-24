/* 
* AnalogMeasurement.cpp
*
* Created: 20.11.2019 10:11:48
* Author: domin
*/


#include "AnalogMeasurement.h"

AnalogMeasurement::AnalogMeasurement(unsigned long fCpu)
{
	
	ADMUX = (1 << REFS1) | (1 << REFS0)			// Internal 2.56V as VREF.
			| (0 << ADLAR)						// Right adjust result.
			| INPUT_CHANNELS[currentChannel];	// Select first channel as analog input.
			
	ADCSRA =  (1 << ADEN)						// ADC enable.
			| (1 << ADIE)						// ADC interrupt enable.
			| (1 << ADATE)						// ADC auto trigger enable.
			| (1 << ADPS2) | (1 << ADPS1)| (1 << ADPS0); // ADC input clock, F_CPU / 128
			
	// Triggering measurements by hardware.
	ADCSRB = (1 << ADTS2) | (0 << ADTS1) | (1 << ADTS0); // ADC measure triggered by timer1 in compare match B.
	TCCR1A =  (0 << COM1A1) | (0 << COM1A0) | (0 << COM1B1) | (0 << COM1B0)
			| (0 << FOC1A) | (0 << FOC1B) | (0 << WGM11) | (0 << WGM10);
			
	// New measure every 5ms -> 200 Hz.
	// fCpu = 10 240 000 Hz.
	TCCR1B =  (0 << WGM13) | (1 << WGM12) | (0 << WGM11) | (0 << WGM10) // CTC timer mode.
			| (0 << CS12) | (1 << CS11) | (0 << CS00);					// fCpu / 8
	OCR1B = OCR1A = (fCpu / ADC_MEASURE_F / 8);							// e.g. 10 240 000 / 200 / 8 = 6400 
	
}

AnalogMeasurement::~AnalogMeasurement()
{
}

void AnalogMeasurement::startConversion() {
	ADCSRA |= (1 << ADSC);
}

void AnalogMeasurement::run() {
	if(rawADCFull) {
		
		for(uint8_t i = 0; i < ADC_CH_NO; ++i) {
			sumADC[i] += rawADC[i];
			newValsFlags[i] = 1;
		}
		++nAvgAdc;
		
		rawADCFull = 0;
	}
}

void AnalogMeasurement::isrADCVect() {
	
	// Skip first measurement, process each channel twice.
	rawADC[(currentChannel >> 1)] = ADC;
	
	if(++currentChannel == (ADC_CH_NO << 1)) {
		currentChannel = 0;
		rawADCFull  = 1;
	}
	
	ADMUX = (ADMUX & 0xE0) | INPUT_CHANNELS[currentChannel];
	
	TIFR1 |= (1 << OCF1B); // Clear timer1 compare match B interrupt, enable next conversion.
}

uint16_t AnalogMeasurement::getAvgADC(adcChannels channel) {
	return avgADC[channel];
}

uint16_t AnalogMeasurement::getADC(adcChannels channel) {
	newValsFlags[channel] = 0;
	return (nAvgAdc ? (sumADC[channel] / nAvgAdc) : avgADC[channel]);
}

void AnalogMeasurement::countAverages() {
	for (uint8_t i = 0; i < ADC_CH_NO; ++i) {
		avgADC[i] = sumADC[i] / nAvgAdc;
		sumADC[i] = 0;
	}
	nAvgAdc = 0;
}

uint8_t AnalogMeasurement::isNewValueAvailable(adcChannels channel) {
	return newValsFlags[channel];
}

