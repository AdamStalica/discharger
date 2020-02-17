#include "UartHolder.h"
#include <exception>
#include <QSerialPort>
#include <QMessageBox>
#include <QDebug>
#include <QTimer>


using json = nlohmann::json;

UartHolder::UartHolder(QObject *parent)
	:	QObject(parent),
		serial(this)
{
	connect(&serial, &SerialPort::gotLineSignal, this, &UartHolder::proccessNewLine);
	connect(&serial, &SerialPort::errorOccuredSignal, this, [this](const std::string & error) {
		lastError = error.c_str();
		qDebug() << error.c_str();
	});

	//serial.setDestructorMsgIfPortOpen("{\"stop\":\"now\"}");
}

UartHolder::~UartHolder()
{
}

bool UartHolder::open(const QString & com)
{
	if (serial.isOpen()) 
		return true;

	serial.setPortName(com.toStdString());
	serial.setBaudrate(57600);
	serial.setStopBits(serial::stopbits_two);
	
	return serial.open();
}

void UartHolder::close() {
	serial.close();
}

bool UartHolder::isOpen()
{
	return serial.isOpen();
}

void UartHolder::handshake()
{
	qTimer.disconnect();
	connect(&qTimer, &QTimer::timeout, this, [this] {
		
		lastError = "Handshake timeout (over " + QString::number(HANDSHAKE_TIMEOUT) + " ms).";
		emit gotHandshake(-1);
		qTimer.stop();
	});

	qTimer.start(HANDSHAKE_TIMEOUT);
	elapsedTimer.start();

	serial.println("{\"handshake\":\"PC\"}");
}

void UartHolder::handshakeHolder()
{
	qTimer.stop();
	emit gotHandshake(elapsedTimer.elapsed());
}

void UartHolder::sendData(int id, float current, float temperature)
{
	if (current > 30.0) current = 30.0;

	int curr = int(current * 10.0 + 0.5);

	std::string toSend = "{\"id\":" + std::to_string(id) + ",\"I\":" + std::to_string(curr) + (temperature != FLT_MAX ? (",\"temp\":" + std::to_string(int(temperature * 100.0 + 0.5))) : "") + "}";

	serial.println(toSend);
}

void UartHolder::sendStop()
{
	serial.println("{\"stop\":\"now\"}");
}

void UartHolder::clear()
{
	serial.close();
}

void UartHolder::proccessNewLine(const std::string & newLine) {
	QString nl = QString::fromStdString(newLine);

	if (nl.contains(regExpJSON)) {
		regExpJSON.indexIn(nl);

		QString jsonStr = regExpJSON.capturedTexts().front();

		json received;
		try {
			received = json::parse(jsonStr.toStdString());
		}
		catch (const std::exception & ex) {
			lastError = "Can not parse received string.\n" + QString(ex.what());
			QMessageBox::critical(nullptr, "Error", lastError);
			//qDebug() << "error UartHolder.cpp : " << buffer;
			return;
		}

		if (!received["id"].is_null())
			emit gotData(ReceivedData(received));
		else if (!received["handshake"].is_null())
			handshakeHolder();
		else if (!received["stop"].is_null())
			emit gotStop(true);
		else if (!received["error"].is_null()) {
			emit gotError(DeviceError(received["error"].get<int>()));
		}
		else if (!received["debug"].is_null()) {
			qDebug() << received["debug"].get<std::string>().c_str();
		}
	}
}

/*
void UartHolder::read() {


	if (serial->canReadLine()) {


		QString tmp(serial->readLine());

		qDebug() << tmp;

		if (tmp.size() > 1) {

			tmp.replace(QRegExp("[\n\r]"), "");
			/*

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
				received = json::parse(tmp.toStdString());
			}
			catch (const std::exception & ex) {
				lastError = "Can not parse received string.\n" + QString(ex.what());
				QMessageBox::critical(nullptr, "Error", lastError);
				//qDebug() << "error UartHolder.cpp : " << buffer;
				return;
			}

			if (!received["id"].is_null())
				emit gotData(ReceivedData(received));
			else if (!received["handshake"].is_null())
				handshakeHolder();
			else if (!received["stop"].is_null())
				emit gotStop(true);
			else if (!received["error"].is_null()) {
				emit gotError(DeviceError(received["error"].get<int>()));
			}
		}
	}
}

*/