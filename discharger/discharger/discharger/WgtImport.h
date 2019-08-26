#pragma once

#include <QWidget>
#include "ui_WgtImport.h"
#include "WgtNewSpeedway.h"
#include "WgtNewRace.h"

#include "json.h"

class ThreadSynch;
class ApiHolder;

/*

	TODO
		file validation

*/

class WgtImport : public QWidget
{
	Q_OBJECT

public:
	WgtImport(ApiHolder * api, QWidget *parent = Q_NULLPTR);
	~WgtImport();

	QString getLastError() { return lastError; };

private:
	Ui::WgtImport ui;
	ApiHolder * api;
	WgtNewSpeedway * new_sp;
	WgtNewRace * new_race;
	QString lastError = "";
	QString filepath;

	QString mask_filepath = "data/masks.json";

	std::vector<QComboBox *> col_combo_boxes;
	int id_log_info;
	
	/*
		first - begin time
		second - end time
	*/
	std::pair<QString, QString> logTime;


	nlohmann::json selects;

	/*
		batteries:	id_batt
	*/
	nlohmann::json batteries;
	
	/*
		log_types:	id_log_type, name
	*/
	nlohmann::json log_types;
	
	/*
		races:		id_race, id_speedway, name, race_date
	*/
	nlohmann::json races;
	
	/*
		speedways:	id_speedway, name
	*/
	nlohmann::json speedways;
	
	/*
		cars:		id_car, name
	*/
	nlohmann::json cars;

	/*
		[ { "name" : std::string , "mask" : { "col" : "old", ...} }, ...]
	*/
	nlohmann::json col_mask;

	void loadData(const QString & sql);
	int loadingId = 0;
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
	void created();
	void finished();
	void error();
};
