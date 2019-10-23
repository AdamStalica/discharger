#pragma once

#include <QWidget>
#include "ui_WgtLogin.h"
#include "ClearAble.h"


class ApiHolder;
class WgtLoader;

class WgtLogin : public QWidget, public ClearAble
{
	Q_OBJECT

public:
	WgtLogin(ApiHolder * api, WgtLoader * loader, QWidget *parent = Q_NULLPTR);
	~WgtLogin();

	void clear() override;

private:
	Ui::WgtLogin ui;
	ApiHolder * api;
	WgtLoader * loader;

private slots:
	void loginBtn();

signals:
	void loggedIn();
};
