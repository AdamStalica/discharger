#include "TestDriver.h"
#include "QMessageBox"

TestDriver::TestDriver(QObject *parent)
	: QObject(parent),
	ui(*dynamic_cast<TestGUI*>(parent))
{
	chart = new QLabel("Chart", qobject_cast<QWidget *>(this->parent()));
	chart->hide();
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
		ui.setChart(chart);
		chart->show();
	}
	else {
		ui.removeChart(chart);
		chart->hide();
	}
}

void TestDriver::setDevice(DeviceInterface * dev) {
	if (devicePtr.use_count()) {
		throw std::exception("Another device is already set!");
	}
	devicePtr = std::shared_ptr<DeviceInterface>(dev);

	devicePtr->setOnNewDataCallback([this] { deviceNewData(); });
	devicePtr->setOnErrorCallback([this](Device::Error error) {
		deviceErrorOccured(error);
	});
	devicePtr->setOnWarningCallback([this](Device::Warning warn) {
		deviceWarningOccured(warn);
	});
}

void TestDriver::removeDevice() {
	devicePtr.reset();
}

void TestDriver::loadPageData() {
	ui.setTestPatametersData(prepareTestParametersData());
	if (devicePtr->getCurrentSource() == DeviceInterface::CurrentSource::NO_CURR_SOURCE)
		ui.setVarTestCurrent(QString::number(devicePtr->getTestCurrent()));
	ui.setVarVoltLimit(QString::number(devicePtr->getVoltageLimit()));
	ui.setVarHeatSinkTempLimit(QString::number(devicePtr->getHeatSinkTempLimit()));
}

void TestDriver::deviceNewData() {

}

void TestDriver::deviceErrorOccured(Device::Error error) {

}

void TestDriver::deviceWarningOccured(Device::Warning warning) {

}

TestParametersData TestDriver::prepareTestParametersData() {
	TestParametersData data;
	data.setTestName(testName);
	data.setTestStatus(TEST_STATES.at(testState));
	data.setProgress(devicePtr->getProgress());
	bool noCurrSource = (devicePtr->getCurrentSource() == DeviceInterface::CurrentSource::NO_CURR_SOURCE);
	if (!noCurrSource) {
		data.setTestCurrent(devicePtr->getTestCurrent());
	}

	ui.setTestCurrentLineEditEnabled(noCurrSource);
	// time began at
	// est end
	// test time
	// est time
	if (devicePtr->hasCapacity()) {
		data.setCapacity(devicePtr->getCapacity());
	}
	else {
		// TODO: Calc 
	}
	if (devicePtr->hasConsumedEnergy()) {
		data.setConsumedEnergy(devicePtr->getConsumedEnergy());
	}
	else {

	}
	if (devicePtr->hasHeatSinkTemp())
		data.setHeatSinkTemp(devicePtr->getHeatSinkTemp());
	data.setCurrent(devicePtr->getCurrent());
	data.setBattLeftId(idBattLeft);
	if (devicePtr->hasBattLeftVolt())
		data.setBattLeftVolt(devicePtr->getBattLeftVolt());
	if (devicePtr->hasBattLeftTemp())
		data.setBattLeftTemp(devicePtr->getBattLeftTemp());
	if(!isSingleBattery()) {
		data.setSingleBatteryMode(false);
		data.setBattRightId(idBattRight);
		if (devicePtr->hasBattRightVolt())
			data.setBattRightVolt(devicePtr->getBattRightVolt());
		if (devicePtr->hasBattRightTemp())
			data.setBattRightTemp(devicePtr->getBattRightTemp());
	}
	return data;
}
