#include "MainWin.h"
#include "ObjectFactory.h"
#include "DischargerDevice1.h"
#include "DischargerDevice.h"
#include "SerialPort.h"
#include "User.h"
#include "TestConfigData.h"
#include "TestDriver.h"
#include "DbTestData.h"
#include <QMessageBox>
#include <QTreeWidget>
#include <QMovie>
#include <QScrollBar>
#include <QCloseEvent>


using namespace serialPort;

// TODO: about to close, check if test is in progress

MainWin::MainWin(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setDockedWidgetsVisibility(false);
	this->showMaximized();

	ObjectFactory::createInstance(new WebApi(this));
	ObjectFactory::createInstance(new User(this));
	ObjectFactory::createInstance(new TestConfigData(this));
	ObjectFactory::createInstance(new TestDriver(this));
	ObjectFactory::createInstance(new SerialPort(this));
	ObjectFactory::createInstance(new db::TestData(this));
	//ObjectFactory::createInstance(new dischargerDevice::Device(this));
	
	auto serial_ = ObjectFactory::getInstance<SerialPort>();	



	testDriver = ObjectFactory::getInstance<TestDriver>();

	ui.stackedWidget->setCurrentIndex(PagesEnum::LOG_IN);

	setupTestToolBar();
	setTestToolBarVisibility(false);

	connect(ui.dockWgtCommFlow, &QDockWidget::topLevelChanged, this, &MainWin::dockedWgtTopLevelChanged);
	connect(ui.dockWgtParams, &QDockWidget::topLevelChanged, this, &MainWin::dockedWgtTopLevelChanged);


	connect(ui.authPage, &LoginWgt::loggedOut, this, &MainWin::userLoggedOut);
	connect(ui.authPage, &LoginWgt::loggedIn, this, &MainWin::userLoggedIn);
	connect(ui.authPage, &LoginWgt::authorizing, this, &MainWin::loader);


	//connect(ui.authBtnLogIn, &QPushButton::clicked, this, &MainWin::login);
	connect(ui.CTBtnConn, &QPushButton::clicked, this, &MainWin::prepareNewTest);
	connect(ui.CTBtnRefreshSerialPort, &QPushButton::clicked, this, &MainWin::refreshComPortsList);
	connect(ui.testBtnConfChart, &QPushButton::clicked, testDriver, &TestDriver::confChart);

	connect(ui.parVarEdtCurr, &QLineEdit::editingFinished, this, &MainWin::handleTestCurrEdited);
	connect(ui.parVarEdtVolLim, &QLineEdit::editingFinished, this, &MainWin::handleVoltLimitEdited);
	connect(ui.parVarEdtTempLim, &QLineEdit::editingFinished, this, &MainWin::handleHeatSinkTempLimitEdited);

	connect(ui.CTBtnSelectFile, &QPushButton::clicked, this, &MainWin::selectFile);

	connect(serial_, &SerialPort::opened, this, &MainWin::serialOpened);
	connect(serial_, &SerialPort::closed, this, &MainWin::serialClosed);
	connect(serial_, &SerialPort::receivedLine, this, &MainWin::serialReceivedLine);
	connect(serial_, &SerialPort::transmitedLine, this, &MainWin::serialTransmitedLine);
	
	connect(ui.actionLogout, &QAction::triggered, this, &MainWin::logout);

	//ui.page.

	//ui.stackedWidget->setCurrentIndex(1);

	/*

	connect(ui.dockWgtCommFlow, &QDockWidget::dockLocationChanged, [](Qt::DockWidgetArea area) {
	
		qDebug() << area;
	
	});

	qDebug() << ui.dockWgtCommFlow->windowFlags();
	

	connect(ui.dockWgtCommFlow, &QDockWidget::topLevelChanged, [this](bool b) {

		qDebug() << ui.dockWgtCommFlow->windowFlags();
		if (b) {
			ui.dockWgtCommFlow->setWindowFlags(Qt::CustomizeWindowHint |
				Qt::Window | Qt::WindowMinimizeButtonHint |
				Qt::WindowMaximizeButtonHint |
				Qt::WindowCloseButtonHint);
			ui.dockWgtCommFlow->show();

		}
		else {
			ui.dockWgtCommFlow->setWindowFlags(Qt::WindowTitleHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint | Qt::WindowFullscreenButtonHint);
			ui.dockWgtCommFlow->show();
		}
		qDebug() << b;
	});
	
	ChartPropertiesDialog * ch = new ChartPropertiesDialog(this);

	ch->show();
	ch->setSeries({ 
		{ true, "Current", QColor("red") },
		{ false, "Test current", QColor("blue") },
		{ false, "Battery left voltage", QColor("yellow") },
		{ true, "Battery right voltage", QColor("green") },
		{ false, "Heat sink temp", QColor("black") }
	});
	//connect(ui.stackedWidget, &QStackedWidget::currentChanged, this, &MainWin::currentPageChannged);


	/*
	auto Dcoms = ObjectFactory::getInstance<TestConfigData>();
	Dcoms->refreshComs();
	auto coms = Dcoms->getComsList();
	serial_->setPort(coms.at(0).toStdString());
	serial_->setBaudrate(57600);
	serial_->open();
	serial_->println(QString("{\"handshake\":\"PC\"}"));
	*/

	/*
	
	auto ds = ObjectFactory::getInstance<dischargerDevice::Device>();
	ds->connectToDevice("COM9");

	QMessageBox::information(this, "", "Device id " + QString::number(ds->getDeviceId()) + ", software version " + QString::number(ds->getDeviceSoftwareVersion()) + " flash date %3.");

	ds->sendStop();
	ds->disconnectDevice();
	*/
}

