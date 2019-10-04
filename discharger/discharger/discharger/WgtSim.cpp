#include "WgtSim.h"
#include "WgtLoader.h"
#include "ApiHolder.h"
#include "UartHolder.h"

#include <QRegExpValidator>
#include <QMessageBox>

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

	connect(ui.start_stop_btn, SIGNAL(clicked()), this, SLOT(startStopSimulation()));

	connect(ui.back_btn, &QPushButton::clicked, this, [this]() {
		emit finished();
	});
	connect(ui.set_temp_ln, &QLineEdit::editingFinished, this, [this]() {
		this->temperatureChanged = true;
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

void WgtSim::uartErrorsHolder(const DeviceError & error)
{

}

void WgtSim::startStopSimulation() {

	auto ans = QMessageBox::question(
		this, 
		"Confirm",
		("Please, confirm simulation " + QString(simulationInProgress ? "stop" : "start") + ".\nDo you?"),
		QMessageBox::StandardButton::No,
		QMessageBox::StandardButton::Yes
	);

	if (ans == QMessageBox::StandardButton::Yes) {
		if (simulationInProgress) {
			simulationInProgress = false;
			ui.start_stop_btn->setText("Start");
			stopSimulation();
		}
		else {
			qDebug() << "Start";
			simulationInProgress = true;
			ui.back_btn->setEnabled(false);
			ui.start_stop_btn->setText("Stop");
			startSimulation();
		}
	}
}

void WgtSim::fetchedCallback(const std::string & status, int no, const std::string & comment)
{

	loader->hideLoader(true);
	ui.est_time_lbl->setText(getSimulationEstimatedTime().toString(QTIME_FORMAT));

	currChart = new WgtChart(this, "Race", "Simulation");
	currChart->setUnit("A");
	ui.curr_chart_lay->addWidget(currChart);

	voltChart = new WgtChart(this, "Left", "Right");
	voltChart->setUnit("V");
	ui.volt_chart_lay->addWidget(voltChart);
}

void WgtSim::simulationFinished()
{

	// checking
	qDebug() << "Not got answer: " << notGetAnswer() << " times.";
}

void WgtSim::setNewChartPoint(const simDataType & point)
{
	currChart->append(
		std::get<SIM_TIME>(point.first), 
		std::get<CURRENT>(point.first), 
		point.second.getCurrent()
	);
	voltChart->append(
		std::get<SIM_TIME>(point.first),
		point.second.getBattLeftVolt(),
		point.second.getBattRightVolt()
	);
}

void WgtSim::startSimulation()
{
	qDebug() << "Not got answer: " << notGetAnswer() << " times.";

	connect(uart, SIGNAL(gotError(const DeviceError & error)), this, SLOT(uartErrorsHolder(const DeviceError & error)));
	connect(&sendingToDeviceTimer, SIGNAL(timeout()), this, SLOT(sendNextDataToDevice()));

	connect(uart, &UartHolder::gotData, this, [this](const ReceivedData & data) {
		this->setNextSimulatedDataPoint(data);
		this->setNewSimulationData(data);
	});

	connect(&sendingToDbTimer, &QTimer::timeout, this, [this]() {
		this->sendData();
	});

	ui.sim_stat_lbl->setText("In progress");
	sendNextDataToDevice();
	sendingToDeviceTimer.start(getMeanPeriod());

#ifndef DoNotSend
	sendingToDbTimer.start(SENDING_TO_DB_PERIOD);
#endif // !DoNotSend
}

void WgtSim::stopSimulation()
{
	if (simulationInProgress) {
		uart->sendStop();
		ui.sim_stat_lbl->setText("Stopped");
	}
	simulationInProgress = false;
	temperatureChanged = false;
	sendingToDeviceTimer.disconnect();
	sendingToDeviceTimer.stop();
	sendingToDeviceTimer.disconnect();
	sendingToDbTimer.stop();
	clearData();
	clearLables();

	delete currChart;
	delete voltChart;

	emit finished();
}

void WgtSim::sendNextDataToDevice()
{
	if (!isLastPoint()) {
		int id = getCurrentId();
		double current = getCurrentCurrent();
		current = (current > MaxCurrent ? MaxCurrent : current);

		if (temperatureChanged) {
			temperatureChanged = false;

			float temp = ui.set_temp_ln->text().toFloat();
			uart->sendData(id, current, temp);
		}
		else
			uart->sendData(id, current);

		goToTheNextPoint();
	}
}

void WgtSim::setNewSimulationData(const ReceivedData & data)
{
	//currChart->appendYSeries("Simulation", data.getId(), data.getCurrent());
	ui.sim_progress_bar->setValue(int((data.getId() + 1.0) / SimData::size() * 100.0 + 0.5));
	ui.sim_time_lbl->setText(getCurrentSimulationTime().toString(QTIME_FORMAT));
	ui.set_curr_lbl->setText(QString::number(getCurrentCurrent()));
	ui.current_lbl->setText(QString::number(data.getCurrent()));
	ui.vol_left_lbl->setText(QString::number(data.getBattLeftVolt()));
	ui.temp_left_lbl->setText(QString::number(data.getBattLeftTemp()));
	ui.vol_right_lbl->setText(QString::number(data.getBattRightVolt()));
	ui.temp_right_lbl->setText(QString::number(data.getBattRightTemp()));
}

void WgtSim::clearLables()
{
	ui.sim_progress_bar->setValue(0);
	ui.est_time_lbl->setText("");
	ui.sim_time_lbl->setText("");
	ui.set_curr_lbl->setText("");
	ui.current_lbl->setText("");
	ui.vol_left_lbl->setText("");
	ui.temp_left_lbl->setText("");
	ui.vol_right_lbl->setText("");
	ui.temp_right_lbl->setText("");
}
