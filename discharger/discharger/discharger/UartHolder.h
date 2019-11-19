#pragma once

#include <QObject>
#include <QTimer>
#include <QElapsedTimer>

#include "SerialPortThread.h"
#include "DeviceError.h"
#include "ReceivedData.h"
#include "json.h"
#include "ClearAble.h"

constexpr auto HANDSHAKE_TIMEOUT = 2000;

class UartHolder : public QObject, public ClearAble
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

	void clear() override;

	//QSerialPort * serial;

private:

	SerialPortThread serial;

	QString lastError;
	QRegExp regExpJSON = QRegExp("[{][^}]+[}]");

	QTimer qTimer;
	QElapsedTimer elapsedTimer;

	//QString buffer;
	//QByteArray txBuffer;

	//QRegExp regExpTheBeginning = QRegExp("[{][^}]+");

	//std::chrono::high_resolution_clock timer;
	//decltype(timer.now()) start;

	

	//void sendData(const std::string & data);

	void handshakeHolder();
	void println(const QString & data);

private slots:
	void proccessNewLine(const std::string & newLine);
	//void read();
	//void sendNextBytes(qint64 lastSendBytesWritten);

signals:
	/**
	*	Signal emitted when got data.
	*	@param received data {"id":int,"curr":double,"bLV":double,"bRV":double,"bLT":double,"bRT":double}
	*/
	void gotData(const ReceivedData & data);

	void gotStop(bool);

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
	
	void printlnSignal(const QString & data);
	void closeSignal();
};
