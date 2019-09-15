#include "WgtImport.h"
#include "ApiHolder.h"
#include "BasicData.h"
#include "WgtLoader.h"

#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

using json = nlohmann::json;

WgtImport::WgtImport(ApiHolder * api, BasicData * data, WgtLoader * loader, QWidget *parent)
	:	QWidget(parent),
		data(data),
		loader(loader),
		api(api)
{
	ui.setupUi(this);

	/*
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
	*/
	//loadData(selects[loadingId].dump().c_str());
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

	connect(this->data, &BasicData::fetched, this, [this] {
		setComboBoxes();
	});

}

WgtImport::~WgtImport(){

}
/*

void WgtImport::loadData(const QString & sql) {

	api->apiSelect(sql);

	connect(api, &ApiHolder::gotResponse, this, [this](const QString & data) {
	
		api->disconnect();
		json obj = json::parse(data.toStdString());

		if (obj["status"] != "ERROR") {

			switch (this->loadingId) {

				case 0:

					this->data->batteries = obj["output"];
					loadData(selects[++loadingId].dump().c_str());
					break;
				case 1:

					this->data->speedways = obj["output"];
					loadData(selects[++loadingId].dump().c_str());
					break;
				case 2:
					
					this->data->races = obj["output"];
					loadData(selects[++loadingId].dump().c_str());
					break;
				case 3:

					this->data->log_types = obj["output"];
					loadData(selects[++loadingId].dump().c_str());
					break;

				case 4:

					this->data->cars = obj["output"];
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
*/

void WgtImport::setComboBoxes() {

	for (auto & sp : this->data->speedways) {
		int id_sp = sp["id_speedway"];
		std::string name = sp["name"];

		ui.sp_list->addItem(name.c_str(), QVariant(id_sp));
	}
	for (auto & batt : this->data->batteries) {
		int id_batt = batt["id_batt"];

		ui.lg_batt_l_list->addItem(QString::number(id_batt), QVariant(id_batt)); 
		ui.lg_batt_r_list->addItem(QString::number(id_batt), QVariant(id_batt));
	}
	for (auto & type : this->data->log_types) {
		int id_type = type["id_log_type"];
		std::string name = type["name"];

		ui.lg_types_list->addItem(name.c_str(), QVariant(id_type));
	}
	for (auto & car : this->data->cars) {
		int id_car = car["id_car"];
		std::string name = car["name"];

		ui.lg_car_list->addItem(QString::number(id_car) + ": " + QString(name.c_str()), QVariant(id_car));
	}
	for (auto & ch : ui.col_box->children()) {
		QComboBox * chCB = dynamic_cast<QComboBox *>(ch);
		if (chCB != nullptr) {
			col_combo_boxes.push_back(chCB);
			chCB->addItem("null");
			if (std::find(recountable.begin(), recountable.end(), chCB->objectName()) != recountable.end())
				chCB->addItem("recount");
		}
	}

	ui.lg_batt_l_list->addItem("null", QVariant(-1));
	ui.lg_batt_r_list->addItem("null", QVariant(-1));

	//emit created();
}

