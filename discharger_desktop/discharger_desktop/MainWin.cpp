#include "MainWin.h"
#include "ObjectFactory.h"
#include "User.h"
#include <QMessageBox>


MainWin::MainWin(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setDockedWidgetsVisibility(false);
	//setTestToolBarVisibility(false);

	ObjectFactory::createInstance(new WebApi(this));
	ObjectFactory::createInstance(new User(this));

	auto user = ObjectFactory::getInstance<User>();

	user->logIn("dominikkala@gmail.com", "test1234");






	setupMainToolBar();
	setupTestToolBar();


	connect(ui.btnLogIn, &QPushButton::clicked, [this] {
	
		ui.stackedWidget->setCurrentIndex(PagesEnum::PAGE_CONF_TEST);
	
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

void MainWin::logout() {
	// TODO: checking if test is in progress
	ui.stackedWidget->setCurrentIndex(PagesEnum::PAGE_LOG_IN);
	ObjectFactory::getInstance<User>()->logOut();
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

void MainWin::testStart() {
	ui.toolBarTest->actions()[0]->setVisible(false);
	ui.toolBarTest->actions()[1]->setVisible(true);
	// TODO: Test start
}

void MainWin::testStop() {
	ui.toolBarTest->actions()[0]->setVisible(true);
	ui.toolBarTest->actions()[1]->setVisible(false);
	// TODO: Test stop
}
