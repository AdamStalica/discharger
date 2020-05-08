#include "MenuWgt.h"
#include "ObjectFactory.h"
#include "User.h"

MenuWgt::MenuWgt(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	connect(ui.btnNewTest, &QPushButton::clicked, [this] {
		emit newTest();
	});
	connect(ui.btnChtic, &QPushButton::clicked, [this] {
		emit deviceChtic();
	});
}

void MenuWgt::clear() {
	ui.lblName->clear();
}

void MenuWgt::setup() {
	auto userName = ObjectFactory::getInstance<User>()->getName();
	ui.lblName->setText(userName);
}