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
	connect(this, &UartHolder::printlnSignal, &serial, &SerialPortThread::println);
	connect(this, &UartHolder::closeSignal, &serial, &SerialPortThread::close);
	connect(&serial, &QThread::finished, &serial, &SerialPortThread::deleteLater);
	connect(&serial, &SerialPortThread::gotNewLine, this, &UartHolder::proccessNewLine);
	connect(&serial, &SerialPortThread::errorOccured, this, [this](const QString & error) {
		lastError = error;
		qDebug() << error;
	});

	serial.setDestructorMsgIfPortOpen("{\"stop\":\"now\"}");
}

UartHolder::~UartHolder()
{
}
/*
void UartHolder::sendData(const std::string & data) {
	
	txBuffer.append((data + "\n\r").c_str());

	serial->write(txBuffer);
	serial->waitForBytesWritten(-1);
}
*/

bool UartHolder::open(const QString & com)
{
	if (serial.isOpen()) 
		return true;

	serial.setPortName(com);
	serial.setBaudRate(57600);
	serial.setStopBits(QSerialPort::TwoStop);
	
	return serial.open();
}

void UartHolder::close() {
	emit closeSignal();
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

	println("{\"handshake\":\"PC\"}");
}

void UartHolder::handshakeHolder()
{
	qTimer.stop();
	emit gotHandshake(elapsedTimer.elapsed());
}

void UartHolder::println(const QString & data)
{
	emit printlnSignal(data);
}

void UartHolder::sendData(int id, float current, float temperature)
{
	json data = {
		{"id", id},
		{"curr", int(current * 100.0 + 0.5)}
	};
	if (temperature != FLT_MAX)
		data["temp"] = int(temperature * 100.0 + 0.5);
	println(QString(data.dump().c_str()));
}

void UartHolder::sendStop()
{
	println("{\"stop\":\"now\"}");
}

void UartHolder::clear()
{
	serial.close();
}

void UartHolder::proccessNewLine(const QString & newLine) {
	if (newLine.contains(regExpJSON)) {
		regExpJSON.indexIn(newLine);

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