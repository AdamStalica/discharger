#include "UartHolder.h"
#include <exception>
#include <QSerialPort>
#include <QMessageBox>
#include <QDebug>

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
}

UartHolder::~UartHolder()
{
	serial->close();
	delete serial;
}

void UartHolder::sendData(const nlohmann::json & data) {
	
	QByteArray toSend(data.dump().c_str());
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
		else if (tmp.contains(regExpTheEnd)) {

			regExpTheEnd.indexIn(tmp);
			buffer += regExpTheEnd.capturedTexts().at(0);

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
			//QMessageBox::critical(nullptr, "Error", "Can not parse received string.\n" + QString(ex.what()));
			qDebug() << "error : " << buffer;
			return;
		}
		//emit gotData(received);
	}
}
