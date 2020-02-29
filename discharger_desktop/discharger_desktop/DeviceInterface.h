#pragma once
#include <QDateTime>
#include <functional>
#include <DeviceEventsDef.h>

class DeviceInterface
{
public:
	enum CurrentSource {
		MAIN,
		MOTOR,
		NO_CURR_SOURCE
	};

	DeviceInterface() {};
	virtual ~DeviceInterface() {};

	virtual void setOnErrorCallback(std::function<void(Device::Error)> errCallback) = 0;
	virtual void setOnWarningCallback(std::function<void(Device::Warning)> warnCallback) = 0;
	virtual void setOnNewDataCallback(std::function<void(void)> dataCallback) = 0;

	virtual bool isStartable() { return true; };
	//virtual bool isStopable() { return true; };

	virtual void connect() = 0;
	virtual void start() = 0;
	virtual void stop() = 0;

	//virtual bool hasLogInfoId() { return false; };
	virtual CurrentSource getCurrentSource() { return CurrentSource::NO_CURR_SOURCE; };

	virtual unsigned int getLogInfoId() { return 0; };
	virtual unsigned int getLogDataId() { return 0; };
	//virtual unsigned int getLogDataId() { return 0; };

	virtual unsigned int getProgress() { return 0; }

	//virtual bool hasTestCurrent() { return false; }

	virtual float getTestCurrent() { return 0.0; }; 
	virtual float getVoltageLimit() = 0;
	virtual float getHeatSinkTempLimit() { return 0.0; };

	virtual void setTestCurrent(float current) = 0;
	virtual void setVoltageLimit(float volt) = 0;
	virtual void setHeatSinkTempLimit(float tempLimit) = 0;

	virtual bool hasEstimatedTestTime() { return false; };
	virtual QTime getEstimatedTestTime() { return QTime(); };
	//virtual QDateTime getBeginTime() = 0;

	virtual bool hasCapacity() { return false; }
	virtual float getCapacity() { return 0.0; };

	virtual bool hasConsumedEnergy() { return false; };
	virtual float getConsumedEnergy() { return 0.0; };

	virtual bool hasHeatSinkTemp() { return false; };
	virtual float getHeatSinkTemp() { return 0.0; };
	
	virtual float getCurrent() = 0;
	
	virtual bool hasBattLeftVolt() { return false; };
	virtual float getBattLeftVolt() { return 0.0; };

	virtual bool hasBattLeftTemp() { return false; };
	virtual float getBattLeftTemp() { return 0.0; };

	virtual bool hasBattRightVolt() { return false; };
	virtual float getBattRightVolt() { return 0.0; };
	
	virtual bool hasBattRightTemp() { return false; };
	virtual float getBattRightTemp() { return 0.0; };

	virtual bool checkBatteryNumber(int numebrOfBatteries) = 0;
	//virtual bool isTestCurrentEditable() { return false; };

};