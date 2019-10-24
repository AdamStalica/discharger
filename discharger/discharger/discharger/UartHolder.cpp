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

	connect(serial, SIGNAL(readyRead()), this, SLOT(read()));
	connect(serial, SIGNAL(bytesWritten()), this, SLOT(sendNextBytes()));
	connect(serial, &QSerialPort::errorOccurred, this, [this](const QSerialPort::SerialPortError & error) {
		qDebug() << error;
	});
	qTimer = new QTimer(this);
}

UartHolder::~UartHolder()
{
	if(isOpen()) sendStop();
	serial->close();
	delete serial;
}

void UartHolder::sendData(const std::string & data) {
	
	txBuffer.append((data + "\n\r").c_str());

	serial->write(txBuffer);
	serial->waitForBytesWritten(-1);
}

bool UartHolder::open(const QString & com)
{
	if (serial->isOpen()) 
		return true;

	serial->setBaudRate(57600);
	serial->setDataBits(QSerialPort::Data8);
	serial->setParity(QSerialPort::NoParity);
	serial->setStopBits(QSerialPort::TwoStop);
	serial->setFlowControl(QSerialPort::NoFlowControl);
	
	serial->setPortName(com);
	if (!serial->open(QIODevice::ReadWrite)) {
		lastError = serial->errorString();
		return false;
	}
	
	return true;
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
		
		lastError = "Handshake timeout (over " + QString::number(HANDSHAKE_TIMEOUT) + " ms).";
		emit gotHandshake(-1);
		qTimer->stop();
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

void UartHolder::sendNextBytes(qint64 lastSendBytesWritten)
{

}

void UartHolder::sendData(int id, float current, float temperature)
{
	json data = {
		{"id", id},
		{"curr", int(current * 100.0 + 0.5)}
	};
	if (temperature != FLT_MAX)
		data["temp"] = int(temperature * 100.0 + 0.5);
	sendData(data.dump());
}

void UartHolder::sendStop()
{
	sendData("{\"stop\":\"now\"}");
}

void UartHolder::clear()
{
	if (isOpen()) {
		close();
	}
}

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
			*/

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
