#include "ChartWgt.h"
#include "ObjectFactory.h"
#include "TestDriver.h"

ChartWgt::ChartWgt(QWidget *parent)
	: QWidget(parent),
	chartPorps(graphsProps, this)
{
	ui.setupUi(this);
	connect(ui.btnConfChart, &QPushButton::clicked, this, &ChartWgt::configChart);
	connect(&chartPorps, &ChartPropertiesDialog::graphVisibilityHasChanged, this, &ChartWgt::handleGraphVisibilityChanged);
	connect(&chartPorps, &ChartPropertiesDialog::graphColorHasChanged, this, &ChartWgt::handleGraphColorChanged);
	showConfPage();
	setupChart();
}

ChartWgt::~ChartWgt() {

}

void ChartWgt::handleGraphVisibilityChanged(int graphId, bool visible) {
	ui.plot->graph(graphId)->setVisible(visible);
	if (visible)
		ui.plot->graph(graphId)->addToLegend();
	else
		ui.plot->graph(graphId)->removeFromLegend();
	pagesManager();
}

void ChartWgt::handleGraphColorChanged(int graphId, const QColor & color) {
	QPen pen = ui.plot->graph(graphId)->pen();
	pen.setColor(color);
	ui.plot->graph(graphId)->setPen(pen);
	ui.plot->replot();
}

void ChartWgt::handleNewDbSimData(const db::SimData & simData) {
	if (!usageFlagsSet)
		setUsageFlags(simData);
	appendChartData(simData);
}

void ChartWgt::showConfPage() {
	ui.stackedWidget->setCurrentIndex(Pages::CONF);
}

void ChartWgt::showPlotPage() {
	ui.stackedWidget->setCurrentIndex(Pages::PLOT);
}

bool ChartWgt::areAllGraphsHidden() {
	for (auto & props : graphsProps)
		if (props.isVisible() && props.isUsed())
			return false;
	return true;
}

void ChartWgt::pagesManager() {
	if (areAllGraphsHidden())
		showConfPage();
	else
		showPlotPage();
}

void ChartWgt::setupChart() {
	for (auto & props : graphsProps) {
		ui.plot->addGraph();
		ui.plot->graph()->setName(props.getName());
		ui.plot->graph()->setVisible(false);
		ui.plot->graph()->removeFromLegend();
		auto pen = ui.plot->graph()->pen();
		pen.setColor(props.getColor());
		pen.setWidth(props.getWidth());
		ui.plot->graph()->setPen(pen);
	}
	QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
	dateTicker->setDateTimeFormat("hh:mm:ss");
	ui.plot->xAxis->setTicker(dateTicker);
	ui.plot->legend->setVisible(true);
	ui.plot->legend->setBrush(QColor(255, 255, 255, 150));
}

void ChartWgt::setUsageFlags(const db::SimData & simData) {
	// TODO: Test current
	//graphsProps[Graphs::TEST_CURRENT] = devicePtr->getTestCurrent();
	graphsProps[Graphs::CURRENT].setUsed(simData.current.isSet());
	graphsProps[Graphs::CAPACITY].setUsed(simData.capacity.isSet());
	graphsProps[Graphs::USED_ENERGY].setUsed(simData.usedEnergy.isSet());
	graphsProps[Graphs::HEAT_SINK_TEMP].setUsed(simData.heatSinkTemp.isSet());
	graphsProps[Graphs::BATT_LEFT_VOLT].setUsed(simData.battLeftVolt.isSet());
	graphsProps[Graphs::BATT_RIGHT_VOLT].setUsed(simData.battRightVolt.isSet());
	graphsProps[Graphs::BATT_LEFT_TEMP].setUsed(simData.battLeftTemp.isSet());
	graphsProps[Graphs::BATT_RIGHT_TEMP].setUsed(simData.battRightTemp.isSet());
	usageFlagsSet = true;
}

void ChartWgt::appendChartData(const db::SimData & simData) {
	int offset = 23 * 60 * 60;
	int secs = simData.timeSinceBeg.get().msecsSinceStartOfDay() / 1000.0 + 0.5 + offset;

	if (simData.current.isSet())		ui.plot->graph(Graphs::CURRENT)->addData(secs, simData.current);
	if (simData.capacity.isSet())		ui.plot->graph(Graphs::CAPACITY)->addData(secs, simData.capacity);
	if (simData.usedEnergy.isSet())		ui.plot->graph(Graphs::USED_ENERGY)->addData(secs, simData.usedEnergy);
	if (simData.heatSinkTemp.isSet())	ui.plot->graph(Graphs::HEAT_SINK_TEMP)->addData(secs, simData.heatSinkTemp);
	if (simData.battLeftVolt.isSet())	ui.plot->graph(Graphs::BATT_LEFT_VOLT)->addData(secs, simData.battLeftVolt);
	if (simData.battRightVolt.isSet())	ui.plot->graph(Graphs::BATT_RIGHT_VOLT)->addData(secs, simData.battRightVolt);
	if (simData.battLeftTemp.isSet())	ui.plot->graph(Graphs::BATT_LEFT_TEMP)->addData(secs, simData.battLeftTemp);
	if (simData.battRightTemp.isSet())	ui.plot->graph(Graphs::BATT_RIGHT_TEMP)->addData(secs, simData.battRightTemp);
	
	ui.plot->rescaleAxes(true);
	ui.plot->replot();
}

void ChartWgt::configChart() {
	chartPorps.show();
}

void ChartWgt::clear() {
	for (auto & props : graphsProps) {
		props.setVisible(false);
		props.setUsed(false);
		ui.plot->graph(props.getId())->data().clear();
	}
	usageFlagsSet = false;
}