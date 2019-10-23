#pragma once

#include <QObject>

#include "json.h"
#include "ClearAble.h"


class ApiHolder;
class WgtLoader;

class BasicData : public QObject, public ClearAble
{
	Q_OBJECT

public:
	BasicData(ApiHolder * api, WgtLoader * loader, QObject *parent);
	void fetchData();
	QString getLastError() { return lastError; }
	void clear() override;
	~BasicData();

	/*
		[ { "id_batt" : int }, ...]
	*/
	nlohmann::json batteries;

	/*
		[ { "id_log_type" : int, "name" : std::string }, ...]
	*/
	nlohmann::json log_types;

	/*
		[ { "id_race" : int, "id_speedway" : int, "name" : std::string, "rade_date" : std::string }, ...]
	*/
	nlohmann::json races;

	/*
		[ { "id_speedway" : int, "name" : std::string, "longitude":double, "longitude_toler":double, "latitude":double, "latitude_toler":double }, ...]
	*/
	nlohmann::json speedways;

	/*
		[ { "id_car" : int, "name" : std::string }, ...]
	*/
	nlohmann::json cars;

	/*
		[ { "id_log_info" : int, "id_log_type" : int, "id_race" : int, "id_batt_left" : int, "id_batt_right" : int, "id_car" : int, "begin_time" : std::string, "end_time" : std::string }, ...]
	*/
	nlohmann::json log_info;

private:
	ApiHolder * api;
	WgtLoader * loader;
	
	QString lastError;

	nlohmann::json selects;
	int fetchingId = 0;

	void fetchSingleTable(std::string apiSelect);

signals:
	void fetched();
	void error();

};
