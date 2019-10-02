#include "SimData.h"
#include "json.h"
#include "ApiHolder.h"

#include <QDebug>
#include <algorithm>
#include <numeric>

using json = nlohmann::json;

int SimData::getDbLogId(int id)
{
	if (id < simData.size())
		return std::get<DB_LOG_ID>(simData[id].first);
	throw std::invalid_argument("id");
}

QTime SimData::getSimulationTime(int id)
{
	if (id < simData.size())
		return std::get<SIM_TIME>(simData[id].first);
	throw std::invalid_argument("id");
}

double SimData::getCurrent(int id)
{
	if (id < simData.size())
		return std::get<CURRENT>(simData[id].first);
	throw std::invalid_argument("id");
}

ReceivedData SimData::getSimulatedData(int id)
{
	if (id < simData.size())
		return simData[id].second;
	throw std::invalid_argument("id");
}

void SimData::prepareDurationPoints()
{
	durations.resize(simData.size());

	int lastLogTime = 0;
	durations[0] = getSimulationTime(1).msecsSinceStartOfDay();

	std::transform(simData.begin() + 1, simData.end(), durations.begin() + 1, [&lastLogTime](const simDataType & log)->int {

		int currentLogTime = std::get<SIM_TIME>(log.first).msecsSinceStartOfDay();
		int duration = currentLogTime - lastLogTime;
		lastLogTime = currentLogTime;
		return duration;
	});
}

bool SimData::isLastPoint()
{
	return currentSimulationId == (simData.size() - 1);
}

void SimData::goToTheNextPoint()
{
	++currentSimulationId;
	if (isLastPoint()) simulationFinished();
}

int SimData::getCurrentDuration()
{
	if(currentSimulationId < durations.size())
		return durations[currentSimulationId];
	throw std::out_of_range("There is no more duration points.");
}

std::vector<QTime> SimData::getTimeLine()
{
	std::vector<QTime> timeLine(simData.size());
	std::transform(simData.begin(), simData.end(), timeLine.begin(), [](const simDataType & data)->QTime {
		return std::get<SIM_TIME>(data.first);
	});
	return timeLine;
}

std::vector<double> SimData::getRaceCurrent()
{
	std::vector<double> curr(simData.size());
	std::transform(simData.begin(), simData.end(), curr.begin(), [](const simDataType & data)->double {
		return std::get<CURRENT>(data.first);
	});
	return curr;
}

int SimData::getCurrentId()
{
	return currentSimulationId;
}

double SimData::getCurrentCurrent()
{
	return getCurrent(currentSimulationId);
}

int SimData::getMeanPeriod()
{
	int sum = std::accumulate(durations.begin(), durations.end(), 0);
	return int((float)sum / durations.size() + 0.5);
}

QTime SimData::getSimulationEstimatedTime()
{
	return std::get<SIM_TIME>(simData.back().first);
}

QTime SimData::getCurrentSimulationTime()
{
	return std::get<SIM_TIME>(simData.at(currentSimulationId).first);
}

void SimData::setNextSimulatedDataPoint(const ReceivedData & data)
{
	if (data.isValid()) {
		lastReceivedPointId = data.getId();
		simData[lastReceivedPointId].second = data;
	}
	else throw std::invalid_argument("Argument is marked as invalid.");
}

void SimData::sendData() {

	json insert = {
		{"id_usr", api->getApiUserId()},
		{"into", SIM_DATA_TABLE}
	};
	
	for (int i = lastSentPointId + 1;
		i <= lastReceivedPointId && i < simData.size();
		++i)
	{
		if (simData[i].second.isValid()) {

			json single_row = {
				{"id_sim_info", this->idSimInfo },
				{"id_log_data", std::get<DB_LOG_ID>(simData[i].first) },
				{"id_curr_sim", i},
				{"curr_timestamp", simData[i].second.getTimestamp().toString(QDATE_TIME_FORMAT).toStdString() },
				{"time_since_beg", std::get<SIM_TIME>(simData[i].first).toString(QTIME_FORMAT).toStdString() }
			};

			auto & received = simData[i].second;

			if (!received.isCurrentNull()) single_row["current"] = received.getCurrent();
			if (!received.isBattLeftVoltNull()) single_row["batt_left_volt"] = received.getBattLeftVolt();
			if (!received.isBattRightVoltNull()) single_row["batt_right_volt"] = received.getBattRightVolt();
			if (!received.isBattLeftTempNull()) single_row["batt_left_temp"] = received.getBattLeftTemp();
			if (!received.isBattRightTempNull()) single_row["batt_right_temp"] = received.getBattRightTemp();

			insert["values_list"].push_back(single_row);
		}
		//else throw 
	}

	if (insert["values_list"].size() > 0) {
		lastSentPointId = lastReceivedPointId;

		api->apiInsert(insert.dump());
		api->connect(api, &ApiHolder::gotResponse, api, [this](const QString & data) {

			api->disconnect();
			qDebug() << data;
		});
	}
}

void SimData::fetchData(int idSimInfo, int idLogInfo)
{
	this->idSimInfo = idSimInfo;
	this->idLogInfo = idLogInfo;

	json select = {
		{"id_usr", api->getApiUserId()},
		{"select", "id_log_data, curr_race_time, " + nameOfAnAttributeOfCurrent},
		{"from", "log_data"},
		{"where", "id_log_info=" + std::to_string(this->idLogInfo)}
	};
	api->apiSelect(select.dump());

	api->connect(api, &ApiHolder::gotResponse, api, [this](const QString & data) {
		
		api->disconnect();
		json resp = json::parse(data.toStdString());

		if (resp["status"].get<std::string>() == "OK") {

			simData.resize(resp["output"].size());
			std::transform(resp["output"].begin(), resp["output"].end(), simData.begin(), [this](const json & row)->simDataType {
				
				return std::pair<dbDataType, ReceivedData>(std::make_tuple<int, QTime, double>(
						row["id_log_data"].get<int>(),
						QTime::fromString(row["curr_race_time"].get<std::string>().c_str()),
						row[nameOfAnAttributeOfCurrent].get<double>()
					), 
					ReceivedData()
				);
			});

			prepareDurationPoints();
		}
		fetchedCallback(resp["status"].get<std::string>(), resp["no"].get<int>(), resp["comment"].get<std::string>());

		sendData();
	});

	
}

int SimData::size() const
{
	return simData.size();
}

void SimData::clearData()
{
	durations.clear();
	simData.clear();
	lastSentPointId = -1;
	lastReceivedPointId = 0;
	currentSimulationId = 0;
}
