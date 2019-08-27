#include "BasicData.h"
#include "ApiHolder.h"
#include "WgtLoader.h"

using json = nlohmann::json;

BasicData::BasicData(ApiHolder * api, WgtLoader * loader, QObject *parent)
	:	QObject(parent),
		loader(loader),
		api(api)
{}

void BasicData::clear()
{
	batteries.clear();
	log_types.clear();
	races.clear();
	speedways.clear();
	cars.clear();
}

BasicData::~BasicData()
{}

void BasicData::fetchData() {
	int id_usr = api->getApiUserId();
	selects[0] = {
		{"id_usr", id_usr},
		{ "select", "id_batt" },
		{ "from", "batteries" }
	};
	selects[1] = {
		{"id_usr", id_usr},
		{ "select", "id_speedway, name" },
		{ "from", "speedways" }
	};
	selects[2] = {
		{"id_usr", id_usr},
		{ "select", "id_race, id_speedway, name, race_date" },
		{ "from", "races" }
	};
	selects[3] = {
		{"id_usr", id_usr},
		{ "select", "id_log_type, name" },
		{ "from", "log_types" }
	};
	selects[4] = {
		{"id_usr", id_usr},
		{"select", "id_car, name"},
		{"from", "cars"}
	};

	loader->setState("Fetching batteries table.");
	fetchSingleTable(selects[fetchingId].dump());
}

void BasicData::fetchSingleTable(std::string apiSelect) {

	api->apiSelect(apiSelect);

	connect(api, &ApiHolder::gotResponse, this, [this](const QString & data) {

		api->disconnect();
		json obj = json::parse(data.toStdString());

		if (obj["status"] != "ERROR") {

			switch (this->fetchingId) {

			case 0:
				loader->setState("Fetching speedways table.");
				batteries = obj["output"];
				fetchSingleTable(selects[++fetchingId].dump().c_str());
				break;
			case 1:
				loader->setState("Fetching races table.");
				speedways = obj["output"];
				fetchSingleTable(selects[++fetchingId].dump().c_str());
				break;
			case 2:
				loader->setState("Fetching log types table.");
				races = obj["output"];
				fetchSingleTable(selects[++fetchingId].dump().c_str());
				break;
			case 3:
				loader->setState("Fetching cars table.");
				log_types = obj["output"];
				fetchSingleTable(selects[++fetchingId].dump().c_str());
				break;

			case 4:
				loader->setState("END");
				cars = obj["output"];
				emit fetched();
				break;
			}
		}
		else {
			int no = obj["no"];
			std::string comment = obj["comment"];
			lastError = "No: " + QString::number(no) + ", " + comment.c_str();
			loader->setState("ERROR");
			emit error();
		}
	});
}