#pragma once

#include <QWidget>
#include "ui_ChartGraphPropsWgt.h"
#include "ChartGraphProps.h"

class ChartGraphPropsWgt : public QWidget
{
	Q_OBJECT

public:
	ChartGraphPropsWgt(QWidget *parent, ChartGraphProps * props);
	~ChartGraphPropsWgt() {}

	void reload();

private:
	Ui::ChartGraphPropsWgt ui;
	ChartGraphProps * props;

	void setBtnColor(const QColor & color);

private slots:
	void handleBoxVisibilty(bool visible);
	void handleBtnColor();

signals:
	void graphVisibilityHasChanged(int graphId, bool visible);
	void graphColorHasChanged(int graphId, const QColor & color);
};
