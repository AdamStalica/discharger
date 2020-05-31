#pragma once

#include <QObject>
#include "DbTestData.h"
#include <map>

class LogSimulationData : public QObject
{
	Q_OBJECT

	std::string API_EP_PATH = "desktop_app/get_sim_data.php";
	std::map<unsigned int, double> logCurrent;
	std::map<unsigned int, double>::iterator logCurrIte;
	unsigned int logPeriod;

public:
	LogSimulationData(QObject *parent);
	~LogSimulationData() {};

	bool isTheEnd();
	void first();
	bool previous();
	bool next();
	void last();
	double getCurrentAt(unsigned int idLogData);
	double getCurrent();
	unsigned int getIdLogData();
	unsigned int getLogPeriod();
	size_t size();

public slots:
	void fetchLogSimData(unsigned int idLogInfo, db::CurrentSource currentSource);

signals:
	void logSimDataFetchSuccess();
	void logSimDataFetchFailure();

private:
	bool processApiResponse(nlohmann::json && data);
};
