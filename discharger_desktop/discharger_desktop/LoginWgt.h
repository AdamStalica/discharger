#pragma once

#include <QWidget>
#include "ui_LoginWgt.h"
#include "IClearable.h"

class LoginWgt : public QWidget, IClearable
{
	Q_OBJECT

public:
	LoginWgt(QWidget *parent = Q_NULLPTR);
	~LoginWgt() {};

public slots:
	void clear() override;
	void logOut();

signals:
	void authorizing(const QString & msg);
	void loggedIn();
	void loggedOut();

private:
	Ui::LoginWgt ui;

private slots:
	void login();
	void userLoggedInCallback(bool success, const QString & msg);
};
