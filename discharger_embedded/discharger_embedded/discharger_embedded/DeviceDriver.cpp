/* 
* DeviceDriver.cpp
*
* Created: 18.04.2020 17:16:02
* Author: domin
*/


#include "DeviceDriver.h"
#include "StringProcessor.h"
#include "SafetyGuard.h"
#include "SimulationData.h"

DeviceDriver deviceDriver;

void DeviceDriver::run() {
	if(this->isRxDataReady())
		processNewData();
}

void DeviceDriver::processNewData() {
	StringProcessor sp(this->getRxData());
	
	if(sp.isSetParam("handshake")) {
		callbacks->handleHanshake();
	}
	else if(sp.isSetParam("id")) {
		parseSimParams(&sp);
	}
	else if(sp.isSetParam("chtic") && sp.isSetParam("start")) {
		callbacks->handleChticDetermStart();
	}
	else if(sp.isSetParam("chtic") && sp.isSetParam("read")) {
		callbacks->handleChticRead();
	}
	else if(sp.isSetParam("stop")) {
		callbacks->handleStop();
	}
	else {
		sendWarning(Device::Warning::RECEIVED_NOT_STANDARDIZED_DATA);
		sendDebug(this->getRxData(), this->getRxDataSize());
	}
}

void DeviceDriver::parseSimParams(StringProcessor * sp) {	
	if(!sp->isSetParam("I"))
		SafetyGuard::stopDevice(Device::Error::CURRENT_IS_REQUIRED);
		
	DrivingData data;
	data.id = sp->getUIntValue("id");
	data.current = sp->getUIntValue("I");
	data.tempLimit = sp->isSetParam("TL") ? sp->getUIntValue("TL") : 0xFFFF;
	data.voltLimit = sp->isSetParam("VL") ? sp->getUIntValue("VL") : 0xFFFF;
	callbacks->handleSimNewData(data);
}

void DeviceDriver::sendHandshakeReply() {
	printP(PSTR("{\"handshake\":\"DD\"}")), endl();
}

void DeviceDriver::sendDeviceHasStopped() {
	printP(PSTR("{\"stop\":\"stopped\"}")), endl();
}

void DeviceDriver::sendError(Device::Error errno) {
	printP(PSTR("{\"error\":%d}"), errno), endl();
}

void DeviceDriver::sendWarning(Device::Warning warnno) {
	printP(PSTR("{\"warn\":%d}"), warnno), endl();
}

void DeviceDriver::sendDebug(char * str, int32_t num) {
	printP(PSTR("{\"debug\":\"%s %ld\"}"), str, num), endl();
}

void DeviceDriver::sendDebug(char * str) {
	printP(PSTR("{\"debug\":\"%s\"}"), str), endl();
}

void DeviceDriver::sendSimulationData() {
	printP(
		PSTR("{\"id\":%d,\"I\":%d,\"bLV\":%d,\"bRV\":%d,\"bLT\":%d,\"bRT\":%d,\"HST\":%d}"),
		simData.getDrivingId(),
		simData.getMeasuredCurrent(),
		simData.getMeasuredBLV(),
		simData.getMeasuredBLT(),
		simData.getMeasuredBRV(),
		simData.getMeasuredBRT(),
		simData.getMeasuredHST()
	), endl();
}

void DeviceDriver::sendSimulationData(
	uint16_t id, int16_t I, 
	uint16_t bLV, uint16_t bLT, 
	uint16_t bRV, uint16_t bRT, uint16_t HST) {
	printP(
		PSTR("{\"id\":%d,\"I\":%d,\"bLV\":%d,\"bRV\":%d,\"bLT\":%d,\"bRT\":%d,\"HST\":%d}"),
		id, I, bLV,	bRV, bLT, bRT, HST
	), endl();
}

void DeviceDriver::sendCharacteristicData(uint8_t id, int16_t mV, int16_t I) {
	printP(
		PSTR("{\"chtic\":\"data\",\"id\":%d,\"mV\":%d,\"I\":%d}"),
		id, mV, I
	), endl();
}

void DeviceDriver::sendCharacteristicDone() {
	printP(PSTR("{\"chtic\":\"done\"}")), endl();
}
