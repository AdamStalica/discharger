#pragma once

#include <QDialog>
#include "ui_ChartPropertiesDialog.h"
#include "ChartGraphProps.h"
#include "ChartGraphPropsWgt.h"
#include <array>


class ChartPropertiesDialog : public QDialog
{
	Q_OBJECT

public:
	template<std::size_t Size>
	ChartPropertiesDialog(std::array<ChartGraphProps, Size> & chartGraphsProps, QWidget *parent = Q_NULLPTR);
	~ChartPropertiesDialog() {};

	int getSecsInRange();

private:

	Ui::ChartPropertiesDialog ui;

	std::array<int, 4> PLOT_PERIOD{
		60, 120, 180, -1
	};
	int currentPeriod = PLOT_PERIOD.at(0);

	void showEvent(QShowEvent* event) override;
	
signals:
	void periodHasChanged(int period);
	void graphVisibilityHasChanged(int graphId, bool visible);
	void graphColorHasChanged(int graphId, const QColor & color);
};

template<std::size_t Size>
ChartPropertiesDialog::ChartPropertiesDialog(std::array<ChartGraphProps, Size> & chartGraphsProps, QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	for (auto & props : chartGraphsProps) {
		auto propsWgt = new ChartGraphPropsWgt(this, &props);
		ui.seriesLayout->addWidget(propsWgt);

		connect(propsWgt, &ChartGraphPropsWgt::graphVisibilityHasChanged, 
			[this](int graphId, bool visible) {
				emit graphVisibilityHasChanged(graphId, visible);
		});
		connect(propsWgt, &ChartGraphPropsWgt::graphColorHasChanged,
			[this](int graphId, const QColor & color) {
				emit graphColorHasChanged(graphId, color);
		});
	}

	connect(ui.periodBox, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), 
		[this](int index) {
			emit periodHasChanged(PLOT_PERIOD.at(index));
	});
}