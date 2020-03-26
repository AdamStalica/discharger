#pragma once

#include <QObject>
#include <QTimer>
#include <queue>
#include <DeviceEventsDef.h>
#include "DbSimData.h"
#include "Param.h"

namespace db {

	auto constexpr INSERTING_INTERVAL = 10000; // ms

	enum TestStates {
		READY,
		PROGRESS,
		COMPLETED,
		CONFIRMED,
		REMOVED,
		DEV_ERROR,
		NONE
	};

	enum TestType {
		SIMULATION,
		BASIC_TEST,
		DEV_TERM
	};

	enum CurrentSource {
		MAIN,
		MOTOR,
		NO_CURR_SOURCE
	};

	class TestData : public QObject
	{
		Q_OBJECT

	private:
		const std::string API_TEST_SETUP_FILE = "setup_new_test.php";
		const std::string API_TEST_SYNCH_FILE = "synch_test_data.php";

		const size_t DEFAULT_VEC_CAPACITY = 1000;

		QTimer insertingDataTimer;

		const std::string CURR_SOURCE_STR[3] = {
			"MAIN",
			"MOTOR",
			"NO_CURR_SOURCE"
		};

		std::vector<db::SimData> simDataVec;
		unsigned int lastInsertedId = 0;

		unsigned int idSimInfo = 0;
		TestStates testState = TestStates::NONE;

		Param<Device::Error> testError;
		Param<std::string> beginTime;
		Param<std::string> endTime;
		
	public:
		TestData(QObject *parent);
		~TestData();

		void clear();

		void setupTestInDb(std::function<void(bool success, const QString & comment)> callback,
			TestStates testState, CurrentSource currSource, TestType testType, const QString & name,
			int idBattLeft, int idBattRight, int idLogInfo);

		void setTestState(TestStates testState);
		void setTestError(Device::Error error);

		TestStates getTestState() { return testState; }

		void addSimData(SimData && data);

	private slots:
		void insertSimDataToDb();

	};
}