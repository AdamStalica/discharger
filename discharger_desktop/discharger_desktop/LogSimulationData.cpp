#include "LogSimulationData.h"
#include "nlohmann/json.h"
#include "ObjectFactory.h"
#include "WebApi.h"

using namespace nlohmann;

LogSimulationData::LogSimulationData(QObject *parent)
	: QObject(parent)
{}

bool LogSimulationData::isTheEnd() {
	return (logCurrIte == logCurrent.end());
}

void LogSimulationData::first() {
	logCurrIte = logCurrent.begin();
}

bool LogSimulationData::previous() {
	if (logCurrIte == logCurrent.begin())
		return false;
	--logCurrIte;
	return true;
}

bool LogSimulationData::next() {
	if (logCurrIte == logCurrent.end())
		return false;
	++logCurrIte;
	return true;
}

void LogSimulationData::last() {
	logCurrIte = --logCurrent.end();
}

double LogSimulationData::getCurrentAt(unsigned int idLogData) {
	return logCurrent.at(idLogData);
}

double LogSimulationData::getCurrent() {
	// TODO: Remove div 10
	return (*logCurrIte).second / 10;
}

unsigned int LogSimulationData::getIdLogData() {
	return (*logCurrIte).first;
}

unsigned int LogSimulationData::getLogPeriod() {
	return logPeriod;
}

size_t LogSimulationData::size() {
	return logCurrent.size();;
}

void LogSimulationData::fetchLogSimData(unsigned int idLogInfo, db::CurrentSource currentSource) {
	json request = {
		{"id_log_info", idLogInfo},
		{"id_curr_source", currentSource}
	};
	ObjectFactory::getInstance<WebApi>()->POST(API_EP_PATH,	request,
		[this](WebApi::StatsEnum status, json && data) {
			if (status == WebApi::StatsEnum::API_OK && processApiResponse(std::move(data)))
				emit logSimDataFetchSuccess();
			else
				emit logSimDataFetchFailure();
		}
	);
}

bool LogSimulationData::processApiResponse(json && data) {
	try {
		logPeriod = data.at("period").get<unsigned int>();
		for (auto & log : data.at("data"))
			logCurrent[log.at("id_log_data").get<unsigned int>()] = log.at("current").get<double>();
		logCurrIte = logCurrent.begin();
	}
	catch (const std::exception & ex) {
		qDebug() << ex.what();
		return false;
	}
	return true;
}
