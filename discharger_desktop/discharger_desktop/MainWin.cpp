#include "MainWin.h"
#include "ObjectFactory.h"
#include "DischargerDevice.h"
#include "SerialPort.h"
#include "User.h"
#include "TestConfigData.h"
#include "TestDriver.h"
#include <QMessageBox>
#include <QTreeWidget>
#include <QMovie>
#include <QScrollBar>

using namespace serialPort;

MainWin::MainWin(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setDockedWidgetsVisibility(false);
	//setTestToolBarVisibility(false);

	ObjectFactory::createInstance(new WebApi(this));
	ObjectFactory::createInstance(new User(this));
	ObjectFactory::createInstance(new TestConfigData(this));
	ObjectFactory::createInstance(new TestDriver(this));
	ObjectFactory::createInstance(new SerialPort(this));
	
	auto serial_ = ObjectFactory::getInstance<SerialPort>();	

	/*
	auto Dcoms = ObjectFactory::getInstance<TestConfigData>();
	Dcoms->refreshComs();
	auto coms = Dcoms->getComsList();
	serial_->setPort(coms.at(0).toStdString());
	serial_->setBaudrate(9600);
	serial_->open();
	serial_->println("Hello World!");
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	serial_->close();
	*/

	testDriver = ObjectFactory::getInstance<TestDriver>();

	ui.stackedWidget->setCurrentIndex(PagesEnum::LOG_IN);

//	DischargerDevice<DeviceInterface::CurrentSource::NO_CURR_SOURCE> de;


	setupMainToolBar();
	setupTestToolBar();


	connect(ui.authBtnLogIn, &QPushButton::clicked, this, &MainWin::login);
	connect(ui.CTBtnConn, &QPushButton::clicked, this, &MainWin::prepareNewTest);
	connect(ui.testBtnConfChart, &QPushButton::clicked, testDriver, &TestDriver::confChart);

	//connect(ui.stackedWidget, &QStackedWidget::currentChanged, this, &MainWin::currentPageChannged);

}

void MainWin::setDockedWidgetsVisibility(bool visible) {
	ui.dockWgtParams->setVisible(visible);
	ui.dockWgtCommFlow->setVisible(visible);
}

void MainWin::setTestToolBarVisibility(bool visible) {
	ui.toolBarTest->setVisible(visible);
}

void MainWin::logout() {
	// TODO: checking if test is in progress
	ui.stackedWidget->setCurrentIndex(PagesEnum::LOG_IN);
	ObjectFactory::getInstance<User>()->logOut();
}

void MainWin::login() {
	QString email = ui.authEdtMail->text();
	QString pass = ui.authEdtPass->text();
	
	if (email.isEmpty() || pass.isEmpty()) {
		QMessageBox::warning(this, "Warning", "Both email and password fields must be filled up!");
		return;
	}

	auto user = ObjectFactory::getInstance<User>();
	user->setOnLoggedInCallback(
		[this](bool success, const QString & msg){
			if (success) {
				loader(msg);
				setupTestConfPage();
			}
			else {
				ui.stackedWidget->setCurrentIndex(PagesEnum::LOG_IN);
				showError(msg);
				loaderStop();
			}
		}
	);
	loader("Logging");
	user->logIn(email, pass);
}

void MainWin::setupMainToolBar() {
	ui.mainToolBar->addAction(QIcon("media/icons/logout.ico"), "Logout", this, &MainWin::logout);
	ui.mainToolBar->addAction(QIcon("media/icons/help.ico"), "Help", [] {
		// TODO: help 
	});
}

void MainWin::setupTestToolBar() {
	ui.toolBarTest->addAction(QIcon("media/icons/start.ico"), "Start test", this, &MainWin::testStart);
	ui.toolBarTest->addAction(QIcon("media/icons/stop.ico"), "Stop test", this, &MainWin::testStop)->setVisible(false);
	ui.toolBarTest->addAction(QIcon("media/icons/new_test.ico"), "Configure new test", this, &MainWin::testStop)->setVisible(false);
	ui.toolBarTest->addSeparator();
	ui.toolBarTest->addAction(QIcon("media/icons/parameters.ico"), "Parameters", ui.dockWgtParams, &QDockWidget::show);
	ui.toolBarTest->addAction(QIcon("media/icons/comm_flow.ico"), "Communication flow", ui.dockWgtCommFlow, &QDockWidget::show);
	ui.toolBarTest->addAction(QIcon("media/icons/chart.ico"), "Chart", testDriver, &TestDriver::confChart);
	ui.toolBarTest->addSeparator();
	ui.toolBarTest->addAction(QIcon("media/icons/web.ico"), "Results on-line", [] {
		// TODO: Reference to results on-line
	});
	ui.toolBarTest->addAction(QIcon("media/icons/qr_code.ico"), "QR Code", [] {
		// TODO: Qr code reference to results on-line
	});
	ui.toolBarTest->addSeparator();
}

