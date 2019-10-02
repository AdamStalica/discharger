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

	std::vector<qint64> X;

	QtCharts::QChart * chart;
	QtCharts::QChartView * chartView;
	QtCharts::QDateTimeAxis *axisX;
	QtCharts::QValueAxis *axisY;

		
	std::map<QString, QtCharts::QLineSeries> series;




	







public:
	WgtChart(QWidget *parent = Q_NULLPTR);
	~WgtChart();

	void setXseries(std::vector<QTime> x); // { X = x; };
	void addYseries(QString name, std::vector<double> y);

	//void addYpoint(double value, int id, QString name) {};
	void appendYSeries(QString name, int id, double value);


private:
	Ui::WgtChart ui;

};
