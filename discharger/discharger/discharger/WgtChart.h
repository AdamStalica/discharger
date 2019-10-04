#pragma once

#include <QWidget>
#include <QTime>
#include <QLineSeries>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QDateTimeAxis>
#include <QvalueAxis>
#include <QVBoxLayout>


#include "ui_WgtChart.h"


class WgtChart : public QWidget
{
	Q_OBJECT

private:

	const int seriesCount;
	const std::vector<QString> names;

	const int pointsCount = 50;

	std::vector<qint64> X;

	QtCharts::QChart * chart;
	QtCharts::QChartView * chartView;
	QtCharts::QDateTimeAxis *axisX;
	QtCharts::QValueAxis *axisY;

		
	std::map<QString, QtCharts::QLineSeries *> series;


public:

	template<typename ...N>
	WgtChart(QWidget *parent = Q_NULLPTR, const N &...names) 
		:	QWidget(parent),
			seriesCount(sizeof...(names)),
			names({names...})
	{
		ui.setupUi(this);

		chart = new QtCharts::QChart();

		//chart->legend()->hide();
		chart->legend()->attachToChart();
		chart->legend()->setBackgroundVisible(false);

		axisX = new QtCharts::QDateTimeAxis;
		axisX->setTickCount(10);
		//axisX->setRange(QDateTime(QDate::currentDate(), QTime::fromString("00:00:00")), QDateTime(QDate::currentDate(), QTime::fromString("00:01:00")));
		axisX->setFormat("HH:mm:ss");
		chart->addAxis(axisX, Qt::AlignBottom);

		axisY = new QtCharts::QValueAxis;
		axisY->setLabelFormat("%i [A]");
		axisY->setRange(0, 100);
		chart->addAxis(axisY, Qt::AlignLeft);

		chartView = new QtCharts::QChartView(chart);
		chartView->setRenderHint(QPainter::Antialiasing);

		for (auto name : names) {
			series[name] = new QtCharts::QLineSeries(this);

		}

		ui.layout->addWidget(chartView);
	}
	~WgtChart() {}

	template<typename ...V>
	void append(const QTime & time, V ...data) {
		if (sizeof...(V) != seriesCount)
			std::exception(("Series count mismatched. Excepted " + std::to_string(seriesCount) + " got " + std::to_string(sizeof...(V))).c_str());

		QDateTime x = QDateTime::currentDateTime();
		x.setTime(time);

		static int count = 0;

		std::vector<qreal> y = { static_cast<qreal>(data)... };

		for (int i = 0; i < seriesCount; ++i) {

			int isNewSeries = series[names[i]]->pointsVector().size() == 0;
			auto v = series[names[i]]->pointsVector();

			if (count > pointsCount)
				series[names[i]]->remove(0);

			series[names[i]]->append(x.toMSecsSinceEpoch(), y[i]);
			//axisX->setRange(QDateTime::fromMSecsSinceEpoch(static_cast<qint64>(v.front().x())), QDateTime::fromMSecsSinceEpoch(static_cast<qint64>(v.back().x())));

			if (isNewSeries) {

				chart->addSeries(series[names[i]]);

				series[names[i]]->attachAxis(axisY);
				series[names[i]]->setName(names[i]);
			}
			else {
				axisX->setRange(QDateTime::fromMSecsSinceEpoch(static_cast<qint64>(v.front().x())), QDateTime::fromMSecsSinceEpoch(static_cast<qint64>(v.back().x())));
				series[names[i]]->attachAxis(axisX);
			}
		}
		++count;

	}


private:
	Ui::WgtChart ui;

};