#pragma once

#include <QThread>
#include <atomic>
#include <serial/serial.h>


auto constexpr DEF_BAUDRATE = 9600;

class SerialPortThread : public QThread
{
	Q_OBJECT

public:
	SerialPortThread(QObject *parent = Q_NULLPTR);
	~SerialPortThread();

	void setPortName(const std::string & port);
	void setBaudrate(uint32_t baudrate);
	void setByteSize(serial::bytesize_t bytesize);
	void setParity(serial::parity_t parity);
	void setStopBits(serial::stopbits_t stopBits);
	void setFlowControl(serial::flowcontrol_t flowControl);

	void open();
	bool isOpen();
	void close();
	void println(const std::string & line);

private:
	void run() override;

	std::atomic<bool> _opened = false;

	std::string _port = "";
	std::atomic<int> _baudrate = DEF_BAUDRATE;
	std::atomic<serial::bytesize_t>		_byteSize = serial::eightbits;
	std::atomic<serial::parity_t>		_parity = serial::parity_none;
	std::atomic<serial::stopbits_t>		_stopBits = serial::stopbits_two;
	std::atomic<serial::flowcontrol_t>  _flowControl = serial::flowcontrol_none;

signals:
	void openSignal();
	void closeSignal();
	void writeSignal(const std::string & data);
	void gotLineSignal(const std::string & line);
	void errorOccuredSignal(const std::string & error);
};



/*
#pragma once

#include <QSerialPort>
#include <QThread>
#include <QTimer>

constexpr auto WAIT_TIME_MS = 1;

class SerialPortThread : public QThread
{
	Q_OBJECT

public:
	SerialPortThread(QObject *parent);
	~SerialPortThread();

	void setDestructorMsgIfPortOpen(const QString & msg);
	void setPortName(const QString & comName);
	void setBaudRate(qint32 baudRate);
	void setDataBits(QSerialPort::DataBits dataBits);
	void setParity(QSerialPort::Parity parity);
	void setStopBits(QSerialPort::StopBits stopBits);
	void setFlowControl(QSerialPort::FlowControl flowControl);
	void setOpenModeFlag(QIODevice::OpenModeFlag openModeFlag);
	bool open();
	bool isOpen();

public slots:
	void println(const QString & data);
	//void println(const std::string & data);
	void print(const QString & data);
	void print(const std::string & data);
	void close();

private:
	void run() override;

	QSerialPort serial;
	QByteArray buffer;
	QTimer watchingTimer;

	std::string onDeleteMsg;

	QString com = "";
	qint32 baudRate = 0;
	QSerialPort::DataBits dataBits = QSerialPort::DataBits::Data8;
	QSerialPort::Parity parity = QSerialPort::Parity::NoParity;
	QSerialPort::StopBits stopBits = QSerialPort::StopBits::OneStop;
	QSerialPort::FlowControl flowControl = QSerialPort::FlowControl::NoFlowControl;
	QIODevice::OpenModeFlag openModeFlag = QIODevice::OpenModeFlag::ReadWrite;

	bool closing = false;

private slots:
	void onReadyRead();
	void onBytesWritten();

signals:
	void errorOccured(const QString & error);
	void gotNewLine(const QString & newLine);
};
*/