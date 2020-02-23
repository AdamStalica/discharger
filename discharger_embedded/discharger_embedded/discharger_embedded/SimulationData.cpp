/* 
* SimulationData.cpp
*
* Created: 15.10.2019 19:25:51
* Author: domin
*/

#include "SimulationData.h"
#include "SafetyGuard.h"

Device::Error SimulationData::lastError = Device::Error::NO_ERROR;
Device::Warning SimulationData::lastWarn = Device::Warning::NO_WARNING;
uint16_t SimulationData::voltLimit = BATT_VOLT_LIMIT_DEFAULT;
uint16_t SimulationData::radiatorTempLimit = HEAT_SINK_TEMP_LIMIT_DEFAULT;
uint16_t SimulationData::measuredCurrent = 0;
uint16_t SimulationData::measuredBLV = 0;
uint16_t SimulationData::measuredBRV = 0;
uint16_t SimulationData::measuredBLT = 0;
uint16_t SimulationData::measuredBRT = 0;
uint16_t SimulationData::measuredHST = 0;
uint8_t SimulationData::inProgress = 0;

void SimulationData::processNewData() {
	
	char * data = this->getRxData();
	
	if(doesStrContainParam(data, "handshake")) {
		sendHandshake();
		return;
	}
	
	if(doesStrContainParam(data, "id")) {
		
		if(inProgress) {
			sendResponse();
		}
		else {
			inProgress = 1;
			simHasStarted();
		}
			
		currentId = getUIntValueFromStr(data, "id");
		
		if(doesStrContainParam(data, "I")) {
			currentCurrent = getUIntValueFromStr(data, "I");
		}
		else {
			SafetyGuard::stopDevice(Device::Error::CURRENT_IS_REQUIRED);
			return;
		}
		if(doesStrContainParam(data, "TL")) {
			radiatorTempLimit = getUIntValueFromStr(data, "TL");
		}
		if(doesStrContainParam(data, "VL")) {
			voltLimit = getUIntValueFromStr(data, "VL");
		}
		
		return;
	}
	
	if(doesStrContainParam(data, "stop")) {
		sendResponse();
		sendDeviceHasStopped();
		return;
	}
	
	logWarning(Device::Warning::RECEIVED_NOT_STANDARDIZED_DATA);
	debugLog(data, strlen(data));
}

void SimulationData::sendResponse() {
	
	aboutToSendNewData();	
	printP(
		PSTR("{\"id\":%d,\"I\":%d,\"bLV\":%d,\"bRV\":%d,\"bLT\":%d,\"bRT\":%d,\"HST\":%d}"),
		currentId,
		measuredCurrent,
		measuredBLV,
		measuredBRV,
		measuredBLT,
		measuredBRT,
		measuredHST
	);
	endl();
}

void SimulationData::sendHandshake() {
	printP(PSTR("{\"handshake\":\"DD\"}"));
	endl();
	//_comm_established = 1;
	communicationEstablished();
}

void SimulationData::sendError() {
	printP(PSTR("{\"error\":%d}"), lastError);
	endl();
}

void SimulationData::sendWarning() {
	printP(PSTR("{\"warn\":%d}"), lastWarn);
	endl();
}

void SimulationData::run() {
	if(this->isRxDataReady()) {
		processNewData();
	}
	
	if(lastError != Device::Error::NO_ERROR) {
		sendError();
		lastError = Device::Error::NO_ERROR;
	}
	if(lastWarn != Device::Warning::NO_WARNING) {
		sendWarning();
		lastWarn = Device::Warning::NO_WARNING;
	}
}

void SimulationData::setDeviceHasStopped()
{
	currentId = 0;
	currentCurrent = 0;
	inProgress = 0;
}

void SimulationData::sendDeviceHasStopped() {

	printP(PSTR("{\"stop\":\"stopped\"}"));
	endl();
	setDeviceHasStopped();
	raceivedStopDevice();
}
/*
uint8_t SimulationData::simulationInProgress() {
	return currentId != 0;
}
*/
uint8_t SimulationData::doesStrContainParam(char * str, char * param) {
	return (strstr(str, param) != nullptr);
}

uint16_t SimulationData::getUIntValueFromStr(char * str, char * name) {
	char * type = strstr(str, name);
	char * begin = strchr(type, ':') + 1;
	return strtol(begin, &type, 10);
}