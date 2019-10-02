#include "WgtChart.h"

QT_CHARTS_USE_NAMESPACE

WgtChart::WgtChart(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	chart = new QChart();

	//chart->legend()->hide();
	chart->legend()->attachToChart();
	chart->legend()->setBackgroundVisible(false);

	axisX = new QDateTimeAxis;
	axisX->setTickCount(10);
	axisX->setFormat("HH:mm:ss");
	chart->addAxis(axisX, Qt::AlignBottom);

	axisY = new QValueAxis;
	axisY->setLabelFormat("%i [A]");
	chart->addAxis(axisY, Qt::AlignLeft);

	chartView = new QChartView(chart);
	chartView->setRenderHint(QPainter::Antialiasing);

	ui.layout->addWidget(chartView);
}

WgtChart::~WgtChart()
{

}

void WgtChart::setXseries(std::vector<QTime> x)
{
	X.resize(x.size());
	std::transform(x.begin(), x.end(), X.begin(), [](const QTime & time)->qint64 {
		QDateTime t;// = QDateTime::currentDateTime();
		t.setTime(time);
		return t.toMSecsSinceEpoch();
	});
}

void WgtChart::addYseries(QString name, std::vector<double> y)
{
	for (int i = 0; i < y.size() && i < X.size(); ++i) {
		series[name].append(X.at(i), y.at(i));
	}
	//series[name].setPointLabelsFormat("(@xPoint, @yPoint)");
	chart->addSeries(&series[name]);
	series[name].attachAxis(axisX);
	series[name].attachAxis(axisY);
	//chart->legend()->update();
}

void WgtChart::appendYSeries(QString name, int id, double value)
{
	bool isNewSeries = series.count(name);

	series[name].append(X.at(id), value);

	if (isNewSeries) {
		chart->addSeries(&series[name]);
		series[name].attachAxis(axisX);
		series[name].attachAxis(axisY);
	}
}
