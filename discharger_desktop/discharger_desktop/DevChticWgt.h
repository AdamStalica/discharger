#pragma once

#include <QWidget>
#include "ui_DevChticWgt.h"

class DevChticWgt : public QWidget
{
	Q_OBJECT

public:
	DevChticWgt(QWidget *parent = Q_NULLPTR);
	~DevChticWgt();

private:
	Ui::DevChticWgt ui;
};
