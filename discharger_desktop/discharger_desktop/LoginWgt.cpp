#include "LoginWgt.h"
#include "ObjectFactory.h"
#include "User.h"
#include <QMessageBox>

LoginWgt::LoginWgt(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	connect(ui.btnLogin, &QPushButton::clicked, this, &LoginWgt::login);
}

void LoginWgt::clear() {
	ui.edtMail->clear();
	ui.edtMail->clear();
}

void LoginWgt::logOut() {
	clear();
	auto user = ObjectFactory::getInstance<User>();
	user->logOut();
	emit loggedOut();
}

void LoginWgt::login() {
	QString email = ui.edtMail->text();
	QString pass = ui.edtPass->text();

	if (email.isEmpty() || pass.isEmpty()) {
		QMessageBox::warning(this, tr("Warning"), tr("Both email and password fields must be filled up!"));
		return;
	}

	auto user = ObjectFactory::getInstance<User>();
	user->setOnLoggedInCallback([this](bool success, const QString & msg) {
		this->userLoggedInCallback(success, msg);
	});
	user->logIn(email, pass);
	emit authorizing(tr("Authorizing..."));
}

void LoginWgt::userLoggedInCallback(bool success, const QString & msg) {
	if (success) {
		emit loggedIn();
	}
	else {
		QMessageBox::critical(this, tr("Error"), msg);
		emit loggedOut();
	}
}