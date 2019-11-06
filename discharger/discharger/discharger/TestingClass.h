#pragma once

#include <QObject>

#include <QSerialPort>

#include "UartHolder.h"
#include <QTimer>
#include <QDebug>

#include <map>

#include <thread>
#include <chrono>

#include <QThread>

/*

class SerialPortThread : public QThread
{
	Q_OBJECT

private:

	inline void run() override; 
	inline bool open(
		const QString & com,
		qint32 baudRate, 
		QSerialPort::DataBits dataBits = QSerialPort::DataBits::Data8, 
		QSerialPort::Parity parity = QSerialPort::Parity::NoParity,
		QSerialPort::StopBits stopBits = QSerialPort::StopBits::TwoStop,
		QSerialPort::FlowControl flowControl = QSerialPort::FlowControl::NoFlowControl
	);
	inline SerialPortThread(QObject * parent = Q_NULLPTR);
	QSerialPort * serial = new QSerialPort;

	int i = 0;

signals:
	void resultReady(const QString & result);
	void gotError(const QString & error);
};

SerialPortThread::SerialPortThread(QObject * parent) 
	: QThread(parent)
{
	serial = new QSerialPort(this);
}

void SerialPortThread::run() {
	while (1) {
		std::this_thread::sleep_for(std::chrono::milliseconds(5000));

		emit resultReady("Execution no. " + QString::number(i++));
	}
}

bool SerialPortThread::open(const QString & com, qint32 baudRate, QSerialPort::DataBits dataBits, QSerialPort::Parity parity, QSerialPort::StopBits stopBits, QSerialPort::FlowControl flowControl) {
	serial->setBaudRate(baudRate);
	serial->setDataBits(dataBits);
	serial->setParity(parity);
	serial->setStopBits(stopBits);
	serial->setFlowControl(flowControl);

	serial->setPortName(com);
	if (!serial->open(QIODevice::ReadWrite)) {
		
		emit gotError(serial->errorString());
		return false;
	}
	return true;
}
*/

constexpr auto SENDING_PERIOD = 1000;

class TestingClass : public QObject
{
	Q_OBJECT

public:
	inline TestingClass(QObject *parent);
	inline ~TestingClass();

	UartHolder * uart;
	QTimer * timer;
	QTimer * t;

	int i = 0;

	std::map<int, double> data = {
		{0, 0.0},
		{1, 12.0},
		{2, 14.2},
		{3, 16.0},
		{4, 20.1},
		{5, 22.9},
		{6, 20.0},
		{7, 18.7},
		{9, 9.9},
		{10, 5.4},
		{11, 0.0},
	};
	};

TestingClass::TestingClass(QObject * parent) : QObject(parent) {

	/*
	uart = new UartHolder(this);
	timer = new QTimer(this);

	// When got handshake start sending data.
	connect(uart, &UartHolder::gotHandshake, this, [this](int duration) {
		qDebug() << "Got handshake after " << duration << " us.";
		if (duration != -1) {
			timer->start(SENDING_PERIOD);
			t->stop();
		}
	});

	// When got data, print it.
	connect(uart, &UartHolder::gotData, this, [this](const ReceivedData & data) {
		qDebug() << "Got data, id: " << data.getId() << ", current: " << data.getCurrent();
	});

	// When got stop, stop sending data.
	connect(uart, &UartHolder::gotStop, this, [this] {
		qDebug() << "Stopped";
		timer->stop();
		qDebug() << "Done.\nThank you.";
	});

	// When timer got timeout, send next data.
	connect(timer, &QTimer::timeout, this, [this]() {
		if (i < data.size()) {
			qDebug() << "Sending data, id: " << i;
			uart->sendData(i, data[i]);
		}
		else {
			qDebug() << "Require stop";
			uart->sendStop();
		}
		++i;
	});

	// Open port
	qDebug() << "Opening port";
	uart->open("COM7");

	// Send handshake
	qDebug() << "Sending handshake";

	uart->serial->waitForReadyRead(100);


	t = new QTimer;
	connect(t, &QTimer::timeout, this, [this] {
		
		uart->handshake();
	});
	t->start(2000);


	
	while (1) {
		while (uart->serial->waitForReadyRead(100));
	}
	

	*/


	/*
	std::thread * t1 = new std::thread([] {


		QSerialPort * serial = new QSerialPort;

		serial->setBaudRate(57600);
		serial->setDataBits(QSerialPort::Data8);
		serial->setParity(QSerialPort::NoParity);
		serial->setStopBits(QSerialPort::TwoStop);
		serial->setFlowControl(QSerialPort::NoFlowControl);

		serial->setPortName("COM7");
		if (!serial->open(QIODevice::ReadWrite)) {
			qDebug() << serial->errorString();
			return false;
		}
		else {


			serial->write("{\"handshake\":\"PC\"}");
			serial->waitForBytesWritten(200);
			qDebug() << "{\"handshake\":\"PC\"}";

			/*
			QByteArray data;
			QRegExp re = QRegExp("[{][^}]+[}]");

			while (1) {
				while (serial->waitForReadyRead(100)) {
					while (serial->bytesAvailable() > 0) {
						serial->read(&d, 1);
						if (d == '\n')
							break;
						else {
							data.append(d);
						}
					}
				}
			}
			*


			int i = 0;

			while (1) {

				char d;

				QByteArray data;
				while (d != '\n') {
					serial->waitForReadyRead(100);
					while (serial->bytesAvailable() > 0) {
						serial->read(&d, 1);
						if (d == '\n') break;
						else {
							data.append(d);
						}
					}
				}

				qDebug() << data;

				qDebug() << ("{\"id\":" + std::to_string(i) + ",\"curr\":2000}").c_str();
				serial->write(("{\"id\":" + std::to_string(i++) + ",\"curr\":2000}\n\r").c_str());


				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			}
		}
	});
	t1->detach();

	*/

/*
	WorkerThread * workerThread = new WorkerThread;
	connect(workerThread, &WorkerThread::resultReady, this, [](const QString & data) {
	
		qDebug() << data;
	
	});
	connect(workerThread, &WorkerThread::finished, workerThread, &QObject::deleteLater);
	workerThread->start();
*/


}

TestingClass::~TestingClass() 
{
}