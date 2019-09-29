#include "WgtSim.h"
#include "WgtLoader.h"
#include "ApiHolder.h"
#include "UartHolder.h"

#include <QRegExpValidator>

#include <chrono>
#include <thread>

using json = nlohmann::json;

WgtSim::WgtSim(ApiHolder * api, BasicData * data, WgtLoader * loader, QWidget *parent)
	:	QWidget(parent),	
		SimData(api),
		api(api),
		data(data),
		loader(loader)
{
	ui.setupUi(this);



	connect(ui.back_btn, &QPushButton::clicked, this, [this]() {
		emit finished();
	});

	ui.set_temp_ln->setValidator(new QRegExpValidator(QRegExp("-?\\d+\\.?\\d+"), this));
}

void WgtSim::setUartHolder(UartHolder * uart)
{
	this->uart = uart;

	connect(uart, &UartHolder::gotError, this, [this](const DeviceError & error) {
		qDebug() << error.what().c_str();
	});
}

void WgtSim::setBasicSimData(const json & data)
{
	if (data["id_batt_left"].is_null()) throw std::exception("Id_batt_left is required.");
	if (data["id_batt_right"].is_null()) throw std::exception("Id_batt_right is required.");
	if (data["id_log_info"].is_null()) throw std::exception("Id_log_info is required.");
	if (data["id_sim_info"].is_null()) throw std::exception("Id_sim_info is required.");
	if (data["name"].is_null()) throw std::exception("Name is required.");

	id_batt_left = data["id_batt_left"].get<int>();
	id_batt_right = data["id_batt_right"].get<int>();
	id_log_info = data["id_log_info"].get<int>();
	id_sim_info = data["id_sim_info"].get<int>();
	sim_name = data["name"].get<std::string>();
}

void WgtSim::prepareSimulation()
{
	if (sim_name == "null") throw std::exception("Simulation basic data are not set.");

	loader->setState("Fetching logs data to be simulated during the simulation.");

	SimData::fetchData(id_sim_info, id_log_info);

}

WgtSim::~WgtSim()
{
}

void WgtSim::fetchedCallback(const std::string & status, int no, const std::string & comment)
{
	loader->hideLoader(true);
}