void MainWin::showPage(PagesEnum page) {
	loaderStop();
	ui.stackedWidget->setCurrentIndex(page);
}

void MainWin::setupTestConfPage() {
	loader("Fetching test configure data");
	auto confData = ObjectFactory::getInstance<TestConfigData>();

	confData->setOnDataReadyCallback([this](bool success, const QString & comment) {
		if (success) {
			loadTestConfPage();
		}
		else {
			ui.stackedWidget->setCurrentIndex(PagesEnum::LOG_IN);
			showError(comment);
		}
		loaderStop();
	});

	confData->perpareData();
}

void MainWin::loadTestConfPage() {
	clearTestConfPage();
	auto confData = ObjectFactory::getInstance<TestConfigData>();
	ui.CTComboSerialPort->addItems(confData->getComsList());
	ui.CTComboBattLeft->addItems(confData->getBatteriesLeftList());
	ui.CTComboBattRight->addItems(confData->getBatteriesRightList());
	ui.CTSimTreeRaces->setAnimated(true);
	ui.CTSimTreeRaces->addTopLevelItems(confData->getLogsTreeItems());
	ui.stackedWidget->setCurrentIndex(PagesEnum::CONF_TEST);
}

void MainWin::clearTestConfPage() {
	clearChildrens<QLineEdit>(ui.confTestPage);
	clearChildrens<QComboBox>(ui.confTestPage, "CTCombo.*");
	clearChildrens<QTreeWidget>(ui.confTestPage);
	ui.CTSimRadioCollapse->setChecked(true);
}

void MainWin::prepareNewTest() {
	loader("Setting up a device");
	if (!setupDevice())
		showPage(PagesEnum::CONF_TEST);
}

bool MainWin::setupDevice() {
	QString com					{ ui.CTComboSerialPort->currentText() };
	QString voltageLimit		{ ui.CTEdtVoltLim->text() };
	QString heatSinkTempLimit	{ ui.CTEdtTempLim->text().isEmpty() ? "0" : ui.CTEdtTempLim->text() };
	int numOfBatt{
		ui.CTComboBattRight->currentText() == "-1" ? 1 : 2
	};
	//if (ifEmptyShowWarning(com, "Com port")) return false;
	if (ifEmptyShowWarning(voltageLimit, "Voltage limit")) return false;
	if (ifEmptyShowWarning(heatSinkTempLimit, "Heat Sink temperature limit")) return false;

	switch (ui.CTToolBoxTestType->currentIndex()) {
		case TestType::SIMULATION: {
			/*
				Data to DischargerDevice:
					com, voltLim, tempLim, currSource, idLogInfo
			*/
			auto selected = ui.CTSimTreeRaces->selectedItems();
			if (selected.size() != 1) {
				showWarning("A log session must be selected from the tree view!");
				return false;
			}
			QString idLogInfo{ selected.front()->text(TREE_ID_LOG_INFO_COL_NUM) };
			DeviceInterface::CurrentSource currSource{ (
				ui.CTSimRadioCurrSourceMotor->isChecked() ?
				DeviceInterface::CurrentSource::MOTOR :
				DeviceInterface::CurrentSource::MAIN
			) };
			auto dev = new DischargerDevice{ testDriver, com, currSource };
			dev->setVoltageLimit(voltageLimit.toFloat());
			dev->setHeatSinkTempLimit(heatSinkTempLimit.toFloat());
			testDriver->setDevice(dev);
			if (!dev->checkBatteryNumber(numOfBatt)) {
				showError("Invalid number of batteries");
				testDriver->removeDevice();
				showPage(PagesEnum::CONF_TEST);
				return false;
			}
			dev->fetchCurrentToTest(idLogInfo.toInt(), [this](bool success, const QString & comment) {
				if (success) {
					setupTestDriver();
				}
				else {
					showError(comment);
					testDriver->removeDevice();
					showPage(PagesEnum::CONF_TEST);
				}
			});
			break;
		}
		case TestType::BASIC_TEST: {
			/*
				Data to DischargerDevice:
					com, voltLim, tempLim, currSource, testCurr
			*/
			auto testCurrStr{ ui.CTBasicEdtTestCurr->text() };
			if (ifEmptyShowWarning(testCurrStr, "Test current")) return false;
			auto dev = new DischargerDevice{ testDriver, com, DeviceInterface::CurrentSource::NO_CURR_SOURCE };
			dev->setTestCurrent(testCurrStr.toFloat());
			dev->setVoltageLimit(voltageLimit.toFloat());
			dev->setHeatSinkTempLimit(heatSinkTempLimit.toFloat());
			testDriver->setDevice(dev);
			if (!dev->checkBatteryNumber(numOfBatt)) {
				showError("Invalid number of batteries");
				testDriver->removeDevice();
				showPage(PagesEnum::CONF_TEST);
				return false;
			}
			setupTestDriver();
			break;
		}
		case TestType::DEV_TERMINAL: {
			// TODO: Other devices
			/*
				Data to DischargerDevice:
					com, voltLim, tempLim, buadrate, parity, data bits, stop bits, mask, currentRatio
			*/
			break;
		}
		default:
			break;
	}
	return true;
}

