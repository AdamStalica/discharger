#include "SerialPort.h"

using namespace serialPort;
//using namespace serialPort::worker;

SerialPort::SerialPort(QObject *parent)
	:	QObject(parent),
		timer(this)
{
	/*
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
	*/
	timer.setInterval(SCAN_INTERVAL);
	connect(&timer, &QTimer::timeout, this, &SerialPort::handleTimerTimeout);
}

SerialPort::~SerialPort() {
	//emit emitClose();
	//serialThread.quit();
	//serialThread.wait();
}

void SerialPort::open() {
	if (_port.empty())
		throw std::exception("You must set port name");
	if (serial.isOpen())
		throw std::exception("There is another port opened");

	serial.setPort(_port);
	serial.setBaudrate(_baudrate);
	serial.setBytesize(_datasize);
	serial.setStopbits(_stopbits);
	serial.setParity(_parity);
	
	serial.open();
	if (serial.isOpen()) {
		timer.start();
		emit opened();
	}
	else {
		emit unableToOpen();
	}
	/*
	serial::Serial * serial_ = new serial::Serial{
		_port,
		_baudrate,
		serial::Timeout(),
		_datasize,
		_parity,
		_stopbits
	};

	emit emitOpen(serial_);
	*/
}

void SerialPort::close() {
	serial.close();
	timer.stop();
	emit closed();
}

void SerialPort::println(const std::string & line) {
	serial.write(line + "\r\n");
	emit transmitedLine(line.c_str());
}

void SerialPort::printlnQ(const QString & line) {
	println(line.toStdString());
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
bool serialPort::SerialPort::isOpen() {
	return serial.isOpen();
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
void SerialPort::handleTimerTimeout() {
	if (serial.available()) {
		emit receivedLine(
			serial.readline().c_str()
		);
	}
}

/*
void SerialPort::handleNewLine(const QString & line) {
	//_portNewLineCallback(line.toStdString());
	emit receivedLine(line);
}
*/
/*
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
*/
