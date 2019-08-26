#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_win_main.h"

#include "WgtNewSpeedway.h"
#include "WgtImport.h"
#include "WgtLogin.h"

#include "ApiHolder.h"
#include "BasicData.h"

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
	
	WgtImport * imp;
	WgtLogin * login;
};
