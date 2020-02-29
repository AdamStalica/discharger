#pragma once

#include <QObject>
#include <QLabel>
#include "TestGUI.h"
#include "DeviceInterface.h"

class TestDriver : public QObject
{
	Q_OBJECT
private: 
	const QStringList TEST_STATES{
		"Ready to start",
		"In progress",
		"Completed",
		"Confirmed",
		"Removed",
		"Error"
	};

	TestGUI & ui;
	QLabel * chart;
	std::shared_ptr<DeviceInterface> devicePtr;

	QString testName, filepath;
	int idBattLeft, idBattRight;

public:
	enum TestStates {
		READY,
		PROGRESS,
		COMPLETED,
		CONFIRMED,
		REMOVED,
		ERROR
	};

	TestDriver(QObject *parent);
	~TestDriver();

	void confChart();
	void setDevice(DeviceInterface * dev);
	std::shared_ptr<DeviceInterface> getDevice() { return devicePtr; };
	void removeDevice();

	void setTestName(const QString & name) { testName = name; };
	void setIdBattLeft(int id) { idBattLeft = id; };
	void setIdBattRight(int id) { idBattRight = id; };
	void setFilepathToLog(const QString &filepath) { this->filepath = filepath; };
	void loadPageData();
	void startTest();
	void stopTest();
	void clear();

	TestStates getTestState() { return testState; };

private:
	TestStates testState = READY;

	void deviceNewData();
	void deviceErrorOccured(Device::Error error);
	void deviceWarningOccured(Device::Warning warning);

	TestParametersData prepareTestParametersData();
	bool isSingleBattery() { return idBattRight == -1; };
};
