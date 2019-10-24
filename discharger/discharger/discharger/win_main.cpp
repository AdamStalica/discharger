#include "win_main.h"

#include <QDebug>
#include <QtWebSockets/QtWebSockets>
#include <nlohmann/json.hpp>
#include <sstream>

#include <QMessageBox>

//#define TESTING

#ifdef TESTING
/*************** Testing Class *********************/

#include "TestingClass.h"

/***************************************************/
#endif // TESTING


using json = nlohmann::json;

win_main::win_main(QWidget *parent)
	:	QMainWindow(parent)
{
	ui.setupUi(this);


	loader = new WgtLoader();
	api = new ApiHolder(this);
	data = new BasicData(api, loader, this);

	login = new WgtLogin(api, loader);
	main = new WgtMain();
	imp = new WgtImport(api, data, loader);
	simConfig = new WgtSimConfig(api, data, loader);
	sim = new WgtSim(api, data, loader);

	winHelp = new WinHelp(HELP_FILE);

	uart = new UartHolder(this);

	clearAble = {
		static_cast<ClearAble *>(api),
		static_cast<ClearAble *>(data),
		static_cast<ClearAble *>(login),
		static_cast<ClearAble *>(imp),
		static_cast<ClearAble *>(simConfig),
		static_cast<ClearAble *>(sim),
		static_cast<ClearAble *>(uart)
	};

	simConfig->setUartHolder(uart);
	sim->setUartHolder(uart);

	#ifdef TESTING
	/*************** Testing Class *********************/
	
	TestingClass * testingClass = new TestingClass(this);
	
	/***************************************************/
	#endif // TESTING

	setWgtsConnections();
	setWinConnections();
	setFrontEnd();
	loadCSS();

	ui.mainArea->setWidget(login);
}

win_main::~win_main() {
	delete api;
	delete data;
	delete uart;
	delete imp;
	delete login;
	delete main;
}

void win_main::setFrontEnd()
{
	statusBar()->hide();
	ui.mainToolBar->hide();
}

void win_main::setWgtsConnections()
{
	connect(loader, &WgtLoader::showLoader, this, [this] {
		lastWgt = ui.mainArea->takeWidget();
		ui.mainArea->setWidget(loader);
	});
	connect(loader, &WgtLoader::showLastWgt, this, [this] {
		ui.mainArea->takeWidget();
		ui.mainArea->setWidget(lastWgt);
	});

	connect(login, &WgtLogin::loggedIn, this, [this] {
		data->fetchData();
	});

	connect(data, &BasicData::error, this, [this] {
		QMessageBox::critical(this, "Error", data->getLastError());
	});
	connect(data, &BasicData::fetched, this, [this] {
		ui.mainArea->takeWidget();
		ui.mainArea->setWidget(main);
	});

	// logout clear all widgets & data;
	connect(main, &WgtMain::logout, this, [this] {
		ui.mainArea->takeWidget();
		for (auto & c : clearAble) {
			c->clear();
		}
		ui.mainArea->setWidget(login);
	});
	connect(main, &WgtMain::importLogs, this, [this] {
		ui.mainArea->takeWidget();
		ui.mainArea->setWidget(imp);
	});
	connect(main, &WgtMain::exportSims, this, [this] {
		//ui.mainArea->takeWidget();
		//ui.mainArea->setWidget(imp);
	});
	connect(main, &WgtMain::newSim, this, [this] {
		ui.mainArea->takeWidget();
		ui.mainArea->setWidget(simConfig);
		//json fakeData = json::parse("{\"id_batt_left\":58,\"id_batt_right\":57,\"id_log_info\":4,\"id_sim_info\":15, \"name\":\"First test sim in program\"}");
		//sim->setBasicSimData(fakeData);
		//ui.mainArea->setWidget(sim);
		//sim->prepareSimulation();
	});

	// import widget closed clear all fields
	connect(imp, &WgtImport::finished, this, [this] {
		ui.mainArea->takeWidget();
		ui.mainArea->setWidget(main);
		imp->clear();
	});

	// simConfig widget closed clear all fields
	connect(simConfig, &WgtSimConfig::finished, this, [this] {
		ui.mainArea->takeWidget();
		ui.mainArea->setWidget(main);
		simConfig->clear();
	});
	// simConfig widget closed clear all fields
	connect(simConfig, &WgtSimConfig::preparedNewSimCanStart, this, [this](const json & data) {
		ui.mainArea->takeWidget();
		sim->setBasicSimData(data);
		ui.mainArea->setWidget(sim);
		sim->prepareSimulation();
		simConfig->clear();
	});

	// sim widget closed clear all fields
	connect(sim, &WgtSim::finished, this, [this]() {
		ui.mainArea->takeWidget();
		ui.mainArea->setWidget(main);
		sim->clear();
	});
}

void win_main::setWinConnections()
{
	connect(ui.actionHelp, &QAction::triggered, this, [this](bool checked) {

		if (winHelp->showHelpFor(ui.mainArea->widget()->objectName()))
			winHelp->show();
	});

	connect(ui.actionReload_CSS, &QAction::triggered, this, [this](bool checked) {

		this->setStyleSheet("");
		loadCSS();
	});
}

void win_main::loadCSS()
{
	QFile css(CSS_FILE);

	if (css.open(QIODevice::ReadOnly | QIODevice::Text)) {
		this->setStyleSheet(
			QString(css.readAll())
		);
	}
}


void win_main::closeEvent(QCloseEvent *event)
{
	winHelp->close();
	//event->ignore();
	//event->accept();
}