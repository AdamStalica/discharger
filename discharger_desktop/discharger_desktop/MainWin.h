#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWin.h"

class MainWin : public QMainWindow
{
	Q_OBJECT

public:
	MainWin(QWidget *parent = Q_NULLPTR);

private:
	Ui::MainWinClass ui;

	enum PagesEnum {
		PAGE_LOG_IN,
		PAGE_CONF_TEST,
		PAGE_TEST
	};

	void setDockedWidgetsVisibility(bool visible);
	void setTestToolBarVisibility(bool visible);
};