void MainWin::closeEvent(QCloseEvent * event) {
	// TODO: Is test in progress
	if (testDriver->getTestState() == db::TestStates::PROGRESS) {
		showWarning("Test in progress you can not close the program");
		event->ignore();
		return;
	}
	if (testDriver->getTestState() == db::TestStates::READY) {
		if (showQuestionBox("Do you really want to discard this configuration?") == false) {
			event->ignore();
			return;
		}
	}
	event->accept();
}

void MainWin::setDockedWidgetsVisibility(bool visible) {
	ui.dockWgtParams->setVisible(visible);
	ui.dockWgtCommFlow->setVisible(visible);
}

void MainWin::dockedWgtTopLevelChanged(bool) {
	QDockWidget* dw = static_cast<QDockWidget*>(QObject::sender());
	if (dw->isFloating()) {
		dw->setWindowFlags(Qt::CustomizeWindowHint |
			Qt::Window | Qt::WindowMinimizeButtonHint |
			Qt::WindowMaximizeButtonHint |
			Qt::WindowCloseButtonHint);
		dw->show();
	}
	else {
		dw->setWindowFlags(Qt::WindowTitleHint | 
			Qt::WindowSystemMenuHint | 
			Qt::WindowMinMaxButtonsHint | 
			Qt::WindowCloseButtonHint | 
			Qt::WindowFullscreenButtonHint);
		dw->show();
	}
}

void MainWin::setTestToolBarVisibility(bool visible) {
	ui.toolBarTest->setVisible(visible);
}

void MainWin::logout() {
	//TODO: Is test in progess?
	if (testDriver->getTestState() == db::TestStates::PROGRESS) {
		showWarning("Test in progress you can not log out"); 
		return;
	}
	//TODO: Has test finished?
	if (testDriver->getTestState() == db::TestStates::READY) {
		if (showQuestionBox("Do you really want to discard this configuration?") == false) return;
	}

	ui.authPage->logOut();
}

void MainWin::userLoggedOut() {
	ui.stackedWidget->setCurrentIndex(PagesEnum::LOG_IN);
	// Todo: clear
	setTestToolBarVisibility(false);
	setDockedWidgetsVisibility(false);
	clearTestConfPage();
	clearTestPage();
	testDriver->clear();
}

void MainWin::userLoggedIn() {
	//showPage(PagesEnum::CONF_TEST);
	//setupTestConfPage();
	ui.menuPage->setup();
	showPage(PagesEnum::MENU);
}