void WgtImport::setRaces(int id_speedway) {

	ui.race_list->clear();
	
	for (auto & race : this->data->races) {
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

	connect(new_sp, &WgtNewSpeedway::addedNewSpeedway, this, [this](const json & newSp) {

		this->data->speedways.push_back(newSp);
		ui.sp_list->addItem(newSp["name"].get<std::string>().c_str(), QVariant(newSp["id_speedway"].get<int>()));
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
	new_race->setSpeedway(ui.sp_list->currentData().toInt(), ui.sp_list->currentText());

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
		this->data->races.push_back(newRace);
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

	bool recount_enabled = false;
	/******************** RECOUNT ********************/

	QString time_format = "hh:mm:ss.zzz";

	json coords = *std::find_if(data->speedways.begin(), data->speedways.end(), [&](const json & sp)->bool {
		return (sp["id_speedway"].get<int>() == ui.sp_list->currentData().toInt());
	});

	/*{
		{ "longitude", 16.808013 },
		{ "longitude_toler", 15.0 },
		{ "latitude", 52.420263 },
		{ "latitude_toler", 5.0 }
	};*/
	double tolerance_ratio = 10000.0;
	double longitude_tolerance_calculated = coords["longitude_toler"].get<double>() / tolerance_ratio;
	double latitude_tolerance_calculated = coords["latitude_toler"].get<double>() / tolerance_ratio;
	
	bool was_inside = false;

	int laps_num = 0;
	int curr_lap_begin_ms = 0;
	int curr_race_begin_ms = 0;

	int curr_lap_logs_num = 0;
	double motor_curr_lap_avg = 0.0;
	double main_curr_lap_avg = 0.0;

	std::vector<QString> to_recount;


	// counting lambdas
	auto timestampToMs = [time_format](const std::string & timestamp)->int {

		return QTime::fromString(QString(timestamp.c_str()).split(" ")[1], time_format).msecsSinceStartOfDay();
	};

	auto currLapAvg = [&curr_lap_logs_num](double & avg, double val)->std::string {

		avg = (((avg * (double)curr_lap_logs_num) + val) / double(curr_lap_logs_num + 1));
		return std::to_string(avg);
	};

	auto currRaceTime = [&curr_race_begin_ms, &timestampToMs, time_format](const std::string & timestamp)->std::string {

		int ms = timestampToMs(timestamp) - curr_race_begin_ms;
		return QTime::fromMSecsSinceStartOfDay(ms).toString(time_format).toStdString();
	};

	auto currLapTime = [&curr_lap_begin_ms, &timestampToMs, time_format](const std::string & timestamp)->std::string {

		int ms = timestampToMs(timestamp) - curr_lap_begin_ms;
		return QTime::fromMSecsSinceStartOfDay(ms).toString(time_format).toStdString();
	};

	auto isInside = [
		&coords, 
		longitude_tolerance_calculated, 
		latitude_tolerance_calculated]
		(double latitude, double longitude)->bool {

		return (
			(latitude >= coords["latitude"].get<double>() - latitude_tolerance_calculated) &&
			(latitude <= coords["latitude"].get<double>() + latitude_tolerance_calculated) &&
			(longitude >= coords["longitude"].get<double>() - longitude_tolerance_calculated) &&
			(longitude <= coords["longitude"].get<double>() + longitude_tolerance_calculated)
		);
	};


	auto recount = [&](json & log) {

		std::string curr_timestamp = log["curr_timestamp"];
		
		double latitude = (log["gps_latitude"].type() == json::value_t::string) ? std::stod(log["gps_latitude"].get<std::string>()) : log["gps_latitude"].get<double>();
		double longitude = (log["gps_longitude"].type() == json::value_t::string) ? std::stod(log["gps_longitude"].get<std::string>()) : log["gps_longitude"].get<double>();

		bool is_inside = isInside(latitude, longitude);

		/*
			is inside and was not inside		-> new lap and mark as was inside
			is inside and was inside			-> do not change
			is not inside and was inside		-> mark as was not inside
			is not inside and was not inside	-> do not change
		*/
		if (is_inside && !was_inside) {
			was_inside = true;

			++laps_num;
			curr_lap_logs_num = 0;
			motor_curr_lap_avg = 0;
			main_curr_lap_avg = 0;
			curr_lap_begin_ms = timestampToMs(curr_timestamp);

		}
		if (!is_inside && was_inside) {
			was_inside = false;
		}

		for (auto & col : to_recount) {
			if (col == recountable[CURR_RACE_TIME]) {
				log[col.toStdString()] = currRaceTime(curr_timestamp);
			}
			else if (col == recountable[CURR_LAP_TIME]) {
				log[col.toStdString()] = currLapTime(curr_timestamp);
			}
			else if (col == recountable[LAPS_NUM]) {
				log[col.toStdString()] = laps_num;
			}
			else if (col == recountable[MOTOR_CURR_LAP_AVG]) {
				if (!log["motor_curr"].empty()) {
					double motor_current = (log["motor_curr"].type() == json::value_t::string) ? std::stod(log["motor_curr"].get<std::string>()) : log["motor_curr"].get<double>();

					log[col.toStdString()] = currLapAvg(motor_curr_lap_avg, motor_current);
				}
			}
			else if (col == recountable[MAIN_CURR_LAP_AVG]) {
				if (!log["main_curr"].empty()) {
					double motor_current = (log["main_curr"].type() == json::value_t::string) ? std::stod(log["main_curr"].get<std::string>()) : log["main_curr"].get<double>();

					log[col.toStdString()] = currLapAvg(main_curr_lap_avg, motor_current);
				}
			}
		}
		++curr_lap_logs_num;
	};


	/*************************************************/
	
	std::vector<std::pair<std::string, std::string>> cols;
	for (auto & cb : col_combo_boxes) {
		if (cb->currentText() != "null")
			cols.emplace_back(cb->objectName().toStdString(), cb->currentText().toStdString());
		if (cb->currentText() == "recount") {
			recount_enabled = true;
			to_recount.push_back(cb->objectName());
		}
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
			if(col.second != "recount")
				data["values_list"][i][col.first] = rec[col.second];

			if (col.first == "curr_timestamp") {
				if (i == 0) {
					std::string begTime = rec[col.second].get<std::string>();
					logTime.first = begTime.c_str();

					curr_lap_begin_ms = curr_race_begin_ms = timestampToMs(begTime);
				}
				else {
					endTime = rec[col.second].get<std::string>();
				}
			}
		}

		if (recount_enabled)
			recount(data["values_list"][i]);

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

	loader->setState("Creating new log info");

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
			loader->setState("Importing data");
			id_log_info = no;
			importData();
		}
		else {
			loader->setState("ERROR");
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

			loader->setState("Updating timing");
			updateLogTime();
		}
		else {
			loader->setState("ERROR");
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

			loader->setState("END");
			QMessageBox::information(this, "Success", "Successfully imported!");
			emit finished();
		}
		else {
			loader->setState("ERROR");
			lastError = "No: " + QString::number(no) + ", " + comment.c_str();
			QMessageBox::critical(this, "Error", lastError);
		}
	});
}