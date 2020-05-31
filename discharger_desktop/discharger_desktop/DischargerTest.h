#pragma once
#include "DeviceInterface.h"
#include "DischargerDevice.h"
#include "LogSimulationData.h"

class DischargerTest :
	public DeviceInterface
{
	const unsigned int TEST_DEFAULT_PERIOD = 1000;

	dischargerDevice::Device * dev;
	LogSimulationData logData;
	QTimer drivingDataTimer;
	QString comPort;

	unsigned int idTestData = 0;

public:
	DischargerTest(
		QObject * parent, 
		const QString & comPort,
		db::TestType testType, 
		db::CurrentSource currSource, 
		int idBattLeft, 
		int idBattRight = -1
	);

	bool checkBatteryNumber(int numebrOfBatteries) override;
	bool isTestCurrentEditable() override;
	bool isStartable() override;
	bool isStopable() override;

	void setupTestData() override;
	void connectToDevice() override;
	void disconnectFromDevice() override;
	void start() override;
	void stop() override;
	void setIdLogInfo(unsigned int idLogInfo);

private slots:
	void sendSimDrivingData();
	void sendTestDrivingData();
	void handleConnected();
	void handleConnectionFailure();
	void handleSimulationData(dischargerDevice::SimData simData);
	void handleDeviceHasStopped();
	void handleError(const QString & err);

private:
	unsigned int computeSimProgress();
	unsigned int computeTestProgress(const db::SimData & dbData);
};
