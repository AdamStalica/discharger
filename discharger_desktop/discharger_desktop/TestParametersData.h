#pragma once
#include <QString>

class TestParametersData
{
	QString name = "-",
		status = "-",
		testCurrent = "-",
		begin = "-",
		end = "-",
		testTime = "-",
		estTime = "-",
		capacity = "-",
		consumedEnergy = "-",
		heatSilkTemp = "-",
		current = "-",
		battLeftId = "-",
		battLeftVolt = "-",
		battLeftTemp = "-",
		battRightId = "-",
		battRightVolt = "-",
		battRightTemp = "-";
	bool singleBattMode = false;
	unsigned int progress = 0;

public:
	TestParametersData() {};
	~TestParametersData() {};

	void setTestName(const QString & name) { this->name = name; };
	void setTestStatus(const QString & status) { this->status = status; };
	void setTestCurrent(float current) { testCurrent = QString::number(current); };
	void setTestBeginedAt(const QString & begin) { this->begin = begin; };
	void setTestEstimatedEnd(const QString & end) { this->end = end; };
	void setTestTime(const QString & testTime) { this->testTime = testTime; };
	void setEstimatedTime(const QString & estTime) { this->estTime = estTime; };
	void setCapacity(float capacity) { this->capacity = QString::number(capacity); };
	void setConsumedEnergy(float energy) { this->consumedEnergy = QString::number(energy); };
	void setHeatSilkTemp(float temp) { heatSilkTemp = QString::number(temp); };
	void setCurrent(float curr) { current = QString::number(curr); };
	void setBattLeftId(unsigned int id) { battLeftId = QString::number(id); }
	void setBattLeftVolt(float volt) { battLeftVolt = QString::number(volt); };
	void setBattLeftTemp(float temp) { battLeftTemp = QString::number(temp); };
	void setBattRightId(unsigned int id) { battRightId = QString::number(id); }
	void setBattRightVolt(float volt) { battRightVolt = QString::number(volt); };
	void setBattRightTemp(float temp) { battRightTemp = QString::number(temp); };

	void setProgress(unsigned int prog) { progress = prog; };
	void setSingleBatteryMode(bool singleBattery) { singleBattMode = singleBattery; };

	QString getTestName() const { return name; };
	QString getTestStatus() const { return status; };
	QString getTestCurrent() const { return testCurrent; };
	QString getTestBeginedAt() const { return begin; };
	QString getTestEstimatedEnd() const { return end; };
	QString getTestTime() const { return testTime; };
	QString getEstimatedTime() const { return estTime; };
	QString getCapacity() const { return capacity; };
	QString getConsumedEnergy() const { return consumedEnergy; };
	QString getHeatSilkTemp() const { return heatSilkTemp; };
	QString getCurrent() const { return current; };
	QString getBattLeftId() const { return battLeftId; }
	QString getBattLeftVolt() const { return battLeftVolt; };
	QString getBattLeftTemp() const { return battLeftTemp; };
	QString getBattRightId() const { return battRightId; }
	QString getBattRightVolt() const { return battRightVolt; };
	QString getBattRightTemp() const { return battRightTemp; };

	unsigned int getProgress() const { return progress; };
	bool isSingleBatteryMode() const { return singleBattMode; };
};