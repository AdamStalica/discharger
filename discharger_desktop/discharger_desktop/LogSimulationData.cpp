#include "LogSimulationData.h"

LogSimulationData::LogSimulationData(QObject *parent)
	: QObject(parent)
{
}

LogSimulationData::~LogSimulationData() {

}

bool LogSimulationData::isTheEnd() {
	return false;
}

bool LogSimulationData::first() {
	return false;
}

bool LogSimulationData::previous() {
	return false;
}

bool LogSimulationData::next() {
	return false;
}

bool LogSimulationData::last() {
	return false;
}

double getCurrentAt(unsigned int idLogData) {
	return 1;
}

double LogSimulationData::getCurrent() {
	return 0.0;
}

unsigned int LogSimulationData::getIdLogData() {
	return 0;
}

unsigned int LogSimulationData::getLogPeriod() {
	return 0;
}

size_t LogSimulationData::size() {
	return size_t();
}
