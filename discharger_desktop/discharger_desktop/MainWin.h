#pragma once

#include <QtWidgets/QMainWindow>
#include "TestGUI.h"
#include "TestDriver.h"
#include "ui_MainWin.h"
#include "WebApi.h"

#include <functional>

class MainWin : public QMainWindow, public TestGUI
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

	enum PagesEnum {
		LOG_IN,
		LOADER,
		CONF_TEST,
		TEST
	};

	enum TestActions {
		START,
		STOP,
		NEW_TEST
	};

	enum TestType {
		SIMULATION,
		BASIC_TEST,
		DEV_TERMINAL
	};

	enum MeasureSchem {
		DOUBLE_BATT,
		SINGLE_BATT
	};

	const unsigned int TREE_ID_LOG_INFO_COL_NUM = 2;

	template<class T>
	void clearChildrens(QObject * parent, const QString & regex = QString());

	void setDockedWidgetsVisibility(bool visible);
	void setTestToolBarVisibility(bool visible);

	void logout();
	void login();

	void setupMainToolBar();
	void setupTestToolBar();

	void setupTestConfPage();
	void loadTestConfPage();
	void clearTestConfPage();
	void prepareNewTest();


	void showTestConfPage();
	void showTestPage();
	
	void loader(const QString & msg);
	void loaderStop();

	void testStart();
	void testStop();
	void configureNewTest();

	bool ifEmptyShowWarning(const QString & toCheck, const QString & name);
	void showWarning(const QString & msg);
	void showError(const QString & msg);

	void testFinised() override;
	void clearParameters() override;
	void setTestPatametersData(const TestParametersData & data) override;
	void setTestCurrentLineEditEnabled(bool enabled) override;
	void appendTestDataLine(const QString & line) override;
	void appendEventsLine(const QString & line) override;
	void appendRawDataLine(const QString & line) override;
	void setChart(QWidget * chart) override;
	void removeChart(QWidget * chart) override;

	void appendLineToTextBrowser(QTextBrowser * brow, const QString & line, bool scrollDown = false);
};

template<class T>
inline void MainWin::clearChildrens(QObject * parent, const QString & regex) {}

template<>
inline void MainWin::clearChildrens<QLineEdit>(QObject * parent, const QString & regex) {
	for (auto obj : parent->findChildren<QLineEdit *>(QRegularExpression(regex))) {
		obj->setText("");
	}
}

template<>
inline void MainWin::clearChildrens<QComboBox>(QObject * parent, const QString & regex) {
	for (auto obj : parent->findChildren<QComboBox *>(QRegularExpression(regex))) {
		obj->clear();
		obj->setCurrentIndex(-1);
	}
}

template<>
inline void MainWin::clearChildrens<QProgressBar>(QObject * parent, const QString & regex) {
	for (auto obj : parent->findChildren<QProgressBar *>(QRegularExpression(regex))) {
		obj->reset();
	}
}

template<>
inline void MainWin::clearChildrens<QLabel>(QObject * parent, const QString & regex) {
	for (auto obj : parent->findChildren<QLabel *>(QRegularExpression(regex))) {
		obj->setText("");
	}
}

template<>
inline void MainWin::clearChildrens<QTextBrowser>(QObject * parent, const QString & regex) {
	for (auto obj : parent->findChildren<QTextBrowser *>(QRegularExpression(regex))) {
		obj->setText("");
	}
}

template<>
inline void MainWin::clearChildrens<QTreeWidget>(QObject * parent, const QString & regex) {
	for (auto obj : parent->findChildren<QTreeWidget *>(QRegularExpression(regex))) {
		obj->clear();
	}
}