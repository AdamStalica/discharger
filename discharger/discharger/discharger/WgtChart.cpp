/*

#include "WgtChart.h"

QT_CHARTS_USE_NAMESPACE



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

*/

/*

void WgtChart::appendYSeries(QString name, int id, double value)
{
	static int count = 0;

	bool isNewSeries = series.count(name) != 0 ? false : true;

	series[name].append(X.at(id), value);
	

	if (isNewSeries) {
		chart->addSeries(&series[name]);
		series[name].attachAxis(axisX);
		series[name].attachAxis(axisY);
	}
	if(count++ > pointsCount)
		series[name].remove(0);
}

*/