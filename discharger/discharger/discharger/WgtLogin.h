#pragma once

#include <QWidget>
#include "ui_WgtLogin.h"

class ApiHolder;
class WgtLoader;

class WgtLogin : public QWidget
{
	Q_OBJECT

public:
	WgtLogin(ApiHolder * api, WgtLoader * loader, QWidget *parent = Q_NULLPTR);
	~WgtLogin();

private:
	Ui::WgtLogin ui;
	ApiHolder * api;
	WgtLoader * loader;

private slots:
	void loginBtn();

signals:
	void loggedIn();
};
