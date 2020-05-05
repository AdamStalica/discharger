#pragma once

#include <QObject>

class SerialPortWorker : public QObject
{
	Q_OBJECT

public:
	SerialPortWorker(QObject *parent);
	~SerialPortWorker();
};
