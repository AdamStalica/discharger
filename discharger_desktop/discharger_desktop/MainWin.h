#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWin.h"
#include "WebApi.h"

#include <functional>

class MainWin : public QMainWindow
{
	Q_OBJECT

public:
	MainWin(QWidget *parent = Q_NULLPTR);
	~MainWin() {
		ObjectFactory::deleteFactory();
	}

private:
	Ui::MainWinClass ui;

	enum PagesEnum {
		PAGE_LOG_IN,
		PAGE_CONF_TEST,
		PAGE_TEST
	};

	void setDockedWidgetsVisibility(bool visible);
	void setTestToolBarVisibility(bool visible);

	void logout();

	void setupMainToolBar();
	void setupTestToolBar();

	void testStart();
	void testStop();
};
