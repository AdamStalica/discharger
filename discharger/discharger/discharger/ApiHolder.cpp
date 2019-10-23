#include "ApiHolder.h"
#include "json.h"

#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkAccessManager>

#include <QDebug>
#include <QTextStream>

using json = nlohmann::json;

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

void ApiHolder::clear()
{
	name = "";
	surname = "";
	email = "";
	id_usr = -1;
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

void ApiHolder::apiUpdate(const QString & param) {
	post_request(param.toStdString(), "update.php");
}

void ApiHolder::apiUpdate(const std::string & param) {
	post_request(param, "update.php");
}

void ApiHolder::post_request(const std::string & param, const QString & file) {

	QUrl url(this->api_url + file);

	QNetworkRequest req(url);
	req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

	mgr->post(req, param.c_str());
}

void ApiHolder::apiLogin(const QString & email, const QString & pass) {

	json login = {
		{"email", email.toStdString()},
		{"pass", pass.toStdString()}
	};

	std::string tmp = login.dump();
	post_request(login.dump(), "auth/login.php");
	
	login_conn = connect(this, &ApiHolder::gotResponse, this, [this](const QString & resp) {
	
		this->disconnect(this->login_conn);
		json resp_obj = json::parse(resp.toStdString());

		int no = resp_obj["no"].type() == json::value_t::string ? std::stoi(resp_obj["no"].get<std::string>()) : resp_obj["no"].get<int>();
		std::string comment = resp_obj["comment"];

		if(resp_obj["status"] == "OK") {

			std::string tmp = resp_obj["name"];
			std::string tmp1 = resp_obj["surname"];
			std::string tmp2 = resp_obj["email"];

			this->name = tmp.c_str();
			this->surname = tmp1.c_str();
			this->email = tmp2.c_str();
			this->id_usr = no;
			emit loginResult(true);
		}
		else {
			lastError = "No: " + QString::number(no) + ", " + comment.c_str();
			emit loginResult(false);
		}
	});

}
