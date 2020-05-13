#pragma once

#include <QtWidgets/QMainWindow>
#include "TestDriver.h"
#include "ui_MainWin.h"
#include "WebApi.h"

#include <functional>

class MainWin : public QMainWindow
{
	Q_OBJECT

public:
	MainWin(QWidget *parent = Q_NULLPTR);
	~MainWin() {
		ObjectFactory::deleteFactory();
	}

private:
	Ui::MainWinClass ui;
	TestDriver * testDriver;

	void closeEvent(QCloseEvent *event) override;

	enum PagesEnum {
		LOG_IN,
		LOADER,
		CONF_TEST,
		TEST,
		MENU,
		DEV_CHTIC
	};
	/*
	enum TestType {
		SIMULATION,
		BASIC_TEST,
		DEV_TERMINAL
	};
	
	enum MeasureSchem {
		DOUBLE_BATT,
		SINGLE_BATT
	};
	*/
	void setDockedWidgetsVisibility(bool visible);
	void dockedWgtTopLevelChanged(bool);
	void setTestToolBarVisibility(bool visible);

	void logout();
	//void login();

	void setupTestToolBar();
	void testToolBarAboutToStart();
	void testToolBarAboutToStop();
	void testToolBarAboutToNewTest();

	void showPage(PagesEnum page);

	//void setupTestConfPage();
	void showTestConfPage();
	//void clearTestConfPage();

	//void prepareNewTest();
	//bool setupDeviceInterface();
	//void setupTestDriver();
	//void establishConnectionToDevice();
	//void setupDbForTest();
	//void rollbackTestConf(const QString & rollbackMsg);
	void clearTestPage();


	//void showTestConfPage();
	
	void loader(const QString & msg);
	void loaderStop();

	void testStart();
	void testStop();
	void configureNewTest();

	//bool ifEmptyShowWarning(const QString & toCheck, const QString & name);
	void showError(const QString & msg);

	void showWarning(const QString & msg);
	void showDeviceError(const QString & msg);
	bool showQuestionBox(const QString & text);
	void testFinised();
	void clearParameters();
	//void setTestPatametersData(const TestParametersData & data) override;
	//void setTestCurrentLineEditEnabled(bool enabled) override;
	//void setVarTestCurrent(const QString & curr) override;
	//void setVarVoltLimit(const QString & volt) override;
	//void setVarHeatSinkTempLimit(const QString & temp) override;
	//void appendTestDataLine(const QString & line) override;
	//void appendEventsLine(const QString & line) override;
	//void appendRawDataLine(const QString & line) override;
	//void setChart(QWidget * chart) override;
	//void removeChart(QWidget * chart) override;

	//void appendLineToTextBrowser(QTextBrowser * brow, const QString & line, bool scrollDown = false);

private slots:
	void showMenu();
	void testConfigDone();
	void testSetupDone();
	//void refreshComPortsList();
	void showTestPage();
	void showDevChticPage();
	//void serialOpened();
	//void serialClosed();
	//void serialReceivedLine(const QString & line);
	//void serialTransmitedLine(const QString & line);
	//void handleTestCurrEdited();
	//void handleVoltLimitEdited();
	//void handleHeatSinkTempLimitEdited();
	//void selectFile();

	void userLoggedIn();
	void userLoggedOut();
};
