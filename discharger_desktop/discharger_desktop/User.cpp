#include "User.h"

#include "ObjectFactory.h"
#include "WebApi.h"
#include "nlohmann/json.h"


User::User(QObject *parent) :
	QObject(parent)
{
	if (ObjectFactory::hasInstance<User>()) {
		std::exception("There can be only one instance of user object");
	}
}

void User::logIn(const QString & mail, const QString & password) {
	auto api = ObjectFactory::getInstance<WebApi>();
	nlohmann::json data{
		{"email", mail.toStdString()},
		{"pass", password.toStdString()}
	};

	api->POST(API_FILE, data.dump(), [this](bool success, std::string && response) {
		nlohmann::json resp = nlohmann::json::parse(response);
		if (success) {
			name =		QString::fromStdString(resp["name"].get<std::string>());
			surname =	QString::fromStdString(resp["surname"].get<std::string>());
			email =		QString::fromStdString(resp["email"].get<std::string>());
			id = resp["no"].type() == nlohmann::json::value_t::string ? 
				std::stoi(resp["no"].get<std::string>()) 
				: 
				resp["no"].get<int>();
			userLoggedIn = true;

			loggedInCallback(true, resp["comment"].get<std::string>().c_str());
		}
		else {
			loggedInCallback(false, resp["comment"].get<std::string>().c_str());
		}
	});
}

void User::logOut() {
	userLoggedIn = false;
	id = 0;
	name = surname = email = "";
}

void User::setOnLoggedInCallback(std::function<void(bool, const QString&)> callback) {
	loggedInCallback = callback;
}