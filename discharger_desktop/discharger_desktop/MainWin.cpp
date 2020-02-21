#include "MainWin.h"
#include "ObjectFactory.h"
#include <QMessageBox>

std::function<void(bool, std::string &&)> MainWin::apiCallback = MainWin::tmpCallback;

MainWin::MainWin(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setDockedWidgetsVisibility(false);
	setTestToolBarVisibility(false);


	ObjectFactory::createInstance(new WebApi(this));

	WebApi * webApi = ObjectFactory::getInstance<WebApi>();


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

	post("", "", MainWin::tmpCallback);
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

/*



*/