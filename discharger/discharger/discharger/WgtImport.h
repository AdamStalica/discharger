#pragma once

#include <QWidget>
#include "ui_WgtImport.h"
#include "WgtNewSpeedway.h"
#include "WgtNewRace.h"

#include <nlohmann/json.h>
#include "ClearAble.h"

//class ThreadSynch;
class ApiHolder;
class BasicData;
class WgtLoader;

/*

	TODO
		file validation

*/

class WgtImport : public QWidget, public ClearAble
{
	Q_OBJECT

public:
	WgtImport(ApiHolder * api, BasicData * data, WgtLoader * loader, QWidget *parent = Q_NULLPTR);
	~WgtImport();

	QString getLastError() { return lastError; };
	void clear() override;

private:
	Ui::WgtImport ui;
	ApiHolder * api;
	BasicData * data;
	WgtLoader * loader;

	WgtNewSpeedway * new_sp;
	WgtNewRace * new_race;
	QString lastError = "";
	QString filepath;

	QString mask_filepath = "data/masks.json";

	enum recountable_enum {
		CURR_RACE_TIME,
		CURR_LAP_TIME,
		LAPS_NUM,
		MOTOR_CURR_LAP_AVG,
		MAIN_CURR_LAP_AVG
	};
	/*
		CURR_RACE_TIME
		CURR_LAP_TIME
		LAPS_NUM
		MOTOR_CURR_LAP_AVG
		MAIN_CURR_LAP_AVG
	*/
	std::vector<QString> recountable = {
		"curr_race_time",
		"curr_lap_time",
		"laps_num",
		"motor_curr_lap_avg",
		"main_curr_lap_avg"
	};

	std::vector<QComboBox *> col_combo_boxes;
	int id_log_info;
	
	/*
		first - begin time
		second - end time
	*/
	std::pair<QString, QString> logTime;


	/*
		[ { "name" : std::string , "mask" : { "col" : "old", ...} }, ...]
	*/
	nlohmann::json col_mask;

	//void loadData(const QString & sql);
	//int loadingId = 0;
	void setComboBoxes();
	void setRaces(int id_speedway);
	void preProcessFile();
	bool processFile(std::string & out);
	void loadMasks();
	void setMasks(int id_mask);
	void importData();
	void updateLogTime();



private slots:
	void newSpBtn();
	void newRaceBtn();
	void openFileBtn();
	void saveMskBtn();
	void importBtn();


signals:
	//void created();
	void finished();
	void error();
};
