#pragma once

#include <QObject>

class LogSimulationData : public QObject
{
	Q_OBJECT

public:
	LogSimulationData(QObject *parent);
	~LogSimulationData();

	bool isTheEnd();
	bool first();
	bool previous();
	bool next();
	bool last();
	double getCurrent();
	unsigned int getIdLogData();
	unsigned int getLogPeriod();
	size_t size();
};
