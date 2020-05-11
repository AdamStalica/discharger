#pragma once

#include <QWidget>
#include "ui_ChartWgt.h"

class ChartWgt : public QWidget
{
	Q_OBJECT

public:
	ChartWgt(QWidget *parent = Q_NULLPTR);
	~ChartWgt();

private:
	Ui::ChartWgt ui;
};
