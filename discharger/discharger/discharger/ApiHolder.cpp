#include "ApiHolder.h"

#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkAccessManager>

#include <QDebug>
#include <QTextStream>

ApiHolder::ApiHolder(QObject *parent)
	: QObject(parent)
{
	this->mgr = new QNetworkAccessManager(this);
	
	connect(mgr, &QNetworkAccessManager::finished, this, [this](QNetworkReply * resp) {
		QString out;
		if (resp->error() != QNetworkReply::NoError) {
			QTextStream ts(&out);
			ts << "{\"status\":\"ERROR\",\"no\":";
			ts << resp->error();
			ts << ",\"comment\":\"...\"}";
		}
		else {

			QByteArray response = resp->readAll();
			out = QString(response);
		}
		emit gotResponse(out);
	});
}

ApiHolder::~ApiHolder()
{
	delete this->mgr;
}

void ApiHolder::apiInsert(const QString & param) {
	post_request(param.toStdString(), "insert.php");
}

void ApiHolder::apiInsert(const std::string & param) {
	post_request(param, "insert.php");
}

void ApiHolder::apiSelect(const QString & param) {
	post_request(param.toStdString(), "select.php");
}

void ApiHolder::apiSelect(const std::string & param) {
	post_request(param, "select.php");
}

void ApiHolder::post_request(const std::string & param, const QString & file) {

	QUrl url(this->api_url + file);

	QNetworkRequest req(url);
	req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

	mgr->post(req, param.c_str());
}
