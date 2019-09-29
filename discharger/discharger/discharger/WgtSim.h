#pragma once

#include <QWidget>
#include "ui_WgtSim.h"
#include "json.h"
#include "SimData.h"

class ApiHolder;
class BasicData;
class WgtLoader;
class UartHolder;

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
	~WgtSim();

private:
	Ui::WgtSim ui;
	ApiHolder * api;
	BasicData * data;
	WgtLoader * loader;
	UartHolder * uart;


	int id_batt_left, id_batt_right, id_log_info, id_sim_info;
	std::string sim_name = "null";

	void fetchedCallback(const std::string & status, int no, const std::string & comment) override;

signals:
	void finished();
};
