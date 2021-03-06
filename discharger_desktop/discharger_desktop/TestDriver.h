#pragma once

#include <QObject>
#include <QLabel>
#include <QCustomPlot.h>
#include "DeviceInterface.h"
#include "DbSimData.h"
#include "ChartPropertiesDialog.h"
#include "TestParametersData.h"
#include "Calculations.h"
#include "DbTestData.h"

#include "IClearable.h"
#include "ISetupable.h"
#include "FileLogger.h"

// TODO: Move such a declaration into one header
auto constexpr TIME_FORMAT = "hh:mm:ss.zzz";

class TestDriver : public QObject, IClearable, ISetupable
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

	//TODO: Move it to ChartWgt
	/*
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
		{ tr("Test current [A]"),							QColor("red") },
		{ tr("Capacity [Ah]"),								QColor("green") },
		{ tr("Used energy [Wh]"),							QColor("yellow") },
		{ tr("Heat sink temp. [%1C]").arg(QChar(0260)),		QColor("orange") },
		{ tr("Battery left volt. [V]"),						QColor("pink") },
		{ tr("Battery right volt. [V]"),					QColor("violet") },
		{ tr("Battery left temp. [%1C]").arg(QChar(0260)),	QColor("grey") },
		{ tr("Battery right temp. [%1C]").arg(QChar(0260)),	QColor("brown") }
	}};
	std::vector<bool> graphsUsage;
	QCustomPlot * plot;
	ChartPropertiesDialog chartPorps;
	*/

	Calculations calcs;
	db::TestData testData;

	QSharedPointer<DeviceInterface> dev;
	QSharedPointer<FileLogger> fileLogger;
	
	QTime testStartTime, testEstimEndTime;

	//std::vector<db::SimData> dbSimDataVec;

	QString testName;
	//bool jsonLogFile = false;
	//unsigned int idBattLeft, 
	//			idBattRight;

public:


	TestDriver(QObject *parent);
	~TestDriver();

	void setDevice(QSharedPointer<DeviceInterface> dev);
	void setFileLogger(QSharedPointer<FileLogger> fileLogger);
	void setTestName(const QString & name) { testName = name; };
	bool isTestBeforeStart() const;
	bool isTestInProgress() const;

	//QSharedPointer<DeviceInterface> getDevice() { return dev; };
	//void removeDevice();

	//void setIdBattLeft(int id) { idBattLeft = id; };
	//void setIdBattRight(int id) { idBattRight = id; };
	//void setFilepathToLog(const QString &filepath, bool jsonFile = false);

	//void setupTestInDb(std::function<void(bool, const QString &)> callback);

	//void loadPageData();
	//void startTest();
	//void stopTest();
	//void clear();

	db::TestStates getTestState() { return testState; };

	//void confChart() {}

private:
	db::TestStates testState = db::TestStates::NONE;

	void processNewDbSimData(db::SimData & simData);
	TestParametersData prepareTestParametersData(const db::SimData & sd);
	void updateTestParams(const db::SimData & sd = db::SimData());
	void setTestState(db::TestStates testState);

	//void deviceFinished();
	//void deviceNewData(db::SimData dbSimData);
	//void deviceErrorOccured(dischargerDevice::Error error);
	//void deviceWarningOccured(dischargerDevice::Warning warning);
	//void deviceDebug(const QString & msg);

	//void updateUI(const db::SimData & sd = db::SimData());

	//TestParametersData prepareTestParametersData(const db::SimData & sd);
	//bool isSingleBattery() { return idBattRight == -1; };

	//void setupLogFile(const db::SimData & sd);
	//void logToFile(const db::SimData & sd);

	//void setUsageGraphsFlags(const db::SimData & sd);
	//void appendChartData(const db::SimData & sd);
	//void setupChart();
	//void chartRescaleAxes(int max = -1);

private slots:
	//void chartPortpertiesAccepted();
	void handleTestDataFailure();
	void handleTestDataOk();
	void handleDevConnFailure();
	void handleDevError(const QString & err);
	void handleDevConnOk();
	void handleDevFinished();
	void handleDevNewData(db::SimData simData);

public slots:
	void setup() override;
	void clear() override;
	void handleTestStart();
	void handleTestStop();
	void setTestCurrent(double current);
	void setVoltageLimit(double voltLim);
	void setHeatSinkTempLimit(double tempLim);


signals:
	void setupStatus(const QString & msg);
	void setupDone();
	void setupFailure();
	void testDone();
	void testParametersData(const TestParametersData & data);
	void dbSimData(const db::SimData & simData);
};
