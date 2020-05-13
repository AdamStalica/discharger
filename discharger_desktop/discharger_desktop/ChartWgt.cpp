#include "ChartWgt.h"
#include "ObjectFactory.h"
#include "TestDriver.h"

ChartWgt::ChartWgt(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	auto testDriver = ObjectFactory::getInstance<TestDriver>();
	connect(ui.btnConfChart, &QPushButton::clicked, this, &ChartWgt::configChart);
	connect(testDriver, &TestDriver::dbSimData, this, &ChartWgt::handleNewDbSimData);
}

ChartWgt::~ChartWgt() {

}

void ChartWgt::configChart() {

}

void ChartWgt::handleNewDbSimData(const db::SimData & simData) {

}