#include "WgtImport.h"
#include "ApiHolder.h"

#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

using json = nlohmann::json;

WgtImport::WgtImport(ApiHolder * api, QWidget *parent)
	: QWidget(parent),
		api(api)
{
	ui.setupUi(this);

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

	loadData(selects[loadingId].dump().c_str());
	loadMasks();

	connect(ui.sp_btn, SIGNAL(clicked()), this, SLOT(newSpBtn()));
	connect(ui.race_btn, SIGNAL(clicked()), this, SLOT(newRaceBtn()));
	connect(ui.lg_fp_btn, SIGNAL(clicked()), this, SLOT(openFileBtn()));
	connect(ui.col_new_msk_btn, SIGNAL(clicked()), this, SLOT(saveMskBtn()));
	connect(ui.import_btn, SIGNAL(clicked()), this, SLOT(importBtn()));

	connect(ui.go_back_btn, &QPushButton::clicked, this, [this] {
		emit this->finished();
	});
	connect(ui.cnl_btn, &QPushButton::clicked, this, [this] {
		emit this->finished();
	});
	connect(ui.sp_list, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this](int i) { 
		int id_sp = ui.sp_list->currentData().toInt();
		setRaces(id_sp); 
	});
	connect(ui.col_mask_list, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this](int i) {
		setMasks(i);
	});

}

WgtImport::~WgtImport(){

}

