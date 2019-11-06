#include "SerialPortThread.h"

SerialPortThread::SerialPortThread(QObject *parent)
	: QThread(parent),
	serial(this)
{
	connect(&serial, &QSerialPort::readyRead, this, &SerialPortThread::onReadyRead);
	connect(&serial, &QSerialPort::errorOccurred, this, [this](QSerialPort::SerialPortError error) {
		emit errorOccured(serial.errorString());
	});
	start();
}

SerialPortThread::~SerialPortThread()
{
	close();
}

void SerialPortThread::setDestructorMsgIfPortOpen(const QString & msg)
{
	this->onDeleteMsg = msg;
}

void SerialPortThread::setPortName(const QString & portName)
{
	this->com = portName;
	serial.setPortName(portName);
}

void SerialPortThread::setBaudRate(qint32 baudRate)
{
	this->baudRate = baudRate;
	serial.setBaudRate(baudRate);
}

void SerialPortThread::setDataBits(QSerialPort::DataBits dataBits)
{
	this->dataBits = dataBits;
	serial.setDataBits(dataBits);
}

void SerialPortThread::setParity(QSerialPort::Parity parity)
{
	this->parity = parity;
	serial.setParity(parity);
}

void SerialPortThread::setStopBits(QSerialPort::StopBits stopBits)
{
	this->stopBits = stopBits;
	serial.setStopBits(stopBits);
}

void SerialPortThread::setFlowControl(QSerialPort::FlowControl flowControl)
{
	this->flowControl = flowControl;
	serial.setFlowControl(flowControl);
}

void SerialPortThread::setOpenModeFlag(QIODevice::OpenModeFlag openModeFlag)
{
	this->openModeFlag = openModeFlag;
}

bool SerialPortThread::open()
{
	if (com == "") {
		emit errorOccured("First set com name");
		return false;
	}
	serial.setPortName(com);
	if (baudRate == 0) {
		emit errorOccured("First set baud rate");
		return false;
	}
	serial.setBaudRate(baudRate);
	serial.setDataBits(dataBits);
	serial.setParity(parity);
	serial.setStopBits(stopBits);
	serial.setFlowControl(flowControl);

	bool opened = serial.open(openModeFlag);
	if (!opened) emit errorOccured(serial.errorString());
	closing = !opened;

	return opened;
}

bool SerialPortThread::isOpen()
{
	return serial.isOpen();
}

void SerialPortThread::close()
{
	closing = true;
}

void SerialPortThread::println(const QString & data) {
	print(data + "\n\r");
}

/*
void SerialPortThread::println(const std::string & data) {
	serial.write((data + "\n\r").c_str());
}
*/
void SerialPortThread::print(const QString & data) {
	print(data.toStdString());
}

void SerialPortThread::print(const std::string & data) {
	serial.write(data.c_str());
}

void SerialPortThread::run()
{
	while (!serial.isOpen());

	while (serial.isOpen()) {
		if (closing) {
			
			if (onDeleteMsg != "") {
				serial.write((onDeleteMsg.toStdString() + "\n\r").c_str());
				while (serial.waitForBytesWritten(1000));
			}
			serial.close();
		}
		while (serial.isOpen() && serial.waitForBytesWritten(1));
		while (serial.isOpen() && serial.waitForReadyRead(1));
	}
}

void SerialPortThread::onReadyRead() {
	const auto data = serial.readAll();
	buffer.append(data);

	QString str(buffer);
	auto lines = str.split(QRegExp("[\\n\\r]+"));

	if (lines.size() > 1) {

		for (auto & line : lines) {
			if (line.length() > 0) {
				emit gotNewLine(line);
			}
		}

		buffer.clear();
		if (lines.back().length() > 0)
			buffer.append(lines.back().toStdString().c_str());
	}
}