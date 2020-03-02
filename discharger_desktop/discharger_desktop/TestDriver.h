#pragma once

#include <QObject>
#include <QLabel>
#include <QCustomPlot.h>
#include "TestGUI.h"
#include "DeviceInterface.h"
#include "DbSimData.h"

auto constexpr TIME_FORMAT = "hh:mm:ss.zzz";

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
	QCustomPlot * plot;
	QSharedPointer<DeviceInterface> devicePtr;

	QTime testStartTime;

	std::vector<db::SimData> dbSimDataVec;

	QString testName, filepath;
	int idBattLeft, idBattRight;

public:
	enum TestStates {
		READY,
		PROGRESS,
		COMPLETED,
		CONFIRMED,
		REMOVED,
		DEV_ERROR
	};

	TestDriver(QObject *parent);
	~TestDriver();

	void confChart();
	void setDevice(DeviceInterface * dev);
	QSharedPointer<DeviceInterface> getDevice() { return devicePtr; };
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

	void deviceFinished();
	void deviceNewData();
	void deviceErrorOccured(Device::Error error);
	void deviceWarningOccured(Device::Warning warning);

	void prepareSimData(db::SimData & sd);
	TestParametersData prepareTestParametersData();
	bool isSingleBattery() { return idBattRight == -1; };
};
