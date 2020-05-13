#pragma once

#include <QWidget>
#include "ui_DevChticWgt.h"
#include "ISetupable.h"
#include "IClearable.h"
#include "DischargerDeviceData.h"

class DevChticWgt : 
	public QWidget, ISetupable, IClearable
{
	Q_OBJECT

public:
	DevChticWgt(QWidget *parent = Q_NULLPTR);
	~DevChticWgt();

public slots:
	void clear() override;
	void setup() override;

private slots:
	void handleComsReload();
	void handleBtnConnect();
	void handleBtnGoBack();
	void handleBtnRead();
	void handleBtnDetermine();
	void handleBtnSaveData();
	void handleBtnSaveChart();
	void handleDevConnOk();
	void handleDevConnFailure();
	void handleDevChticPoint(const dischargerDevice::CharacteristicPoint & point);
	void handleDevDone();


signals:
	void setupDone();
	void showMenu();

private:
	enum Cols {
		VOLT, CURR
	};

	Ui::DevChticWgt ui;
	std::vector<dischargerDevice::CharacteristicPoint> chticData;

	void setChticBtnsEnabled(bool enabled);
	void setConnBtnEnabled(bool enabled);
	void setGoBackBtnEnabled(bool enabled);
	void clearData();
};
