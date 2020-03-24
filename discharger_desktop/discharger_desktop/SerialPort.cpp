#include "SerialPort.h"

using namespace serialPort;
using namespace serialPort::worker;

SerialPort::SerialPort(QObject *parent)
	: QObject(parent) 
{
	SerialPortWorker * worker = new SerialPortWorker;
	worker->moveToThread(&serialThread);
	connect(&serialThread, &QThread::finished, worker, &QObject::deleteLater);
	connect(this, &SerialPort::emitOpen, worker, &SerialPortWorker::open);
	connect(this, &SerialPort::emitClose, worker, &SerialPortWorker::close);
	connect(this, &SerialPort::emitPrint, worker, &SerialPortWorker::print);
	connect(worker, &SerialPortWorker::serialOpened, this, &SerialPort::handleSerialOpened);
	connect(worker, &SerialPortWorker::serialClosed, this, &SerialPort::handleSerialClosed);
	connect(worker, &SerialPortWorker::receivedNewLine, this, &SerialPort::handleNewLine);
	serialThread.start();
}

SerialPort::~SerialPort() {
	emit emitClose();
	serialThread.quit();
	serialThread.wait();
}

void SerialPort::open() {
	if (_port.empty())
		throw std::exception("You must set port name");
	if (_opened)
		throw std::exception("There is another port opened");

	serial::Serial * serial_ = new serial::Serial{
		_port,
		_baudrate,
		serial::Timeout(),
		_datasize,
		_parity,
		_stopbits
	};

	emit emitOpen(serial_);
}

void SerialPort::close() {
	emit emitClose();
}

void SerialPort::println(const std::string & line) {
	printlnQ(QString::fromStdString(line));
}

void SerialPort::printlnQ(const QString & line) {
	emit emitPrint((line + "\r\n"));
	emit transmitedLine(line);
}

void SerialPort::setPortQ(const QString & port) {
	setPort(port.toStdString());
}

void SerialPort::setPort(const std::string & port) {
	_port = port;
}

void SerialPort::setBaudrate(uint32_t baudrate) {
	_baudrate = baudrate;
}

void SerialPort::setDataSize(datasize_t datasize) {
	_datasize = datasize;
}

void SerialPort::setStopBits(stopbits_t stopbits) {
	_stopbits = stopbits;
}

void SerialPort::setParity(parity_t parity) {
	_parity = parity;
}
/*
void SerialPort::setOnPortOpenedCallback(std::function<void(void)> callback) {
	_portOpenedCallback = callback;
}

void SerialPort::setOnPortClosedCallback(std::function<void(void)> callback) {
	_portClosedCallback = callback;
}

void SerialPort::setOnNewLineCallback(std::function<void(const std::string&)> callback) {
	_portNewLineCallback = callback;
}
*/
void SerialPort::handleNewLine(const QString & line) {
	//_portNewLineCallback(line.toStdString());
	emit receivedLine(line);
}

void SerialPort::handleSerialClosed() {
	_opened = false;
	//_portClosedCallback();
	emit closed();
}

void SerialPort::handleSerialOpened() {
	_opened = true;
	//_portOpenedCallback();
	emit opened();
}

