#include "SerialPortThread.h"

#include <thread>
#include <chrono>


SerialPortThread::SerialPortThread(QObject *parent)
	: QThread(parent)
{
	start();
}

SerialPortThread::~SerialPortThread()
{
	quit();
	while (isRunning());
}

void SerialPortThread::setPortName(const std::string & port)
{
	_port = port;
}

void SerialPortThread::setBaudrate(uint32_t baudrate)
{
	_baudrate = baudrate;
}

void SerialPortThread::setByteSize(serial::bytesize_t bytesize)
{
	_byteSize = bytesize;
}

void SerialPortThread::setParity(serial::parity_t parity)
{
	_parity = parity;
}

void SerialPortThread::setStopBits(serial::stopbits_t stopBits)
{
	_stopBits = stopBits;
}

void SerialPortThread::setFlowControl(serial::flowcontrol_t flowControl)
{
	_flowControl = flowControl;
}

void SerialPortThread::open()
{
	if (_port == "") {
		emit errorOccuredSignal("Port must be specified.");
		return;
	}
	emit openSignal();
}

bool SerialPortThread::isOpen()
{
	return _opened;
}

void SerialPortThread::close()
{
	emit closeSignal();
}

void SerialPortThread::println(const std::string & line)
{
	emit writeSignal(line + "\n\r");
}

void SerialPortThread::run() {

	serial::Serial uart;
	QByteArray buffer;

	connect(this, &SerialPortThread::openSignal, [&] {
		uart.setPort(this->_port);
		uart.setBaudrate(this->_baudrate);
		uart.setBytesize(this->_byteSize);
		uart.setParity(this->_parity);
		uart.setStopbits(this->_stopBits);
		uart.setFlowcontrol(this->_flowControl);

		try {
			uart.open();
		}
		catch (const std::exception & ex) {
			emit errorOccuredSignal(ex.what());
		}
		this->_opened = uart.isOpen();

	});

	connect(this, &SerialPortThread::closeSignal, [&] {

		if (uart.isOpen()) {
			uart.close();
		}
		this->_opened = uart.isOpen();
	});

	connect(this, &SerialPortThread::writeSignal, [&](const std::string & data) {

		if (uart.isOpen()) {
			uart.write(data);
		}
		else {
			emit errorOccuredSignal("Can not write data, port is closed.");
		}
	});


	while (1) {
		std::this_thread::sleep_for(std::chrono::milliseconds(10));

		if (uart.isOpen()) {
			auto bytesAvailable = uart.available();
			if (bytesAvailable != 0) {
				auto data = uart.read(bytesAvailable);

				buffer.append(data.c_str());

				QString str(buffer);
				auto lines = str.split(QRegExp("[\\n\\r]+"));

				if (lines.size() > 1) {

					for (auto & line : lines) {
						if (line.length() > 0) {
							emit gotLineSignal(line.toStdString());
						}
					}

					buffer.clear();
					if (lines.back().length() > 0)
						buffer.append(lines.back().toStdString().c_str());
				}
			}
		}
	}
}

/*
#include "SerialPortThread.h"
#include <QDebug>

SerialPortThread::SerialPortThread(QObject *parent)
	: QThread(parent),
	serial(this)
{
	connect(&serial, &QSerialPort::readyRead, [this] {
		onReadyRead();
	});//&SerialPortThread::onReadyRead);
	connect(&serial, &QSerialPort::bytesWritten, this, &SerialPortThread::onBytesWritten);
	connect(&serial, &QSerialPort::errorOccurred, this, [this](QSerialPort::SerialPortError error) {
		emit errorOccured(serial.errorString());
	});
	connect(&watchingTimer, &QTimer::timeout, this, [this] {

		if (serial.isOpen()) {
			if (serial.isReadable())
				qDebug() << serial.bytesAvailable();
		}

	});
	//watchingTimer.start(200);
	start();
}

SerialPortThread::~SerialPortThread()
{
	quit();
	close();
}

void SerialPortThread::setDestructorMsgIfPortOpen(const QString & msg)
{
	this->onDeleteMsg = (msg.toStdString() + "\n\r");
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
	if (serial.isOpen()) {
		if (onDeleteMsg != "") {
			serial.write(onDeleteMsg.c_str());
			while (serial.waitForBytesWritten(1));
		}
		watchingTimer.stop();

		while (serial.isOpen())
			serial.close();
	}
}

void SerialPortThread::println(const QString & data) {
	print(data + "\n\r");
}

/*
void SerialPortThread::println(const std::string & data) {
	serial.write((data + "\n\r").c_str());
}
*

void SerialPortThread::print(const QString & data) {
	print(data.toStdString());
}

void SerialPortThread::print(const std::string & data) {
	serial.write(data.c_str());
	//serial.flush();
	//serial.waitForReadyRead();
	//while(serial.waitForBytesWritten(WAIT_TIME_MS));
	//while (serial.waitForReadyRead(WAIT_TIME_MS));
}


void SerialPortThread::run()
{

	while (!serial.isOpen());

	while (serial.isOpen()) {
		if (serial.waitForBytesWritten(1)) {}
		else if (serial.waitForReadyRead(1)) {}
	}

	//exec();
}


void SerialPortThread::onReadyRead() {

	//serial.waitForReadyRead(WAIT_TIME_MS);

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

void SerialPortThread::onBytesWritten() {
	//serial.waitForBytesWritten(WAIT_TIME_MS);
}

*/