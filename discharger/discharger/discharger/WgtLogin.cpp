#include "WgtLogin.h"
#include "ApiHolder.h"
#include "json.h"

#include <QRegExpValidator>
#include <QMessageBox>

using json = nlohmann::json;

WgtLogin::WgtLogin(ApiHolder * api, QWidget *parent)
	:	QWidget(parent),
		api(api)
{
	ui.setupUi(this);

	ui.email->setText("dominikkala@gmail.com");
	ui.pass->setText("test1234");

	ui.email->setValidator(new QRegExpValidator(QRegExp("[a-z0-9._%+-]+@[a-z0-9.-]+\\.[a-z]{2,4}"), this));
	ui.pass->setValidator(new QRegExpValidator(QRegExp("[^\\s]{8,}"), this));
	
	connect(ui.login_btn, SIGNAL(clicked()), this, SLOT(loginBtn()));
}

WgtLogin::~WgtLogin()
{
}

void WgtLogin::loginBtn() {

	QString email = ui.email->text();
	QString pass = ui.pass->text();

	if (email.length() == 0 || pass.length() < 8) {

		QMessageBox::warning(this, "Notice", "Email is can not be empty and password must have length more than 8 characters.");
		return;
	}

	api->apiLogin(email, pass);

	connect(api, &ApiHolder::loginResult, this, [this](bool result) {
		
		api->disconnect();

		if (result) {

			emit loggedIn();
		}
		else {
			QMessageBox::critical(this, "Error", api->getLastError());
		}

	});

}