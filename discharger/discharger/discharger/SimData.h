#pragma once

#include <vector>
#include <QTime>
#include "ReceivedData.h"

constexpr auto DB_LOG_ID = 0;
constexpr auto SIM_TIME = 1;
constexpr auto CURRENT = 2;

class ApiHolder;
class ReceivedData;

typedef std::pair<std::tuple<int, QTime, double>, ReceivedData> simDataType;
typedef std::tuple<int, QTime, double> dbDataType;

class SimData
{
	ApiHolder * api;
	
	int idSimInfo;
	int idLogInfo;
	int lastSentPointId = 0;
	int currentSimulationId = 0;
	std::string nameOfAnAttributeOfCurrent = "motor_curr";

	std::vector<int> durations;
	std::vector<simDataType> simData;

	int getDbLogId(int id);
	QTime getSimulationTime(int id);
	double getCurrent(int id);
	ReceivedData getSimulatedData(int id);

	void prepareDurationPoints();


protected:

	virtual void fetchedCallback(const std::string & status, int no, const std::string & comment) = 0;

	/**
	*	Constructor.
	*	@param parent - Pointer to the instance of qObject.
	*	@param api - Api Holder object pointer.
	*/
	SimData(ApiHolder * api) :  api(api) {};

	/**
	*	Method to check if current point is the last one.
	*	@return True if is the last one, otherwise false.
	*/
	bool isLastPoint();

	/**
	*	Increments current point to the next one.
	*/
	void goToTheNextPoint();

	/**
	*	Getter.
	*	@return Current duration to wait before sending next data.
	*	@throws If there is no more duration points.
	*/
	int getCurrentDuration();

	/**
	*	Getter.
	*	@returns Time line.
	*/
	std::vector<QTime> getTimeLine();

	/**
	*	Getter.
	*	@return Id of current simulation point.
	*/
	int getCurrentId();

	/**
	*	Getter.
	*	@return Current to be simulated in next time point.
	*/
	double getCurrentCurrent();
	
	/**
	*	Setter.
	*	@param Received data from simulation device to be set.
	*/
	void setNextSimulatedDataPoint(const ReceivedData & data);

	/**
	*	Method to send simulated data to the Db.
	*	If there is no data, won't do anything.
	*/
	void sendData();

	/**
	*	Method to fetch data from Db.
	*	Prepare also sending data durations.
	*	@param simulationInfoId - Simulation info id.
	*	@param idLogInfo - id of log info.
	*/
	void fetchData(int idSimInfo, int idLogInfo);

	/**
	*	Destructor.
	*/
	~SimData() {};
};