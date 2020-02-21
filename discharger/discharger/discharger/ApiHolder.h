#pragma once

#include <QObject>
#include <QNetworkReply>
#include <functional>

#include "ClearAble.h"


class QNetworkAccessManager;

constexpr auto QTIME_FORMAT = "HH:mm:ss.zzz";
constexpr auto QDATE_FORMAT = "yyyy-MM-dd";
constexpr auto QDATE_TIME_FORMAT = "yyyy-MM-dd HH:mm:ss.zzz";

class ApiHolder : public QObject, public ClearAble
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

	void clear() override;


	static std::function<void(bool, std::string &&)> apiCallback;
	template<class Functor>
	static void post(const std::string & url, const std::string & post, Functor & callback) {

	}
	
	static void tmpCallback(bool success, std::string && data) {
		success = 1;
	}

signals:
	void gotResponse(const QString & resp);
	void loginResult(bool);

private:

	QString api_url = "http://api.sgp.slavek.webd.pro/";
	QString lastError;

	QNetworkAccessManager * mgr;

	void post_request(const std::string & param, const QString & file);

	QMetaObject::Connection login_conn;

	/*============================ API USER ==============================*/
	QString name, surname, email;
	int id_usr = -1;

};
