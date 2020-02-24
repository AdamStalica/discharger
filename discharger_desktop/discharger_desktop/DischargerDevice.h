#pragma once
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
	public QObject,
	public DeviceInterface
{
	Q_OBJECT

private:
	const int BATT_NUM = 2;
	const DeviceInterface::CurrentSource CURRENT_SOURCE;

	const std::string API_GET_CURR = "get_test_current.php";
	const std::string DB_MOTOR_CURR = "motor_curr";
	const std::string DB_MAIN_CURR = "main_curr";
	std::string currSourceName = DB_MAIN_CURR;

	QString comPortName;
	unsigned int sendingNewDataPeriod = 1000;

	float voltLimit, heatSinkTempLimit;

	//Simulation data
	QTime estSimTime;
	std::queue<std::pair<unsigned int, float>> queueOfLogData;
	unsigned int dataSize;

	unsigned int dataId = 0;

	// Current params
	float testCurrent = 0,
		current = 0,
		battLeftVolt = 0,
		battRightVolt = 0,
		battLeftTemp = 0,
		battRightTemp = 0,
		heatSinkTemp = 0;

 	unsigned int idLogInfo,
		idLogData;

	//DeviceInterface
	std::function<void(Device::Error)> errorCallback;
	std::function<void(Device::Warning)> waraningCallback;
	std::function<void(void)> newDataCallback;

public:

	DischargerDevice(QObject * parent, const QString & com, DeviceInterface::CurrentSource currSource);
	~DischargerDevice();

	void fetchCurrentToTest(int idLogInfo, std::function<void(bool, const QString & comment)> callback);

	//DeviceInterface
	void connect() override;
	void start() override;
	void stop() override;

	void setOnErrorCallback(std::function<void(Device::Error)> errCallback) override;
	void setOnWarningCallback(std::function<void(Device::Warning)> warnCallback) override;
	void setOnNewDataCallback(std::function<void(void)> dataCallback) override;

	DeviceInterface::CurrentSource getCurrentSource() override { return CURRENT_SOURCE; };
	unsigned int getLogInfoId() override;
	unsigned int getLogDataId() override;
	unsigned int getProgress() override;

	float getTestCurrent() override { return testCurrent; };
	float getVoltageLimit() override { return voltLimit; };
	float getHeatSinkTempLimit() override { return heatSinkTempLimit; };
	void setTestCurrent(float current) override;
	void setVoltageLimit(float volt) override;
	void setHeatSinkTempLimit(float tempLimit) override;

	bool hasEstimatedTestTime() override;
	QTime getEstimatedTestTime() override;

	bool hasBattLeftVolt() override { return true; };
	bool hasBattLeftTemp() override { return true; };
	bool hasBattRightVolt() override { return true; };
	bool hasBattRightTemp() override { return true; };
	bool hasHeatSinkTemp() override { return true; };

	float getCurrent() override { return current; }; 
	float getBattLeftVolt() override { return battLeftVolt; };
	float getBattLeftTemp() override { return battLeftTemp; };
	float getBattRightVolt() override { return battRightVolt; };
	float getBattRightTemp() override { return battRightTemp; };
	float getHeatSinkTemp() override { return heatSinkTemp; };

	bool checkBatteryNumber(int numebrOfBatteries) override;
};