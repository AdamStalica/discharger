#pragma once

#include <QWidget>
#include "ui_ChartWgt.h"
#include "DbSimData.h"
#include "ChartGraphItem.h"

auto constexpr GRAPH_NUM = 9;

class ChartWgt : public QWidget
{
	Q_OBJECT

public:
	ChartWgt(QWidget *parent = Q_NULLPTR);
	~ChartWgt();

public slots:
	void configChart();

private slots:
	void handleNewDbSimData(const db::SimData & simData);

private:
	enum Pages {
		CONF, PLOT
	};

	enum Graphs {
		CURRENT,
		TEST_CURRENT,
		CAPACITY,
		USED_ENERGY,
		HEAT_SINK_TEMP,
		BATT_LEFT_VOLT,
		BATT_RIGHT_VOLT,
		BATT_LEFT_TEMP,
		BATT_RIGHT_TEMP
	};

	std::array<ChartGraphProps, GRAPH_NUM> graphsProps{ {
		{ tr("Current"),				tr("A"),					QColor("blue") },
		{ tr("Test current"),			tr("A"),					QColor("red") },
		{ tr("Capacity"),				tr("Ah"),					QColor("green") },
		{ tr("Used energy"),			tr("Wh"),					QColor("yellow") },
		{ tr("Heat sink temp."),		tr("%1C").arg(QChar(0260)),	QColor("orange") },
		{ tr("Battery left volt."),		tr("V"),					QColor("pink") },
		{ tr("Battery right volt."),	tr("V"),					QColor("violet") },
		{ tr("Battery left temp."),		tr("%1C").arg(QChar(0260)),	QColor("grey") },
		{ tr("Battery right temp."),	tr("%1C").arg(QChar(0260)),	QColor("brown") }
	} };


	Ui::ChartWgt ui;
	ChartPropertiesDialog chartPorps;
};
