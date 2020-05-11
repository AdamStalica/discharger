#pragma once

#include <QWidget>
#include "ui_TestConfigWgt.h"
#include "IClearable.h"
#include "ISetupable.h"
#include "TestConfigData.h"
#include "DischargerTest.h"


class TestConfigWgt : public QWidget, IClearable, ISetupable
{
	Q_OBJECT

public:
	TestConfigWgt(QWidget *parent = Q_NULLPTR);
	~TestConfigWgt() {};

	QString getTestName();
	QString getLogFileName();
	QSharedPointer<DeviceInterface> getDevice();

public slots:
	void clear() override;
	void setup() override;

private slots:
	void dataReadyCallback(bool success, const QString & msg);
	void handleRefreshPortsList();
	void handleSelectFile();
	void handleCancel();
	void handlePrepareTest();

signals:
	void setupFailure();
	void setupDone();
	void canceled();
	void setupState(const QString & msg);
	void testConfigurationDone();

private:
	const unsigned int TREE_ID_LOG_INFO_COL_NUM = 2;

	Ui::TestConfigWgt ui;
	TestConfigData testConfData;

	QSharedPointer<DeviceInterface> dev;
	QString testName{ "" }, 
		comPort		{ "" }, 
		logFileName	{ "" };
	double voltLimit		{ 0.0 }, 
		heatSinkTempLimit	{ 0.0 },
		testCurrent		{ 0.0 };
	int idLeftBatt		{ 0 }, 
		idRightBatt		{ 0 },
		idLogInfo		{ 0 };
	db::CurrentSource currSource{ db::CurrentSource::NO_CURR_SOURCE };
	db::TestType testType{ db::TestType::BASIC_TEST };

	enum DevSetupType {
		DISCH_SIM, DISCH_TEST, ANOTHER_DEV
	};
	
	void loadPageData();
	bool validateBasicData();
	bool validateSimData();
	bool validateBasicTestData();
	bool validateDevTermData();

	void createDischargerTestDevice();

	// TODO: Move it to log class
	enum LogFilesFormats {
		CSV, JSON, XLSX
	};

	const std::map<QString, LogFilesFormats> LOG_FILES_FORMATS_MAP = {
		{ tr("Comma separated values (*.csv)"), LogFilesFormats::CSV },
		{ tr("JSON file (*.json)"), LogFilesFormats::JSON },
		{ tr("Excel file (*.xlsx)"), LogFilesFormats::XLSX }
	};

	QString getLogFilesFormatsFilter() {
		QString filter = "";
		for (auto & fileFormat : LOG_FILES_FORMATS_MAP)
			filter += fileFormat.first;
		return filter;
	}

	LogFilesFormats getLogFileFormatId(const QString & name) {
		return LOG_FILES_FORMATS_MAP.at(name);
	}
};