void MainWin::setupTestDriver() {
	loader("Setting up the test driver");

	QString name			{ ui.CTEdtTestName->text() };
	int idBattLeft			{ ui.CTComboBattLeft->currentText().toInt() };
	int idBattRight			{ ui.CTComboBattRight->currentText().toInt() };
	QString filepathToLog	{ ui.CTEdtFileName->text() };

	if (ifEmptyShowWarning(name, "Test name")) {}
	else if (idBattLeft == idBattRight) {
		showError("Id of battery left and right can not be equal");
	}
	else {
		// TODO: Setup db record


		testDriver->setTestName(name);
		testDriver->setIdBattLeft(idBattLeft);
		testDriver->setIdBattRight(idBattRight);
		testDriver->setFilepathToLog(filepathToLog);
		showTestPage();

		return;
	}
	testDriver->removeDevice();
	showPage(PagesEnum::CONF_TEST);
}

void MainWin::showTestPage() {
	testDriver->loadPageData();
	showPage(PagesEnum::TEST);
}

void MainWin::showTestConfPage() {
}


void MainWin::loader(const QString & msg) {
	QMovie * mv = ui.loaderLblMovie->movie();
	if (mv == nullptr) {
		mv = new QMovie("media/load.gif");
		mv->setScaledSize(QSize(180, 180));
		ui.loaderLblMovie->setMovie(mv);
	}
	if (ui.stackedWidget->currentIndex() != PagesEnum::LOADER)
		ui.stackedWidget->setCurrentIndex(PagesEnum::LOADER);
	ui.loaderLblStatus->setText(msg);
	mv->start();
}

void MainWin::loaderStop() {
	ui.loaderLblStatus->setText("");
	ui.loaderLblMovie->movie()->stop();
}



void MainWin::testStart() {
	ui.toolBarTest->actions()[TestActions::START]->setVisible(false);
	ui.toolBarTest->actions()[TestActions::STOP]->setVisible(true);
	// TODO: Test start
}

void MainWin::testStop() {
	ui.toolBarTest->actions()[TestActions::STOP]->setVisible(false);
	ui.toolBarTest->actions()[TestActions::NEW_TEST]->setVisible(true);
	// TODO: Test stop
}

void MainWin::configureNewTest() {

}

bool MainWin::ifEmptyShowWarning(const QString & toCheck, const QString & name)
{
	if (toCheck.isEmpty()) showWarning(name + " must be filled up!");
	return toCheck.isEmpty();
}

void MainWin::showWarning(const QString & msg) {
	QMessageBox::warning(this, "Warning", msg);
}

void MainWin::showError(const QString & msg) {
	QMessageBox::critical(this, "Error", msg);
}

void MainWin::testFinised() {
	testStop();
}

