#include "win_main.h"

#include <QDebug>
#include <QtWebSockets/QtWebSockets>
#include <nlohmann/json.hpp>
#include <sstream>

#include <QMessageBox>

using json = nlohmann::json;

win_main::win_main(QWidget *parent)
	:	QMainWindow(parent)
{
	ui.setupUi(this);

	this->setStyleSheet("QLineEdit#");

	api = new ApiHolder(this);






	imp = new WgtImport(api);


	connect(imp, &WgtImport::created, this, [this] {
		qDebug() << "ok";
		ui.layout->addWidget(imp);
	});

	connect(imp, &WgtImport::finished, this, [this] {
		delete imp;
	});





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