#pragma once

#include "ObjectFactory.h"
#include "nlohmann/json.h"
#include <QObject>
#include <QDebug>
#include <functional>
#include <map>

auto constexpr API_DEBUG = true;
auto constexpr API_DEBUG_STR = API_DEBUG ? "?XDEBUG_SESSION_START=1" : "";

class QNetworkAccessManager;
class QNetworkReply;
class User;

class WebApi : public QObject
{
	Q_OBJECT

public:
	enum StatsEnum {
		API_OK, API_WARNING, API_ERROR
	};

	friend class User;

	WebApi(QObject *parent);
	~WebApi();

	void POST(
		const std::string & fileName,
		nlohmann::json & post,
		std::function<void(WebApi::StatsEnum, nlohmann::json &&)> callback
	);
	void GET(
		const std::string & fileName,
		std::function<void(WebApi::StatsEnum, nlohmann::json &&)> callback
	);

signals:
	void apiKeyExpired();

private:
	const std::string API_URL			{ "http://192.168.1.41/api" }; // { "http://api.sgp.slavek.webd.pro" };
	const std::string STATUS_NAME		{ "status" };
	const std::string API_KEY_INVALID	{ "invalid" };
	const std::string API_KEY_NAME		{ "api_key" };
	std::string apiKey					{ API_KEY_INVALID };

	const std::map<std::string, StatsEnum> STATS_MAP = {
		{ "OK", API_OK },
		{ "WARNING", API_WARNING },
		{ "ERROR", API_ERROR }
	};

	QNetworkAccessManager * mgr;
	std::function<void(StatsEnum, nlohmann::json &&)> apiCallback;

	void POST(const std::string & fileName,	const std::string & post);
	void invalidateApiKey();

private slots:
	void processNetworkReply(QNetworkReply * repl);
};