void MainWin::clearParameters() {
	clearChildrens<QLineEdit>(ui.dockWgtParams);
	clearChildrens<QProgressBar>(ui.dockWgtParams);
	clearChildrens<QLabel>(ui.dockWgtParams, ".*Lbl.*");
}

void MainWin::setTestPatametersData(const TestParametersData & data) {
	ui.parLblName->setText(data.getTestName());
	ui.parLblStatus->setText(data.getTestStatus());
	ui.parProgBar->setValue(data.getProgress());
	if (!ui.parVarEdtCurr->isEnabled())
		ui.parVarEdtCurr->setText(data.getTestCurrent());
	ui.parTimeLblBeg->setText(data.getTestBeganAt());
	ui.parTimeLblEstEnd->setText(data.getTestEstimatedEnd());
	ui.parTimeLblTestTime->setText(data.getTestTime());
	ui.parTimeLblEstTime->setText(data.getEstimatedTime());
	ui.parCalcLblCapa->setText(data.getCapacity());
	ui.parCalcLblEnergy->setText(data.getConsumedEnergy());
	if (data.isSingleBatteryMode()) {
		ui.parMeasure1BLblHeatSinkTemp->setText(data.getHeatSinkTemp());
		ui.parMeasure1BLblCurr->setText(data.getCurrent());
		ui.parMeasure1BLblId->setText(data.getBattLeftId());
		ui.parMeasure1BLblVolt->setText(data.getBattLeftVolt());
		ui.parMeasure1BLblTemp->setText(data.getBattLeftTemp());
		ui.parMeasureStackedWgt->setCurrentIndex(MeasureSchem::SINGLE_BATT);
	}
	else {
		ui.parMeasure2BLblHeatSinkTemp->setText(data.getHeatSinkTemp());
		ui.parMeasure2BLblCurr->setText(data.getCurrent());
		ui.parMeasure2BLblLeftId->setText(data.getBattLeftId());
		ui.parMeasure2BLblLeftVolt->setText(data.getBattLeftVolt());
		ui.parMeasure2BLblLeftTemp->setText(data.getBattLeftTemp());
		ui.parMeasure2BLblRightId->setText(data.getBattRightId());
		ui.parMeasure2BLblRightVolt->setText(data.getBattRightVolt());
		ui.parMeasure2BLblRightTemp->setText(data.getBattRightTemp());
		ui.parMeasureStackedWgt->setCurrentIndex(MeasureSchem::DOUBLE_BATT);
	}
}

void MainWin::setTestCurrentLineEditEnabled(bool enabled) {
	ui.parVarEdtCurr->setEnabled(enabled);
}

void MainWin::setVarTestCurrent(const QString & curr) {
	ui.parVarEdtCurr->setText(curr);
}

void MainWin::setVarVoltLimit(const QString & volt) {
	ui.parVarEdtVolLim->setText(volt);
}

void MainWin::setVarHeatSinkTempLimit(const QString & temp) {
	ui.parVarEdtTempLim->setText(temp);
}

void MainWin::appendTestDataLine(const QString & line) {
	appendLineToTextBrowser(
		ui.commFlowTabTestDataTxtBrow,
		line,
		ui.commFlowTabTestDataChckScroll->isChecked()
	);
}

void MainWin::appendEventsLine(const QString & line) {
	appendLineToTextBrowser(
		ui.commFlowTabEventsTxtBrow,
		line,
		ui.commFlowTabEventsChckScroll->isChecked()
	);
}

void MainWin::appendRawDataLine(const QString & line) {
	appendLineToTextBrowser(
		ui.commFlowTabRawDataTxtBrow,
		line,
		ui.commFlowTabRawDataChckScroll->isChecked()
	);
}

void MainWin::setChart(QWidget * chart) {
	ui.testFrameConfChart->hide();
	ui.testPageLayout->addWidget(chart);
}

void MainWin::removeChart(QWidget * chart) {
	ui.testPageLayout->removeWidget(chart);
	ui.testFrameConfChart->show();
}

void MainWin::appendLineToTextBrowser(QTextBrowser * brow, const QString & line, bool scrollDown) {
	brow->setHtml(
		brow->toHtml() +
		line + "<br>"
	);
	if (scrollDown) {
		QScrollBar *sb = brow->verticalScrollBar();
		sb->setValue(sb->maximum());
	}
}
