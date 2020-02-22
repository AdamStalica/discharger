#pragma once
#include <QObject>
#include <functional>

class User : public QObject
{
	Q_OBJECT

private:
	const std::string API_FILE{ "auth/login.php" };

	QString name, surname, email;
	unsigned int id{ 0 };
	bool userLoggedIn{ false };

	std::function<void(bool, QString)> loggedInCallback{
		[](bool success, const QString & response) {}
	};

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
};
