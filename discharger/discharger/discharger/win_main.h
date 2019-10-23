#pragma once

#include <QtWidgets/QMainWindow>
#include <QCloseEvent>
#include "ui_win_main.h"

#include "WgtNewSpeedway.h"
#include "WgtImport.h"
#include "WgtLogin.h"
#include "WgtMain.h"
#include "WgtLoader.h"
#include "WgtSimConfig.h"
#include "WgtSim.h"

#include "WinHelp.h"

#include "ApiHolder.h"
#include "BasicData.h"
#include "UartHolder.h"

constexpr auto CSS_FILE = "media/style.css";
constexpr auto HELP_FILE = "help/help.json";

class QWebSocket;

class win_main : public QMainWindow
{
	Q_OBJECT

public:
	win_main(QWidget *parent = Q_NULLPTR);
	~win_main();

private:
	Ui::win_mainClass ui;

	ApiHolder * api;
	BasicData * data;
	UartHolder * uart;

	WgtImport * imp;
	WgtLogin * login;
	WgtMain * main;
	WgtLoader * loader;
	WgtSimConfig * simConfig;
	WgtSim * sim;

	WinHelp * winHelp;

	std::vector<ClearAble *> clearAble;

	QWidget * lastWgt;


	void setFrontEnd();
	void setWgtsConnections();
	void setWinConnections();
	void loadCSS();
	void closeEvent(QCloseEvent *) override;
};
