#include "DbTestData.h"
#include "ObjectFactory.h"
#include "WebApi.h"

db::TestData::TestData(QObject *parent)
	: QObject(parent)
{
}

db::TestData::~TestData()
{
}

void db::TestData::clear() {
	simDataVec.clear();
	if (!simDataToInsertQueue.empty())
		insertSimDataToDb();
	idSimInfo = 0;
	testState = TestStates::NONE;
	testError = Device::Error::NO_DEV_ERROR;
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
		[this](bool success, std::string && resp) {

			nlohmann::json response = nlohmann::json::parse(resp);
			if (success) {
				this->idSimInfo = response["id_sim_info"].get<unsigned int>();
				cb(true, "Ok");
			}
			else cb(false, "WebApi faliure");
	});
}

void db::TestData::insertSimDataToDb() {

}