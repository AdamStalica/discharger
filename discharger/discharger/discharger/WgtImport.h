#pragma once

#include <QWidget>
#include "ui_WgtImport.h"
#include "WgtNewSpeedway.h"

#include "json.h"

class ThreadSynch;
class ApiHolder;

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
	QString lastError = "";



	/*
		batteries:	id_batt
		speedways:	id_speedway, name
		races:		id_race, id_speedway, name, race_date
		log_types:	id_log_type, name
	*/
	nlohmann::json selects, batteries, log_types, races, speedways;

	void loadData(const QString & sql);
	int loadingId = 0;
	void setComboBoxes();
	void setRaces(int id_speedway);

private slots:
	void newSpBtn();

signals:
	void created();
	void error();
};
