/* 
* SimulationData.cpp
*
* Created: 15.10.2019 19:25:51
* Author: domin
*/

#include "SimulationData.h"
#include <avr/pgmspace.h>

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
			sendDeviceHasStopped();
		}
	}
}

void SimulationData::sendResponse() {
	
	aboutToSendNewData();
	//char str[] PROGMEM = "{\"id\":%d,\"curr\":%d,\"bLV\":%d,\"bRV\":%d,\"bLT\":%d,\"bRT\":%d}";
	//strcpy_P(_txBuffer, (PGM_P)pgm_read_word(str));
	sprintf(
		_txBuffer, 
		"{\"id\":%d,\"curr\":%d,\"bLV\":%d,\"bRV\":%d,\"bLT\":%d,\"bRT\":%d}",
		currentId,
		measuredCurrent,
		measuredBLV,
		measuredBRV,
		measuredBLT,
		measuredBRT
	);	
	
	this->println(_txBuffer);
}

void SimulationData::logError(uint16_t errno) {
	sprintf(_txBuffer, "{\"error\":%d}", errno);
	this->println(_txBuffer);
}

void SimulationData::run() {
	if(this->isRxDataReady()) {
		processNewData();
	}
}

void SimulationData::sendDeviceHasStopped() {

	stopDevice();
	this->println("{\"stop\":\"stopped\"}");
	currentId = 0;
	currentCurrent = 0;
	currentTemp = 0;
	inProgress = 0;
}

uint8_t SimulationData::simulationInProgress() {
	return currentId != 0;
}