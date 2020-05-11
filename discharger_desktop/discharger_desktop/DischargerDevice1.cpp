#include "DischargerDevice1.h"

DischargerDevice1::DischargerDevice1(QObject * parent, const QString & com, db::TestType testType, db::CurrentSource currSource) :
	DeviceInterface(parent, testType, currSource, 1, 1)
{
	/*
	comPortName = com;
	connect(&timer, &QTimer::timeout, this, &DischargerDevice1::timerTimeout);
	connect(&connectionTimer, &QTimer::timeout, this, &DischargerDevice1::connectionTimerTimeout);
	connectionTimer.setInterval(DISCHARGER_CONN_TIMEOUT);
	connectionTimer.setSingleShot(true);
	connect(serial, &serialPort::SerialPort::receivedLine, this, &DischargerDevice1::serialRecivedNewData);
	*/
}

DischargerDevice1::~DischargerDevice1() {

}

// TODO: log time
void DischargerDevice1::fetchCurrentToTest(int idLogInfo, std::function<void(bool, const QString & comment)> callback) {
	/*
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

	api->POST(API_GET_CURR, req, [this](WebApi::StatsEnum status, nlohmann::json && resp) {
		if (status == WebApi::API_OK) {
			sendingNewDataPeriod = resp.at("period").get<int>();
			logDataVec.reserve(resp.at("data").size());
			for (auto & log : resp.at("data")) {
				logDataVec.emplace_back(
					log.at("id_log_data").get<unsigned int>(),
					log.at(currSourceName).get<double>()
				);
			}
			std::sort(logDataVec.begin(), logDataVec.end());
			logDataVecIte = logDataVec.begin();
		}
		cb(status == WebApi::API_OK, resp.at("comment").get<std::string>().c_str());
	});
	*/
}

bool DischargerDevice1::isStopable() { 
	return TEST_TYPE != db::TestType::SIMULATION; 
}

void DischargerDevice1::connectToDevice() {
	/*
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
	*/
}

void DischargerDevice1::start() {
	/*
	if(TEST_TYPE == db::TestType::SIMULATION)
		estimetedTestTime = QTime::fromMSecsSinceStartOfDay(sendingNewDataPeriod * logDataVec.size());
	timer.setInterval(sendingNewDataPeriod);
	timer.start();
	timerTimeout();
	*/
}

void DischargerDevice1::stop() {
	/*
	timer.stop();
	sendStop();
	*/
}

bool DischargerDevice1::checkBatteryNumber(int numebrOfBatteries) {
	//return (numebrOfBatteries == BATT_NUM);
	return 0;
}

void DischargerDevice1::timerTimeout() {
	/*
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
	sendDrivingData(idCurrSim.val(), newCurrent, heatSinkTempLimit.val(), voltageLimit.val());
	*/
}

void DischargerDevice1::connectionTimerTimeout() {
	/*
	if (gotHandshake) return;
	serial->close();
	emit signalCanNotEstablishConnection();
	*/
}

void DischargerDevice1::serialRecivedNewData(const QString & line) {
	/*
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
		if(!gotHandshake)
			emit signalConnectionEstablished();
		gotHandshake = true;
	}
	else if (!data["sim"].is_null()) {
		// process new data
		handleNewMesures(data);
	}
	else if (!data["warn"].is_null()) {
		// process warning
		handleWarning(static_cast<dischargerDevice::Warning>(data["warn"].get<int>()));
	}
	else if (!data["error"].is_null()) {
		// process error
		handleError(static_cast<dischargerDevice::Error>(data["error"].get<int>()));
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
	*/
}

void DischargerDevice1::handleWarning(dischargerDevice::Warning warn) {
	//emit signalWarning(warn);
}

void DischargerDevice1::handleError(dischargerDevice::Error err) {
	/*
	timer.stop();
	serial->close();
	emit signalError(err);
	*/
}

void DischargerDevice1::handleNewMesures(const nlohmann::json & data) {
	/*
	current = data["I"].get<float>() / 100.0;
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

		if ((logDataVecIte + 1) == logDataVec.end())
			testFinished();
	}
	idCurrSim = idCurrSim.val() + 1;

	emit signalNewData(getDbSimData());
	*/
}

void DischargerDevice1::testFinished() {
	/*
	sendStop();
	timer.stop();
	*/
}

unsigned int DischargerDevice1::countProgress() {
	/*
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
	*/
	return 1;
}

void DischargerDevice1::sendHandshake() {
	/*
	serial->println(
		"{\"handshake\":\"PC\"}"
	);
	*/
}

void DischargerDevice1::sendStop() {
	/*
	serial->println(
		"{\"stop\":\"now\"}"
	);
	*/
}

void DischargerDevice1::sendDrivingData(unsigned int id, double current, double temperatureLimit, double voltageLimit) {
	/*
	nlohmann::json data;
	data["sim"] = "drive";
	data["id"] = id;
	data["I"] = int(current * 100 + 0.5);
	if (temperatureLimit != DBL_MAX)
		data["TL"] = int(temperatureLimit * 100 + 0.5);
	if (voltageLimit != DBL_MAX)
		data["VL"] = int(voltageLimit * 1000 + 0.5);
	
	serial->println(data.dump());
	*/
}
