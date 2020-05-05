#pragma once
#include <QObject>
#include <functional>
#include "WebApi.h"

class User : public QObject
{
	Q_OBJECT

private:
	const std::string API_FILE{ "auth/login_new.php" };

	QString name, surname, email, password;
	unsigned int id		{ 0 };
	bool userLoggedIn	{ false };

	std::function<void(bool, QString)> loggedInCallback{
		[](bool success, const QString & response) {}
	};

	void handleApiCallback(WebApi::StatsEnum status, nlohmann::json && response);

	QString getPassword() { return password; }

public:
	User(QObject *parent);
	~User() {};

	void logIn(const QString & mail, const QString & password);
	void logOut();

	void setOnLoggedInCallback(std::function<void(bool, const QString &)> callback);

	QString getName()	{ return name; }
	QString getSurname(){ return surname; }
	QString getEmail()	{ return email; }
	unsigned int getId(){ return id; }

	operator bool() { return userLoggedIn; }

	friend class WebApi;
};
