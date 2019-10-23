/* 
* SimulationData.cpp
*
* Created: 15.10.2019 19:25:51
* Author: domin
*/

#include "SimulationData.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void SimulationData::processNewData() {
	
	char * data = (char*)this->getRxData();
	
	char * type = strstr(data, "handshake");
	if(type != NULL) {
		this->println("{\"handshake\":\"DD\"}");
	}
	
	type = strstr(data, "id");
	if(type != NULL) {
		
		if(inProgress)
			sendResponse();
		else {
			inProgress = 1;
		}
		
		char * begin = strchr(type, ':');
		if(begin == NULL) 
			return;
		++begin;
		
		currentId = (uint16_t)strtol(begin, &type, 10);
		
		begin = strchr(type, ':');
		if(begin == NULL)
			return;
		++begin;
		
		currentCurrent = (uint16_t)strtol(begin, &type, 10);
		
		begin = strchr(type, ':');
		if(begin == NULL)
			return;
		++begin;
		
		currentTemp = (uint16_t)strtol(begin, &type, 10);
	}
	
	type = strstr(data, "stop");
	if(type != NULL) {
		if(inProgress) {
			sendResponse();
			this->println("{\"stop\":\"stopped\"}");
			inProgress = 0;
		}
	}
}

void SimulationData::sendResponse() {
	
	sprintf(
		buff, 
		"{\"id\":%d,\"curr\":%d,\"bLV\":%d,\"bRV\":%d,\"bLT\":%d,\"bRT\":%d}",
		currentId,
		currentCurrent + 50, //measuredCurrent,
		(1210 - currentCurrent / 100), //measuredBLV,
		(1207 - currentCurrent / 100), //measuredBRV,
		2000,
		3000
	);	
	this->println(buff);
}

void SimulationData::logError(uint8_t errno) {
	sprintf(buff, "{\"error\":%d}", errno);
	this->println(buff);
}

void SimulationData::run() {
	if(this->isRxDataReady()) {
		processNewData();
	}
}