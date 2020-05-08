#pragma once

#include <QWidget>
#include "ui_TestConfigWgt.h"
#include "IClearable.h"
#include "ISetupable.h"
#include "TestConfigData.h"

class TestConfigWgt : public QWidget, IClearable, ISetupable
{
	Q_OBJECT

public:
	TestConfigWgt(QWidget *parent = Q_NULLPTR);
	~TestConfigWgt() {};

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
	Ui::TestConfigWgt ui;
	TestConfigData testConfData;
	
	void loadPageData();

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
