#include "ParamsWgt.h"
#include "Cleaner.h"

ParamsWgt::ParamsWgt(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	forwardChangeSignals();
}

void ParamsWgt::clear() {
	Cleaner::clearChildrens<QLineEdit>(this);
	Cleaner::clearChildrens<QProgressBar>(this);
	Cleaner::clearChildrens<QLabel>(this, ".*[Ll]bl.*");
}

void ParamsWgt::setTestCurrent(double testCurrent) {
	ui.varEdtCurr->setText(QString::number(testCurrent));
}

void ParamsWgt::setVoltageLimit(double voltLim) {
	ui.varEdtVolLim->setText(QString::number(voltLim));
}

void ParamsWgt::setHeatSinkTempLimit(double tempLim) {
	ui.varEdtTempLim->setText(QString::number(tempLim));
}

void ParamsWgt::setTestParamsData(const TestParametersData & paramsData) {
	ui.lblName->setText(paramsData.getTestName());
	ui.lblStatus->setText(paramsData.getTestStatus());
	ui.progBar->setValue(paramsData.getProgress());
	if (!paramsData.isTestCurrentLineEnabled())
		ui.varEdtCurr->setText(paramsData.getTestCurrent());
	ui.varEdtCurr->setEnabled(paramsData.isTestCurrentLineEnabled());
	ui.timeLblBeg->setText(paramsData.getTestBeganAt());
	ui.timeLblEstEnd->setText(paramsData.getTestEstimatedEnd());
	ui.timeLblTestTime->setText(paramsData.getTestTime());
	ui.timeLblEstTime->setText(paramsData.getEstimatedTime());
	ui.calcLblCapa->setText(paramsData.getCapacity());
	ui.calcLblEnergy->setText(paramsData.getConsumedEnergy());
	if (paramsData.isSingleBatteryMode()) {
		ui.measure1BLblHeatSinkTemp->setText(paramsData.getHeatSinkTemp());
		ui.measure1BLblCurr->setText(paramsData.getCurrent());
		ui.measure1BLblId->setText(paramsData.getBattLeftId());
		ui.measure1BLblVolt->setText(paramsData.getBattLeftVolt());
		ui.measure1BLblTemp->setText(paramsData.getBattLeftTemp());
		ui.measureStackedWgt->setCurrentIndex(MeasureSchem::SINGLE_BATT);
	}
	else {
		ui.measure2BLblHeatSinkTemp->setText(paramsData.getHeatSinkTemp());
		ui.measure2BLblCurr->setText(paramsData.getCurrent());
		ui.measure2BLblLeftId->setText(paramsData.getBattLeftId());
		ui.measure2BLblLeftVolt->setText(paramsData.getBattLeftVolt());
		ui.measure2BLblLeftTemp->setText(paramsData.getBattLeftTemp());
		ui.measure2BLblRightId->setText(paramsData.getBattRightId());
		ui.measure2BLblRightVolt->setText(paramsData.getBattRightVolt());
		ui.measure2BLblRightTemp->setText(paramsData.getBattRightTemp());
		ui.measureStackedWgt->setCurrentIndex(MeasureSchem::DOUBLE_BATT);
	}
}

void ParamsWgt::forwardChangeSignals() {
	connect(ui.varEdtCurr, &QLineEdit::editingFinished, [this] {
		emit testCurrentHasChanged(ui.varEdtCurr->text().toDouble());
	});
	connect(ui.varEdtVolLim, &QLineEdit::editingFinished, [this] {
		emit voltageLimitHasChanged(ui.varEdtVolLim->text().toDouble());
	});
	connect(ui.varEdtTempLim, &QLineEdit::editingFinished, [this] {
		emit heatSinkTempLimitHasChanged(ui.varEdtTempLim->text().toDouble());
	});
}

