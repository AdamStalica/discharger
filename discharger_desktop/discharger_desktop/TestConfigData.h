#pragma once

#include <QObject>
#include <QTreeWidgetItem>
#include <functional>
#include <nlohmann/json.h>
#include "ObjectFactory.h"

class TestConfigData : public QObject
{
	Q_OBJECT

private:
	std::string API_FILE = "get_test_config_data.php";

	nlohmann::json jsonData;

	QStringList batteries;
	QStringList coms;
	//QList<QTreeWidgetItem *> logsTreeItems;


	std::function<void(bool, const QString &)> dataReadyCallback{
		[](bool success, const QString & response) {}
	};

	void proccessResponse();
	//void createStandardItemModel();

public:
	TestConfigData(QObject *parent);
	~TestConfigData();

	void perpareData();
	void setOnDataReadyCallback(std::function<void(bool, const QString &)> callback);
	void refreshComs();

	QStringList getBatteriesLeftList() { return batteries; }
	QStringList getBatteriesRightList();
	QStringList getComsList() { return coms; }
	QList<QTreeWidgetItem *> getLogsTreeItems();// { return logsTreeItems; }
};
