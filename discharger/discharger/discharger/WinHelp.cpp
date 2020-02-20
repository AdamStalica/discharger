#include "WinHelp.h"
#include "QFile"
#include "QDebug"
#include <qmessagebox.h>

using json = nlohmann::json;

WinHelp::WinHelp(const QString & helpFileName, QWidget *parent)
	:	QWidget(parent), 
		helpFileName(helpFileName)
{
	ui.setupUi(this);

	QFile helpFile(helpFileName);

	std::string str = getFileContent(helpFileName.toStdString());

	if (str != "null") {
		try {
			helpJSON = json::parse(str);
		}
		catch (const std::exception & ex) {
			qDebug() << ex.what();
		}
	}
}

bool WinHelp::showHelpFor(const QString & wgtName)
{
	auto ite = std::find_if(helpJSON.begin(), helpJSON.end(), [&wgtName](const json & help)->bool {

		bool ans = !help["wgtName"].is_null();
		if (ans) {
			ans = help["wgtName"] == wgtName.toStdString();
		}
		return ans;
	});
		
	if (ite != helpJSON.end() && !(*ite)["helpHTMLFile"].is_null()) {

		std::string currHelpFileName = (*ite)["helpHTMLFile"];
		std::string str = getFileContent(currHelpFileName);

		if (str != "null") {
			ui.textBrowser->setHtml(str.c_str());
			return true;
		}
	}
	return false;
}

std::string WinHelp::getFileContent(const std::string & fileName)
{
	QFile helpFile(fileName.c_str());

	if (helpFile.open(QIODevice::ReadOnly | QIODevice::Text)) {

		QByteArray fileContent = helpFile.readAll();

		return std::string(fileContent);
	}
	else return "null";
}
