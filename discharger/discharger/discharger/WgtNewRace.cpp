#include "WgtNewRace.h"

#include "ApiHolder.h"
#include <nlohmann/json.h>

#include <QDebug>
#include <QTimer>

using json = nlohmann::json;

WgtNewRace::WgtNewRace(ApiHolder * api, QWidget *parent)
	:	QWidget(parent),
		api(api)
{
	ui.setupUi(this);

	timer = new QTimer;
	connect(timer, &QTimer::timeout, this, [this] {
		ui.race_lbl->setText(ui.race_lbl->text() + ".");
	});

	connect(ui.race_add_btn, SIGNAL(clicked()), this, SLOT(addNewRace()));
	connect(ui.race_cnl_btn, &QPushButton::clicked, this, [this] {
		emit canceledNewRace();
	});

	ui.name->setValidator(new QRegExpValidator(QRegExp(".{5,50}"), this));
}

WgtNewRace::~WgtNewRace() {
	delete timer;
}


void WgtNewRace::addNewRace() {

	json insert;
	QString ans;

	insert["id_usr"] = api->getApiUserId();
	insert["into"] = "races";
	insert["values_list"][0]["race_date"] = ui.race_date->date().toString("yyyy-MM-dd").toStdString();
	insert["values_list"][0]["id_speedway"] = id_speedway;

	if (!ui.name->text().isEmpty()) {
		insert["values_list"][0]["name"] = ui.name->text().toStdString();
	}
	else {
		ui.name->setStyleSheet("background-color: red;");
		ui.race_lbl->setText("Name can not be empty!");
		return;
	}
	
	ui.race_lbl->setText("Adding");
	timer->start(500);

	api->apiInsert(insert.dump());
	connect(api, &ApiHolder::gotResponse, this, [this](const QString & resp) {
		
		api->disconnect();
		timer->stop();

		json resp_json = json::parse(resp.toStdString());

		int no = resp_json["no"];
		std::string comment = resp_json["comment"];

		if (resp_json["status"] == "OK") {
			ui.race_lbl->setText("Added and got id = " + QString::number(no));
			emit addedNewRace(no, this->id_speedway, ui.name->text(), ui.race_date->date().toString("yyyy-MM-dd"));
		}
		else {
			ui.race_lbl->setText("Error no: " + QString::number(no) + ": " + QString(comment.c_str()));
		}
	});
}