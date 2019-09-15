#include "WgtSimConfig.h"
#include "ApiHolder.h"
#include "BasicData.h"
#include "WgtLoader.h"
#include "UartHolder.h"

#include <QStandardItemModel>
#include <QMessageBox>
#include <QSerialPortInfo>

#include <QTimer>

using json = nlohmann::json;

WgtSimConfig::WgtSimConfig(ApiHolder * api, BasicData * data, WgtLoader * loader, QWidget *parent)
	:	QWidget(parent),
		api(api),
		data(data),
		loader(loader)
{
	ui.setupUi(this);

	auto ports = QSerialPortInfo::availablePorts();
	for (auto & ite : ports) {
		ui.ports_list->addItem(ite.portName());
	}

	connect(ui.go_back_btn, &QPushButton::clicked, this, [this] {
		emit finished();
	});
	connect(this->data, &BasicData::fetched, this, [this] {
		init();
	});
	connect(ui.expand_btn, &QPushButton::clicked, this, [this] {
		if (ui.expand_btn->text() == "Expand all") {
			ui.races_tree->expandToDepth(2);
			ui.expand_btn->setText("Collapse all");
		}
		else {
			ui.races_tree->collapseAll();
			ui.expand_btn->setText("Expand all");
		}
	});
	connect(ui.open_com_btn, SIGNAL(clicked()), this, SLOT(openAndTestCom()));


	connect(ui.pushButton, &QPushButton::clicked, this, [this] {
		uart->sendData(json::parse("{\"hehe\":\"okok\"}"));
	});

	t = new QTimer(this);
	
	connect(t, &QTimer::timeout, this, [this] {
		uart->sendData(json::parse("{\"hehe\":\"okok\"}"));
	});
	
	

}

WgtSimConfig::~WgtSimConfig()
{

}

// TODO remove 1 at the beginning of the tree
void WgtSimConfig::init()
{
	auto tree = ui.races_tree;
	model = new QStandardItemModel(this);
	
	for (auto sp : data->speedways) {
		int id_sp = sp["id_speedway"].get<int>();

		QStandardItem * sp_item = new QStandardItem(sp["name"].get<std::string>().c_str());
		sp_item->setData(QVariant(id_sp));

		auto condition_races = [id_sp](const json & race)->bool {
			return id_sp == race["id_speedway"].get<int>();
		};

		int races_on_the_speedway_count = 0;
		for (
			auto race_it = find_if(data->races.begin(), data->races.end(), condition_races);
			race_it != data->races.end(); 
			race_it = find_if(++race_it, data->races.end(), condition_races)
			) 
		{
			auto race = *race_it;
			int id_race = race["id_race"].get<int>();
			QStandardItem * race_item = new QStandardItem((race["race_date"].get<std::string>() + " " + race["name"].get<std::string>()).c_str());
			race_item->setData(QVariant(id_race));

			int log_series_in_the_race = 0;

			for (auto log_type : data->log_types) {
				int id_log_type = log_type["id_log_type"].get<int>();

				auto condition_logs = [id_race, id_log_type](const json & log_info) {
					return (
						id_race == log_info["id_race"].get<int>() &&
						id_log_type == log_info["id_log_type"].get<int>()
						);
				};

				QStandardItem * single_log_type = new QStandardItem(log_type["name"].get<std::string>().c_str());
				single_log_type->setData(QVariant(id_log_type));

				int log_series_in_the_same_log_type = 0;

				for (
					auto log_info_it = find_if(data->log_info.begin(), data->log_info.end(), condition_logs);
					log_info_it != data->log_info.end();
					log_info_it = find_if(++log_info_it, data->log_info.end(), condition_logs)
					)
				{
					auto log_info = *log_info_it;
					int id_log_info = log_info["id_log_info"].get<int>();

					QStandardItem * log_info_item = new QStandardItem(("Car no. " + std::to_string(log_info["id_car"].get<int>()) + ", begin time " + log_info["begin_time"].get<std::string>()).c_str());
					log_info_item->setData(QVariant(id_log_info));

					log_info_item->setCheckable(true);

					log_info_item->setWhatsThis("hehe");

					QList<QStandardItem *> details = {
						new QStandardItem(("Begin time: " + log_info["begin_time"].get<std::string>()).c_str()),
						new QStandardItem(("End time: " + log_info["end_time"].get<std::string>()).c_str())
					};

					if (!log_info["id_batt_left"].is_null() && !log_info["id_batt_right"].is_null()) {
						details.append(new QStandardItem(("Left battery: " + std::to_string(log_info["id_batt_left"].get<int>())).c_str()));
						details.append(new QStandardItem(("Right battery: " + std::to_string(log_info["id_batt_right"].get<int>())).c_str()));
					}

					log_info_item->appendColumn(details);

					log_info_items.push_back(log_info_item);
					single_log_type->appendRow(log_info_item);
					++log_series_in_the_same_log_type;
				}

				if (log_series_in_the_same_log_type) {
					race_item->appendRow(single_log_type);
					++log_series_in_the_race;
				}
			}

			if (log_series_in_the_race) {
				sp_item->appendRow(race_item);
				++races_on_the_speedway_count;
			}
		}
		if (races_on_the_speedway_count) {
			model->appendRow(sp_item);
		}

	}

	connect(model, SIGNAL(itemChanged(QStandardItem *)), this, SLOT(raceCheckedChanged(QStandardItem *)));
	

	tree->setAnimated(true);
	tree->setModel(model);
}

int WgtSimConfig::getCheckedLogsInfoId()
{
	for (auto lg : log_info_items) {
		if (lg->checkState() == Qt::Checked) {
			return lg->data().toInt();
		}
	}
	QMessageBox::warning(this, "Warning", "Nothing has been chosen!");
	return -1;
}

void WgtSimConfig::openAndTestCom() {

	uart = new UartHolder(this);

	connect(uart, &UartHolder::gotData, this, [this](const json & data) {
		qDebug() << data.dump().c_str();
	});

	if (uart->open(ui.ports_list->currentText())) {
		//uart->sendData(json::parse("{\"hehe\":\"okok\"}"));
		t->start(1000);
	}
	else {
		QMessageBox::critical(this, "Error", uart->getLastError());
	}
}

void WgtSimConfig::raceCheckedChanged(QStandardItem * item) {
	for (auto it : log_info_items) {
		if (it->data().toInt() != item->data().toInt() && it->checkState() != Qt::Unchecked) {

			model->disconnect(SIGNAL(itemChanged(QStandardItem *)));

			it->setCheckState(Qt::Unchecked);

			connect(model, SIGNAL(itemChanged(QStandardItem *)), this, SLOT(raceCheckedChanged(QStandardItem *)));
		}
	}
}