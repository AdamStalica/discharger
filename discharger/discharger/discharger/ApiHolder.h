#pragma once

#include <QObject>
#include <QNetworkReply>

class QNetworkAccessManager;

class ApiHolder : public QObject
{
	Q_OBJECT

public:
	ApiHolder(QObject *parent);
	~ApiHolder();

	void apiInsert(const QString & param);
	void apiInsert(const std::string & param);
	void apiSelect(const QString & param);
	void apiSelect(const std::string & param);
	void apiUpdate(const QString & param);
	void apiUpdate(const std::string & param);
	int getApiUserId() { return 1; }


signals:
	void gotResponse(const QString & resp);

private:

	QString api_url = "http://api.sgp.dominikkala.pl/";

	QNetworkAccessManager * mgr;

	void post_request(const std::string & param, const QString & file);
};
