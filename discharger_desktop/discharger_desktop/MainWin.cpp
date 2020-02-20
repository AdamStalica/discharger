#include "MainWin.h"
#include <QMessageBox>

MainWin::MainWin(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setDockedWidgetsVisibility(false);
	setTestToolBarVisibility(false);


	connect(ui.btnLogIn, &QPushButton::clicked, [this] {
	
		ui.stackedWidget->setCurrentIndex(PagesEnum::PAGE_CONF_TEST);
	
	});

	ui.mainToolBar->addAction("Log out", [this] {
		ui.stackedWidget->setCurrentIndex(PagesEnum::PAGE_LOG_IN);
	});
	ui.mainToolBar->addAction("Show test tool bar", [this] {
		setTestToolBarVisibility(true);
	});
	ui.mainToolBar->addSeparator();
	ui.mainToolBar->addAction("Say hi", [this] {
		QMessageBox::information(this, "Hi", "Hello World!");
	});

	ui.toolBarTest->addAction("Show params", [this] {
		ui.dockWgtParams->setVisible(
			!ui.dockWgtParams->isVisible()
		);
	});
	ui.toolBarTest->addAction("Show comm flow", [this]{
		ui.dockWgtCommFlow->setVisible(
			!ui.dockWgtCommFlow->isVisible()
		);
	});
}

void MainWin::setDockedWidgetsVisibility(bool visible)
{
	ui.dockWgtParams->setVisible(visible);
	ui.dockWgtCommFlow->setVisible(visible);
}

void MainWin::setTestToolBarVisibility(bool visible)
{
	ui.toolBarTest->setVisible(visible);
}

