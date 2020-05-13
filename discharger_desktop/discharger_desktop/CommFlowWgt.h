#pragma once

#include <QWidget>
#include "ui_CommFlowWgt.h"
#include "IClearable.h"
#include "DbSimData.h"

class CommFlowWgt : public QWidget
{
	Q_OBJECT

public:
	CommFlowWgt(QWidget *parent = Q_NULLPTR);
	~CommFlowWgt() {};

private slots:
	void handleSerialOpened();
	void handleSerialCanNotOpen();
	void handleSerialClosed();
	void handleSerialSentLine(const QString & line);
	void handleSerialGotLine(const QString & line);
	void handleDebug(const QString & msg);
	void handleWarning(const QString & warn);
	void handleError(const QString & err);
	void handleNewDbSimData(const db::SimData & simData);

private:
	Ui::CommFlowWgt ui;

	void appendLineToTextBrowser(QTextBrowser * brow, const QString & line, bool scrollDown);
	void appendTestDataLine(const QString & line);
	void appendEventsLine(const QString & line);
	void appendRawDataLine(const QString & line);
};
