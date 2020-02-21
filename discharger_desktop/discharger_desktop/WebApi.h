#pragma once

#include "ObjectFactory.h"
#include <QObject>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkAccessManager>

#include <functional>

class WebApi : public QObject
{
	Q_OBJECT

public:

	WebApi(QObject *parent);
	
	~WebApi();

private:
	static const std::string API_URL;

	std::string hi;

	QNetworkAccessManager mgr;
	static std::function<void(bool, std::string &&)> apiCallback;


	template<class Functor>
	static void post(const std::string & url, const std::string & post, Functor & callback);


	//static WebApi instance;
};

template<class Functor>
inline void WebApi::post(const std::string & url, const std::string & post, Functor & callback)
{
	apiCallback = callback;

}
