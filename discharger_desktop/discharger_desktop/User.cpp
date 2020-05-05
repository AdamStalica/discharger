#include "User.h"

#include "ObjectFactory.h"
#include "WebApi.h"
#include "nlohmann/json.h"

#include <QCryptographicHash>

User::User(QObject *parent) :
	QObject(parent)
{
	if (ObjectFactory::hasInstance<User>()) {
		throw std::exception("There can be only one instance of user object");
	}
}

void User::logIn(const QString & mail, const QString & password) {
	this->password = QString(QCryptographicHash::hash(
		QByteArray(password.toStdString().c_str()),
		QCryptographicHash::Md5
	).toHex());
	auto api = ObjectFactory::getInstance<WebApi>();
	nlohmann::json data{
		{"email", mail.toStdString()},
		{"pass", this->password.toStdString()}
	};

	api->POST(API_FILE, data, [this](WebApi::StatsEnum status, nlohmann::json && response) {
		handleApiCallback(status, std::move(response));
	});
}

void User::logOut() {
	userLoggedIn = false;
	id = 0;
	name = surname = email = password = "";
	ObjectFactory::getInstance<WebApi>()->invalidateApiKey();
}

void User::setOnLoggedInCallback(std::function<void(bool, const QString&)> callback) {
	loggedInCallback = callback;
}

void User::handleApiCallback(WebApi::StatsEnum status, nlohmann::json && response) {
	if (status == WebApi::API_OK) {
		name = QString::fromStdString(response.at("name").get<std::string>());
		surname = QString::fromStdString(response.at("surname").get<std::string>());
		email = QString::fromStdString(response.at("email").get<std::string>());
		id = response.at("id_usr").get<int>();
		userLoggedIn = true;
		loggedInCallback(true, response.at("comment").get<std::string>().c_str());
	}
	else {
		password = "";
		loggedInCallback(false, response.at("comment").get<std::string>().c_str());
	}
}