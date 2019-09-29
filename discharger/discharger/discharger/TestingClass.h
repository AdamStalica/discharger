#pragma once

#include <QObject>

#include "UartHolder.h"
#include <QTimer>
#include <QDebug>


class TestingClass : public QObject
{
	Q_OBJECT

public:
	inline TestingClass(QObject *parent);
	inline ~TestingClass();

	UartHolder * uart;
	int i = 0;
};

TestingClass::TestingClass(QObject * parent) : QObject(parent) {


	uart = new UartHolder(this);

	uart->open("COM3");

	connect(uart, &UartHolder::gotHandshake, this, [this](int duration) {
		qDebug() << "Got handshake after " << duration << " us.";
	});

	connect(uart, &UartHolder::gotData, this, [this](const ReceivedData & data) {
		
		//qDebug() << data.getJson().dump().c_str();
		
	});


	QTimer * timer = new QTimer(this);

	connect(timer, &QTimer::timeout, this, [this, timer]() {
		qDebug() << "Sending handshake";
		//uart->handshake();
		uart->sendData(this->i++, 20.0 + ((rand() % 21) - 10) / 10);

	});
	timer->start(1000);

}

TestingClass::~TestingClass() {
	delete uart;
}