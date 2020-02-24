#pragma once

#include <QObject>
#include <QLabel>
#include "TestGUI.h"
#include "DeviceInterface.h"

class TestDriver : public QObject
{
	Q_OBJECT
private: 
	TestGUI & ui;
	QLabel * chart;
	std::shared_ptr<DeviceInterface> devicePtr;



public:
	TestDriver(QObject *parent);
	~TestDriver();

	void confChart();
	void setDevice(DeviceInterface * dev);
	void removeDevice();

private:
	void deviceNewData();
	void deviceErrorOccured(Device::Error error);
	void deviceWarningOccured(Device::Warning warning);
};
