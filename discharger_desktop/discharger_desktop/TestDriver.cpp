#include "TestDriver.h"
#include "DeviceEventsDecriptions.h"
#include "QMessageBox"
#include <QDialog>

using namespace db;

TestDriver::TestDriver(QObject *parent)
	: QObject(parent),
	ui(*dynamic_cast<TestGUI*>(parent))
{
	plot = new QCustomPlot(qobject_cast<QWidget *>(this->parent()));
	plot->hide();

	connect(&chartPorps, &ChartPropertiesDialog::accepted, this, &TestDriver::chartPortpertiesAccepted);
}

TestDriver::~TestDriver() {
}


void TestDriver::setDevice(DeviceInterface * dev) {
	if (!devicePtr.isNull()) {
		throw std::exception("Another device is already set!");
	}
	devicePtr = QSharedPointer<DeviceInterface>(dev);
	
	connect(dev, &DeviceInterface::signalFinished, this, &TestDriver::deviceFinished);
	//connect(dev, &DeviceInterface::signalError, this, &TestDriver::deviceErrorOccured);
	//connect(dev, &DeviceInterface::signalWarning, this, &TestDriver::deviceWarningOccured);
	//connect(dev, &DeviceInterface::signalDebugMsg, this, &TestDriver::deviceDebug);
	connect(dev, &DeviceInterface::signalNewData, this, &TestDriver::deviceNewData);	
}

void TestDriver::removeDevice() {
	ObjectFactory::getInstance<serialPort::SerialPort>()->close();
	devicePtr.reset();
}

void TestDriver::setFilepathToLog(const QString & filepath, bool jsonFile) {
	this->filepath = filepath;
	jsonLogFile = jsonFile;
}

void TestDriver::setupTestInDb(std::function<void(bool, const QString&)> callback) {
	ObjectFactory::getInstance<db::TestData>()->setupTestInDb(
		callback, TestStates::READY, devicePtr->getCurrentSource(),
		devicePtr->getTestType(), testName, idBattLeft, idBattRight, 
		devicePtr->getLogInfoId() ? devicePtr->getLogInfoId().val() : -1
	);
}

void TestDriver::loadPageData() {
	//testState = TestStates::READY;
	setTestState(TestStates::READY);
	if (devicePtr->getCurrentSource() == db::CurrentSource::NO_CURR_SOURCE)
		ui.setVarTestCurrent(QString::number(devicePtr->getTestCurrent().val()));
	ui.setVarVoltLimit(QString::number(devicePtr->getVoltageLimit().val()));
	ui.setVarHeatSinkTempLimit(QString::number(devicePtr->getHeatSinkTempLimit().val()));
	updateUI();
	setupChart();
}

void TestDriver::startTest() {
	devicePtr->start();
}

void TestDriver::stopTest() {
	devicePtr->stop();
	if (devicePtr->isStopable()) {
		deviceFinished();
		return;
	}
	//testState = TestStates::REMOVED;
	setTestState(TestStates::REMOVED);
	updateUI();
}

void TestDriver::clear() {
	devicePtr->disconnect();
	removeDevice();
	//testState = TestStates::NONE;
	setTestState(TestStates::NONE);
	testStartTime = QTime();
	testEstimEndTime = QTime();
	testName.clear();
	filepath.clear();
	idBattLeft = int();
	idBattRight = int();
	graphsUsage.clear();
	chartPorps.clear();
	//dbSimDataVec.clear();
	plot->clearGraphs();
	plot->hide();
	ui.removeChart(plot);
	calcs.clear();
	ObjectFactory::getInstance<db::TestData>()->clear();
}

void TestDriver::deviceFinished() {
	if (testState >= TestStates::COMPLETED) return;
	//testState = TestStates::COMPLETED;
	setTestState(TestStates::COMPLETED);
	testEstimEndTime = QTime::currentTime();
	updateUI();
	ui.testFinised();

	bool confirmed = ui.showQuestionBox(
		"Test has been finished successfuly,\n"
		"shall be confirmed?\n"
		"(If no then it will be marked as removed)"
	);
	if (confirmed) {
		//testState = TestStates::CONFIRMED;
		setTestState(TestStates::CONFIRMED);
	}
	else {
		//testState = TestStates::REMOVED;
		setTestState(TestStates::REMOVED);
	}
	updateUI();
}

