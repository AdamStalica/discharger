#pragma once

#include <QWidget>
#include "ui_ParamsWgt.h"

class ParamsWgt : public QWidget
{
	Q_OBJECT

public:
	ParamsWgt(QWidget *parent = Q_NULLPTR);
	~ParamsWgt();

private:
	Ui::ParamsWgt ui;
};
