#include "MainWin.h"
#include "ObjectFactory.h"
#include "User.h"
#include "TestConfigData.h"
#include <QMessageBox>
#include <QTreeWidget>
#include <QMovie>
#include <QScrollBar>

MainWin::MainWin(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setDockedWidgetsVisibility(false);
	//setTestToolBarVisibility(false);

	ObjectFactory::createInstance(new WebApi(this));
	ObjectFactory::createInstance(new User(this));
	ObjectFactory::createInstance(new TestConfigData(this));

	//ui.stackedWidget->setCurrentIndex(PagesEnum::LOG_IN);


	setupMainToolBar();
	setupTestToolBar();


	connect(ui.authBtnLogIn, &QPushButton::clicked, this, &MainWin::login);
	connect(ui.CTBtnConn, &QPushButton::clicked, this, &MainWin::prepareNewTest);

	//connect(ui.stackedWidget, &QStackedWidget::currentChanged, this, &MainWin::currentPageChannged);

}

void MainWin::setDockedWidgetsVisibility(bool visible)
{
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

void MainWin::setupMainToolBar()
{
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
	ui.toolBarTest->addAction(QIcon("media/icons/chart.ico"), "Chart", [] {
		// TODO: Chart settings
	});
	ui.toolBarTest->addSeparator();
	ui.toolBarTest->addAction(QIcon("media/icons/web.ico"), "Results on-line", [] {
		// TODO: Reference to results on-line
	});
	ui.toolBarTest->addAction(QIcon("media/icons/qr_code.ico"), "QR Code", [] {
		// TODO: Qr code reference to results on-line
	});
	ui.toolBarTest->addSeparator();
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
	clearChildrens<QComboBox>(ui.confTestPage, "CTCombo*");
	clearChildrens<QTreeWidget>(ui.confTestPage);
	ui.CTSimRadioCollapse->setChecked(true);
}

void MainWin::prepareNewTest() {
	QString name				{ ui.CTEdtTestName->text() };
	QString com					{ ui.CTComboSerialPort->currentText() };
	QString voltageLimit		{ ui.CTEdtVoltLim->text() };
	QString heatSilkTempLimit	{ ui.CTEdtTempLim->text() };
	QString idBattLeft			{ ui.CTComboBattLeft->currentText() };
	QString idBattRight			{ ui.CTComboBattRight->currentText() };
	QString fileToLogPath		{ ui.CTEdtFileName->text() };

	if (ifEmptyShowWarning(name, "Test name")) return;
	//if (ifEmptyShowWarning(com, "Com port")) return;
	if (ifEmptyShowWarning(voltageLimit, "Voltage limit")) return;
	if (ifEmptyShowWarning(heatSilkTempLimit, "Heat silk temperature limit")) return;
	if (ifEmptyShowWarning(idBattLeft, "Id battery left")) return;

	switch (ui.CTToolBoxTestType->currentIndex()) {
	case TestType::SIMULATION: {

			auto selected = ui.CTSimTreeRaces->selectedItems();
			if (selected.size() != 1) {
				showWarning("You must select one log session from the tree view!");
				return;
			}
			QString idLogInfo{ selected.front()->text(TREE_ID_LOG_INFO_COL_NUM) };

					   
			break;
		}
		case TestType::BASIC_TEST: {

			break;
		}
		case TestType::DEV_TERMINAL: {

			break;
		}
		default:
			break;
	}
}


void MainWin::showTestConfPage() {

}

void MainWin::showTestPage() {

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
	//ui.toolBarTest->actions()[TestActions::START]->setVisible(false);
	//ui.toolBarTest->actions()[TestActions::STOP]->setVisible(true);
	// TODO: Test start

	static QPushButton * btn = nullptr;
	if (btn == nullptr) {
		btn = new QPushButton("Hi");
		setChart(btn);
	}
	else {
		removeChart(btn);
		delete btn;
		btn = nullptr;
	}
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
	ui.parTimeLblBeg->setText(data.getTestBeginedAt());
	ui.parTimeLblEstEnd->setText(data.getTestEstimatedEnd());
	ui.parTimeLblTestTime->setText(data.getTestTime());
	ui.parTimeLblEstEnd->setText(data.getTestEstimatedEnd());
	ui.parCalcLblCapa->setText(data.getCapacity());
	ui.parCalcLblEnergy->setText(data.getConsumedEnergy());
	if (data.isSingleBatteryMode()) {
		ui.parMeasure1BLblHeatSilkTemp->setText(data.getHeatSilkTemp());
		ui.parMeasure1BLblCurr->setText(data.getCurrent());
		ui.parMeasure1BLblId->setText(data.getBattLeftId());
		ui.parMeasure1BLblVolt->setText(data.getBattLeftVolt());
		ui.parMeasure1BLblTemp->setText(data.getBattLeftTemp());
		ui.parMeasureStackedWgt->setCurrentIndex(MeasureSchem::SINGLE_BATT);
	}
	else {
		ui.parMeasure2BLblHeatSilkTemp->setText(data.getHeatSilkTemp());
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
