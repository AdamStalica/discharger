#pragma once

#include <QWidget>
#include "ui_WgtSimConfig.h"
#include <nlohmann/json.h>
#include "ClearAble.h"


constexpr auto SIM_IN_PROGRESS = 0;

class UartHolder;

class ApiHolder;
class BasicData;
class WgtLoader;
class QStandardItem;
class QStandardItemModel;

class WgtSimConfig : public QWidget, public ClearAble
{
	Q_OBJECT

public:
	WgtSimConfig(ApiHolder * api, BasicData * data, WgtLoader * loader, QWidget *parent = Q_NULLPTR);
	void setUartHolder(UartHolder * uart);
	~WgtSimConfig();

	void clear() override;

private:
	Ui::WgtSimConfig ui;
	ApiHolder * api;
	BasicData * data;
	WgtLoader * loader;
	UartHolder * uart;

	QTimer * t;

	std::vector<QStandardItem *> log_info_items;
	QStandardItemModel * model;

	QString noValueCSS = "border: 10px red solid; background-color: red;";

	void init();
	int getCheckedLogsInfoId();
	void createTree();
	void loadBetteriesList();

private slots:
	void raceCheckedChanged(QStandardItem *);
	void openAndTestCom();
	void handshakeHolder(int ms);
	void expandCollapseTree();
	void loadComs();
	void prepareSimulation();

signals:
	void finished();
	/**
	*	@param json: {
	*		id_sim_info: int,
	*		id_log_info: int,
	*		id_batt_left: int,
	*		id_batt_right: int,
	*		name: std::string
	*	}
	*/
	void preparedNewSimCanStart(const nlohmann::json & data);
};
