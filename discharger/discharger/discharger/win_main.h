#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_win_main.h"

#include "WgtNewSpeedway.h"
#include "WgtImport.h"
#include "WgtLogin.h"
#include "WgtMain.h"
#include "WgtLoader.h"
#include "WgtSimConfig.h"
#include "WgtSim.h"

#include "ApiHolder.h"
#include "BasicData.h"
#include "UartHolder.h"

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

	QWidget * lastWgt;
};