void WgtImport::loadData(const QString & sql) {

	api->apiSelect(sql);

	connect(api, &ApiHolder::gotResponse, this, [this](const QString & data) {
	
		api->disconnect();
		json obj = json::parse(data.toStdString());

		if (obj["status"] != "ERROR") {

			switch (this->loadingId) {

				case 0:

					batteries = obj["output"];
					loadData(selects[++loadingId].dump().c_str());
					break;
				case 1:

					speedways = obj["output"];
					loadData(selects[++loadingId].dump().c_str());
					break;
				case 2:
					
					races = obj["output"];
					loadData(selects[++loadingId].dump().c_str());
					break;
				case 3:

					log_types = obj["output"];
					loadData(selects[++loadingId].dump().c_str());
					break;

				case 4:

					cars = obj["output"];
					setComboBoxes();
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

void WgtImport::setComboBoxes() {

	for (auto & sp : speedways) {
		int id_sp = sp["id_speedway"];
		std::string name = sp["name"];

		ui.sp_list->addItem(name.c_str(), QVariant(id_sp));
	}
	for (auto & batt : batteries) {
		int id_batt = batt["id_batt"];

		ui.lg_batt_l_list->addItem(QString::number(id_batt), QVariant(id_batt)); 
		ui.lg_batt_r_list->addItem(QString::number(id_batt), QVariant(id_batt));
	}
	for (auto & type : log_types) {
		int id_type = type["id_log_type"];
		std::string name = type["name"];

		ui.lg_types_list->addItem(name.c_str(), QVariant(id_type));
	}
	for (auto & car : cars) {
		int id_car = car["id_car"];
		std::string name = car["name"];

		ui.lg_car_list->addItem(QString::number(id_car) + ": " + QString(name.c_str()), QVariant(id_car));
	}
	for (auto & ch : ui.col_box->children()) {
		QComboBox * chCB = dynamic_cast<QComboBox *>(ch);
		if (chCB != nullptr) {
			col_combo_boxes.push_back(chCB);
			chCB->addItem("null");
		}
	}

	ui.lg_batt_l_list->addItem("null", QVariant(-1));
	ui.lg_batt_r_list->addItem("null", QVariant(-1));

	emit created();
}

void WgtImport::setRaces(int id_speedway) {

	ui.race_list->clear();
	
	for (auto & race : races) {
		int race_id_sp = race["id_speedway"];

		if (race_id_sp == id_speedway) {
			int id_race = race["id_race"];
			std::string race_date = race["race_date"];
			std::string name = race["name"];

			ui.race_list->addItem((race_date + " " + name).c_str(), QVariant(id_race));
		}
	}

	ui.race_box->setEnabled(ui.sp_list->count());
	ui.lg_box->setEnabled(ui.race_list->count());
}

void WgtImport::newSpBtn() {
	ui.sp_btn->hide();
	ui.race_box->setEnabled(false);
	ui.lg_box->setEnabled(false);

	new_sp = new WgtNewSpeedway(api, this);
	ui.sp_lay->addWidget(new_sp, Qt::AlignRight);

	connect(new_sp, &WgtNewSpeedway::canceledNewSpeedway, this, [this] {
		delete new_sp;
		ui.sp_btn->show();
		ui.race_box->setEnabled(true);
		ui.lg_box->setEnabled(ui.race_list->count());
	});

	connect(new_sp, &WgtNewSpeedway::addedNewSpeedway, this, [this](int id, const QString & name) {

		json newSp = {
			{"id_speedway", id},
			{"name", name.toStdString()}
		};
		speedways.push_back(newSp);
		ui.sp_list->addItem(name, QVariant(id));
		ui.sp_list->setCurrentIndex(ui.sp_list->count() - 1);

		delete new_sp;
		ui.sp_btn->show();
		ui.race_box->setEnabled(true);
		ui.lg_box->setEnabled(false);
	});
}

void WgtImport::newRaceBtn() {
	ui.race_btn->hide();
	ui.sp_box->setEnabled(false);
	ui.lg_box->setEnabled(false);
	
	new_race = new WgtNewRace(api, this);
	new_race->setSpeedway(ui.sp_list->currentData().toInt() , ui.sp_list->currentText());

	ui.race_lay->addWidget(new_race);

	connect(new_race, &WgtNewRace::canceledNewRace, this, [this] {
		delete new_race;
		ui.race_btn->show();
		ui.sp_box->setEnabled(true);
		ui.lg_box->setEnabled(true);
	});

	connect(new_race, &WgtNewRace::addedNewRace, this, [this](int id_race, int id_speedway, const QString & name, const QString & date) {
		
		json newRace = {
			{"id_race", id_race},
			{"id_speedway", id_speedway},
			{"name", name.toStdString()},
			{"race_date", date.toStdString()}
		};
		races.push_back(newRace);
		ui.race_list->addItem(date + " " + name, QVariant(id_race));
		ui.race_list->setCurrentIndex(ui.race_list->count() - 1);

		delete new_race;
		ui.race_btn->show();
		ui.sp_box->setEnabled(true);
		ui.lg_box->setEnabled(true);
	});

}

void WgtImport::openFileBtn() {
	filepath = QFileDialog::getOpenFileName(this, "Select log file", "C:\\", "Logs file (*.txt)");

	ui.lg_fp_ln->setText(filepath);
	preProcessFile();
}

void WgtImport::preProcessFile() {

	QFile file(filepath);
	if (!file.open(QIODevice::ReadOnly)) {
		QMessageBox::critical(this, "Error", "Can not open the file");
		return;
	}

	QTextStream in(&file);
	if (in.atEnd()) {
		QMessageBox::critical(this, "Error", "This file is empty");
		file.close();
		return;
	}

	QString line = in.readLine();
	file.close();

	json record = json::parse(line.toStdString()); 
	
	for (auto & r : record.items()) {
		QString key = r.key().c_str();
		for (auto & cb : col_combo_boxes) {
			cb->addItem(key);
		}
	}
	
	ui.col_mask_box->setEnabled(true);
	ui.col_box->setEnabled(true);
	ui.col_save_box->setEnabled(true);
	ui.import_btn->setEnabled(true);

}

bool WgtImport::processFile(std::string & out) {
	
	std::vector<std::pair<std::string, std::string>> cols;
	for (auto & cb : col_combo_boxes) {
		if (cb->currentText() != "null")
			cols.emplace_back(cb->objectName().toStdString(), cb->currentText().toStdString());
	}

	QFile file(filepath);
	if (!file.open(QIODevice::ReadOnly)) {
		lastError = "Can not open log file";
		QMessageBox::critical(this, "Error", lastError);
		return false;
	}

	json data;
	data["id_usr"] = api->getApiUserId();
	data["into"] = "log_data";

	std::string endTime;
	int i = 0;

	QTextStream ts(&file);
	while (!ts.atEnd()) {
		
		QString line = ts.readLine();
		if (line.length() < 10) continue;

		json rec = json::parse(line.toStdString());

		data["values_list"][i]["id_log_info"] = id_log_info;
		for (auto & col : cols) {
			data["values_list"][i][col.first] = rec[col.second];

			if (col.first == "curr_timestamp") {
				if (i == 0) {
					std::string begTime = rec[col.second];
					logTime.first = begTime.c_str();
				}
				else {
					std::string tmp = rec[col.second];
					endTime = tmp;
				}
			}
		}
		++i;

	}
	file.close();

	logTime.second = endTime.c_str();

	out = data.dump();
	return true;
}

void WgtImport::saveMskBtn() {
	json newMask;
	std::string newName = QDateTime::currentDateTime().toString("yyyy-MM-dd hhmmss").toStdString() + " " + ui.col_new_msk_ln->text().toStdString();
	newMask["name"] = newName;

	for (auto & cb : col_combo_boxes) {
		newMask["mask"][cb->objectName().toStdString()] = cb->currentText().toStdString();
	}
	col_mask.push_back(newMask);
	ui.col_mask_list->addItem(newName.c_str());
	ui.col_mask_list->setCurrentText(newName.c_str());

	QFile file(mask_filepath);
	if (file.open(QIODevice::ReadWrite)) {
		QTextStream ts(&file);
		ts << col_mask.dump().c_str();
	}
	else {
		QMessageBox::critical(this, "Error", "Can not save the new mask");
	}
	file.close();
}

void WgtImport::loadMasks() {

	QFile file(mask_filepath);

	if (file.open(QIODevice::ReadOnly)) {
		QTextStream ts(&file);
		if (!ts.atEnd()) {
			std::string mask_str = ts.readAll().toStdString();

			col_mask = json::parse(mask_str);

			for (auto & m : col_mask) {
				std::string name = m["name"];
				ui.col_mask_list->addItem(name.c_str());
			}
		}
	}
	file.close();
}

void WgtImport::setMasks(int id_mask) {
	if (id_mask) {

		for (auto & cb : col_combo_boxes) {
			std::string curr_name = col_mask[id_mask - 1]["mask"][cb->objectName().toStdString()];
			cb->setCurrentText(curr_name.c_str());
		}

		ui.col_save_box->setEnabled(false);
		ui.col_box->setEnabled(false);
	}
	else {

		ui.col_save_box->setEnabled(true);
		ui.col_box->setEnabled(true);
	}
}

void WgtImport::importBtn() {

	int count = 0;
	for (auto & cb : col_combo_boxes) {
		if (cb->currentText() == "null") ++count;
	}
	if (col_combo_boxes.size() == count) {
		QMessageBox::warning(this, "Warning", "All columns are marked as null, can not import.");
		return;
	}

	json insert;
	insert["id_usr"] = api->getApiUserId();
	insert["into"] = "log_info";
	insert["values_list"][0]["id_log_type"] = ui.lg_types_list->currentData().toInt();
	insert["values_list"][0]["id_race"] = ui.race_list->currentData().toInt();
	insert["values_list"][0]["id_car"] = ui.lg_car_list->currentData().toInt();

	if (ui.lg_batt_l_list->currentData().toInt() != -1 && ui.lg_batt_r_list->currentData().toInt() != -1) {
		insert["values_list"][0]["id_batt_left"] = ui.lg_batt_l_list->currentData().toInt();
		insert["values_list"][0]["id_batt_right"] = ui.lg_batt_r_list->currentData().toInt();
	}

	api->apiInsert(insert.dump());
	connect(api, &ApiHolder::gotResponse, this, [this](const QString & resp) {
		
		api->disconnect();
		json obj = json::parse(resp.toStdString());

		int no = obj["no"];
		std::string comment = obj["comment"];

		if (obj["status"] == "OK") {
			id_log_info = no;
			importData();
		}
		else {
			lastError = "No: " + QString::number(no) + ", " + comment.c_str();
			QMessageBox::critical(this, "Error", lastError);
		}
	});
}

void WgtImport::importData() {

	std::string insert;
	if (!processFile(insert)) return;

	api->apiInsert(insert);
	connect(api, &ApiHolder::gotResponse, this, [this](const QString & resp) {
		
		api->disconnect();
		json resp_obj = json::parse(resp.toStdString());

		int no = resp_obj["no"];
		std::string comment = resp_obj["comment"];

		if (resp_obj["status"] == "OK") {

			updateLogTime();
		}
		else {
			lastError = "No: " + QString::number(no) + ", " + comment.c_str();
			QMessageBox::critical(this, "Error", lastError);
		}

	});

}

void WgtImport::updateLogTime() {
	
	json update;
	update["id_usr"] = api->getApiUserId();
	update["update"] = "log_info";
	update["set"]["begin_time"] = logTime.first.toStdString();
	update["set"]["end_time"] = logTime.second.toStdString();
	update["where"] = "id_log_info=" + std::to_string(id_log_info);

	api->apiUpdate(update.dump());
	connect(api, &ApiHolder::gotResponse, this, [this](const QString & resp) {
	
		api->disconnect();
		json resp_obj = json::parse(resp.toStdString());

		int no = resp_obj["no"];
		std::string comment = resp_obj["comment"];

		if (resp_obj["status"] == "OK") {
			QMessageBox::information(this, "Success", "Successfully imported!");
			emit finished();
		}
		else {
			lastError = "No: " + QString::number(no) + ", " + comment.c_str();
			QMessageBox::critical(this, "Error", lastError);
		}
	});
}