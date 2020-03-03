#pragma once
#include <QObject>
#include <DeviceEventsDef.h>
#include "DbSimData.h"

class DeviceInterface : 
	public QObject,
	protected db::SimData
{
	Q_OBJECT

public:
	enum CurrentSource {
		MAIN,
		MOTOR,
		NO_CURR_SOURCE
	};

protected:
	const DeviceInterface::CurrentSource CURRENT_SOURCE;

	Param<unsigned int> progress;
	Param<float> testCurrent;
	Param<float> voltageLimit;
	Param<float> heatSinkTempLimit;
	Param<QTime> estimetedTestTime;
	Param<unsigned int> idLogInfo;

public:

	DeviceInterface(QObject * parent, CurrentSource currSource) : 
		QObject(parent),
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
	
	const Param<unsigned int> & getLogInfoId() { return idLogInfo; };
	const Param<unsigned int> & getProgress() { return progress; };
	const Param<float> & getTestCurrent() { return testCurrent; };
	const Param<float> & getVoltageLimit() { return voltageLimit; };
	const Param<float> & getHeatSinkTempLimit() { return heatSinkTempLimit; };
	const Param<QTime> & getEstimetedTestTime() { return estimetedTestTime; };
	db::SimData getDbSimData() { return static_cast<db::SimData>(*this); }
	CurrentSource getCurrentSource() { return CURRENT_SOURCE; };

	void setTestCurrent(float current) {
		if (CURRENT_SOURCE != DeviceInterface::CurrentSource::NO_CURR_SOURCE) {
			throw std::exception("This current source not support such a functionality");
		}
		testCurrent = current;
	}
	void setVoltageLimit(float volt) {
		voltageLimit = volt;
	}
	void setHeatSinkTempLimit(float tempLimit) {
		heatSinkTempLimit = tempLimit;
	}

signals:
	void signalError(Device::Error);
	void signalWarning(Device::Warning);
	void signalNewData();
	void signalFinished();
	void signalConnectionEstablished();
};