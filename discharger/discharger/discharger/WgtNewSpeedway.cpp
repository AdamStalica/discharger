#include "WgtNewSpeedway.h"
#include <nlohmann/json.h>

#include <QRegExpValidator>
#include <ApiHolder.h>
#include <QTimer>

using json = nlohmann::json;

WgtNewSpeedway::WgtNewSpeedway(ApiHolder * api, QWidget *parent)
	:	QWidget(parent),
		api(api)
{
	ui.setupUi(this);

	timer = new QTimer(this);

	connect(ui.sp_add_btn, SIGNAL(clicked()), this, SLOT(addNewSpeedway()));
	connect(ui.sp_cnl_btn, &QPushButton::clicked, this, [this] {
		emit canceledNewSpeedway();
	});
	connect(timer, &QTimer::timeout, this, [this]() {
		ui.sp_lbl->setText(ui.sp_lbl->text() + ".");
	});

	sp_lns = {
		ui.name,
		ui.longitude,
		ui.longitude_toler,
		ui.latitude,
		ui.latitude_toler
	};

	for (auto & ln : sp_lns) {
		if (ln->objectName() == "name") {
			ln->setValidator(new QRegExpValidator(QRegExp("\\w{5,30}"), this));
		}
		else {
			ln->setValidator(new QRegExpValidator(QRegExp("-?\\d+\\.?\\d+"), this));
		}
	}
}

WgtNewSpeedway::~WgtNewSpeedway()
{
	delete timer;
}

void WgtNewSpeedway::addNewSpeedway() {
		
	json insert;
	QString ans = "";

	insert["id_usr"] = api->getApiUserId();
	insert["into"] = "speedways";
	bool isValid = true;

	for (auto & ln : sp_lns) {

		auto txt = ln->text();

		if (!txt.isEmpty()) {
			if (ln->objectName() != "name" && txt.back() == ".") {
				txt += "0";
				ln->setText(txt);
			}

			insert["values_list"][0][ln->objectName().toStdString()] = txt.toStdString();
		}
		else {
			isValid = false;
			ln->setStyleSheet("background-color: red;");
		}
	}
	if (!isValid) {
		ui.sp_lbl->setText("Fill empty fields!");
		return;
	}

	ui.sp_lbl->setText("Adding");
	timer->start(500);

	api->apiInsert(insert.dump());
	connect(api, &ApiHolder::gotResponse, this, [&](const QString & resp) {

		api->disconnect();
		timer->stop();

		json resp_json = json::parse(resp.toStdString());

		int no = resp_json["no"];
		std::string comment = resp_json["comment"];

		if (resp_json["status"] == "OK") {
			ui.sp_lbl->setText("Added and got id = " + QString::number(no));

			json newSp = {
				{"id_speedway", no},
				{"longitude", ui.longitude->text().toDouble()},
				{"longitude_toler", ui.longitude_toler->text().toDouble()},
				{"latitude", ui.latitude->text().toDouble()},
				{"latitude_toler", ui.latitude_toler->text().toDouble()},
				{"name", ui.name->text().toStdString()}
			};

			emit addedNewSpeedway(newSp);
		}
		else {
			
			ui.sp_lbl->setText("Error no: " + QString::number(no) + ": " + QString(comment.c_str()));
		}
	});
}