#pragma once

#include "ObjectFactory.h"
#include <QObject>
#include <QDebug>
#include <functional>

class QNetworkAccessManager;
class QNetworkReply;

class WebApi : public QObject
{
	Q_OBJECT

public:
	WebApi(QObject *parent);
	~WebApi();

	void POST(
		const std::string & fileName, 
		const std::string & post, 
		std::function<void(bool, std::string &&)> callback
	);

private:
	const std::string API_URL{ "http://api.sgp.slavek.webd.pro" };
	
	QNetworkAccessManager * mgr;
	std::function<void(bool, std::string &&)> apiCallback{ 
		[](bool sucess, std::string && str) {
			qDebug() << "Api default callback\n"
				<< "Requested " << (sucess ? "successfully" : "unsuccessfully") << "."
				<< (str.compare("") ? "" : ("\nResponse:\n" + str).c_str());
		} 
	};

	void processNetworkReply(QNetworkReply * repl);
};
