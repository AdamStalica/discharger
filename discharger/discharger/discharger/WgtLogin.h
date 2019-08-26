#pragma once

#include <QWidget>
#include "ui_WgtLogin.h"

class ApiHolder;

class WgtLogin : public QWidget
{
	Q_OBJECT

public:
	WgtLogin(ApiHolder * api, QWidget *parent = Q_NULLPTR);
	~WgtLogin();

private:
	Ui::WgtLogin ui;
	ApiHolder * api;

private slots:
	void loginBtn();

signals:
	void loggedIn();
};
