#pragma once

#include <QObject>

#include "json.h"

class ApiHolder;
class WgtLoader;

class BasicData : public QObject
{
	Q_OBJECT

public:
	BasicData(ApiHolder * api, WgtLoader * loader, QObject *parent);
	void fetchData();
	QString getLastError() { return lastError; }
	void clear();
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
		[ { "id_speedway" : int, "name" : std::string }, ...]
	*/
	nlohmann::json speedways;

	/*
		[ { "id_car" : int, "name" : std::string }, ...]
	*/
	nlohmann::json cars;

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
