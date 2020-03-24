#pragma once

#include <QObject>
#include <QLabel>
#include <QCustomPlot.h>
#include "TestGUI.h"
#include "DeviceInterface.h"
#include "DbSimData.h"
#include "ChartPropertiesDialog.h"
#include "Calculations.h"

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
	const std::array<std::pair<QString, QColor>, 9> GRAPHS_NAMES_COLORS { {
		{ tr("Current [A]"),								QColor("blue") },
		{"Test current [A]",								QColor("red") },
		{"Capacity [Ah]",									QColor("green") },
		{"Used energy [Wh]",								QColor("yellow") },
		{tr("Heat sink temp. [%1C]").arg(QChar(0260)),		QColor("orange") },
		{"Battery left volt. [V]",							QColor("pink") },
		{"Battery right volt. [V]",							QColor("violet") },
		{tr("Battery left temp. [%1C]").arg(QChar(0260)),	QColor("grey") },
		{tr("Battery right temp. [%1C]").arg(QChar(0260)),	QColor("brown") }
	}};
	std::vector<bool> graphsUsage;
	QCustomPlot * plot;
	ChartPropertiesDialog chartPorps;
	Calculations calcs;

	TestGUI & ui;
	QSharedPointer<DeviceInterface> devicePtr;
	
	QTime testStartTime, testEstimEndTime;

	std::vector<db::SimData> dbSimDataVec;

	QString testName, 
		filepath;
	bool jsonLogFile = false;
	int idBattLeft, 
		idBattRight;

public:
	enum TestStates {
		READY,
		PROGRESS,
		COMPLETED,
		CONFIRMED,
		REMOVED,
		DEV_ERROR,
		NONE
	};

	TestDriver(QObject *parent);
	~TestDriver();

	void setDevice(DeviceInterface * dev);
	QSharedPointer<DeviceInterface> getDevice() { return devicePtr; };
	void removeDevice();

	void setTestName(const QString & name) { testName = name; };
	void setIdBattLeft(int id) { idBattLeft = id; };
	void setIdBattRight(int id) { idBattRight = id; };
	void setFilepathToLog(const QString &filepath, bool jsonFile = false);

	void loadPageData();
	void startTest();
	void stopTest();
	void clear();

	TestStates getTestState() { return testState; };

	void confChart();

private:
	TestStates testState = NONE;

	void deviceFinished();
	void deviceNewData(db::SimData dbSimData);
	void deviceErrorOccured(Device::Error error);
	void deviceWarningOccured(Device::Warning warning);
	void deviceDebug(const QString & msg);

	void updateUI(const db::SimData & sd = db::SimData());

	TestParametersData prepareTestParametersData(const db::SimData & sd);
	bool isSingleBattery() { return idBattRight == -1; };

	void setupLogFile(const db::SimData & sd);
	void logToFile(const db::SimData & sd);

	void setUsageGraphsFlags(const db::SimData & sd);
	void appendChartData(const db::SimData & sd);
	void setupChart();
	void chartRescaleAxes(int max = -1);

private slots:
	void chartPortpertiesAccepted();
};
