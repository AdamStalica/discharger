/* 
* ChticData.h
*
* Created: 17.04.2020 14:52:42
* Author: domin
*/


#ifndef __CHTICDATA_H__
#define __CHTICDATA_H__

#include "GlobalDefs.h"
#include "SimulationData.h"
#include "DeviceDriver.h"
#include <avr/eeprom.h>


// [ VOLT_0, CURR_0, CURR_1, ... ]
class ChticData
{
	#define VOLT_0 0
	#define CURR_N(N) (N + 1)
	#define DATA_N(N) (N - 1)

	int16_t data[CHTIC_CURRENT_POINTS + 1] = { 0 };
	int8_t rangeBegin = CURR_N(0);

	uint8_t getChticId() {
		return eeprom_read_byte((uint8_t *)CHTIC_EEPROM_FLAG_ADDR);
	}

	protected:
	uint8_t setPoint(int16_t mv, int16_t curr) {
		if (data[VOLT_0] == 0 || curr <= CHTIC_ZERO_CURRENT) {
			data[VOLT_0] = mv;
			data[CURR_N(0)] = curr;
		}
		else {
			uint8_t id = CURR_N((mv - data[VOLT_0]) / CHTIC_NON_ZERO_STEP);
			if (id > CHTIC_CURRENT_POINTS)
			return CHTIC_OUT_OF_RANGE;
			data[id] = curr;
		}
		return 0;
	}

	public:
	void loadFromEEPROM() {
		uint8_t id = getChticId();
		if(id == 0xFF) {
			deviceDriver.sendWarning(Device::Warning::NO_CHTIC_IN_EEPROM_MEMORY);
			return;
		}
		eeprom_read_block(
			(void *)&data, 
			(const void *)CHTIC_EEPROM_BEG, 
			CHTIC_EEPROM_SIZE
		);
	}

	void storeInEEPROM() {
		uint8_t id = getChticId();
		if(++id == 0xFF) 
			id = 1;
		eeprom_write_byte((uint8_t *)CHTIC_EEPROM_FLAG_ADDR, id);
		eeprom_write_block(
			(const void*)&data, 
			(void *)CHTIC_EEPROM_BEG, 
			CHTIC_EEPROM_SIZE
		);
	}

	uint8_t moveRangeTo(int16_t current) {
		if (current <= CHTIC_ZERO_CURRENT) {
			rangeBegin = CURR_N(0);
			return 0;
		}
		
		for (uint8_t i = CURR_N(0); (i + 1) < CHTIC_CURRENT_POINTS; ++i) {
			if (data[i] <= current && data[i + 1] > current) {
				rangeBegin = i;
				return 0;
			}
		}
		return CHTIC_TOO_HIGH_CURRENT;
	}

	int16_t getRangeBeginMv() const {
		return data[VOLT_0] + CHTIC_NON_ZERO_STEP * DATA_N(rangeBegin);
	}

	int16_t getRangeBeginCurrent() const {
		return data[rangeBegin];
	}

	int16_t getRangeEndMv() const {
		return getRangeBeginMv() + CHTIC_NON_ZERO_STEP;
	}

	int16_t getRangeEndCurrent() const {
		return data[rangeBegin + 1];
	}
	
	uint8_t readPointAt(uint8_t id, int16_t & mV, int16_t & I) {
		if(id < CHTIC_CURRENT_POINTS) {
			mV = data[VOLT_0] + id * CHTIC_NON_ZERO_STEP;
			I = data[CURR_N(id)];
		}
		return (id < CHTIC_CURRENT_POINTS);
	}
};


#endif //__CHTICDATA_H__