void TestDriver::deviceNewData(db::SimData dbSimData) {

	dbSimData.currTimestamp = QDateTime::currentDateTime();

	// TODO: calcs of capacity, used energy, etc. - DONE
	calcs.addValues(
		testStartTime.elapsed(), 
		dbSimData.current.val(), 
		dbSimData.battLeftVolt.val(), 
		dbSimData.battRightVolt.val()
	);
	if (!dbSimData.capacity)
		dbSimData.capacity = calcs.computeCapacity();
	if (!dbSimData.usedEnergy)
		dbSimData.usedEnergy = calcs.computeUsedEnergy();
	
	if (testState == TestStates::READY) {
		setTestState(TestStates::PROGRESS);
		testStartTime.start();
		if (devicePtr->getEstimetedTestTime()) {
			testEstimEndTime = testStartTime.addMSecs(
				devicePtr->getEstimetedTestTime().val().msecsSinceStartOfDay()
			);
		}
		ui.appendTestDataLine(dbSimData.getColumnsNames());
		setUsageGraphsFlags(dbSimData);
		setupLogFile(dbSimData);
	}
	dbSimData.timeSinceBeg = QTime::fromMSecsSinceStartOfDay(testStartTime.elapsed());

	appendChartData(dbSimData);
	updateUI(dbSimData);
	ui.appendTestDataLine(dbSimData.toCSV());
	logToFile(dbSimData);
	ObjectFactory::getInstance<db::TestData>()->addSimData(std::move(dbSimData));
	//dbSimDataVec.push_back(std::move(dbSimData));
}

void TestDriver::deviceErrorOccured(dischargerDevice::Error error) {
	//ObjectFactory::getInstance<db::TestData>()->setTestError(error);
	setTestState(TestStates::DEV_ERROR);
	updateUI();
	QString errorStr = QString::fromStdString(dischargerDevice::getErrorDescription(error));
	ui.appendEventsLine("<div style=\"color: red\">" + errorStr + "</div>");
	ui.showDeviceError(errorStr);
}

void TestDriver::deviceWarningOccured(dischargerDevice::Warning warning) {
	ui.appendEventsLine("<div style=\"color: orange\">" + 
		QString::fromStdString(dischargerDevice::getWarningDescription(warning)) + 
		"</div>"
	);
}

void TestDriver::deviceDebug(const QString & msg) {
	ui.appendEventsLine(
		"<div style=\"color: green\">" + msg + "</div>"
	);
}

void TestDriver::updateUI(const db::SimData & sd) {
	ui.setTestPatametersData(prepareTestParametersData(sd));
}

void TestDriver::setTestState(db::TestStates testState) {
	this->testState = testState;
	ObjectFactory::getInstance<db::TestData>()->setTestState(testState);
}

TestParametersData TestDriver::prepareTestParametersData(const db::SimData & sd) {
	TestParametersData data;
	auto d = devicePtr;
	data.setTestName(testName);
	data.setTestStatus(TEST_STATES.at(testState));
	if(d->getProgress()) data.setProgress(d->getProgress().val());
	bool noCurrSource = (d->getCurrentSource() == db::CurrentSource::NO_CURR_SOURCE);
	if (!noCurrSource) {
		if(d->getTestCurrent()) data.setTestCurrent(d->getTestCurrent().val());
	}
	ui.setTestCurrentLineEditEnabled(noCurrSource);

	if (testStartTime.isValid())	data.setTestBeganAt(testStartTime.toString(TIME_FORMAT));
	if (testEstimEndTime.isValid())	data.setTestEstimatedEnd(testEstimEndTime.toString(TIME_FORMAT));
	if (d->getEstimetedTestTime())	data.setEstimatedTime(d->getEstimetedTestTime().val().toString(TIME_FORMAT));
	if (sd.timeSinceBeg)			data.setTestTime(sd.timeSinceBeg.val().toString(TIME_FORMAT));

	if (sd.capacity)		data.setCapacity(sd.capacity.val());
	if (sd.usedEnergy)		data.setConsumedEnergy(sd.usedEnergy.val());
	if (sd.heatSinkTemp)	data.setHeatSinkTemp(sd.heatSinkTemp.val());
	if (sd.current)			data.setCurrent(sd.current.val());
							data.setBattLeftId(idBattLeft);
	if (sd.battLeftVolt)	data.setBattLeftVolt(sd.battLeftVolt.val());
	if (sd.battLeftTemp)	data.setBattLeftTemp(sd.battLeftTemp.val());

	if (!isSingleBattery()) {
		data.setSingleBatteryMode(false);
		data.setBattRightId(idBattRight);
		if (sd.battRightVolt)	data.setBattRightVolt(sd.battRightVolt.val());
		if (sd.battRightTemp)	data.setBattRightTemp(sd.battRightTemp.val());
	}
	return data;
}

void TestDriver::setupLogFile(const db::SimData & sd) {
	if (!filepath.isEmpty() && !jsonLogFile) {
		QFile f(filepath);
		if (f.open(QIODevice::WriteOnly | QIODevice::Append)) {
			QTextStream out(&f);
			out << sd.getColumnsNames() << "\n";
		}
		f.close();
	}
}

void TestDriver::logToFile(const db::SimData & sd) {
	if (!filepath.isEmpty()) {
		QFile f(filepath);
		if (f.open(QIODevice::WriteOnly | QIODevice::Append)) {
			QString data;
			if (jsonLogFile) {
				data = nlohmann::json(sd).dump().c_str();
			}
			else {
				data = sd.toCSV();
			}
			QTextStream out(&f);
			out << data << "\n";
		}
		f.close();
	}
}

