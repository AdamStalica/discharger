#pragma once

#include <QWidget>
#include "ui_MenuWgt.h"
#include "IClearable.h"
#include "ISetupable.h"

class MenuWgt : public QWidget, IClearable, ISetupable
{
	Q_OBJECT

public:
	MenuWgt(QWidget *parent = Q_NULLPTR);
	~MenuWgt() {};

public slots:
	void clear() override;
	void setup() override;
	
signals:
	void newTest();
	void deviceChtic();

private:
	Ui::MenuWgt ui;
};
