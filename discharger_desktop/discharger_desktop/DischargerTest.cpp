#include "DischargerTest.h"
#include "ObjectFactory.h"

using namespace dischargerDevice;

DischargerTest::DischargerTest(
	QObject * parent, 
	const QString & comPort,
	db::TestType testType, 
	db::CurrentSource currSource, 
	int idBattLeft, 
	int idBattRight
)	:	DeviceInterface(parent, testType, currSource, idBattLeft, idBattRight),
		logData(this),
		comPort(comPort) {
	dev = ObjectFactory::getInstance<dischargerDevice::Device>();
	connect(dev, &Device::connected, this, &DischargerTest::handleConnected);
	connect(dev, &Device::connectionFailure, this, &DischargerTest::handleConnectionFailure);
	connect(dev, &Device::gotSimulationData, this, &DischargerTest::handleSimulationData);
	connect(dev, &Device::deviceHasStopped, this, &DischargerTest::handleDeviceHasStopped);
	connect(dev, static_cast<void(Device::*)(const QString &)>(&Device::error), this, &DischargerTest::handleError);
	connect(&drivingDataTimer, &QTimer::timeout, this, 
		testType == db::TestType::SIMULATION ? 
			&DischargerTest::sendSimDrivingData : &DischargerTest::sendTestDrivingData
	);
	connect(&logData, &LogSimulationData::logSimDataFetchSuccess, [this] {
		if(TEST_TYPE == db::TestType::SIMULATION)
			emit singalTestDataOk();
	});
	connect(&logData, &LogSimulationData::logSimDataFetchFailure, [this] {
		if (TEST_TYPE == db::TestType::SIMULATION)
			emit signalTestDataFailure();
	});	
}

bool DischargerTest::checkBatteryNumber(int numebrOfBatteries) {
	return (1 <= numebrOfBatteries && numebrOfBatteries <= 2);
}

inline bool DischargerTest::isTestCurrentEditable() {
	return TEST_TYPE != db::TestType::SIMULATION;
}

inline bool DischargerTest::isStartable() {
	return true;
}

inline bool DischargerTest::isStopable() {
	return TEST_TYPE != db::TestType::SIMULATION;
}

void DischargerTest::setupTestData() {
	if (TEST_TYPE == db::TestType::SIMULATION)
		logData.fetchLogSimData(idLogInfo, CURRENT_SOURCE);
	else
		emit singalTestDataOk();
}

void DischargerTest::connectToDevice() {
	dev->connectToDevice(comPort);
}

void DischargerTest::disconnectFromDevice() {
	dev->disconnectDevice();
}

void DischargerTest::start() {
	unsigned int period;
	if (TEST_TYPE == db::TestType::SIMULATION) {
		period = logData.getLogPeriod();
		sendSimDrivingData();
	}
	else {
		period = TEST_DEFAULT_PERIOD;
		sendTestDrivingData();
	}
	drivingDataTimer.setInterval(period);
	drivingDataTimer.start();
}

void DischargerTest::stop() {
	drivingDataTimer.stop();
	dev->sendStop();
}

void DischargerTest::setIdLogInfo(unsigned int idLogInfo) {
	this->idLogInfo = idLogInfo;
}

void DischargerTest::sendSimDrivingData() {
	if (logData.isTheEnd()) {
		stop();
	}
	else {
		testCurrent = logData.getCurrent(); 
		sendTestDrivingData();
		logData.next();
	}
}

void DischargerTest::sendTestDrivingData() {
	dev->sendSimDrivingData({
		idTestData++,
		testCurrent.get(),
		heatSinkTempLimit.get(),
		voltageLimit.get()
	});
}

void DischargerTest::handleConnected() {
	emit signalConnectionEstablished();
}

void DischargerTest::handleConnectionFailure() {
	emit signalCanNotEstablishConnection();
}

void DischargerTest::handleSimulationData(dischargerDevice::SimData simData) {
	auto dbData = db::SimData::fromDeviceSimData(simData);
	// TODO: Remove mult 10
	dbData.current = dbData.current.get() * 10;
	if (TEST_TYPE == db::TestType::SIMULATION) {
		logData.previous();
		dbData.idLogData = logData.getIdLogData();
		logData.next();
		progress = computeSimProgress();
	}
	else {
		progress = computeTestProgress(dbData);
	}
	emit signalNewData(dbData);
}

void DischargerTest::handleDeviceHasStopped() {
	emit signalFinished();
}

void DischargerTest::handleError(const QString & err) {
	drivingDataTimer.stop();
	emit signalError(err);
}

unsigned int DischargerTest::computeSimProgress() {
	return (idTestData * 100.0 / logData.size() + 0.5);
}

unsigned int DischargerTest::computeTestProgress(const db::SimData & dbData) {
	static float battLeftBeginVolt = -1,
		battRightBeginVolt = -1;
	if (battLeftBeginVolt == -1 && battRightBeginVolt == -1) {
		battLeftBeginVolt = dbData.battLeftVolt.get();
		battRightBeginVolt = dbData.battRightVolt.get();
	}
	float p1, p2 = 0.0;
	p1 = (battLeftBeginVolt - dbData.battLeftVolt.get()) / (battLeftBeginVolt - voltageLimit.get()) * 100.0 + 0.5;
	if (!isSingleBatteryTest()) {
		p1 = (battRightBeginVolt - dbData.battRightVolt.get()) / (battRightBeginVolt - voltageLimit.get()) * 100.0 + 0.5;
	}
	return std::max(p1, p2);
}
