#include "CommFlowWgt.h"
#include "ObjectFactory.h"
#include "SerialPort.h"
#include "DischargerDevice.h"
#include "TestDriver.h"

using namespace serialPort;
using namespace dischargerDevice;

CommFlowWgt::CommFlowWgt(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	auto serial = ObjectFactory::getInstance<SerialPort>();
	auto dischDev = ObjectFactory::getInstance<Device>();
	auto testDriver = ObjectFactory::getInstance<TestDriver>();

	connect(serial, &SerialPort::opened, this, &CommFlowWgt::handleSerialOpened);
	connect(serial, &SerialPort::unableToOpen, this, &CommFlowWgt::handleSerialCanNotOpen);
	connect(serial, &SerialPort::closed, this, &CommFlowWgt::handleSerialClosed);
	connect(serial, &SerialPort::transmitedLine, this, &CommFlowWgt::handleSerialSentLine);
	connect(serial, &SerialPort::receivedLine, this, &CommFlowWgt::handleSerialGotLine);
	connect(dischDev, &Device::debug, this, &CommFlowWgt::handleDebug);
	connect(dischDev, static_cast<void(Device::*)(const QString &)>(&Device::warning), 
		this, &CommFlowWgt::handleWarning);
	connect(dischDev, static_cast<void(Device::*)(const QString &)>(&Device::error), 
		this, &CommFlowWgt::handleError);
	connect(testDriver, &TestDriver::dbSimData, this, &CommFlowWgt::handleNewDbSimData);
}

void CommFlowWgt::handleSerialOpened() {
	appendRawDataLine(
		"<div style=\"text-align: center;\">Port opened</div>"
	);
}

void CommFlowWgt::handleSerialCanNotOpen() {
	appendRawDataLine(
		"<div style=\"text-align: center;\">Could not open port</div>"
	);
}

void CommFlowWgt::handleSerialClosed() {
	appendRawDataLine(
		"<div style=\"text-align: center;\">Port closed</div>"
	);
}

void CommFlowWgt::handleSerialSentLine(const QString & line) {
	appendRawDataLine(
		"<div style=\"text-align: left;\">" + line + "</div>"
	);
}

void CommFlowWgt::handleSerialGotLine(const QString & line) {
	appendRawDataLine(
		"<div style=\"text-align: right;\">" + line + "</div>"
	);
}

void CommFlowWgt::handleDebug(const QString & msg) {
	appendEventsLine(
		"<div style=\"color: green\">" + msg + "</div>"
	);
}

void CommFlowWgt::handleWarning(const QString & warn) {
	appendEventsLine(
		"<div style=\"color: orange\">" + warn+ "</div>"
	);
}

void CommFlowWgt::handleError(const QString & err) {
	appendEventsLine(
		"<div style=\"color: red\">" + err + "</div>"
	);
}

void CommFlowWgt::handleNewDbSimData(const db::SimData & simData) {
	appendTestDataLine(simData.toCSV());
}

void CommFlowWgt::appendLineToTextBrowser(QTextBrowser * brow, const QString & line, bool scrollDown) {
	brow->append(line);
	if (scrollDown) {
		QScrollBar *sb = brow->verticalScrollBar();
		sb->setValue(sb->maximum());
	}
}

void CommFlowWgt::appendTestDataLine(const QString & line) {
	appendLineToTextBrowser(
		ui.tabTestDataTxtBrow,
		line,
		ui.tabTestDataChckScroll->isChecked()
	);
}

void CommFlowWgt::appendEventsLine(const QString & line) {
	appendLineToTextBrowser(
		ui.tabEventsTxtBrow,
		line,
		ui.tabEventsChckScroll->isChecked()
	);
}

void CommFlowWgt::appendRawDataLine(const QString & line) {
	appendLineToTextBrowser(
		ui.tabRawDataTxtBrow,
		line,
		ui.tabRawDataChckScroll->isChecked()
	);
}
