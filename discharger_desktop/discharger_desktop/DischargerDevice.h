#pragma once
#include <QTimer>
#include <queue>
#include <set>
#include "DeviceInterface.h"
#include "WebApi.h"

auto constexpr DISCHARGER_CONN_TIMEOUT = 2000;
auto constexpr DISCHARGER_BOUDRATE = 57600;
auto constexpr DISCHARGER_DATA_SIZE = serialPort::datasize_t::eightbits;
auto constexpr DISCHARGER_STOP_BITS = serialPort::stopbits_t::stopbits_two;
auto constexpr DISCHARGER_PARITY = serialPort::parity_t::parity_none;


/**
1. construction of an object	
2. initialization 
*/


/*
set current,
id log data,

current,
volt left,
volt right,
temp left,
temp right,
temp heat sink

*/


class DischargerDevice :
	public DeviceInterface
{
	Q_OBJECT

private:
	struct LogData {
		unsigned int idLogData = 0;
		double current = 0.0;
		LogData() {}
		LogData(unsigned int idLogData_, double curr_) :
			idLogData(idLogData_), current(curr_)
		{}
		bool operator<(const LogData & oth) const {
			return idLogData < oth.idLogData;
		}
	};

	const int BATT_NUM = 2;

	const std::string API_GET_CURR = "get_test_current.php";
	const std::string DB_MOTOR_CURR = "motor_curr";
	const std::string DB_MAIN_CURR = "main_curr";
	std::string currSourceName = DB_MAIN_CURR;

	bool gotHandshake = false;
	QTimer timer, connectionTimer;

	QString comPortName;
	unsigned int sendingNewDataPeriod = 1000;

	std::vector<LogData> logDataVec;
	std::vector<LogData>::iterator logDataVecIte;
	//std::queue<std::pair<unsigned int, float>> queueOfLogData;
	//unsigned int dataSize;

public:

	DischargerDevice(QObject * parent, const QString & com, DeviceInterface::CurrentSource currSource);
	~DischargerDevice();

	void fetchCurrentToTest(int idLogInfo, std::function<void(bool, const QString & comment)> callback);

	bool isStopable() override;
	//DeviceInterface
	void connectToDevice() override;
	void start() override;
	void stop() override;
	
	bool checkBatteryNumber(int numebrOfBatteries) override;

private slots:
	void timerTimeout();
	void connectionTimerTimeout();
	void serialRecivedNewData(const QString & line);
	//void handleHandshake(const QString & devId);

private:
	void handleWarning(Device::Warning warn);
	void handleError(Device::Error err);
	void handleNewMesures(const nlohmann::json & data);
	void testFinished();
	unsigned int countProgress();

	void sendHandshake();
	void sendStop();
	void sendDrivingData(
		unsigned int id, 
		double current, 
		double temperatureLimit = DBL_MAX, 
		double voltageLimit = DBL_MAX
	);
};