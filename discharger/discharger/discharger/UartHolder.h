#pragma once

#include <QObject>
#include "json.h"

class QSerialPort;

class UartHolder : public QObject
{
	Q_OBJECT

public:
	UartHolder(QObject *parent);
	~UartHolder();
	void sendData(const nlohmann::json & data);
	bool open(const QString & com);
	QString getLastError() { return lastError; }

private:
	QSerialPort * serial;
	QString lastError;
	QString buffer;

	QRegExp regExpTheWhole = QRegExp("[{][\"a-z:0-9.]+[}]");
	QRegExp regExpTheBeginning = QRegExp("[{][\"a-z:0-9.]*");
	QRegExp regExpTheEnd = QRegExp("[\"a-z:0-9.]*[}]");

private slots:
	void read();

signals:
	void gotData(const nlohmann::json & data);
};
