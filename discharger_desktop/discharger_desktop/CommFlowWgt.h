#pragma once

#include <QWidget>
#include "ui_CommFlowWgt.h"

class CommFlowWgt : public QWidget
{
	Q_OBJECT

public:
	CommFlowWgt(QWidget *parent = Q_NULLPTR);
	~CommFlowWgt();

private:
	Ui::CommFlowWgt ui;
};
