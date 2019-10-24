#include "WgtSim.h"
#include "WgtLoader.h"
#include "ApiHolder.h"
#include "UartHolder.h"

#include <QRegExpValidator>
#include <QMessageBox>

#include <chrono>
#include <thread>

using json = nlohmann::json;

// public

WgtSim::WgtSim(ApiHolder * api, BasicData * data, WgtLoader * loader, QWidget *parent)
	:	QWidget(parent),	
		SimData(api),
		api(api),
		data(data),
		loader(loader)
{
	ui.setupUi(this);

	connect(ui.start_stop_btn, SIGNAL(clicked()), this, SLOT(startStopSimulationBtn()));

	connect(ui.back_btn, &QPushButton::clicked, this, [this]() {
		closeWidget();
	});
	connect(ui.set_temp_ln, &QLineEdit::editingFinished, this, [this]() {
		this->temperatureChanged = true;
	});

	ui.set_temp_ln->setValidator(new QRegExpValidator(QRegExp("-?\\d+\\.?\\d+"), this));
}

void WgtSim::setUartHolder(UartHolder * uart)
{
	this->uart = uart;
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

	ui.sim_name->setText(sim_name.c_str());
	ui.id_left_batt->setText(QString::number(id_batt_left));
	ui.id_right_batt->setText(QString::number(id_batt_right));
}

void WgtSim::prepareSimulation()
{
	if (sim_name == "null") throw std::exception("Simulation basic data are not set.");

	loader->setState("Fetching logs data to be simulated during the simulation.");

	SimData::fetchData(id_sim_info, id_log_info);
}

// slots

void WgtSim::startStopSimulationBtn() {

	auto ans = QMessageBox::question(
		this,
		"Confirm",
		("Please, confirm simulation " + QString(simulationInProgress ? "stop" : "start") + ".\nDo you?"),
		QMessageBox::StandardButton::No,
		QMessageBox::StandardButton::Yes
	);

	if (ans == QMessageBox::StandardButton::Yes) {
		if (simulationInProgress) {
			stopSimulation();
			ui.back_btn->setEnabled(true);
			ui.start_stop_btn->setText("Start");
		}
		else {
			startSimulation();
			ui.back_btn->setEnabled(false);
			ui.start_stop_btn->setText("Stop");
		}
	}
}

void WgtSim::clear()
{

}

void WgtSim::uartErrorsHolder(const DeviceError & error)
{
	qDebug() << error.what().c_str();
}

void WgtSim::sendNextDataToDevice()
{
	if (!reachedEnd()) {
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
	else {
		if (!stopRequestSent) {
			uart->sendStop();
			ui.sim_stat_lbl->setText("Finished");

#ifndef Arduino
			sendingToDbTimer.stop();
			sendingToDeviceTimer.stop();
#endif // !Arduino


		}
	}
}

void WgtSim::deviceStopped(bool gotResponse)
{
	simulationFinished(SIM_STATE::COMPLETED);

	if (!gotResponse) {
		QMessageBox::warning(
			this,
			"Warning",
			"The device did not confirm finish of simulation.\nCheck it.",
			QMessageBox::StandardButton::Ok
		);
	}
	auto resp = QMessageBox::question(
		this,
		"Confirm",
		"You can confirm this simulation.\n(It is not required, do it if everything looks ok.)",
		QMessageBox::StandardButton::Apply,
		QMessageBox::Cancel
	);
	if (resp == QMessageBox::StandardButton::Apply)
		simulationFinished(SIM_STATE::CONFIRMED);
	
	closeWidget();
}

// private overridden

void WgtSim::fetchedCallback(const std::string & status, int no, const std::string & comment)
{
	loader->hideLoader(true);

	currChart = new WgtChart(this, "Race", "Simulation");
	currChart->setUnit("A");
	currChart->setColors(QColor(182, 253, 142), QColor(0, 253, 142));
	ui.curr_chart_lay->addWidget(currChart);

	voltChart = new WgtChart(this, "Left", "Right");
	voltChart->setUnit("V");
	ui.volt_chart_lay->addWidget(voltChart);

	if (status == "OK") {
		ui.est_time_lbl->setText(getSimulationEstimatedTime().toString(QTIME_FORMAT));
	}
	else {
		QMessageBox::critical(this, status.c_str(), "No. " + QString::number(no) + ", " + QString(comment.c_str()));
		closeWidget();
	}
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

void WgtSim::setBeginTime(const QDateTime & time)
{
	ui.started_at_lbl->setText(time.toString(QDATE_TIME_FORMAT));
}

void WgtSim::setEstimatedEndTime(const QDateTime & time)
{
	ui.finished_at_lbl->setText(time.toString(QDATE_TIME_FORMAT));
}

void WgtSim::setEndTime(const QDateTime & time)
{
	ui.finished_name_lbl->setText("Finished at: ");
	ui.finished_at_lbl->setText(time.toString(QDATE_TIME_FORMAT));
}

// private

void WgtSim::startSimulation()
{
	if (!simulationInProgress) {
		simulationInProgress = true;

		connect(&sendingToDeviceTimer, SIGNAL(timeout()), this, SLOT(sendNextDataToDevice()));

		connect(uart, &UartHolder::gotError, this, &WgtSim::uartErrorsHolder);
		connect(uart, &UartHolder::gotStop, this, &WgtSim::deviceStopped);

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
		sendingToDbTimer.start(SENDING_TO_DB_PERIOD);

#ifndef DoNotSend
		this->setSendingIntoDbEnabled(true);
#endif // !DoNotSend
	}
}

void WgtSim::stopSimulation()
{
	if (simulationInProgress) {
		simulationInProgress = false;
		uart->sendStop();
		ui.sim_stat_lbl->setText("Stopping...");

#ifndef Arduino
		sendingToDbTimer.stop();
		sendingToDeviceTimer.stop();
#endif // !Arduino
		
		uart->disconnect();
		connect(uart, &UartHolder::gotStop, this, [this](bool b) {
			this->simulationFinished(SIM_STATE::REMOVED);
			closeWidget();
		});
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
	ui.sim_name->setText("");
	ui.sim_stat_lbl->setText("Not started yet.");
	ui.sim_progress_bar->setValue(0);
	ui.started_at_lbl->setText("");
	ui.finished_name_lbl->setText("Estimated end: ");
	ui.finished_at_lbl->setText("");
	ui.est_time_lbl->setText("");
	ui.sim_time_lbl->setText("");
	ui.set_curr_lbl->setText("");
	ui.current_lbl->setText("");
	ui.id_left_batt->setText("");
	ui.vol_left_lbl->setText("");
	ui.temp_left_lbl->setText("");
	ui.id_right_batt->setText("");
	ui.vol_right_lbl->setText("");
	ui.temp_right_lbl->setText("");
}

void WgtSim::closeWidget()
{
	uart->disconnect();

	ui.back_btn->setEnabled(true);
	stopRequestSent = false;
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



/*
	1. Start button clicked.
	2. Sending first data and starting timer to send next data.
	3. If button stop clicked, that stops simulation. 
	4. If there is no more data to be simulated sends stop signal.
	4. When got confirmation that simulation has been stopped, 

*/