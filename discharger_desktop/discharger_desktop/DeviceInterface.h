#pragma once
#include <QObject>
#include <DeviceEventsDef.h>
#include "ObjectFactory.h"
#include "DbTestData.h"
#include "SerialPort.h"

class DeviceInterface : 
	public QObject,
	protected db::SimData
{
	Q_OBJECT

protected:
	const db::TestType TEST_TYPE;
	const db::CurrentSource CURRENT_SOURCE;

	Param<unsigned int> progress;
	Param<float> testCurrent;
	Param<float> voltageLimit;
	Param<float> heatSinkTempLimit;
	Param<QTime> estimetedTestTime;
	Param<unsigned int> idLogInfo;

public:

	DeviceInterface(QObject * parent, db::TestType testType, db::CurrentSource currSource) : 
		QObject(parent),
		TEST_TYPE(testType),
		CURRENT_SOURCE(currSource)
	{};
	virtual ~DeviceInterface() {};
	
	virtual void connectToDevice() = 0;
	virtual void start() = 0;
	virtual void stop() = 0;

	virtual bool checkBatteryNumber(int numebrOfBatteries) = 0;
	virtual bool isTestCurrentEditable() { return false; };
	virtual bool isStartable() { return true; };
	virtual bool isStopable() { return true; };
	
	const Param<unsigned int> & getLogInfoId() const { return idLogInfo; };
	const Param<unsigned int> & getProgress() const { return progress; };
	const Param<float> & getTestCurrent() const { return testCurrent; };
	const Param<float> & getVoltageLimit() const { return voltageLimit; };
	const Param<float> & getHeatSinkTempLimit() const { return heatSinkTempLimit; };
	const Param<QTime> & getEstimetedTestTime() const { return estimetedTestTime; };
	db::SimData getDbSimData() const { return static_cast<db::SimData>(*this); }
	db::TestType getTestType() const { return TEST_TYPE; }
	db::CurrentSource getCurrentSource() const { return CURRENT_SOURCE; };

	inline void setTestCurrent(float current);
	inline void setVoltageLimit(float volt);
	inline void setHeatSinkTempLimit(float tempLimit);

signals:
	void signalError(dischargerDevice::Error);
	void signalWarning(dischargerDevice::Warning);
	void signalDebugMsg(const QString & msg);
	void signalNewData(db::SimData simData);
	void signalFinished();
	void signalConnectionEstablished();
	void signalCanNotEstablishConnection();
};

void DeviceInterface::setTestCurrent(float current) {
	if (CURRENT_SOURCE == db::CurrentSource::NO_CURR_SOURCE) {
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