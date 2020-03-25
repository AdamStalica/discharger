#include "DischargerDevice.h"

DischargerDevice::DischargerDevice(QObject * parent, const QString & com, db::TestType testType, db::CurrentSource currSource) :
	DeviceInterface(parent, testType, currSource)
{
	comPortName = com;
	connect(&timer, &QTimer::timeout, this, &DischargerDevice::timerTimeout);
	connect(&connectionTimer, &QTimer::timeout, this, &DischargerDevice::connectionTimerTimeout);
	connectionTimer.setInterval(DISCHARGER_CONN_TIMEOUT);
	connectionTimer.setSingleShot(true);
	connect(serial, &serialPort::SerialPort::receivedLine, this, &DischargerDevice::serialRecivedNewData);
}

DischargerDevice::~DischargerDevice() {

}

// TODO: log time
void DischargerDevice::fetchCurrentToTest(int idLogInfo, std::function<void(bool, const QString & comment)> callback) {
	if (TEST_TYPE != db::TestType::SIMULATION) {
		throw std::exception("This current source not support such a functionality");
	}

	auto api = ObjectFactory::getInstance<WebApi>();
	this->idLogInfo = idLogInfo;
	static std::function<void(bool, const QString & comment)> cb = callback;

	if (CURRENT_SOURCE == db::CurrentSource::MOTOR) {
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
			logDataVec.reserve(response["data"].size());
			for (auto & log : response["data"]) {
				logDataVec.emplace_back(
					log["id_log_data"].get<unsigned int>(),
					log[currSourceName].get<double>()
				);
			}
			std::sort(logDataVec.begin(), logDataVec.end());
			logDataVecIte = logDataVec.begin();
		}
		cb(success, response["comment"].get<std::string>().c_str());
	});
}

bool DischargerDevice::isStopable() { 
	return TEST_TYPE != db::TestType::SIMULATION; 
}

void DischargerDevice::connectToDevice() {
	serial->setPortQ(comPortName);
	serial->setBaudrate(DISCHARGER_BOUDRATE);
	serial->setDataSize(DISCHARGER_DATA_SIZE);
	serial->setStopBits(DISCHARGER_STOP_BITS);
	serial->setParity(DISCHARGER_PARITY);
	serial->open();
	connectionTimer.start();

	connect(serial, &serialPort::SerialPort::opened, [this] {
		this->sendHandshake();
	});
}

void DischargerDevice::start() {
	if(TEST_TYPE == db::TestType::SIMULATION)
		estimetedTestTime = QTime::fromMSecsSinceStartOfDay(sendingNewDataPeriod * logDataVec.size());
	timer.setInterval(sendingNewDataPeriod);
	timer.start();
	timerTimeout();
}

void DischargerDevice::stop() {
	timer.stop();
	sendStop();
}

bool DischargerDevice::checkBatteryNumber(int numebrOfBatteries) {
	return (numebrOfBatteries == BATT_NUM);
}

void DischargerDevice::timerTimeout() {
	float newCurrent = testCurrent.val();
	if (TEST_TYPE == db::TestType::SIMULATION) {
		static bool isFirst = true;
		if (isFirst)
			newCurrent = (*logDataVecIte).current;
		else if ((logDataVecIte + 1) != logDataVec.end())
			newCurrent = (*(logDataVecIte + 1)).current;
		else {
			// TODO: handle out of ragne
			throw std::exception("Out of range");
		}
		isFirst = false;
	}
	sendDrivingData(idCurrSim, newCurrent, heatSinkTempLimit.val(), voltageLimit.val());
}

void DischargerDevice::connectionTimerTimeout() {
	if (gotHandshake) return;
	serial->close();
	emit signalCanNotEstablishConnection();
}

void DischargerDevice::serialRecivedNewData(const QString & line) {
	nlohmann::json data;
	try {
		data = nlohmann::json::parse(line.toStdString());
	}
	catch (const std::exception & ex) {
		qDebug() << ex.what();
		return;
	}
	if (!data["handshake"].is_null()) {
		// process handshake
		gotHandshake = true;
		emit signalConnectionEstablished();
	}
	else if (!data["id"].is_null()) {
		// process new data
		handleNewMesures(data);
	}
	else if (!data["warn"].is_null()) {
		// process warning
		handleWarning(static_cast<Device::Warning>(data["warn"].get<int>()));
	}
	else if (!data["error"].is_null()) {
		// process error
		handleError(static_cast<Device::Error>(data["error"].get<int>()));
	}
	else if (!data["stop"].is_null()) {
		// process stop
		ObjectFactory::getInstance<serialPort::SerialPort>()->close();
		emit signalFinished();
	}
	else if (!data["debug"].is_null()) {
		// process debug
		emit signalDebugMsg(data["debug"].get<std::string>().c_str());
	}
}

void DischargerDevice::handleWarning(Device::Warning warn) {
	emit signalWarning(warn);
}

void DischargerDevice::handleError(Device::Error err) {
	timer.stop();
	serial->close();
	emit signalError(err);
}

void DischargerDevice::handleNewMesures(const nlohmann::json & data) {
	current = data["I"].get<float>() / 10.0;
	battLeftVolt = data["bLV"].get<float>() / 1000.0;
	battRightVolt = data["bRV"].get<float>() / 1000.0;
	battLeftTemp = data["bLT"].get<float>() / 100.0;
	battRightTemp = data["bRT"].get<float>() / 100.0;
	heatSinkTemp = data["HST"].get<float>() / 100.0;
	progress = countProgress();

	if (TEST_TYPE == db::TestType::SIMULATION) {
		idLogData = (*logDataVecIte).idLogData;
		testCurrent = (*logDataVecIte).current;
		++logDataVecIte;
		if (logDataVecIte == logDataVec.end())
			testFinished();
	}
	idCurrSim = idCurrSim.val() + 1;

	emit signalNewData(getDbSimData());
}

void DischargerDevice::testFinished() {
	sendStop();
	timer.stop();
}

unsigned int DischargerDevice::countProgress() {
	if (TEST_TYPE == db::TestType::SIMULATION) {
		static float battLeft1stVolt = -1,
			battRight1stVolt = -1;
		if (battLeft1stVolt == -1 || battRight1stVolt == -1) {
			battLeft1stVolt = battLeftVolt.val();
			battRight1stVolt = battRightVolt.val();
		}
		float b1 = (battLeft1stVolt - battLeftVolt.val()) / (battLeft1stVolt - voltageLimit.val()) * 100 + 0.5;
		float b2 = (battRight1stVolt - battRightVolt.val()) / (battRight1stVolt - voltageLimit.val()) * 100 + 0.5;
		return (b1 > b2 ? b1 : b2);
	}
	else {
		return (idCurrSim.val() * 100.0) / logDataVec.size() + 0.5;
	}
}

void DischargerDevice::sendHandshake() {
	serial->println(
		"{\"handshake\":\"PC\"}"
	);
}

void DischargerDevice::sendStop() {
	serial->println(
		"{\"stop\":\"now\"}"
	);
}

void DischargerDevice::sendDrivingData(unsigned int id, double current, double temperatureLimit, double voltageLimit) {
	nlohmann::json data;
	data["id"] = id;
	data["I"] = int(current * 100 + 0.5);
	if (temperatureLimit != DBL_MAX)
		data["TL"] = int(temperatureLimit * 100 + 0.5);
	if (voltageLimit != DBL_MAX)
		data["VL"] = int(voltageLimit * 1000 + 0.5);
	
	serial->println(data.dump());
}
