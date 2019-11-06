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

	loadComs();

	connect(ui.open_com_btn, SIGNAL(clicked()), this, SLOT(openAndTestCom()));
	connect(ui.expand_btn, SIGNAL(clicked()), this, SLOT(expandCollapseTree()));
	connect(ui.refresh_btn, SIGNAL(clicked()), this, SLOT(loadComs()));
	connect(ui.prep_sim_btn, SIGNAL(clicked()), this, SLOT(prepareSimulation()));

	connect(ui.go_back_btn, &QPushButton::clicked, this, [this] {
		emit finished();
	});
	connect(this->data, &BasicData::fetched, this, [this] {
		init();
	});
}

void WgtSimConfig::setUartHolder(UartHolder * uart)
{
	this->uart = uart;
	connect(uart, SIGNAL(gotHandshake(int)), this, SLOT(handshakeHolder(int)));
}

WgtSimConfig::~WgtSimConfig()
{
}

void WgtSimConfig::clear()
{

}

// TODO remove 1 at the beginning of the tree
void WgtSimConfig::init()
{
	createTree();
	loadBetteriesList();
}

int WgtSimConfig::getCheckedLogsInfoId()
{
	for (auto lg : log_info_items) {
		if (lg->checkState() == Qt::Checked) {
			return lg->data().toInt();
		}
	}
	return -1;
}

void WgtSimConfig::openAndTestCom() {

	if (!uart->isOpen()) {

		if (!ui.ports_list->count()) {
			QMessageBox::critical(this, "Error", "There is no available com ports.");
			return;
		}

		if (uart->open(ui.ports_list->currentText())) {
			QTimer::singleShot(500, [this] {
				qDebug() << uart->isOpen();
				uart->handshake();
			});
		}
		else {
			QMessageBox::critical(this, "Error", uart->getLastError());
		}
	}
	else {
		uart->close();
		ui.open_com_btn->setText("Open");
		ui.prep_sim_btn->setEnabled(false);
	}
}

void WgtSimConfig::handshakeHolder(int ms)
{
	if (ms == -1) {
		QMessageBox::critical(this, "Error", uart->getLastError());
	}
	else {
		QMessageBox::information(this, "Opened", "Com opened and got handshake within " + QString::number(ms) + "ms.");
		ui.open_com_btn->setText("Close");
		ui.prep_sim_btn->setEnabled(true);
	}
}

void WgtSimConfig::expandCollapseTree()
{
	if (ui.expand_btn->text() == "Expand all") {
		ui.races_tree->expandToDepth(2);
		ui.expand_btn->setText("Collapse all");
	}
	else {
		ui.races_tree->collapseAll();
		ui.expand_btn->setText("Expand all");
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

void WgtSimConfig::loadComs() {
	ui.ports_list->clear();
	auto ports = QSerialPortInfo::availablePorts();
	for (auto & ite : ports) {
		ui.ports_list->addItem(ite.portName());
	}
}

void WgtSimConfig::prepareSimulation() {
	
	if (getCheckedLogsInfoId() == -1) {
		QMessageBox::warning(this, "Warning", "Select a race to be simulated.");
		ui.races_tree->setStyleSheet(noValueCSS);
		return;
	}
	if (!uart->isOpen()) {
		QMessageBox::critical(this, "Error", "Unfortunately got lost communication with the device. Check it and try again.\n\n" + uart->getLastError());
		return;
	}
	if (ui.id_batt_left->currentText() == ui.id_batt_right->currentText()) {
		QMessageBox::warning(this, "Warning", "Id left battery has to be different than id right battery.");
		ui.id_batt_left->setStyleSheet(noValueCSS);
		ui.id_batt_right->setStyleSheet(noValueCSS);
		return;
	}
	if (ui.sim_name->text().size() < 5) {
		QMessageBox::warning(this, "Warning", "Simulation name must be longer than it is now (min 5).");
		ui.sim_name->setStyleSheet(noValueCSS);
		return;
	}

	int id_sim_stat = SIM_IN_PROGRESS;
	int id_usr = api->getApiUserId();
	int id_log_info = getCheckedLogsInfoId();
	int id_batt_left = ui.id_batt_left->currentText().toInt();
	int id_batt_right = ui.id_batt_right->currentText().toInt();
	std::string name = ui.sim_name->text().toStdString();

	QMessageBox::information(this, "Ok", "All required data present, please take a look at this once again and confirm.", QMessageBox::Ok);

	json newSimInfo = {
		{"id_usr", id_usr},
		{"into", "sim_info"},
		{"values_list", {{
				{"id_sim_stat", id_sim_stat},
				{"id_usr", id_usr},
				{"id_log_info", id_log_info},
				{"id_batt_left", id_batt_left},
				{"id_batt_right", id_batt_right},
				{"name", name}
			}}
		}
	};
	loader->setState("Creating new simulation.");

	api->apiInsert(newSimInfo.dump());
	connect(api, &ApiHolder::gotResponse, this, [this](const QString & data) {
	
		api->disconnect();

		json resp = json::parse(data.toStdString());
		if (resp["status"].get<std::string>() == "OK") {
			loader->setState("END");
			emit preparedNewSimCanStart(
				json({
					{ "id_sim_info", resp["no"].get<int>() },
					{ "id_log_info", getCheckedLogsInfoId() },
					{ "id_batt_left", ui.id_batt_left->currentText().toInt() },
					{ "id_batt_right", ui.id_batt_right->currentText().toInt() },
					{ "name", ui.sim_name->text().toStdString() }
				})
			);
		}
		else {
			loader->setState("ERROR");
			QMessageBox::critical(this, "Error", "No. " + QString::number(resp["no"].get<int>()) + ", " + resp["comment"].get<std::string>().c_str());
		}
	});
}

void WgtSimConfig::createTree()
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

void WgtSimConfig::loadBetteriesList()
{
	QStringList ids;
	for (auto & batt : data->batteries)
		ids.append(QString::number(batt["id_batt"].get<int>()));

	ui.id_batt_left->addItems(ids);
	ui.id_batt_right->addItems(ids);
}