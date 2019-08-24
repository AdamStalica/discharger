#include "WgtImport.h"
#include "ApiHolder.h"

using json = nlohmann::json;

WgtImport::WgtImport(ApiHolder * api, QWidget *parent)
	: QWidget(parent),
		api(api)
{
	ui.setupUi(this);

	int id_usr = 1;
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

	loadData(selects[loadingId].dump().c_str());


	connect(ui.sp_btn, SIGNAL(clicked()), this, SLOT(newSpBtn()));
	connect(ui.sp_list, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this](int i) { 
		int id_sp = ui.sp_list->currentData().toInt();
		setRaces(id_sp); 
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

	ui.lg_box->setEnabled((ui.race_list->count()));
}

void WgtImport::newSpBtn() {
	ui.sp_btn->hide();

	new_sp = new WgtNewSpeedway(api, this);
	ui.sp_lay->addWidget(new_sp);

	connect(new_sp, &WgtNewSpeedway::canceledNewSpeedway, this, [this] {
		delete new_sp;
		ui.sp_btn->show();
	});

	connect(new_sp, &WgtNewSpeedway::addedNewSpeedway, this, [this](int id, const QString & name) {

		json newSp = {
			{"id_speedway", id},
			{"name", name.toStdString()}
		};
		speedways.push_back(newSp);
		ui.sp_list->insertItem(id, name);
		ui.sp_list->setCurrentIndex(speedways.size() - 1);

		delete new_sp;
		ui.sp_btn->show();
	});
}
