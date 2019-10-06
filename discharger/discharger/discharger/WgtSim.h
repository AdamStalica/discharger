#pragma once

#include <QWidget>
#include <QTimer>

#include "ui_WgtSim.h"
#include "json.h"
#include "SimData.h"
#include "WgtChart.h"

//#define DoNotSend
#define Arduino

// TODO close event => if simulation in progress then send new state before close.

constexpr auto MaxCurrent = 30.0;

constexpr auto SENDING_TO_DB_PERIOD = 10000;
constexpr auto DEVICE_TIMEOUT = 5000;

class ApiHolder;
class BasicData;
class WgtLoader;
class UartHolder;
class DeviceError;

class WgtSim : public QWidget, SimData
{
	Q_OBJECT

public:
	WgtSim(ApiHolder * api, BasicData * data, WgtLoader * loader, QWidget *parent = Q_NULLPTR);
	void setUartHolder(UartHolder * uart);

	/**
	*	Setter to set simulation basic data.
	*	@param {"id_sim_info":int,"id_log_info":int,"id_batt_left":int,"id_batt_right":int,"name":std::string}
	*/
	void setBasicSimData(const nlohmann::json & data);
	void prepareSimulation();
	~WgtSim() {
		//if (simulationInProgress) simulationFinished(SIM_STATE::REMOVED);
	}

private slots:
	void startStopSimulationBtn();
	void uartErrorsHolder(const DeviceError & error);
	void sendNextDataToDevice();
	void deviceStopped(bool gotResponse);

private:
	Ui::WgtSim ui;
	ApiHolder * api;
	BasicData * data;
	WgtLoader * loader;
	UartHolder * uart;

	WgtChart * currChart, * voltChart;

	QTimer sendingToDbTimer;
	QTimer sendingToDeviceTimer;

	int id_batt_left, id_batt_right, id_log_info, id_sim_info;
	std::string sim_name = "null";

	bool simulationInProgress = false;
	bool temperatureChanged = false;
	bool stopRequestSent = false;

	void fetchedCallback(const std::string & status, int no, const std::string & comment) override;
	void setNewChartPoint(const simDataType & point) override;
	void setBeginTime(const QDateTime & time) override;
	void setEstimatedEndTime(const QDateTime & time) override;
	void setEndTime(const QDateTime & time) override;

	void startSimulation();
	void stopSimulation();
	void setNewSimulationData(const ReceivedData & data);
	void clearLables();
	void closeWidget();

signals:
	void finished();
};
