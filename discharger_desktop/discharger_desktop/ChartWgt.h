#pragma once

#include <QWidget>
#include "ui_ChartWgt.h"
#include "DbSimData.h"
#include "ChartGraphProps.h"
#include "ChartPropertiesDialog.h"
#include "IClearable.h"

auto constexpr GRAPH_NUM = 9;

class ChartWgt : public QWidget, IClearable
{
	Q_OBJECT

public:
	ChartWgt(QWidget *parent = Q_NULLPTR);
	~ChartWgt();

public slots:
	void configChart();
	void clear() override;
	void handleNewDbSimData(const db::SimData & simData);

private slots:
	void handleGraphVisibilityChanged(int graphId, bool visible);
	void handleGraphColorChanged(int graphId, const QColor & color);

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
		{ CURRENT,			tr("Current"),				tr("A"),					QColor("blue")	},
		{ TEST_CURRENT,		tr("Test current"),			tr("A"),					QColor("red"),	Qt::DashLine , 2/*Width*/},
		{ CAPACITY,			tr("Capacity"),				tr("Ah"),					QColor("green")	},
		{ USED_ENERGY,		tr("Used energy"),			tr("Wh"),					QColor("yellow")},
		{ HEAT_SINK_TEMP,	tr("Heat sink temp."),		tr("%1C").arg(QChar(0260)),	QColor("orange")},
		{ BATT_LEFT_VOLT,	tr("Battery left volt."),	tr("V"),					QColor("pink")	},
		{ BATT_RIGHT_VOLT,	tr("Battery right volt."),	tr("V"),					QColor("violet")},
		{ BATT_LEFT_TEMP,	tr("Battery left temp."),	tr("%1C").arg(QChar(0260)),	QColor("grey")	},
		{ BATT_RIGHT_TEMP,	tr("Battery right temp."),	tr("%1C").arg(QChar(0260)),	QColor("brown") }
	} };


	Ui::ChartWgt ui;
	ChartPropertiesDialog chartPorps;
	bool usageFlagsSet = false;

	void showConfPage();
	void showPlotPage();
	bool areAllGraphsHidden();
	void pagesManager();
	void setupChart();
	void setUsageFlags(const db::SimData & simData);
	void appendChartData(const db::SimData & simData);
};
