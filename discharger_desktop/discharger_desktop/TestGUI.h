#pragma once

#include <QWidget>
#include "TestParametersData.h"
class TestGUI
{
public:
	TestGUI() {};
	virtual ~TestGUI() {};

	virtual void testFinised() = 0;

	virtual void clearParameters() = 0;
	virtual void setTestPatametersData(const TestParametersData & data) = 0;
	virtual void setTestCurrentLineEditEnabled(bool enabled) = 0;
	virtual void setVarTestCurrent(const QString & curr) = 0;
	virtual void setVarVoltLimit(const QString & volt) = 0;
	virtual void setVarHeatSinkTempLimit(const QString & temp) = 0;
	virtual void appendTestDataLine(const QString & line) = 0;
	virtual void appendEventsLine(const QString & line) = 0;
	virtual void appendRawDataLine(const QString & line) = 0;
	virtual void setChart(QWidget * chart) = 0;
	virtual void removeChart(QWidget * chart) = 0;
	virtual bool showQuestionBox(const QString & text) = 0;
	virtual void showWarning(const QString & msg) = 0;
	virtual void showError(const QString & msg) = 0;
};