void MainWin::setupTestToolBar() {
	connect(ui.actionStart, &QAction::triggered, this, &MainWin::testStart);
	connect(ui.actionStop, &QAction::triggered, this, &MainWin::testStop);
	connect(ui.actionConfNewTest, &QAction::triggered, this, &MainWin::configureNewTest);

	connect(ui.actionShowTestParams, &QAction::triggered, ui.dockWgtParams, &QDockWidget::show);
	connect(ui.actionShowCommFlow, &QAction::triggered, ui.dockWgtCommFlow, &QDockWidget::show);
	connect(ui.actionConfChart, &QAction::triggered, testDriver, &TestDriver::confChart);

	connect(ui.actionResultsOnline, &QAction::triggered, [] {});
	connect(ui.actionQrCode, &QAction::triggered, [] {});
}

void MainWin::testToolBarAboutToStart()
{
	ui.actionStart->setVisible(true);
	ui.actionStop->setVisible(false);
	ui.actionConfNewTest->setVisible(true);
}

void MainWin::testToolBarAboutToStop() {
	ui.actionStart->setVisible(false);
	ui.actionStop->setVisible(true);
	ui.actionConfNewTest->setVisible(false);
}

void MainWin::testToolBarAboutToNewTest() {
	ui.actionStart->setVisible(false);
	ui.actionStop->setVisible(false);
	ui.actionConfNewTest->setVisible(true);
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
			showTestConfPage();
		}
		else {
			ui.stackedWidget->setCurrentIndex(PagesEnum::LOG_IN);
			showError(comment);
		}
		loaderStop();
	});

	confData->perpareData();
}

void MainWin::showTestConfPage() {
	clearTestConfPage();
	auto confData = ObjectFactory::getInstance<TestConfigData>();
	refreshComPortsList();
	ui.CTComboBattLeft->addItems(confData->getBatteriesLeftList());
	ui.CTComboBattRight->addItems(confData->getBatteriesRightList());
	ui.CTSimTreeRaces->setAnimated(true);
	ui.CTSimTreeRaces->addTopLevelItems(confData->getLogsTreeItems());

	ui.stackedWidget->setCurrentIndex(PagesEnum::CONF_TEST);
}

void MainWin::refreshComPortsList() {
	ui.CTComboSerialPort->clear();
	auto confData = ObjectFactory::getInstance<TestConfigData>();
	confData->refreshComs();
	ui.CTComboSerialPort->addItems(confData->getComsList());
}

void MainWin::clearTestConfPage() {
	clearChildrens<QLineEdit>(ui.confTestPage);
	clearChildrens<QComboBox>(ui.confTestPage, "CTCombo.*");
	clearChildrens<QTreeWidget>(ui.confTestPage);
	ui.CTSimRadioCollapse->setChecked(true);
}

void MainWin::prepareNewTest() {
	loader("Setting up a device");
	if (!setupDeviceInterface())
		showPage(PagesEnum::CONF_TEST);
}

