#pragma once

#include <QWidget>
#include "ui_WgtSimConfig.h"

class UartHolder;

class ApiHolder;
class BasicData;
class WgtLoader;
class QStandardItem;
class QStandardItemModel;

class WgtSimConfig : public QWidget
{
	Q_OBJECT

public:
	WgtSimConfig(ApiHolder * api, BasicData * data, WgtLoader * loader, QWidget *parent = Q_NULLPTR);
	~WgtSimConfig();

private:
	Ui::WgtSimConfig ui;
	ApiHolder * api;
	BasicData * data;
	WgtLoader * loader;
	UartHolder * uart;

	QTimer * t;

	std::vector<QStandardItem *> log_info_items;
	QStandardItemModel * model;

	void init();
	int getCheckedLogsInfoId();

private slots:
	void raceCheckedChanged(QStandardItem *);
	void openAndTestCom();

signals:
	void finished();
};
