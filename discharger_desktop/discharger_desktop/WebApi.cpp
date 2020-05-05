#include "WebApi.h"
#include "nlohmann/json.h"

#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>

WebApi::WebApi(QObject *parent)
	: QObject(parent) {
	mgr = new QNetworkAccessManager(this);
	connect(mgr, &QNetworkAccessManager::finished, this, &WebApi::processNetworkReply);

	apiCallback = [](bool sucess, std::string && str) {
		qDebug() << "Api default callback\n"
			<< "Requested " << (sucess ? "successfully" : "unsuccessfully") << "."
			<< (str.compare("") ? "" : ("\nResponse:\n" + str).c_str());
	};
}

WebApi::~WebApi() {
	delete mgr;
}

void WebApi::POST(
	const std::string & fileName, 
	nlohmann::json & post, 
	std::function<void(WebApi::StatsEnum, nlohmann::json &&)> callback) 
{
	if (apiKey != API_KEY_INVALID)
		post[API_KEY_NAME] = apiKey;
	apiCallback = callback;
	POST(fileName, post.dump());
}

void WebApi::GET(
	const std::string & fileName, 
	std::function<void(WebApi::StatsEnum, nlohmann::json &&)> callback) 
{
	nlohmann::json post = nlohmann::json::object();
	POST(fileName, post, callback);
}

void WebApi::POST(const std::string & fileName, const std::string & post) {
	QUrl url((API_URL + "/" + fileName + API_DEBUG_STR).c_str());
	QNetworkRequest req(url);
	req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	mgr->post(req, post.c_str());
}

void WebApi::invalidateApiKey() {
	apiKey = API_KEY_INVALID;
}

void WebApi::processNetworkReply(QNetworkReply * repl) {
	int errNo = repl->error();
	if (errNo != QNetworkReply::NoError) {
		nlohmann::json resp{
			{"status", "ERROR"},
			{"no", errNo},
			{"comment", ("Http error code: " + std::to_string(errNo))}
		};
		apiCallback(StatsEnum::API_ERROR, std::move(resp));
		return;
	}
	nlohmann::json resp;
	try {
		QByteArray response = repl->readAll();
		resp = nlohmann::json::parse(response.toStdString());		
		apiKey = resp.at(API_KEY_NAME).get<std::string>();
	}
	catch (const std::exception & ex) {
		qDebug() << ex.what();
		return;
	}

	if (apiKey == API_KEY_INVALID)
		emit apiKeyExpired();
	else {
		apiCallback(
			STATS_MAP.at(resp.at(STATUS_NAME).get<std::string>()),
			std::move(resp)
		);
	}
}