bool MainWin::setupDeviceInterface() {
	QString com					{ ui.CTComboSerialPort->currentText() };
	QString voltageLimit		{ ui.CTEdtVoltLim->text() };
	QString heatSinkTempLimit	{ ui.CTEdtTempLim->text().isEmpty() ? "0" : ui.CTEdtTempLim->text() };
	int numOfBatt{
		ui.CTComboBattRight->currentText() == "-1" ? 1 : 2
	};
	if (ifEmptyShowWarning(com, "Com port")) return false;
	if (ifEmptyShowWarning(voltageLimit, "Voltage limit")) return false;
	if (ifEmptyShowWarning(heatSinkTempLimit, "Heat Sink temperature limit")) return false;

	switch (ui.CTToolBoxTestType->currentIndex()) {
		case db::TestType::SIMULATION: {
			/*
				Data to DischargerDevice1:
					com, voltLim, tempLim, currSource, idLogInfo
			*/
			auto selected = ui.CTSimTreeRaces->selectedItems();
			if (selected.size() != 1) {
				showWarning("A log session must be selected from the tree view!");
				return false;
			}
			QString idLogInfo{ selected.front()->text(TREE_ID_LOG_INFO_COL_NUM) };
			db::CurrentSource currSource{ (
				ui.CTSimRadioCurrSourceMotor->isChecked() ?
				db::CurrentSource::MOTOR :
				db::CurrentSource::MAIN
			) };
			auto dev = new DischargerDevice1{ testDriver, com, db::TestType::SIMULATION, currSource };
			dev->setVoltageLimit(voltageLimit.toFloat());
			dev->setHeatSinkTempLimit(heatSinkTempLimit.toFloat());
			testDriver->setDevice(dev);
			if (!dev->checkBatteryNumber(numOfBatt)) {
				rollbackTestConf("Invalid number of batteries");
				return false;
			}
			dev->fetchCurrentToTest(idLogInfo.toInt(), [this](bool success, const QString & comment) {
				if (success) {
					setupTestDriver();
				}
				else {
					rollbackTestConf(comment);
				}
			});
			break;
		}
		case db::TestType::BASIC_TEST: {
			/*
				Data to DischargerDevice1:
					com, voltLim, tempLim, currSource, testCurr
			*/
			auto testCurrStr{ ui.CTBasicEdtTestCurr->text() };
			if (ifEmptyShowWarning(testCurrStr, "Test current")) return false;
			auto dev = new DischargerDevice1{ testDriver, com, db::TestType::BASIC_TEST, db::CurrentSource::NO_CURR_SOURCE };
			dev->setTestCurrent(testCurrStr.toFloat());
			dev->setVoltageLimit(voltageLimit.toFloat());
			dev->setHeatSinkTempLimit(heatSinkTempLimit.toFloat());
			testDriver->setDevice(dev);
			if (!dev->checkBatteryNumber(numOfBatt)) {
				rollbackTestConf("Invalid number of batteries");
				return false;
			}
			setupTestDriver();
			break;
		}
		case db::TestType::DEV_TERM: {
			// TODO: Other devices
			/*
				Data to DischargerDevice1:
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
	bool jsonLogFile		{ ui.CTEdtFileName->property("JSON_FILE").value<bool>() };

	if (ifEmptyShowWarning(name, "Test name")) {}
	else if (idBattLeft == idBattRight) {
		rollbackTestConf("Id of battery left and right can not be equal");
		return;
	}

	testDriver->setTestName(name);
	testDriver->setIdBattLeft(idBattLeft);
	testDriver->setIdBattRight(idBattRight);
	if(!filepathToLog.isEmpty())
		testDriver->setFilepathToLog(filepathToLog, jsonLogFile);
	establishConnectionToDevice();
}

void MainWin::establishConnectionToDevice() {
	loader("Establishing connection to the device");
	auto device = testDriver->getDevice();
	connect(device.get(), &DeviceInterface::signalConnectionEstablished, [this] {
		setupDbForTest();
	});
	connect(device.get(), &DeviceInterface::signalCanNotEstablishConnection, [this] {
		rollbackTestConf("Can not establish connection.");
	});
	device->connectToDevice();
}

void MainWin::setupDbForTest() {
	loader("Prepering database");
	testDriver->setupTestInDb([this](bool success, const QString & comment) {
		if (success)
			showTestPage();
		else
			rollbackTestConf(comment);
	});
}

void MainWin::rollbackTestConf(const QString & rollbackMsg){
	showError(rollbackMsg);
	testDriver->removeDevice();
	showPage(PagesEnum::CONF_TEST);
}

void MainWin::showTestPage() {
	testDriver->loadPageData();
	setTestToolBarVisibility(true);
	showPage(PagesEnum::TEST);
	if (testDriver->getDevice()->isStartable()) {
		testToolBarAboutToStart();
	}
	else {
		testToolBarAboutToStop();
	}
}

void MainWin::clearTestPage() {
	clearParameters();
	testDriver->clear();
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
	testToolBarAboutToStop();
	testDriver->startTest();
}

void MainWin::testStop() {
	if (testDriver->getTestState() == db::TestStates::PROGRESS) {
		if (showQuestionBox("Do you really want to stop test?") == false) return;
	}
	testToolBarAboutToNewTest();
	testDriver->stopTest();
}

void MainWin::configureNewTest() {
	if (testDriver->getTestState() == db::TestStates::READY) {
		if (showQuestionBox("Do you really want to discard this configuration?") == false) return;
	}

	clearTestPage();
	testDriver->clear();
	setTestToolBarVisibility(false);
	setDockedWidgetsVisibility(false);
	showTestConfPage();
}

bool MainWin::ifEmptyShowWarning(const QString & toCheck, const QString & name)
{
	if (toCheck.isEmpty()) showWarning(name + " must be filled up!");
	return toCheck.isEmpty();
}

void MainWin::showWarning(const QString & msg) {
	QMessageBox::warning(this, "Warning", msg);
}

void MainWin::showDeviceError(const QString & msg) {
	testToolBarAboutToNewTest();
	QMessageBox::critical(this, "Device error", msg);
}

void MainWin::showError(const QString & msg) {
	QMessageBox::critical(this, "Error", msg);	testToolBarAboutToNewTest();
}

bool MainWin::showQuestionBox(const QString & text) {
	return QMessageBox::question(this, "One question", text, QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes;
}

void MainWin::testFinised() {
	testToolBarAboutToNewTest();
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
	brow->append(line);
	if (scrollDown) {
		QScrollBar *sb = brow->verticalScrollBar();
		sb->setValue(sb->maximum());
	}
}

void MainWin::serialOpened() {
	appendLineToTextBrowser(
		ui.commFlowTabRawDataTxtBrow,
		"<div style=\"text-align: center;\">Port opened<div>",
		ui.commFlowTabRawDataChckScroll->isChecked()
	);
}

void MainWin::serialClosed() {
	appendLineToTextBrowser(
		ui.commFlowTabRawDataTxtBrow,
		"<div style=\"text-align: center;\">Port closed<div>",
		ui.commFlowTabRawDataChckScroll->isChecked()
	);
}

void MainWin::serialReceivedLine(const QString & line) {
	appendLineToTextBrowser(
		ui.commFlowTabRawDataTxtBrow,
		"<div style=\"text-align: left;\">" + line +"<div>",
		ui.commFlowTabRawDataChckScroll->isChecked()
	);
}

void MainWin::serialTransmitedLine(const QString & line) {
	appendLineToTextBrowser(
		ui.commFlowTabRawDataTxtBrow,
		"<div style=\"text-align: right;\">" + line + "<div>",
		ui.commFlowTabRawDataChckScroll->isChecked()
	);
}

void MainWin::handleTestCurrEdited() {
	if (testDriver->getTestState() < db::TestStates::COMPLETED) {
		testDriver->getDevice()->setTestCurrent(ui.parVarEdtCurr->text().toFloat());
	}
}

void MainWin::handleVoltLimitEdited() {
	if (testDriver->getTestState() < db::TestStates::COMPLETED) {
		testDriver->getDevice()->setVoltageLimit(ui.parVarEdtVolLim->text().toFloat());
	}
}

void MainWin::handleHeatSinkTempLimitEdited() {
	if (testDriver->getTestState() < db::TestStates::COMPLETED) {
		testDriver->getDevice()->setHeatSinkTempLimit(ui.parVarEdtTempLim->text().toFloat());
	}
}

void MainWin::selectFile() {
	QString filter = "";
	QString fileName = QFileDialog::getSaveFileName(this, tr("Log to file"),
		QStandardPaths::writableLocation(QStandardPaths::DesktopLocation),
		tr("Text file (*.txt);;Comma separated file (*.csv);;JSON file (*.json)"), &filter);

	bool jsonFile = filter.toLower().indexOf("json") != -1;
	ui.CTEdtFileName->setText(fileName);
	ui.CTEdtFileName->setProperty("JSON_FILE", jsonFile);
}
