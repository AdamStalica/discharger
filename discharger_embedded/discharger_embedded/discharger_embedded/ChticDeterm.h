/* 
* ChticDeterm.h
*
* Created: 17.04.2020 14:53:40
* Author: domin
*/


#ifndef __CHTICDETERM_H__
#define __CHTICDETERM_H__

#include "GlobalDefs.h"
#include "ChticData.h"

class ChticDeterm :
public ChticData
{
	uint8_t id = 0;
	int16_t mv = 0;
	uint8_t progress = 0;
	uint8_t step = CHTIC_ZERO_STEP;

public:
	int16_t getMilivolts() {
		return mv;
	}

	uint8_t setCurrent(int16_t current) {
		++id;
		if (step == CHTIC_ZERO_STEP && current > CHTIC_ZERO_CURRENT) {
			step = CHTIC_NON_ZERO_STEP;
			mv -= CHTIC_ZERO_STEP;
		}
		else if (
		setPoint(mv, current) == CHTIC_OUT_OF_RANGE ||
		mv > CHTIC_VOLT_LIM ||
		current > CHTIC_CURRENT_LIM)
		{
			progress = 0;
			return CHTIC_DONE;
		}

		mv += step;
		return 0;
	}

	uint8_t isInProgress() {
		return progress;
	}

	void start() {
		progress = 1;
	}
	
	uint8_t getId() {
		return id;
	}
	
	void clear() {
		id = 0;
		mv = 0;
		progress = 0;
	}

};


#endif //__CHTICDETERM_H__
