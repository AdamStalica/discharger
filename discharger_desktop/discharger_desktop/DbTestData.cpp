#include "DbTestData.h"
#include "ObjectFactory.h"
#include "WebApi.h"

db::TestData::TestData(QObject *parent)
	: QObject(parent)
{
	insertingDataTimer.setInterval(INSERTING_INTERVAL);
	connect(&insertingDataTimer, &QTimer::timeout, this, &db::TestData::insertSimDataToDb);
}

db::TestData::~TestData()
{
}

void db::TestData::clear() {
	simDataVec.clear();
	simDataVec.reserve(DEFAULT_VEC_CAPACITY);
	lastInsertedId = 0;
	idSimInfo = 0;
	testState = TestStates::NONE;
	testError.clear();
	beginTime.clear();
	endTime.clear();
}

void db::TestData::setupTestInDb(
	std::function<void(bool success, const QString &comment)> callback, TestStates testState, 
	CurrentSource currSource, TestType testType, const QString & name, int idBattLeft, 
	int idBattRight, int idLogInfo) 
{
	static std::function<void(bool success, const QString & comment)> cb = callback;

	if (testState == TestStates::NONE)
		throw std::exception("Test state can not be none");

	nlohmann::json setupData;
	setupData["id_sim_stat"] = testState;
	setupData["curr_source"] = CURR_SOURCE_STR[currSource];
	setupData["id_sim_type"] = testType;
	if (idLogInfo != -1)
		setupData["id_log_info"] = idLogInfo;
	setupData["id_batt_left"] = idBattLeft;
	if (idBattRight != -1)
		setupData["id_batt_right"] = idBattRight;
	setupData["name"] = name.toStdString();
	this->testState = testState;

	ObjectFactory::getInstance<WebApi>()->POST(
		API_TEST_SETUP_FILE, setupData,
		[this](WebApi::StatsEnum status, nlohmann::json && resp) {

			if (status == WebApi::API_OK) {
				this->idSimInfo = resp.at("id_sim_info").get<unsigned int>();
				cb(true, "Ok");
			}
			else cb(false, "WebApi faliure");
	});
}

void db::TestData::setTestState(TestStates testState) {
	
	if (testState == TestStates::PROGRESS && this->testState == TestStates::READY) {
		insertingDataTimer.start();
	}
	if (testState != TestStates::PROGRESS && insertingDataTimer.isActive()) {
		insertingDataTimer.stop();
	}
	if (testState > TestStates::PROGRESS && this->testState == TestStates::PROGRESS) {
		if (!endTime && !simDataVec.empty()) {
			endTime = simDataVec.back()
				.currTimestamp
				.val()
				.toString(DB_DATETIME_FORMAT)
				.toStdString();
		}
	}
	this->testState = testState;
	insertSimDataToDb();
}

void db::TestData::setTestError(dischargerDevice::Error error) {
	testError = error;
}

void db::TestData::addSimData(SimData && data) {
	data.idSimInfo = idSimInfo;
	if (!beginTime) {
		beginTime = data.currTimestamp
			.val()
			.toString(DB_DATETIME_FORMAT)
			.toStdString();
	}
	simDataVec.push_back(std::move(data));
}



/*
	{
		"id_sim_info":int,
		"info":{
			"id_sim_stat":int,
			"id_sim_error":int,
			"begin_time":string,
			"end_tiem":string
		}
		"data":{
			
		}
	}
*/

void db::TestData::insertSimDataToDb() {
	nlohmann::json data;
	data["id_sim_info"] = idSimInfo;
	data["info"]["id_sim_stat"] = testState;
	if (testError)
		data["info"]["id_sim_error"] = testError.val();
	if (beginTime)
		data["info"]["begin_time"] = beginTime.val();
	if (endTime)
		data["info"]["end_time"] = endTime.val();

	int dataCount = simDataVec.size() - 1 - lastInsertedId;
	if (dataCount > 0) {
		data["data"] = std::vector<db::SimData>(dataCount);
		std::copy(
			simDataVec.begin() + lastInsertedId + 1, 
			simDataVec.end(), 
			data["data"].begin()
		);
		lastInsertedId = simDataVec.size() - 1;
	}

	ObjectFactory::getInstance<WebApi>()->POST(
		API_TEST_SYNCH_FILE, data,
		[this](WebApi::StatsEnum status, nlohmann::json && resp) {
			qDebug() << resp.dump().c_str();
		}
	);
}