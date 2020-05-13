#include "DevChticWgt.h"
#include "SerialPort.h"
#include "ObjectFactory.h"
#include "DischargerDevice.h"

using namespace dischargerDevice;

DevChticWgt::DevChticWgt(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.comboBoxComs->addAction(ui.actionReload);

	connect(ui.actionReload, &QAction::triggered, this, &DevChticWgt::handleComsReload);		
	connect(ui.btnConn, &QPushButton::clicked, this, &DevChticWgt::handleBtnConnect);
	connect(ui.btnGoBack, &QPushButton::clicked, this, &DevChticWgt::handleBtnGoBack);
	connect(ui.btnRead, &QPushButton::clicked, this, &DevChticWgt::handleBtnRead);
	connect(ui.btnDeterm, &QPushButton::clicked, this, &DevChticWgt::handleBtnDetermine);
	connect(ui.btnSaveData, &QPushButton::clicked, this, &DevChticWgt::handleBtnSaveData);
	connect(ui.btnSaveChart, &QPushButton::clicked, this, &DevChticWgt::handleBtnSaveChart);

	ui.plot->addGraph();
	ui.plot->graph()->setPen(QPen(Qt::blue));
	ui.plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
}

DevChticWgt::~DevChticWgt() {
	
}

void DevChticWgt::clear() {
	ui.lblDevId->clear();
	ui.comboBoxComs->clear();
	clearData();
}

void DevChticWgt::setup() {
	handleComsReload();
	setChticBtnsEnabled(false);
	auto dev = ObjectFactory::getInstance<Device>();
	connect(dev, &Device::connected, this, &DevChticWgt::handleDevConnOk);
	connect(dev, &Device::connectionFailure, this, &DevChticWgt::handleDevConnFailure);
	connect(dev, &Device::gotCharacteristicPoint, this, &DevChticWgt::handleDevChticPoint);
	connect(dev, &Device::characteristicDone, this, &DevChticWgt::handleDevDone);

	emit setupDone();
}

void DevChticWgt::handleComsReload() {
	ui.comboBoxComs->clear();
	ui.comboBoxComs->addItems(
		ObjectFactory::getInstance<serialPort::SerialPort>()->getPortsNames()
	);
}

void DevChticWgt::handleBtnConnect() {
	auto dev = ObjectFactory::getInstance<Device>();
	if (dev->isConnected()) {
		setChticBtnsEnabled(false);
		dev->disconnectDevice();
		ui.btnConn->setText(tr("Connect"));
	}
	else {
		QString comName = ui.comboBoxComs->currentText();
		if (comName == "") return;
		dev->connectToDevice(comName);
		setChticBtnsEnabled(false);
		setConnBtnEnabled(false);
		setGoBackBtnEnabled(false);
	}
}

void DevChticWgt::handleBtnGoBack() {
	clear();
	auto dev = ObjectFactory::getInstance<Device>();
	if (dev->isConnected())
		ui.btnConn->click();
	emit showMenu();
}

void DevChticWgt::handleBtnRead() {
	clearData();
	setChticBtnsEnabled(false);
	setConnBtnEnabled(false);
	setGoBackBtnEnabled(false);
	ObjectFactory::getInstance<Device>()->sendReadCharacteristic();
}

void DevChticWgt::handleBtnDetermine() {
	auto ans = QMessageBox::question(this, 
		tr("Confirm"), 
		tr("Please confirm start of device characteristic determination!"), 
		QMessageBox::Yes, QMessageBox::No
	);
	if (ans == QMessageBox::No)
		return;
	clearData();
	setChticBtnsEnabled(false);
	setConnBtnEnabled(false);
	setGoBackBtnEnabled(false);
	ObjectFactory::getInstance<Device>()->sendStartOfChracteristicDetermination();
}

void DevChticWgt::handleBtnSaveData() {

}

void DevChticWgt::handleBtnSaveChart() {

}

void DevChticWgt::handleDevConnOk() {
	setChticBtnsEnabled(true);
	setConnBtnEnabled(true);
	setGoBackBtnEnabled(true);
	ui.btnConn->setText(tr("Disconnect"));
	auto dev = ObjectFactory::getInstance<Device>();
	ui.lblDevId->setText(QString::number(dev->getDeviceId()));
}

void DevChticWgt::handleDevConnFailure() {
	setChticBtnsEnabled(false);
	setConnBtnEnabled(true);
	setGoBackBtnEnabled(true);
	QMessageBox::critical(
		this,
		tr("Error"),
		tr("Can not establish connection to the device! :(")
	);
}

void DevChticWgt::handleDevChticPoint(const CharacteristicPoint & point) {
	chticData.push_back(point);

	ui.plot->graph()->addData(point.getVoltage(), point.getCurrent());
	ui.plot->graph()->rescaleAxes();
	ui.plot->replot();

	int index = chticData.size() - 1;
	QTableWidgetItem * voltItem = new QTableWidgetItem(QString::number(point.getVoltage()));
	QTableWidgetItem * currentItem = new QTableWidgetItem(QString::number(point.getCurrent()));
	ui.tabData->setRowCount(index + 1);
	ui.tabData->setItem(index, VOLT, voltItem);
	ui.tabData->setItem(index, CURR, currentItem);
}

void DevChticWgt::handleDevDone() {
	setChticBtnsEnabled(true);
	setConnBtnEnabled(true);
	setGoBackBtnEnabled(true);
}

void DevChticWgt::setChticBtnsEnabled(bool enabled) {
	ui.btnRead->setEnabled(enabled);
	ui.btnDeterm->setEnabled(enabled);
}

void DevChticWgt::setConnBtnEnabled(bool enabled) {
	ui.btnConn->setEnabled(enabled);
}

void DevChticWgt::setGoBackBtnEnabled(bool enabled) {
	ui.btnGoBack->setEnabled(enabled);
}

void DevChticWgt::clearData() {
	chticData.clear();
	ui.tabData->clearContents();
	ui.plot->graph()->data()->clear(); 
	ui.plot->replot();
}
