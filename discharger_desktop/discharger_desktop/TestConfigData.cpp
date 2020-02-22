#include "TestConfigData.h"
#include "WebApi.h"
#include <QSerialPortInfo>

TestConfigData::TestConfigData(QObject *parent)
	: QObject(parent) 
{}

TestConfigData::~TestConfigData() {
	qDeleteAll(logsTreeItems);
}

void TestConfigData::perpareData() {
	auto api = ObjectFactory::getInstance<WebApi>();
	api->GET(API_FILE, [this](bool success, std::string && data) {
		jsonData = nlohmann::json::parse(data);
		if (success) {
			proccessResponse();
		}
		else {
			dataReadyCallback(
				false, 
				jsonData["comment"].get<std::string>().c_str()
			);
		}
	});

	refreshComs();
}

void TestConfigData::proccessResponse() {

	batteries.clear();
	for (auto & val : jsonData["batteries"]) {
		batteries.append(QString::number(val.get<int>()));
	}

	createStandardItemModel();

	dataReadyCallback(true, "Ok");
}

/*
{
	status:"OK | ERROR",
	no:0,
	comment:"OK"
	speedways: [
		{
			speedway_name:"name",
			races: [
				{
					race_name:"name",
					race_date:"date",
					logs: [
						{
							id_log_info:10,
							log_type:"parctise",
							car_name:"name",
							time_begin:"time",
							duration:"time",
							avg_motor_curr:20.3
						}
					]
				}, ...
			]
		}, ...
	],
	batteries: [ 1, 2, 3, ...]
}
*/
void TestConfigData::createStandardItemModel() {
	qDeleteAll(logsTreeItems);
	logsTreeItems.clear();

	for (auto speedway : jsonData["speedways"]) {
		QTreeWidgetItem * speedwayItem = new QTreeWidgetItem{
			QStringList {
				speedway["speedway_name"].get<std::string>().c_str()
			}
		};
		speedwayItem->setFlags(Qt::ItemIsEnabled);

		for (auto race : speedway["races"]) {
			QTreeWidgetItem * raceItem = new QTreeWidgetItem{
				QStringList{
					race["race_name"].get<std::string>().c_str(),
					race["race_date"].get<std::string>().c_str()
				}
			};
			raceItem->setFlags(Qt::ItemIsEnabled);

			for (auto log : race["logs"]) {
				QTreeWidgetItem * logItem = new QTreeWidgetItem{
					QStringList{
						"", "",
						QString::number(log["id_log_info"].get<int>()),
						log["log_type"].get<std::string>().c_str(),
						log["car_name"].get<std::string>().c_str(),
						log["time_begin"].get<std::string>().c_str(),
						log["duration"].get<std::string>().c_str(),
						QString::number(log["avg_motor_curr"].get<float>())
					}
				};
				logItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
				raceItem->addChild(logItem);
			}
			speedwayItem->addChild(raceItem);
		}
		logsTreeItems.append(speedwayItem);
	}
}

void TestConfigData::setOnDataReadyCallback(std::function<void(bool, const QString&)> callback) {
	dataReadyCallback = callback;
}

void TestConfigData::refreshComs() {
	coms.clear();
	auto ports = QSerialPortInfo::availablePorts();
	coms.reserve(ports.size());
	std::transform(ports.begin(), ports.end(), coms.begin(),
		[](const QSerialPortInfo & com)->QString {
			return com.portName();
	});
}

QStringList TestConfigData::getBatteriesRightList()
{
	return (QStringList() << "-1" << batteries);
}
