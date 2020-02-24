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

void TestDriver::deviceNewData() {

}

void TestDriver::deviceErrorOccured(Device::Error error) {

}

void TestDriver::deviceWarningOccured(Device::Warning warning) {

}
