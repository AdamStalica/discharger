#pragma once

#include <QWidget>
#include "ui_WgtLoader.h"

class QMovie;

class WgtLoader : public QWidget
{
	Q_OBJECT

public:
	WgtLoader(QWidget *parent = Q_NULLPTR);
	~WgtLoader();
	/*
	@param stat - send stat = "END" to stop, send another text to start and show text.
	*/
	void setState(const QString & stat);

private:
	Ui::WgtLoader ui;
	QMovie * mv;
	bool active = false;

signals:
	void showLoader();
	void showLastWgt();
};
