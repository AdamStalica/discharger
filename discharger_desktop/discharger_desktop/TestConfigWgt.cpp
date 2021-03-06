#include "TestConfigWgt.h"
#include "ObjectFactory.h"
#include "SerialPort.h"
#include "Cleaner.h"
#include "DeviceInterface.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QStandardPaths>

TestConfigWgt::TestConfigWgt(QWidget *parent)
	: QWidget(parent),
	  testConfData(this)
{
	ui.setupUi(this);
	testConfData.setOnDataReadyCallback([this](bool s, const QString & msg) {
		dataReadyCallback(s, msg);
	});
	ui.simTreeRaces->setAnimated(true);
	connect(ui.btnRefreshSerialPort, &QPushButton::clicked, this, &TestConfigWgt::handleRefreshPortsList);
	connect(ui.btnSelectFile, &QPushButton::clicked, this, &TestConfigWgt::handleSelectFile);
	connect(ui.btnCancel, &QPushButton::clicked, this, &TestConfigWgt::handleCancel);
	connect(ui.btnPrepTest, &QPushButton::clicked, this, &TestConfigWgt::handlePrepareTest);

	//TODO: add validators ^\d+(.\d+)?$
}

void TestConfigWgt::clear() {
	Cleaner::clearChildrens<QLineEdit>(this);
	Cleaner::clearChildrens<QComboBox>(this);
	Cleaner::clearChildrens<QTreeWidget>(this);
	ui.simRadioCollapse->setChecked(true);
	testName = comPort = logFileName = "";
	voltLimit = heatSinkTempLimit = testCurrent = 0.0;
	idLeftBatt = idRightBatt = idLogInfo = 0;
	currSource = db::CurrentSource::NO_CURR_SOURCE;
	testType = db::TestType::BASIC_TEST;
	logFileFormat = FileLogger::NONE;
	dev.reset();
}

QString TestConfigWgt::getTestName() {
	return testName;
}

bool TestConfigWgt::hasFileLogger() {
	return logFileFormat != FileLogger::NONE;
}

QSharedPointer<FileLogger> TestConfigWgt::getFileLogger() {
	return QSharedPointer<FileLogger>(
		new FileLogger(this, logFileName, logFileFormat)
	);
}

QSharedPointer<DeviceInterface> TestConfigWgt::getDevice() {
	return dev;
}

void TestConfigWgt::reloadPage() {
	clear();
	loadPageData();
}

void TestConfigWgt::setup() {
	emit setupState(tr("Fetching test configure data"));
	testConfData.perpareData();
}

void TestConfigWgt::handleRefreshPortsList() {
	auto portsNamesList = ObjectFactory::getInstance<serialPort::SerialPort>()->getPortsNames();
	ui.comboSerialPort->clear();
	ui.comboSerialPort->addItems(portsNamesList);
}

void TestConfigWgt::handleSelectFile() {
	QString selectedFilter;
	QString filter = FileLogger::getLogFilesFormatsFilter();
	QString fileName = QFileDialog::getSaveFileName(this, tr("Log to file"),
		QStandardPaths::writableLocation(QStandardPaths::DesktopLocation),
		filter, &selectedFilter);

	logFileFormat = FileLogger::getLogFileFormatId(selectedFilter);
	logFileName = fileName;
	// TODO: change to not allowed to edit
	ui.edtFileName->setText(fileName);
}

void TestConfigWgt::handleCancel() {
	auto ans = QMessageBox::question(
		this, 
		tr("Confirm"), 
		tr("Do you really want to discard the configuration of a new test?"), 
		QMessageBox::Yes,
		QMessageBox::No
	);
	if (ans == QMessageBox::Yes)
		emit canceled();
}

void TestConfigWgt::dataReadyCallback(bool success, const QString & msg) {
	if (success) {
		loadPageData();
		emit setupDone();
	}
	else {
		QMessageBox::critical(this, tr("Error"), msg);
		emit setupFailure();
	}
}

void TestConfigWgt::loadPageData() {
	clear();
	handleRefreshPortsList();
	ui.comboBattLeft->addItems(testConfData.getBatteriesLeftList());
	ui.comboBattRight->addItems(testConfData.getBatteriesRightList());
	ui.simTreeRaces->addTopLevelItems(testConfData.getLogsTreeItems());
}

bool TestConfigWgt::validateBasicData() {
	// TODO: Data validation
	testName = ui.edtTestName->text();
	comPort = ui.comboSerialPort->currentText();
	voltLimit = ui.edtVoltLim->text().toDouble();
	heatSinkTempLimit = ui.edtTempLim->text().toDouble();
	idLeftBatt = ui.comboBattLeft->currentText().toInt();
	idRightBatt = ui.comboBattRight->currentText().toInt();
	return true;
}

bool TestConfigWgt::validateSimData() {
	auto selected = ui.simTreeRaces->selectedItems();
	idLogInfo = selected.front()->text(TREE_ID_LOG_INFO_COL_NUM).toInt();
	currSource = ui.simRadioCurrSourceMain->isChecked() ?
		db::CurrentSource::MAIN : db::CurrentSource::MOTOR;
	return true;
}

bool TestConfigWgt::validateBasicTestData() {
	testCurrent = ui.basicEdtTestCurr->text().toDouble();
	currSource = db::CurrentSource::NO_CURR_SOURCE;
	return true;
}

bool TestConfigWgt::validateDevTermData() {
	return true;
}

void TestConfigWgt::createDischargerTestDevice() {
	DischargerTest * dischTest = new DischargerTest(
		this,
		comPort,
		testType,
		currSource,
		idLeftBatt,
		idRightBatt
	);
	if (testType == db::TestType::SIMULATION)
		dischTest->setIdLogInfo(idLogInfo);
	else
		dischTest->setTestCurrent(testCurrent);
	dev = QSharedPointer<DeviceInterface>(dischTest);
}

void TestConfigWgt::handlePrepareTest() {
	// TODO: Validate data
	// TODO: Create device instance and cast to device interface
	if (!validateBasicData())
		return;
	switch (ui.toolBoxTestType->currentIndex())	{
	case DISCH_SIM:
		if (!validateSimData()) return;
		testType = db::TestType::SIMULATION;
		createDischargerTestDevice();
		break;
	case DISCH_TEST:
		if (!validateBasicTestData()) return;
		testType = db::TestType::BASIC_TEST;
		createDischargerTestDevice();
		break;
	case ANOTHER_DEV:
		if (!validateDevTermData()) return;
		QMessageBox::information(
			this,
			tr("Sorry"),
			tr("This functionality is not supported yet.")
		);
		return;
		break;
	default:
		break;
	}

	dev->setVoltageLimit(voltLimit);
	dev->setHeatSinkTempLimit(heatSinkTempLimit);
	emit testConfigurationDone();
}