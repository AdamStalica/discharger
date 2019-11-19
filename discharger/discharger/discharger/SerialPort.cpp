#include "SerialPort.h"

#include <thread>
#include <chrono>

#include <QDebug>

SerialPort::SerialPort(QObject *parent)
	: QObject(parent)
{
	connect(&receiverTimer, &QTimer::timeout, this, &SerialPort::receiverTimerCallback);
}

SerialPort::~SerialPort()
{
	uart.close();
}

void SerialPort::setPortName(const std::string & port)
{
	_port = port;
}

void SerialPort::setBaudrate(uint32_t baudrate)
{
	_baudrate = baudrate;
}

void SerialPort::setByteSize(serial::bytesize_t bytesize)
{
	_byteSize = bytesize;
}

void SerialPort::setParity(serial::parity_t parity)
{
	_parity = parity;
}

void SerialPort::setStopBits(serial::stopbits_t stopBits)
{
	_stopBits = stopBits;
}

void SerialPort::setFlowControl(serial::flowcontrol_t flowControl)
{
	_flowControl = flowControl;
}

bool SerialPort::open()
{
	if (_port == "") {
		emit errorOccuredSignal("Port must be specified.");
		return false;
	}
	if (!uart.isOpen()) {
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
		if (uart.isOpen()) receiverTimer.start(REC_TIMER_INTERVAL_MS);
	}
	return uart.isOpen();
}

bool SerialPort::isOpen()
{
	return uart.isOpen();
}

void SerialPort::close()
{
	receiverTimer.stop();
	uart.close();
}

void SerialPort::println(const std::string & line)
{
	write(line + "\n\r");
}

void SerialPort::write(const std::string & data)
{
	if (uart.isOpen()) {
		uart.write(data);
	}
	else {
		emit errorOccuredSignal("Can not write data, port is closed.");
	}
}

void SerialPort::receiverTimerCallback() {

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