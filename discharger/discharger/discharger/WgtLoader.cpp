#include "WgtLoader.h"
#include <QMovie>

WgtLoader::WgtLoader(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	mv = new QMovie("media/load.gif");
	mv->setScaledSize(QSize(100, 100));
	ui.mv_lbl->setMovie(mv);
	this->hide();
}

WgtLoader::~WgtLoader()
{
	delete mv;
}

void WgtLoader::setState(const QString & stat)
{
	if (stat != "END" && stat != "ERROR") {
		if (!active) {
			emit showLoader();
			mv->start();
			this->show();
			active = true;
		}
		ui.comment_lbl->setText(stat);
	}
	else {
		if (active) {
			active = false;
			mv->stop();
			ui.comment_lbl->setText("");
			this->hide();
			emit showLastWgt();
		}
	}
}
