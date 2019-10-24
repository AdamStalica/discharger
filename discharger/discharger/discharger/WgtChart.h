#pragma once

#include <QWidget>
#include <QTime>
#include <QLineSeries>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QDateTimeAxis>
#include <QvalueAxis>
#include <QVBoxLayout>

#include <QDebug>

#include <algorithm>

#include "ui_WgtChart.h"


class WgtChart : public QWidget
{
	Q_OBJECT

private:

	Ui::WgtChart ui;

	const int seriesCount;
	const int pointsCount = 60;
	int pointsCounter = 0;
	
	QtCharts::QChart * chart;
	QtCharts::QChartView * chartView;
	QtCharts::QDateTimeAxis *axisX;
	QtCharts::QValueAxis *axisY;

	const std::vector<QString> names;
	std::pair<qreal, qreal> minMax = { DBL_MAX, DBL_MIN};
	std::map<QString, QtCharts::QLineSeries *> series;

	qreal getDivider() {
		return std::pow(10, std::floor(std::log10(minMax.second - minMax.first)));
	}

	qreal getMinValueToSet() {
		qreal div = getDivider();
		return std::floor(minMax.first / div - 1) * div;
	}

	qreal getMaxValueToSet() {
		qreal div = getDivider();
		return std::ceil(minMax.second / div + 1) * div;
	}

public:

	template<typename ...N>
	WgtChart(QWidget *parent = Q_NULLPTR, const N &...names) 
		:	QWidget(parent),
			seriesCount(sizeof...(names)),
			names({names...})
	{
		ui.setupUi(this);

		chart = new QtCharts::QChart();
		

		axisX = new QtCharts::QDateTimeAxis(this);
		axisX->setTickCount(10);
		axisX->setRange(QDateTime(QDate::currentDate(), QTime::fromString("00:00:00")), QDateTime(QDate::currentDate(), QTime::fromString("00:00:01")));
		axisX->setFormat("HH:mm:ss");
		chart->addAxis(axisX, Qt::AlignBottom);

		axisY = new QtCharts::QValueAxis(this);
		axisY->setLabelFormat("%.2f");
		axisY->setRange(0, 1);
		chart->addAxis(axisY, Qt::AlignLeft);

		chartView = new QtCharts::QChartView(chart);
		chartView->setContentsMargins(0, 0, 0, 0);
		chart->setContentsMargins(0, 0, 0, 0);
		chartView->setRenderHint(QPainter::Antialiasing);

		for (auto name : names) {
			series[name] = new QtCharts::QLineSeries(this);

			chart->addSeries(series[name]);

			series[name]->attachAxis(axisY);
			series[name]->attachAxis(axisX);
			series[name]->setName(name);
		}

		chart->legend()->setAlignment(Qt::AlignBottom);

		ui.layout->addWidget(chartView);

		this->setStyleSheet("QWidget { background-color: rgba(0, 0, 0, 0); }");
		chart->setTheme(QtCharts::QChart::ChartThemeDark);
	}
	
	template<typename ...V>
	void setColors(const V &... colors) {
		if (sizeof...(V) != seriesCount)
			std::exception(("Series count mismatched. Excepted " + std::to_string(seriesCount) + " got " + std::to_string(sizeof...(V))).c_str());
		
		std::vector<QColor> colorsVec = { colors... };

		for (int i = 0; i < seriesCount; ++i)
			series[names.at(i)]->setColor(colorsVec.at(i));
	}

	template<typename ...V>
	void append(const QTime & time, V ...data) {
		if (sizeof...(V) != seriesCount)
			std::exception(("Series count mismatched. Excepted " + std::to_string(seriesCount) + " got " + std::to_string(sizeof...(V))).c_str());

		QDateTime x = QDateTime::currentDateTime();
		x.setTime(time);
		
		std::vector<qreal> y = { static_cast<qreal>(data)... };

		QVector<QPointF> pointsVector;

		for (int i = 0; i < seriesCount; ++i) {
			
			if (pointsCounter == pointsCount) series[names[i]]->remove(0);

			series[names[i]]->append(x.toMSecsSinceEpoch(), y[i]);

			pointsVector.append(series[names[i]]->pointsVector());
		}

		auto minMaxPoint = std::minmax_element(
			pointsVector.begin(),
			pointsVector.end(),
			[](const QPointF & l, const QPointF & r)->bool {
			return l.y() < r.y();
		});
		minMax = { minMaxPoint.first->y(), minMaxPoint.second->y() };

		axisY->setRange(
			getMinValueToSet(), 
			getMaxValueToSet()
		);
		axisX->setRange(
			QDateTime::fromMSecsSinceEpoch(static_cast<qint64>(pointsVector.front().x())), 
			QDateTime::fromMSecsSinceEpoch(static_cast<qint64>(pointsVector.back().x()))
		);

		if(pointsCounter < pointsCount) ++pointsCounter;
	}

	void setUnit(const QString & unit) {
		axisY->setLabelFormat("%.2f [" + unit + "]");
	}


	~WgtChart() {
		delete chart;
	}
};