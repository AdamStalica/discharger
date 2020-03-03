#pragma once

#include <QObject>
#include <QLabel>
#include <QCustomPlot.h>
#include "TestGUI.h"
#include "DeviceInterface.h"
#include "DbSimData.h"
#include "ChartPropertiesDialog.h"

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

	enum Graphs {
		CURRENT,
		TEST_CURRENT,
		CAPACITY,
		USED_ENERGY,
		HEAT_SINK_TEMP,
		BATT_LEFT_VOLT,
		BATT_RIGHT_VOLT,
		BATT_LEFT_TEMP,
		BATT_RIGHT_TEMP
	};
	const QStringList GRAPHS_NAMES{
		"Current [A]",
		"Test current [A]",
		"Capacity [Ah]",
		"Used energy [Wh]",
		QString("Heat sink temp. [%1C]").arg(QChar(0260)),
		"Battery left volt. [V]",
		"Battery right volt. [V]",
		QString("Battery left temp. [%1C]").arg(QChar(0260)),
		QString("Battery right temp. [%1C]").arg(QChar(0260))
	};
	std::vector<bool> graphsUsage;
	QCustomPlot * plot;
	ChartPropertiesDialog chartPorps;

	TestGUI & ui;
	QSharedPointer<DeviceInterface> devicePtr;

	std::map<QString, unsigned int> plotDraphId;

	QTime testStartTime, testEstimEndTime;

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

	void confChart();

private:
	TestStates testState = READY;

	void deviceFinished();
	void deviceNewData();
	void deviceErrorOccured(Device::Error error);
	void deviceWarningOccured(Device::Warning warning);

	void updateUI(const db::SimData & sd = db::SimData());

	TestParametersData prepareTestParametersData(const db::SimData & sd);
	bool isSingleBattery() { return idBattRight == -1; };

	void setUsageGraphsFlags(const db::SimData & sd);
	void appendChartData(const db::SimData & sd);
	void setupChart();

private slots:
	void chartPortpertiesAccepted();
};
