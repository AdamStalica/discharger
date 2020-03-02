#include "DischargerDevice.h"


/*
DischargerDevice::DischargerDevice()
{
}



*/

DischargerDevice::DischargerDevice(QObject * parent, const QString & com, DeviceInterface::CurrentSource currSource) :
	DeviceInterface(parent, currSource)
{
	comPortName = com;
	connect(&timer, &QTimer::timeout, this, &DischargerDevice::timerTimeout);
	battLeftVolt = 12.5;
	battRightVolt = 12.8;
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

void DischargerDevice::connectToDevice() {

}

void DischargerDevice::start() {
	estimetedTestTime = QTime::fromMSecsSinceStartOfDay(sendingNewDataPeriod * dataSize);// (QTime::currentTime().msecsSinceStartOfDay() + sendingNewDataPeriod * dataSize);
	timer.setInterval(sendingNewDataPeriod);
	timer.start();
}

void DischargerDevice::stop() {

	timer.stop();
}

bool DischargerDevice::checkBatteryNumber(int numebrOfBatteries)
{
	return (numebrOfBatteries == BATT_NUM);
}

void DischargerDevice::timerTimeout() {
	if (CURRENT_SOURCE != DeviceInterface::CurrentSource::NO_CURR_SOURCE) {
		if (queueOfLogData.empty()) {
			testFinished();
			return;
		}
		idLogData = queueOfLogData.front().first;
		testCurrent = queueOfLogData.front().second;
		queueOfLogData.pop();
	}

	current = testCurrent.val() ? testCurrent.val() - 0.5 : 0.0;

	battLeftVolt = battLeftVolt.val() - 0.025;
	battRightVolt = battRightVolt.val() - 0.034;

	battLeftTemp = 21.0 - (rand() % 100) / 30.0;
	battRightTemp = 23.0 - (rand() % 100) / 50.0;

	heatSinkTemp = 60.0 - (rand() % 100) / 10.0;


	progress = countProgress();
	// TMP!!!!
	if (progress.val() > 100) {
		handleError(Device::Error::STOPPED_VOLTAGE_TOO_LOW);
	}

	idCurrSim = idCurrSim.val() + 1;

	//newDataCallback();
	emit signalNewData();
}

void DischargerDevice::handleWarning(Device::Warning warn) {

}

void DischargerDevice::handleError(Device::Error err) {
	timer.stop();
	emit signalError(err);
}

void DischargerDevice::testFinished() {
	// TODO: send stop to device
	timer.stop();
	emit signalFinished();
}

unsigned int DischargerDevice::countProgress() {
	if (CURRENT_SOURCE == DeviceInterface::CurrentSource::NO_CURR_SOURCE) {
		static float battLeft1stVolt = -1,
			battRight1stVolt = -1;
		if (battLeft1stVolt == -1 || battRight1stVolt == -1) {
			battLeft1stVolt = battLeftVolt.val();
			battRight1stVolt = battRightVolt.val();
		}
		float b1 = (battLeft1stVolt - battLeftVolt.val()) / (battLeft1stVolt - voltageLimit.val()) * 100 + 0.5;
		float b2 = (battRight1stVolt - battRightVolt.val()) / (battRight1stVolt - heatSinkTempLimit.val()) * 100 + 0.5;
		return (b1 > b2 ? b1 : b2);
	}
	else {
		return (idCurrSim.val() * 100.0) / dataSize + 0.5;
	}
}


/*
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
		return (dataId * 100.0) / dataSize + 0.5;
	}
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
*/