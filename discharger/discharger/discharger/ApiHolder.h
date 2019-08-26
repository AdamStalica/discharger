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

	void apiLogin(const QString & email, const QString & pass);
	QString getLastError() { return lastError; }

	int getApiUserId() { return id_usr; }
	QString getApiUserName() { return name; }
	QString getApiUserSurname() { return surname; }
	QString getApiUserEmail() { return email; }


signals:
	void gotResponse(const QString & resp);
	void loginResult(bool);

private:

	QString api_url = "http://api.sgp.dominikkala.pl/";
	QString lastError;

	QNetworkAccessManager * mgr;

	void post_request(const std::string & param, const QString & file);

	QMetaObject::Connection login_conn;

	/*============================ API USER ==============================*/
	QString name, surname, email;
	int id_usr;

};
