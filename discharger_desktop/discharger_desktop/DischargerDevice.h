#pragma once
#include <QTimer>
#include <queue>
#include "DeviceInterface.h"
#include "ObjectFactory.h"
#include "WebApi.h"

/**
1. construction of an object	
2. initialization 
*/


/*
set current,
id log data,

current,
volt left,
volt right,
temp left,
temp right,
temp heat sink

*/


class DischargerDevice :
	public DeviceInterface
{
	Q_OBJECT

private:
	const int BATT_NUM = 2;

	const std::string API_GET_CURR = "get_test_current.php";
	const std::string DB_MOTOR_CURR = "motor_curr";
	const std::string DB_MAIN_CURR = "main_curr";
	std::string currSourceName = DB_MAIN_CURR;

	QTimer timer;

	QString comPortName;
	unsigned int sendingNewDataPeriod = 1000;

	std::queue<std::pair<unsigned int, float>> queueOfLogData;
	unsigned int dataSize;

public:

	DischargerDevice(QObject * parent, const QString & com, DeviceInterface::CurrentSource currSource);
	~DischargerDevice();

	void fetchCurrentToTest(int idLogInfo, std::function<void(bool, const QString & comment)> callback);

	//DeviceInterface
	void connectToDevice() override;
	void start() override;
	void stop() override;
	
	bool checkBatteryNumber(int numebrOfBatteries) override;

private slots:
	void timerTimeout();
	//void handleHandshake(const QString & devId);

private:
	void handleWarning(Device::Warning warn);
	void handleError(Device::Error err);
	void testFinished();
	unsigned int countProgress();
};