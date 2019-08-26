#include "BasicData.h"
#include "ApiHolder.h"

using json = nlohmann::json;

BasicData::BasicData(ApiHolder * api, QObject *parent)
	:	QObject(parent),
		api(api)
{}

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

				batteries = obj["output"];
				fetchSingleTable(selects[++fetchingId].dump().c_str());
				break;
			case 1:

				speedways = obj["output"];
				fetchSingleTable(selects[++fetchingId].dump().c_str());
				break;
			case 2:

				races = obj["output"];
				fetchSingleTable(selects[++fetchingId].dump().c_str());
				break;
			case 3:

				log_types = obj["output"];
				fetchSingleTable(selects[++fetchingId].dump().c_str());
				break;

			case 4:

				cars = obj["output"];
				emit fetched();
				break;
			}
		}
		else {
			int no = obj["no"];
			std::string comment = obj["comment"];
			lastError = "No: " + QString::number(no) + ", " + comment.c_str();
			emit error();
		}
	});
}