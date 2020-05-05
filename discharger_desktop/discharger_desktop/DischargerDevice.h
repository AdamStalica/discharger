#pragma once

#include <QObject>
#include <QDate>
#include <QTimer>
#include "SerialPort.h"
#include "DischargerDeviceData.h"
#include <DeviceEventsDef.h>
#include <nlohmann/json.h>

namespace dischargerDevice {
	class Device : public QObject
	{
		Q_OBJECT
	private:
		const unsigned int HANDSHAKE_MAX_ATTMEPT_NUM = 2;
		const unsigned int RESPONSE_MAX_TIME = 1000;
		const unsigned int BOUDRATE = 230400;
		const serialPort::datasize_t DATA_SIZE = serialPort::datasize_t::eightbits;
		const serialPort::stopbits_t STOP_BITS = serialPort::stopbits_t::stopbits_two;
		const serialPort::parity_t PARITY = serialPort::parity_t::parity_none;
		const unsigned int YEAR_OFFSET = 2000;

		serialPort::SerialPort * serial;
		QTimer handshakeTimer;
		bool gotHandshake = false,
			gotDeviceInfo = false,
			gotStop = false;
		unsigned int handshakeTimerTimeoutCounter = 0;
		nlohmann::json newData = "";

		unsigned int deviceId = 0;
		unsigned int deviceSoftwareVersion = 0;
		QDate deviceFlashDate = QDate();

	public:
		Device(QObject *parent);
		~Device() {};

		void clear();

		void connectToDevice(const QString & comPort);
		void disconnectDevice();

		void sendSimDrivingData(const SimDrivingData & data);
		void sendStop();
		void sendStartOfChracteristicDetermination();
		void sendReadCharacteristic();

		unsigned int getDeviceId();
		unsigned int getDeviceSoftwareVersion();
		QDate getDeviceFlashDate();

	private slots:
		void handlePortOpened();
		void handleUnableToOpen();
		void handleHandshakeTimerTimeout();
		void handleReceivedLine(const QString & line);

	private:
		void sendHandshake();
		void processHandshake();
		void processSimData();
		void processStop();
		void processError();
		void processWarning();
		void processDebug();
		void processCharacteristicPoint();
		void processCharacteristicDone();
		void sendDeviceInfoRequest();
		void processDeviceInfo();

	signals:
		void connected();
		void connectionFailure();
		void gotSimulationData(SimData simData);
		void deviceHasStopped();
		void errorDeviceStopTimeout();
		void error(dischargerDevice::Error errorNo);
		void error(const QString & error);
		void warning(dischargerDevice::Warning warningNo);
		void warning(const QString & warning);
		void debug(const QString & debugMsg);
		void gotCharacteristicPoint(const CharacteristicPoint & point);
		void characteristicDone();
	};
}