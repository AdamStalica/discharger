#pragma once

#include <QObject>
#include <chrono>
#include "DeviceError.h"
#include "ReceivedData.h"
#include "json.h"

constexpr auto HANDSHAKE_TIMEOUT = 1000;

class QSerialPort;
class QTimer;

class UartHolder : public QObject
{
	Q_OBJECT

public:
	UartHolder(QObject *parent);
	~UartHolder();
	bool open(const QString & com);
	void close();
	bool isOpen();
	QString getLastError() { return lastError; }
	
	/**
	*	Sends handshake to the discharger device.
	*	@throw - timeout error when waiting more than 5 seconds.
	*/
	void handshake();

	/**
	*	Sends data to be simulated.
	*	@param id - id of log data.
	*	@param current - current to be simulated.
	*	@param temperature - optional - value of temperature to set temperature of battery.
	*/
	void sendData(int id, float current, float temperature = FLT_MAX);

	/**
	*	Sends stop signal to the device.
	*/
	void sendStop();

private:
	QSerialPort * serial;
	QString lastError;
	QString buffer;

	QRegExp regExpTheWhole = QRegExp("[{][^}]+[}]");
	QRegExp regExpTheBeginning = QRegExp("[{][^}]+");

	std::chrono::high_resolution_clock timer;
	decltype(timer.now()) start;

	QTimer * qTimer;

	void sendData(const std::string & data);
	void handshakeHolder();

private slots:
	void read();

signals:
	/**
	*	Signal emitted when got data.
	*	@param received data {"id":int,"curr":double,"bLV":double,"bRV":double,"bLT":double,"bRT":double}
	*/
	void gotData(const ReceivedData & data);

	void gotStop();

	/**
	*	Signal emitted when got hand shake
	*	@param duration since handshake was sent until got response [ms].
	*/
	void gotHandshake(int);

	/**
	*	Signal emitted when device send error.
	*	@param error - An device error object.
	*/
	void gotError(const DeviceError & error);
};
