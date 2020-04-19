/* 
* DrivingData.h
*
* Created: 18.04.2020 20:45:39
* Author: domin
*/


#ifndef __DRIVINGDATA_H__
#define __DRIVINGDATA_H__

class SimulationData;
class DeviceDriver;

class DrivingData {

	uint16_t id = 0xFFFF, 
		current = 0xFFFF, 
		voltLimit = 0xFFFF, 
		tempLimit = 0xFFFF;
	
	friend class SimulationData;
	friend class DeviceDriver;
	
	void clear() {
		id = 0xFFFF;
		current = 0xFFFF;
		voltLimit = 0xFFFF;
		tempLimit = 0xFFFF;
	}
	
public:
	DrivingData & operator=(const DrivingData & oth) {
		id = oth.id;
		current = oth.current;
		if(oth.voltLimit != 0xFFFF)
			voltLimit = oth.voltLimit;
		if(oth.tempLimit != 0xFFFF)
			tempLimit = oth.tempLimit;
		return *this;
	}
	
}; //DrivingData

#endif //__DRIVINGDATA_H__
