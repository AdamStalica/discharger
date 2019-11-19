#pragma once

#include <QObject>
#include <QTimer>
#include <serial/serial.h>

auto constexpr DEF_BAUDRATE = 9600;
auto constexpr REC_TIMER_INTERVAL_MS = 50;

class SerialPort : public QObject
{
	Q_OBJECT

public:
	SerialPort(QObject *parent = Q_NULLPTR);
	~SerialPort();

	void setPortName(const std::string & port);
	void setBaudrate(uint32_t baudrate);
	void setByteSize(serial::bytesize_t bytesize);
	void setParity(serial::parity_t parity);
	void setStopBits(serial::stopbits_t stopBits);
	void setFlowControl(serial::flowcontrol_t flowControl);

	bool open();
	bool isOpen();
	void close();
	void println(const std::string & line);

private:
	void write(const std::string & data);

	serial::Serial uart;
	QByteArray buffer;
	QTimer receiverTimer;

	std::string _port = "";
	int _baudrate = DEF_BAUDRATE;
	serial::bytesize_t	_byteSize = serial::eightbits;
	serial::parity_t	_parity = serial::parity_none;
	serial::stopbits_t	_stopBits = serial::stopbits_two;
	serial::flowcontrol_t  _flowControl = serial::flowcontrol_none;

private slots:
	void receiverTimerCallback();

signals:
	void openSignal();
	void closeSignal();
	void writeSignal(const std::string & data);
	void gotLineSignal(const std::string & line);
	void errorOccuredSignal(const std::string & error);
};
