#pragma once

#include <QObject>
#include <queue>
#include <DeviceEventsDef.h>
#include "DbSimData.h"
#include "Param.h"

namespace db {

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

		const std::string CURR_SOURCE_STR[3] = {
			"MAIN",
			"MOTOR",
			"NO_CURR_SOURCE"
		};

		std::vector<db::SimData> simDataVec;
		std::queue<db::SimData> simDataToInsertQueue;

		unsigned int idSimInfo = 0;
		TestStates testState = TestStates::NONE;
		Device::Error testError = Device::Error::NO_DEV_ERROR;

		/*
		Param<std::string> currentSource;
		Param<unsigned int> idSimType;
		Param<unsigned int> idLogInfo;
		Param<unsigned int> idBattLeft;
		Param<unsigned int> idBattRight;
		Param<std::string> name;
		*/
		
	public:
		TestData(QObject *parent);
		~TestData();

		void clear();

		void setupTestInDb(std::function<void(bool success, const QString & comment)> callback,
			TestStates testState, CurrentSource currSource, TestType testType, const QString & name,
			int idBattLeft, int idBattRight, int idLogInfo);

	private slots:
		void insertSimDataToDb();

	};
}