void TestDriver::setUsageGraphsFlags(const db::SimData & sd) {
	graphsUsage.resize(plot->graphCount());
	graphsUsage[Graphs::TEST_CURRENT] = devicePtr->getTestCurrent();
	graphsUsage[Graphs::CURRENT] = sd.current;
	graphsUsage[Graphs::CAPACITY] = sd.capacity;
	graphsUsage[Graphs::USED_ENERGY] = sd.usedEnergy;
	graphsUsage[Graphs::HEAT_SINK_TEMP] = sd.heatSinkTemp;
	graphsUsage[Graphs::BATT_LEFT_VOLT] = sd.battLeftVolt;
	graphsUsage[Graphs::BATT_RIGHT_VOLT] = sd.battRightVolt;
	graphsUsage[Graphs::BATT_LEFT_TEMP] = sd.battLeftTemp;
	graphsUsage[Graphs::BATT_RIGHT_TEMP] = sd.battRightTemp;
}

void TestDriver::appendChartData(const db::SimData & sd) {
	int offset = 23 * 60 * 60;
	int secs = sd.timeSinceBeg.val().msecsSinceStartOfDay() / 1000.0 + 0.5 + offset;

	if (devicePtr->getTestCurrent()) plot->graph(Graphs::TEST_CURRENT)->addData(secs, devicePtr->getTestCurrent().val());
	if (sd.current)			plot->graph(Graphs::CURRENT)->addData(secs, sd.current.val());
	if (sd.capacity)		plot->graph(Graphs::CAPACITY)->addData(secs, sd.capacity.val());
	if (sd.usedEnergy)		plot->graph(Graphs::USED_ENERGY)->addData(secs, sd.usedEnergy.val());
	if (sd.heatSinkTemp)	plot->graph(Graphs::HEAT_SINK_TEMP)->addData(secs, sd.heatSinkTemp.val());
	if (sd.battLeftVolt)	plot->graph(Graphs::BATT_LEFT_VOLT)->addData(secs, sd.battLeftVolt.val());
	if (sd.battRightVolt)	plot->graph(Graphs::BATT_RIGHT_VOLT)->addData(secs, sd.battRightVolt.val());
	if (sd.battLeftTemp)	plot->graph(Graphs::BATT_LEFT_TEMP)->addData(secs, sd.battLeftTemp.val());
	if (sd.battRightTemp)	plot->graph(Graphs::BATT_RIGHT_TEMP)->addData(secs, sd.battRightTemp.val());
	
	chartRescaleAxes(secs);
}

void TestDriver::setupChart() {
	for (auto & nameColor : GRAPHS_NAMES_COLORS) {
		plot->addGraph();
		plot->graph()->setName(nameColor.first);
		plot->graph()->setVisible(false);
		plot->graph()->removeFromLegend();
		auto pen = plot->graph()->pen();
		pen.setColor(nameColor.second);
		plot->graph()->setPen(pen);
	}
	auto pen = plot->graph(Graphs::TEST_CURRENT)->pen();
	pen.setStyle(Qt::DotLine);
	pen.setWidthF(2);
	plot->graph(Graphs::TEST_CURRENT)->setPen(pen);
	QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
	dateTicker->setDateTimeFormat("hh:mm:ss");
	plot->xAxis->setTicker(dateTicker);
	plot->legend->setVisible(true);
	plot->legend->setBrush(QColor(255, 255, 255, 150));
}

void TestDriver::chartRescaleAxes(int max) {
	static int lastMax = 1;
	if (max == -1) {
		max = lastMax;
	}
	else {
		lastMax = max;
	}
	plot->rescaleAxes(true);
	int offset = 23 * 60 * 60;
	int secsInRange = chartPorps.getSecsInRange();
	int beginOfRange = ((max - secsInRange) < offset || secsInRange == -1) ? offset : (max - secsInRange);
	plot->xAxis->setRange(beginOfRange, max);
	plot->replot();
}

void TestDriver::confChart() {
	if (graphsUsage.size() != plot->graphCount()) return;
	std::vector<ChartPropertiesDialog::SerieItem> series;
	for (int i = 0; i < plot->graphCount(); ++i) {
		if (!graphsUsage.at(i)) continue;
		series.emplace_back(
			i,
			plot->graph(i)->visible(),
			plot->graph(i)->name(),
			plot->graph(i)->pen().color()
		);
	}
	chartPorps.setSeries(series);
	chartPorps.show();
}

void TestDriver::chartPortpertiesAccepted() {
	auto newSeriesData = chartPorps.getSeries();
	bool allSeriesHiden = true;
	for (auto & serie : newSeriesData) {
		allSeriesHiden &= !serie.visible;
		auto pen = plot->graph(serie.id)->pen();
		plot->graph(serie.id)->setVisible(serie.visible);
		plot->graph(serie.id)->pen().setColor(serie.color);
		pen.setColor(serie.color);
		plot->graph(serie.id)->setPen(pen);
		if (serie.visible)
			plot->graph(serie.id)->addToLegend();
		else
			plot->graph(serie.id)->removeFromLegend();
	}
	if (allSeriesHiden) {
		plot->hide();
		ui.removeChart(plot);
	}
	else if(plot->isHidden()) {
		ui.setChart(plot);
		plot->show();
	}
	chartRescaleAxes();
}