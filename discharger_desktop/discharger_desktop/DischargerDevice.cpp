#include "DischargerDevice.h"


/*
DischargerDevice::DischargerDevice()
{
}



*/

DischargerDevice::DischargerDevice(QObject * parent, const QString & com, DeviceInterface::CurrentSource currSource) :
	QObject(parent),
	CURRENT_SOURCE(currSource)
{
	comPortName = com;
}

DischargerDevice::~DischargerDevice() {

}

// TODO: log time
void DischargerDevice::fetchCurrentToTest(int idLogInfo, std::function<void(bool, const QString & comment)> callback) {
	if (CURRENT_SOURCE == DeviceInterface::CurrentSource::NO_CURR_SOURCE) {
		throw std::exception("This current source not support such a functionality");
	}

	auto api = ObjectFactory::getInstance<WebApi>();
	this->idLogInfo = idLogInfo;
	static std::function<void(bool, const QString & comment)> cb = callback;

	if (CURRENT_SOURCE == DeviceInterface::CurrentSource::MOTOR) {
		currSourceName = DB_MOTOR_CURR;
	}

	nlohmann::json req{
		{"id_log_info",  std::to_string(idLogInfo)},
		{"curr_source", currSourceName}
	};

	api->POST(API_GET_CURR, req, [this](bool success, std::string && resp) {
		nlohmann::json response = nlohmann::json::parse(resp);
		if (success) {

			sendingNewDataPeriod = response["period"].get<int>();
			dataSize = response["data"].size();
			for (auto & log : response["data"]) {
				queueOfLogData.emplace(
					log["id_log_data"].get<unsigned int>(),
					log[currSourceName]
				);
			}
		}
		cb(success, response["comment"].get<std::string>().c_str());
	});
}

void DischargerDevice::connect()
{
}

void DischargerDevice::start()
{
}

void DischargerDevice::stop()
{
}

void DischargerDevice::setOnErrorCallback(std::function<void(Device::Error)> errCallback) {
	errorCallback = errCallback;
}

void DischargerDevice::setOnWarningCallback(std::function<void(Device::Warning)> warnCallback) {
	waraningCallback = warnCallback;
}

void DischargerDevice::setOnNewDataCallback(std::function<void(void)> dataCallback) {
	newDataCallback = dataCallback;
}

unsigned int DischargerDevice::getLogInfoId() {
	if (CURRENT_SOURCE == DeviceInterface::CurrentSource::NO_CURR_SOURCE) {
		throw std::exception("This current source not support such a functionality");
	}
	return idLogInfo;
}

unsigned int DischargerDevice::getLogDataId() {
	if (CURRENT_SOURCE == DeviceInterface::CurrentSource::NO_CURR_SOURCE) {
		throw std::exception("This current source not support such a functionality");
	}
	return idLogData;
}

unsigned int DischargerDevice::getProgress() {
	if (CURRENT_SOURCE == DeviceInterface::CurrentSource::NO_CURR_SOURCE) {
		static float battLeft1stVolt = -1,
			battRight1stVolt = -1;
		if (battLeft1stVolt == -1 || battRight1stVolt == -1) {
			battLeft1stVolt = battLeftVolt;
			battRight1stVolt = battRightVolt;
		}
		float b1 = (battLeft1stVolt - battLeftVolt) / (battLeft1stVolt - voltLimit) * 100;
		float b2 = (battRight1stVolt - battRightVolt) / (battRight1stVolt - voltLimit) * 100;
		return (b1 > b2 ? b1 : b2);
	}
	else {
		return (dataId / dataSize * 100);
	}
}

float DischargerDevice::getTestCurrent() {
	if (CURRENT_SOURCE == DeviceInterface::CurrentSource::NO_CURR_SOURCE) {
		throw std::exception("This current source not support such a functionality");
	}
	return testCurrent;
}

void DischargerDevice::setTestCurrent(float current) {
	if (CURRENT_SOURCE != DeviceInterface::CurrentSource::NO_CURR_SOURCE) {
		throw std::exception("This current source not support such a functionality");
	}
	testCurrent = current;
}

void DischargerDevice::setVoltageLimit(float volt) {
	voltLimit = volt;
}

void DischargerDevice::setHeatSinkTempLimit(float tempLimit) {
	heatSinkTempLimit = tempLimit;
}

bool DischargerDevice::hasEstimatedTestTime() {
	return (CURRENT_SOURCE != DeviceInterface::CurrentSource::NO_CURR_SOURCE);
}

QTime DischargerDevice::getEstimatedTestTime() {
	if (CURRENT_SOURCE == DeviceInterface::CurrentSource::NO_CURR_SOURCE) {
		throw std::exception("This current source not support such a functionality");
	}
	return estSimTime;
}

bool DischargerDevice::checkBatteryNumber(int numebrOfBatteries)
{
	return (numebrOfBatteries == BATT_NUM);
}
