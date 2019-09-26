#include "WgtSim.h"
#include "WgtLoader.h"
#include "ApiHolder.h"
#include "UartHolder.h"

#include <QRegExpValidator>

using json = nlohmann::json;

WgtSim::WgtSim(ApiHolder * api, BasicData * data, WgtLoader * loader, QWidget *parent)
	:	QWidget(parent),	
		api(api),
		data(data),
		loader(loader)
{
	ui.setupUi(this);



	connect(ui.back_btn, &QPushButton::clicked, this, [this]() {
		emit finished();
	});
	connect(uart, &UartHolder::gotError, this, [this](const DeviceError & error) {
		qDebug() << error.what().c_str();
	});

	ui.set_temp_ln->setValidator(new QRegExpValidator(QRegExp("-?\\d+\\.?\\d+"), this));
}

void WgtSim::setUartHolder(UartHolder * uart)
{
	this->uart = uart;
}

void WgtSim::setBasicSimData(const json & data)
{
	try {
		id_batt_left = data["id_batt_left"].get<int>();
		id_batt_right = data["id_batt_right"].get<int>();
		id_log_info = data["id_log_info"].get<int>();
		id_sim_info = data["id_sim_info"].get<int>();
		sim_name = data["name"].get<std::string>();
	}
	catch (const std::exception & ex) {
		throw std::exception("Id_batt_left, id_batt_right, id_log_info, id_sim_info and simulation name are required.");
	}
}

void WgtSim::prepareSimulation()
{
	if (sim_name == "null") throw std::exception("Simulation basic data are not set.");

	loader->setState("Fetching logs data to be simulated during the simulation.");

	json select = {
		{"id_usr", api->getApiUserId()},
		{"select", "id_log_data, curr_race_time, motor_curr"},
		{"from", "log_data"},
		{"where", "id_log_info=" + std::to_string(this->id_log_info)}
	};
	api->apiSelect(select.dump());
	connect(api, &ApiHolder::gotResponse, this, [this](const QString & data) {
	
		api->disconnect();
		json resp = json::parse(data.toStdString());


	
	});
}

WgtSim::~WgtSim()
{
}
