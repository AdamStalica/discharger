#pragma once

#include <QWidget>
#include "ui_WgtNewSpeedway.h"
#include <nlohmann/json.h>

class ApiHolder;
class QTimer;

class WgtNewSpeedway : public QWidget
{
	Q_OBJECT

public:
	WgtNewSpeedway(ApiHolder * api, QWidget *parent = Q_NULLPTR);
	~WgtNewSpeedway();

private:
	Ui::WgtNewSpeedway ui;
	ApiHolder * api;
	QTimer * timer;

	std::vector<QLineEdit *> sp_lns;

private slots:
	void addNewSpeedway();

signals:
	void addedNewSpeedway(const nlohmann::json & newSp);
	void canceledNewSpeedway();
};
