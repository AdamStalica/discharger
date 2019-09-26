#pragma once

#include <QWidget>
#include "ui_WgtSim.h"
#include "json.h"

class ApiHolder;
class BasicData;
class WgtLoader;
class UartHolder;

class WgtSim : public QWidget
{
	Q_OBJECT

public:
	WgtSim(ApiHolder * api, BasicData * data, WgtLoader * loader, QWidget *parent = Q_NULLPTR);
	void setUartHolder(UartHolder * uart);

	/**
	*	Setter to set simulation basic data.
	*	@param ...
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

signals:
	void finished();
};
