#pragma once

#include <vector>
#include <QTime>
#include "ReceivedData.h"

constexpr auto DB_LOG_ID = 0;
constexpr auto SIM_TIME = 1;
constexpr auto CURRENT = 2;

constexpr auto SIM_DATA_TABLE = "sim_data";

class ApiHolder;
class ReceivedData;

typedef std::pair<std::tuple<int, QTime, double>, ReceivedData> simDataType;
typedef std::tuple<int, QTime, double> dbDataType;

class SimData
{
	struct  SendingStatistics
	{
		int total = 0;
		int inserts = 0;
		int errors = 0;

		void add(const QString & data) {
			nlohmann::json resp = nlohmann::json::parse(data.toStdString());
			total += resp["comment"]["total"].get<int>();
			inserts += resp["comment"]["inserts"].get<int>();
			errors += resp["comment"]["errors"].get<int>();
		}

		QString toString() {
			return "Total: " + QString::number(total) + ", inserts: " + QString::number(inserts) + ", errors: " + QString::number(errors) + ".";
		}
	} sendingStatistics;

	ApiHolder * api;
	
	int idSimInfo;
	int idLogInfo;
	int lastSentPointId = -1;
	int lastReceivedPointId = 0;
	int currentSimulationId = 0;
	std::string nameOfAnAttributeOfCurrent = "motor_curr";

	bool canSendData = false;

	std::vector<int> durations;
	std::vector<simDataType> simData;

	int getDbLogId(int id);
	QTime getSimulationTime(int id);
	double getCurrent(int id);
	ReceivedData getSimulatedData(int id);

	void updateBeginTimeAndStatus();
	void updateEndTime();
	void compareDataLocalAndDb();

	void prepareDurationPoints();


public:
	enum SIM_STATE {
		/**
		*	Simulation is in progress.
		*/
		IN_PROGRESS,
		/**
		*	Simulation is complied but not confirmed.
		*/
		COMPLETED,
		/**
		*	Simulation is confirmed.
		*/
		CONFIRMED,
		/**
		*	Simulation has been removed.
		*/
		REMOVED,
	};

protected:

	virtual void fetchedCallback(const std::string & status, int no, const std::string & comment) = 0;
	virtual void setNewChartPoint(const simDataType & point) = 0;
	virtual void setBeginTime(const QDateTime & time) = 0;
	virtual void setEstimatedEndTime(const QDateTime & time) = 0;
	virtual void setEndTime(const QDateTime & time) = 0;

	/**
	*	Constructor.
	*	@param parent - Pointer to the instance of qObject.
	*	@param api - Api Holder object pointer.
	*/
	SimData(ApiHolder * api) :  api(api) {};

	/**
	*	Method to check if current point is the last one.
	*	@return True if there in no more data, otherwise false.
	*/
	bool reachedEnd();

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
	*	@return Time line.
	*/
	std::vector<QTime> getTimeLine();

	/**
	*	Getter.
	*	@return Race current vector.
	*/
	std::vector<double> getRaceCurrent();

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
	*	Getter.
	*	@return Mean logs period.
	*/
	int getMeanPeriod();

	/**
	*	Getter.
	*	@return Simulation estimated time.
	*/
	QTime getSimulationEstimatedTime();

	/**
	*	Getter.
	*	@return Current simulation time.
	*/
	QTime getCurrentSimulationTime();

	/**
	*	Gette.
	*	@return Estimated end time.
	*/
	QDateTime getEstimatedEndTime();
	
	/**
	*	Setter.
	*	@param Received data from simulation device to be set.
	*	@throws If argument is marked as invalid.
	*/
	void setNextSimulatedDataPoint(const ReceivedData & data);

	/**
	*	Setter.
	*	@param enable If set to true will send data into Db. Default false;
	*/
	void setSendingIntoDbEnabled(bool enable);

	/**
	*	Method to send simulated data to the Db.
	*	If there is no data, won't do anything.
	*/
	void sendData();

	/**
	*	Method to fetch data from Db.
	*	Prepare also sending data durations.
	*	@param idSimInfo - Simulation info id.
	*	@param idLogInfo - id of log info.
	*/
	void fetchData(int idSimInfo, int idLogInfo);

	/**
	*	Size.
	*	@return Size of simulation data array.
	*/
	int size() const;

	/**
	*	Method to clear all data.
	*/
	void clearData();

	/**
	*	Call this method when simulation is finished.
	*	@param status - Status of simulation after end.
	*/
	void simulationFinished(SIM_STATE status);

	/**
	*	Destructor.
	*/
	~SimData() {};

	int notGetAnswer() {
		return std::accumulate(simData.begin(), simData.end(), 0, [](int suma, const simDataType & data)->int {
			return suma + (data.second.isValid() ? 0 : 1);
		});
	}
};

//	TODO
//	send status
//	send begin / end time
//	check if all data is correctly inserted into db;