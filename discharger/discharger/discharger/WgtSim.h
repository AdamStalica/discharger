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
	void setBasicSimData(const nlohmann::json & data);
	~WgtSim();

private:
	Ui::WgtSim ui;
	ApiHolder * api;
	BasicData * data;
	WgtLoader * loader;
	UartHolder * uart;
};
