#include "DischargerDevice.h"
#include "DeviceEventsDecriptions.h"
#include "ObjectFactory.h"
#include <nlohmann/json.h>
#include <QDebug>

using namespace dischargerDevice;
using namespace nlohmann;

/*
	Estalishing an connection:
		1. Open port, if can not open emit connectionFilure and stop
		2. Send handshake and start connection timer. If timeout and did not get handshake send next, unless counter overflow then emit connectionFailure 
		3. Send device info request and start single shot timer, if timeout emit connectionFilure.
		4. If got device into emit connected.


*/

Device::Device(QObject *parent)
	:	QObject(parent),
		handshakeTimer(this)

{
	if (!ObjectFactory::hasInstance<serialPort::SerialPort>())
		throw std::exception("The instance of serial port class is required.");
	serial = ObjectFactory::getInstance<serialPort::SerialPort>();

	handshakeTimer.setInterval(RESPONSE_MAX_TIME);
	connect(&handshakeTimer, &QTimer::timeout, this, &dischargerDevice::Device::handleHandshakeTimerTimeout);
	connect(serial, &serialPort::SerialPort::opened, this, &dischargerDevice::Device::handlePortOpened);
	connect(serial, &serialPort::SerialPort::unableToOpen, this, &dischargerDevice::Device::handleUnableToOpen);
	connect(serial, &serialPort::SerialPort::receivedLine, this, &dischargerDevice::Device::handleReceivedLine);
}

void dischargerDevice::Device::clear() {
	gotHandshake = false;
	gotDeviceInfo = false;
	gotStop = false;
	newData.clear();
	deviceId = 0;
	deviceSoftwareVersion = 0;
	deviceFlashDate = QDate();
}

void Device::connectToDevice(const QString & comPort) {
	serial->setPort(comPort.toStdString());
	serial->setBaudrate(BOUDRATE);
	serial->setDataSize(DATA_SIZE);
	serial->setStopBits(STOP_BITS);
	serial->setParity(PARITY);

	serial->open();
}

void Device::disconnectDevice() {
	serial->close();
}

void Device::sendSimDrivingData(const SimDrivingData & data) {
	json j = data;
	serial->println(j.dump());
}

void Device::sendStop() {
	serial->println("{\"stop\":\"now\"}");
	QTimer::singleShot(RESPONSE_MAX_TIME, [this] {
		if (!gotStop)
			emit errorDeviceStopTimeout();
	});
}

void Device::sendStartOfChracteristicDetermination() {
	serial->println("{\"chtic\":\"start\"}");
}

void Device::sendReadCharacteristic() {
	serial->println("{\"chtic\":\"read\"}");
}

void dischargerDevice::Device::sendHandshake() {
	serial->println("{\"handshake\":\"PC\"}");
}

void dischargerDevice::Device::sendDeviceInfoRequest() {
	serial->println("{\"devInfo\":\"get\"}");
}

unsigned int Device::getDeviceId() {
	return deviceId;
}

unsigned int Device::getDeviceSoftwareVersion() {
	return deviceSoftwareVersion;
}

QDate Device::getDeviceFlashDate() {
	return deviceFlashDate;
}

void Device::handlePortOpened() {
	sendHandshake();
	handshakeTimer.start();
}

void Device::handleUnableToOpen() {
	emit connectionFailure();
}

void Device::handleHandshakeTimerTimeout() {
	if (gotHandshake) {
		handshakeTimer.stop();
	}
	else if (++handshakeTimerTimeoutCounter >= HANDSHAKE_MAX_ATTMEPT_NUM) {
		emit connectionFailure();
		handshakeTimer.stop();
	}
	else
		sendHandshake();
}

void Device::handleReceivedLine(const QString & line) {
	try {
		newData = json::parse(line.toStdString());
	}
	catch (const std::exception & ex) {
		return;
	}

	if (!newData["handshake"].is_null()) {
		processHandshake();
	}
	else if (!newData["sim"].is_null() && newData["sim"].get<std::string>() == "data") {
		processSimData();
	}
	else if (!newData["warn"].is_null()) {
		processWarning();
	}
	else if (!newData["error"].is_null()) {
		processError();
	}
	else if (!newData["stop"].is_null()) {
		processStop();
	}
	else if (!newData["debug"].is_null()) {
		processDebug();
	}
	else if (!newData["chtic"].is_null() && newData["chtic"].get<std::string>() == "data") {
		processCharacteristicPoint();
	}
	else if (!newData["chtic"].is_null() && newData["chtic"].get<std::string>() == "done") {
		processCharacteristicDone();
	}
	else if(!newData["devInfo"].is_null() && newData["devInfo"].get<std::string>() == "data") {
		processDeviceInfo();
	}
	else {
		qDebug() << line;
	}
}

void Device::processHandshake() {
	if (gotHandshake)
		return;
	gotHandshake = true;
	sendDeviceInfoRequest();
	QTimer::singleShot(RESPONSE_MAX_TIME, [this] {
		if (!gotDeviceInfo)
			emit connectionFailure();
	});
}

void Device::processSimData() {
	try {
		SimData simData = newData;
		emit gotSimulationData(simData);
	}
	catch (const std::exception & ex) {
		qDebug() << ex.what();
	}
}

void Device::processStop() {
	if (!gotStop)
		emit deviceHasStopped();
	gotStop = true;
}

void Device::processError() {
	Error errorNo = static_cast<Error>(newData["error"].get<int>());
	emit error(errorNo);
	emit error(QString::fromStdString(getErrorDescription(errorNo)));
}

void Device::processWarning() {
	Warning warnNo = static_cast<Warning>(newData["warn"].get<int>());
	emit warning(warnNo);
	emit warning(QString::fromStdString(getWarningDescription(warnNo)));
}

void Device::processDebug() {
	emit debug(QString::fromStdString(newData["debug"].get<std::string>()));
}

void Device::processCharacteristicPoint() {
	try {
		CharacteristicPoint chPoint = newData;
		emit gotCharacteristicPoint(chPoint);
	}
	catch (const std::exception & ex) {
		qDebug() << ex.what();
	}
}

void Device::processCharacteristicDone() {
	emit characteristicDone();
}

void Device::processDeviceInfo() {
	try {
		deviceId = newData["id"].get<int>();
		deviceSoftwareVersion = newData["v"].get<int>();
		deviceFlashDate = QDate(
			YEAR_OFFSET + newData["y"].get<int>(),
			newData["m"].get<int>(),
			newData["d"].get<int>()
		);

		if (!gotDeviceInfo)
			emit connected();
		gotDeviceInfo = true;
	}
	catch (const std::exception & ex) {
		qDebug() << ex.what();
	}
}
