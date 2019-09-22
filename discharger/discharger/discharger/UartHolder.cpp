#include "UartHolder.h"
#include <exception>
#include <QSerialPort>
#include <QMessageBox>
#include <QDebug>
#include <QTimer>


using json = nlohmann::json;

UartHolder::UartHolder(QObject *parent)
	: QObject(parent)
{
	serial = new QSerialPort(this);
	serial->setBaudRate(QSerialPort::Baud115200);
	serial->setDataBits(QSerialPort::Data8);
	serial->setParity(QSerialPort::NoParity);
	serial->setStopBits(QSerialPort::OneStop);
	serial->setFlowControl(QSerialPort::NoFlowControl);

	connect(serial, SIGNAL(readyRead()), this, SLOT(read()));
	connect(serial, &QSerialPort::errorOccurred, this, [this](const QSerialPort::SerialPortError & error) {
		qDebug() << error;
	});
	qTimer = new QTimer(this);
}

UartHolder::~UartHolder()
{
	serial->close();
	delete serial;
}

void UartHolder::sendData(const std::string & data) {
	
	QByteArray toSend(data.c_str());
	serial->write(toSend);
	serial->waitForBytesWritten();
}

bool UartHolder::open(const QString & com)
{
	if (serial->isOpen()) 
		return true;

	serial->setPortName(com);
	if (serial->open(QIODevice::ReadWrite)) {
		return true;
	}
	lastError = serial->errorString();
	
	return false;
}

void UartHolder::close() {
	serial->close();
}

bool UartHolder::isOpen()
{
	return serial->isOpen();
}

void UartHolder::handshake()
{
	qTimer->disconnect();
	connect(qTimer, &QTimer::timeout, this, [this] {

		const int tryingLimit = 5;
		static int counter = 0;

		if (tryingLimit == counter++) {
			lastError = "Handshake timeout (over " + QString::number(HANDSHAKE_TIMEOUT) + " ms).";
			emit gotHandshake(-1);
			qTimer->stop();
		}
		else {
			start = timer.now();
			sendData("{\"handshake\":\"PC\"}");
		}
	}); 
	qTimer->start(HANDSHAKE_TIMEOUT);
	start = timer.now();

	sendData("{\"handshake\":\"PC\"}");
}

void UartHolder::handshakeHolder()
{
	qTimer->stop();
	auto end = timer.now();
	int ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	emit gotHandshake(ms);
}

void UartHolder::sendData(int id, float current, float temperature)
{
	json data = {
		{"id", id},
		{"curr", current}
	};
	if (temperature != FLT_MAX)
		data["temp"] = temperature;
	sendData(data.dump());
}

void UartHolder::sendStop()
{
	sendData("{\"stop\":\"now\"}");
}

void UartHolder::read() {

	QString tmp(serial->readAll());

	if (tmp.size() > 1) {
		
		tmp.replace(QRegExp("[\n\r]"), "");

		if (tmp.contains(regExpTheWhole)) {

			regExpTheWhole.indexIn(tmp);
			buffer = regExpTheWhole.capturedTexts().at(0);
		}
		else if (tmp.contains(regExpTheBeginning)) {

			regExpTheBeginning.indexIn(tmp);
			buffer = regExpTheBeginning.capturedTexts().at(0);
			return;
		}
		else {
			buffer += tmp;

			if (buffer.contains(regExpTheWhole)) {
				regExpTheWhole.indexIn(buffer);
				buffer = regExpTheWhole.capturedTexts().at(0);
			}
			else return;
		}
		
		json received;
		try {
			received = json::parse(buffer.toStdString());
		}
		catch (const std::exception & ex) {
			lastError = "Can not parse received string.\n" + QString(ex.what());
			QMessageBox::critical(nullptr, "Error", lastError);
			//qDebug() << "error UartHolder.cpp : " << buffer;
			return;
		}

		if (!received["id"].is_null())
			emit gotData(received);
		else if (!received["handshake"].is_null())
			handshakeHolder();
		else if (!received["stop"].is_null())
			emit gotStop(received);
		else if (!received["error"].is_null()) {

			lastError = received["error"].get<std::string>().c_str();
			QMessageBox::critical(nullptr, "Error", lastError);
		}
	}
}
