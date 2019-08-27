#pragma once

#include <QWidget>
#include "ui_WgtMain.h"

class WgtMain : public QWidget
{
	Q_OBJECT

public:
	WgtMain(QWidget *parent = Q_NULLPTR);
	~WgtMain();

private:
	Ui::WgtMain ui;

signals:
	void logout();
	void exportSims();
	void importLogs();
	void newSim();
};
