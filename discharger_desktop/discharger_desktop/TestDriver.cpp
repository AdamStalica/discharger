#include "TestDriver.h"
#include "QMessageBox"

TestDriver::TestDriver(QObject *parent)
	: QObject(parent),
	ui(*dynamic_cast<TestGUI*>(parent))
{
	plot = new QCustomPlot(qobject_cast<QWidget *>(this->parent()));
	plot->hide();
	ui.appendEventsLine("Test driver constructor");
}

TestDriver::~TestDriver() {
}

void TestDriver::confChart() {
	ui.appendEventsLine("Setting up chart.");
	auto ans = QMessageBox::information(
		qobject_cast<QWidget *>(this->parent()), 
		"Chart properties", 
		"Show chart?", 
		QMessageBox::No, 
		QMessageBox::Yes
	);
	if (ans == QMessageBox::Yes) {
		ui.setChart(plot);
		plot->show();
	}
	else {
		ui.removeChart(plot);
		plot->hide();
	}
}

void TestDriver::setDevice(DeviceInterface * dev) {
	if (!devicePtr.isNull()) {
		throw std::exception("Another device is already set!");
	}
	devicePtr = QSharedPointer<DeviceInterface>(dev);
	
	connect(dev, &DeviceInterface::signalFinished, this, &TestDriver::deviceFinished);
	connect(dev, &DeviceInterface::signalError, this, &TestDriver::deviceErrorOccured);
	connect(dev, &DeviceInterface::signalWarning, this, &TestDriver::deviceWarningOccured);
	connect(dev, &DeviceInterface::signalNewData, this, &TestDriver::deviceNewData);

	devicePtr->connectToDevice();
}

void TestDriver::removeDevice() {
	devicePtr.reset();
}

void TestDriver::loadPageData() {
	ui.setTestPatametersData(prepareTestParametersData());
	if (devicePtr->getCurrentSource() == DeviceInterface::CurrentSource::NO_CURR_SOURCE)
		ui.setVarTestCurrent(QString::number(devicePtr->getTestCurrent().val()));
	ui.setVarVoltLimit(QString::number(devicePtr->getVoltageLimit().val()));
	ui.setVarHeatSinkTempLimit(QString::number(devicePtr->getHeatSinkTempLimit().val()));
}

void TestDriver::startTest() {
	// TODO: start test
	ui.appendEventsLine("Starting test");
	testState = TestStates::PROGRESS;
	devicePtr->start();
	testStartTime = QTime::currentTime();
}

void TestDriver::stopTest() {
	// TODO: stop test
	ui.appendEventsLine("Stopping test");
	testState = TestStates::REMOVED;
	devicePtr->stop();
	ui.setTestPatametersData(prepareTestParametersData());
}

void TestDriver::clear() {
	devicePtr->disconnect();
	removeDevice();
	testState = TestStates::READY;
	testStartTime = QTime();
	plot->clearGraphs();
}

void TestDriver::deviceFinished() {

}

void TestDriver::deviceNewData() {
	ui.setTestPatametersData(prepareTestParametersData());
}

void TestDriver::deviceErrorOccured(Device::Error error) {
	testState = TestStates::DEV_ERROR;
	ui.setTestPatametersData(prepareTestParametersData());
	ui.appendEventsLine("<img src=\"media/icons/error.ico\"> Error no. " + QString::number(error));
}

void TestDriver::deviceWarningOccured(Device::Warning warning) {

}

void TestDriver::prepareSimData(db::SimData & sd) {
	//if(devicePtr->getLogDataId())
	//	sd.idSimInfo = devicePtr->getLogDataId().val();

}

TestParametersData TestDriver::prepareTestParametersData() {
	auto sd = devicePtr->getDbSimData();
	TestParametersData data;
	data.setTestName(testName);
	data.setTestStatus(TEST_STATES.at(testState));
	data.setProgress(devicePtr->getProgress().val());
	bool noCurrSource = (devicePtr->getCurrentSource() == DeviceInterface::CurrentSource::NO_CURR_SOURCE);
	if (!noCurrSource) {
		data.setTestCurrent(devicePtr->getTestCurrent().val());
	}
	ui.setTestCurrentLineEditEnabled(noCurrSource);
	if (testStartTime.isValid()) {
		data.setTestBeganAt(testStartTime.toString(TIME_FORMAT));
		data.setTestTime(
			QTime::currentTime()
			.addMSecs(-1 * testStartTime.msecsSinceStartOfDay())
			.toString(TIME_FORMAT)
		);
		if (devicePtr->getEstimetedTestTime()) {
			data.setTestEstimatedEnd(
				testStartTime
				.addMSecs(devicePtr->getEstimetedTestTime().val().msecsSinceStartOfDay())
				.toString(TIME_FORMAT)
			);
			data.setEstimatedTime(devicePtr->getEstimetedTestTime().val().toString(TIME_FORMAT));
		}
	}
	if (sd.capacity) {
		data.setCapacity(sd.capacity.val());
	}
	else {
		// TODO: Calc 
	}
	if (sd.usedEnergy) {
		data.setConsumedEnergy(sd.usedEnergy.val());
	}
	else {

	}
	if (sd.heatSinkTemp)
		data.setHeatSinkTemp(sd.heatSinkTemp.val());
	data.setCurrent(sd.current.val());
	data.setBattLeftId(idBattLeft);
	if (sd.battLeftVolt)
		data.setBattLeftVolt(sd.battLeftVolt.val());
	if (sd.battLeftTemp)
		data.setBattLeftTemp(sd.battLeftTemp.val());
	if(!isSingleBattery()) {
		data.setSingleBatteryMode(false);
		data.setBattRightId(idBattRight);
		if (sd.battRightVolt)
			data.setBattRightVolt(sd.battRightVolt.val());
		if (sd.battRightTemp)
			data.setBattRightTemp(sd.battRightTemp.val());
	}
	return data;
}
