#include "TestConfigWgt.h"
#include "ObjectFactory.h"
#include "SerialPort.h"
#include "Cleaner.h"

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
}

void TestConfigWgt::clear() {
	Cleaner::clearChildrens<QLineEdit>(this);
	Cleaner::clearChildrens<QComboBox>(this);
	Cleaner::clearChildrens<QTreeWidget>(this);
	ui.simRadioCollapse->setChecked(true);
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
	QString filter = getLogFilesFormatsFilter();
	QString fileName = QFileDialog::getSaveFileName(this, tr("Log to file"),
		QStandardPaths::writableLocation(QStandardPaths::DesktopLocation),
		filter, &selectedFilter);

	LogFilesFormats fileFormat = getLogFileFormatId(selectedFilter);
	ui.edtFileName->setText(fileName);
	ui.edtFileName->setProperty("FILE_FORMAT", fileFormat);
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

void TestConfigWgt::handlePrepareTest() {
	// TODO: Validate data
	// TODO: Create device instance and cast to device interface
}