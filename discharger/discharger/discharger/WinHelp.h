#pragma once

#include <QWidget>
#include "ui_WinHelp.h"
#include <nlohmann/json.h>

class WinHelp : public QWidget
{
	Q_OBJECT

public:
	WinHelp(const QString & helpFileName, QWidget *parent = Q_NULLPTR);
	~WinHelp() {};

	bool showHelpFor(const QString & wgtName);

private:
	Ui::WinHelp ui;

	const QString helpFileName;
	nlohmann::json helpJSON;

	std::string getFileContent(const std::string & fileName);
};
