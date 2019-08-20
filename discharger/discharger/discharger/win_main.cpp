#include "win_main.h"

#include <QDebug>
#include <QtWebSockets/QtWebSockets>
#include <nlohmann/json.hpp>
#include <sstream>

using json = nlohmann::json;

win_main::win_main(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

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

		std::ostringstream os2;
		os2 << j3["from"];
		qDebug() << os2.str().c_str();



	});	
}

win_main::~win_main() {
	delete ws;
}