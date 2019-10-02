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

	centralWidget()->layout()->setContentsMargins(0, 0, 0, 0);
	statusBar()->hide();
	ui.mainToolBar->hide();

	this->setStyleSheet("QLineEdit#");

	loader = new WgtLoader();
	connect(loader, &WgtLoader::showLoader, this, [this] {
		lastWgt = ui.mainArea->takeWidget();
		ui.mainArea->setWidget(loader);
	});
	connect(loader, &WgtLoader::showLastWgt, this, [this] {
		ui.mainArea->takeWidget();
		ui.mainArea->setWidget(lastWgt);
	});


	api = new ApiHolder(this);
	data = new BasicData(api, loader, this);

	login = new WgtLogin(api, loader);
	main = new WgtMain();
	imp = new WgtImport(api, data, loader);
	simConfig = new WgtSimConfig(api, data, loader);
	sim = new WgtSim(api, data, loader);

	uart = new UartHolder(this);
	uart->open("COM3");
	simConfig->setUartHolder(uart);
	sim->setUartHolder(uart);


	ui.mainArea->setWidget(login);

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

	connect(main, &WgtMain::logout, this, [this] {
		ui.mainArea->takeWidget();
		api->logout();
		data->clear();
		ui.mainArea->setWidget(login);
	});
	connect(main, &WgtMain::importLogs, this, [this] {
		ui.mainArea->takeWidget();
		ui.mainArea->setWidget(imp);
	});
	connect(main, &WgtMain::exportSims, this, [this] {
		ui.mainArea->takeWidget();
		ui.mainArea->setWidget(imp);
	});
	connect(main, &WgtMain::newSim, this, [this] {
		ui.mainArea->takeWidget();
		//ui.mainArea->setWidget(simConfig);
		json fakeData = json::parse("{\"id_batt_left\":58,\"id_batt_right\":57,\"id_log_info\":4,\"id_sim_info\":15, \"name\":\"First test sim in program\"}");
		sim->setBasicSimData(fakeData);
		ui.mainArea->setWidget(sim);
		sim->prepareSimulation();
	});

	connect(imp, &WgtImport::finished, this, [this] {
		ui.mainArea->takeWidget();
		ui.mainArea->setWidget(main);
	});
	connect(simConfig, &WgtSimConfig::finished, this, [this] {
		ui.mainArea->takeWidget();
		ui.mainArea->setWidget(main);
	});
	connect(simConfig, &WgtSimConfig::preparedNewSimCanStart, this, [this](const json & data) {
		ui.mainArea->takeWidget();
		sim->setBasicSimData(data);
		ui.mainArea->setWidget(sim);
	});
	connect(sim, &WgtSim::finished, this, [this]() {
		ui.mainArea->takeWidget();
		ui.mainArea->setWidget(main);
	});

	#ifdef TESTING
	/*************** Testing Class *********************/
	
	TestingClass * testingClass = new TestingClass(this);
	
	/***************************************************/
	#endif // TESTING




	/*

	connect(imp, &WgtImport::created, this, [this] {
		qDebug() << "ok";
		ui.layout->addWidget(imp);
	});

	connect(imp, &WgtImport::finished, this, [this] {
		delete imp;
	});

	*/



	/*

	auto sp = new WgtNewSpeedway(api, this);


	connect(sp, &WgtNewSpeedway::addedNewSpeedway, this, [this](int no, const QString & name) {
		QMessageBox::information(this, "", "No" + QString::number(no) + ", " + name);
	});

	connect(sp, &WgtNewSpeedway::canceledNewSpeedway, this, [this] {
		QMessageBox::information(this, "", "Canceled.");
	});
	*/
}

win_main::~win_main() {
	delete api;
	delete data;
	delete uart;
	delete imp;
	delete login;
	delete main;
}

/*



	ws = new QWebSocket;
	ws->open(QUrl("ws://connect.websocket.in/dk_devices_2019?room_id=12345"));

	connect(ws, &QWebSocket::connected, this, [] {
		qDebug() << "opened";
	});

	connect(ws, &QWebSocket::disconnected, this, [] {
		qDebug() << "closed";
	});

	connect(ws, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error), this, [](QAbstractSocket::SocketError error) {

		qDebug() << "error: " << error;
	});

	connect(ws, &QWebSocket::textMessageReceived, this, [&](const QString & msg) {
		qDebug() << msg;
		ws->sendTextMessage(msg);
		auto j3 = nlohmann::json::parse(msg.toStdString());

		std::ostringstream os;
		os << j3;
		qDebug() << os.str().c_str();

		qDebug() << j3.dump().c_str();

		for (auto & element : j3) {
			std::ostringstream os1;
			os1 << element << '\n';
			qDebug() << os1.str().c_str();
		}

		for (auto & el : j3.items()) {
			std::ostringstream os1;
			os1 << el.key() << " : " << el.value() << "\n";
			qDebug() << os1.str().c_str();
		}

		std::string ok = j3["from"];

		qDebug() << ok.c_str();



	});



*/