#pragma once
#include <QObject>
#include <DeviceEventsDef.h>
#include "ObjectFactory.h"
#include "DbTestData.h"
#include "SerialPort.h"

class DeviceInterface : 
	public QObject
{
	Q_OBJECT

protected:
	const db::TestType TEST_TYPE;
	const db::CurrentSource CURRENT_SOURCE;
	const int idBattLeft, idBattRight;

	Param<unsigned int> progress;
	Param<float> testCurrent;
	Param<float> voltageLimit;
	Param<float> heatSinkTempLimit;
	Param<QTime> estimetedTestTime;
	Param<unsigned int> idLogInfo;

public:

	DeviceInterface(
		QObject * parent, 
		db::TestType testType, 
		db::CurrentSource currSource, 
		int idBattLeft, 
		int idBattRight
	) 	:	QObject(parent), 
			TEST_TYPE(testType),
			CURRENT_SOURCE(currSource), 
			idBattLeft(idBattLeft), 
			idBattRight(idBattRight)
	{};
	virtual ~DeviceInterface() {};
	
	virtual void connectToDevice() = 0;
	virtual void disconnectFromDevice() = 0;
	virtual void start() = 0;
	virtual void stop() = 0;

	virtual bool checkBatteryNumber(int numebrOfBatteries) = 0;
	virtual bool isTestCurrentEditable() = 0;
	virtual bool isStartable() = 0;
	virtual bool isStopable() = 0;
	inline bool isSingleBatteryTest();
	
	const Param<unsigned int> & getLogInfoId() const { return idLogInfo; };
	const Param<unsigned int> & getProgress() const { return progress; };
	const Param<float> & getTestCurrent() const { return testCurrent; };
	const Param<float> & getVoltageLimit() const { return voltageLimit; };
	const Param<float> & getHeatSinkTempLimit() const { return heatSinkTempLimit; };
	const Param<QTime> & getEstimetedTestTime() const { return estimetedTestTime; };
	db::TestType getTestType() const { return TEST_TYPE; }
	db::CurrentSource getCurrentSource() const { return CURRENT_SOURCE; };

	inline void setTestCurrent(float current);
	inline void setVoltageLimit(float volt);
	inline void setHeatSinkTempLimit(float tempLimit);

	inline int getIdBattLeft() const { return idBattLeft; }
	inline int getIdBattRight() const { return idBattRight; }

signals:
	void signalError(const QString & error);
	void signalNewData(db::SimData simData);
	void signalFinished();
	void signalConnectionEstablished();
	void signalCanNotEstablishConnection();
};

bool DeviceInterface::isSingleBatteryTest() {
	return (idBattRight == -1);
}

void DeviceInterface::setTestCurrent(float current) {
	if (CURRENT_SOURCE != db::CurrentSource::NO_CURR_SOURCE) {
		throw std::exception("This current source not supports such a functionality");
	}
	testCurrent = current;
}
void DeviceInterface::setVoltageLimit(float volt) {
	voltageLimit = volt;
}
void DeviceInterface::setHeatSinkTempLimit(float tempLimit) {
	heatSinkTempLimit = tempLimit;
}