#include "SimData.h"
#include "json.h"
#include "ApiHolder.h"

#include <algorithm>

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

int SimData::getCurrentId()
{
	return currentSimulationId;
}

double SimData::getCurrentCurrent()
{
	return getCurrent(currentSimulationId);
}

void SimData::setNextSimulatedDataPoint(const ReceivedData & data)
{
	int id = data.getId();
	simData[id].second = data;
}

void SimData::sendData()
{

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
	});
}
