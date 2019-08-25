#pragma once

#include <QWidget>
#include "ui_WgtNewRace.h"

class ApiHolder;
class QTimer;

class WgtNewRace : public QWidget
{
	Q_OBJECT

public:
	WgtNewRace(ApiHolder * api, QWidget *parent = Q_NULLPTR);
	~WgtNewRace();
	void setSpeedway(int id_speedway, const QString & name) {
		this->id_speedway = id_speedway;
		ui.sp_name->setText(name);
	}

private:
	Ui::WgtNewRace ui;
	ApiHolder * api;
	QTimer * timer;

	int id_speedway;

private slots:
	void addNewRace();

signals:
	void addedNewRace(int id_race, int id_speedway, const QString & name, const QString & date);
	void canceledNewRace();
};
