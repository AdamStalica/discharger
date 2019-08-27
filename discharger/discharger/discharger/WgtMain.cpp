#include "WgtMain.h"

WgtMain::WgtMain(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	connect(ui.logout_btn, &QPushButton::clicked, this, [this] {
		emit logout();
	});
	connect(ui.new_sim_btn, &QPushButton::clicked, this, [this] {
		emit newSim();
	});
	connect(ui.imp_btn, &QPushButton::clicked, this, [this] {
		emit importLogs();
	});
	connect(ui.exp_btn, &QPushButton::clicked, this, [this] {
		emit exportSims();
	});
}

WgtMain::~WgtMain()
{
}
