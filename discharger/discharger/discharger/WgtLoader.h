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
	/**
	*	Method to set state of loader.
	*	@param stat - send stat = "END" to stop, 
	*	send stat = "ERROR" to stop and show last widget, 
	*	send another text to start and show text.
	*/
	void setState(const QString & stat);

	/**
	*	Method to hide loader.
	*	@param showLastWgt If this flag is set, will show last widget.
	*/
	void hideLoader(bool showLastWgt = false);

private:
	Ui::WgtLoader ui;
	QMovie * mv;
	bool active = false;

signals:
	void showLoader();
	void showLastWgt();
};
