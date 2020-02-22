#include "WebApi.h"
#include "nlohmann/json.h"
#include "User.h"

#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>

WebApi::WebApi(QObject *parent)
	: QObject(parent) {
	mgr = new QNetworkAccessManager(this);
	connect(mgr, &QNetworkAccessManager::finished, this, &WebApi::processNetworkReply);
}

WebApi::~WebApi() {
	delete mgr;
}

void WebApi::POST(
	const std::string & fileName, 
	const std::string & post, 
	std::function<void(bool, std::string &&)> callback) 
{
	apiCallback = callback;
	QUrl url((API_URL + "/" + fileName).c_str());

	QNetworkRequest req(url);
	req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

	mgr->post(req, post.c_str());
}

void WebApi::POST(const std::string & fileName, nlohmann::json & post, std::function<void(bool, std::string&&)> callback) {
	auto user = ObjectFactory::getInstance<User>();
	if(user)
		post["usr_id"] = ObjectFactory::getInstance<User>()->getId();
	POST(fileName, post.dump(), callback);
}

void WebApi::GET(const std::string & fileName, std::function<void(bool, std::string&&)> callback) {
	nlohmann::json post{
		{"id_usr", ObjectFactory::getInstance<User>()->getId()}
	};
	POST(fileName, post.dump(), callback);
}

void WebApi::processNetworkReply(QNetworkReply * repl) {
	int errNo = repl->error();
	if (errNo != QNetworkReply::NoError) {
		nlohmann::json resp{
			{"status", "ERROR"},
			{"no", errNo},
			{"comment", ("Http error code: " + std::to_string(errNo) + " " + typeid(repl->error()).name())}
		};
		apiCallback(false, std::move(resp.dump()));
	}
	else {
		QByteArray response = repl->readAll();
		QString out = QString(response);
		apiCallback(
			!out.contains("\"status\":\"ERROR\""),
			std::move(out.toStdString())
		);
	}
}
