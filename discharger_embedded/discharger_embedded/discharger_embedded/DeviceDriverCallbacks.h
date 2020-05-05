/* 
* DeviceDriverCallbacks.h
*
* Created: 18.04.2020 19:03:15
* Author: domin
*/


#ifndef __DEVICEDRIVERCALLBACKS_H__
#define __DEVICEDRIVERCALLBACKS_H__

#include "DrivingData.h"
class DrivingData;

class DeviceDriverCallbacks {
public:	
	virtual void handleHanshake() = 0;
	virtual void handleStop() = 0;
	virtual void handleChticDetermStart() = 0;
	virtual void handleChticRead() = 0;
	virtual void handleSimNewData(const DrivingData & data) = 0;
	virtual void handleSetDACVolt(uint16_t mV) = 0;

}; //DeviceDriverCallbacks

#endif //__DEVICEDRIVERCALLBACKS_H__
