#pragma once

#include <QWidget>
#include "ui_ParamsWgt.h"
#include "TestParametersData.h"
#include "IClearable.h"

class ParamsWgt : public QWidget, IClearable
{
	Q_OBJECT

public:
	ParamsWgt(QWidget *parent = Q_NULLPTR);
	~ParamsWgt() {};

public slots:
	void clear();
	void setTestCurrent(double testCurrent);
	void setVoltageLimit(double voltLim);
	void setHeatSinkTempLimit(double tempLim);
	void setTestParamsData(const TestParametersData & paramsData);
	
signals:
	void testCurrentHasChanged(double current);
	void voltageLimitHasChanged(double voltLim);
	void heatSinkTempLimitHasChanged(double tempLim);

private:
	enum MeasureSchem {
		DOUBLE_BATT,
		SINGLE_BATT
	};

	Ui::ParamsWgt ui;

	void forwardChangeSignals();
};
