#include "ChartPropertiesDialog.h"
#include <QCheckBox>
#include <QLabel>
#include <QPushButton>
#include <QButtonGroup>
#include <QColorDialog>

ChartPropertiesDialog::ChartPropertiesDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	colorDialog = new QColorDialog(this);
	btnGr = new QButtonGroup(this);
	connect(colorDialog, &QColorDialog::accepted, this, &ChartPropertiesDialog::colorPicked);
	connect(btnGr,
		static_cast<void(QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked),
		this, &ChartPropertiesDialog::colorBtnClicked
	);
	connect(this, &QDialog::accepted, this, &ChartPropertiesDialog::dialogAccepted);
}

ChartPropertiesDialog::~ChartPropertiesDialog()
{
}

void ChartPropertiesDialog::setSeries(const std::vector<SerieItem>& series) {
	if (series.empty()) return;

	if (!seriesItems.empty()) clear();
	seriesItems.resize(series.size());

	for (int i = 0; i < series.size(); ++i) {
		SerieItemInner item(series.at(i));
		item.visibleChckBox = new QCheckBox(this);
		//item.nameLbl = new QLabel(this);
		item.colorBtn = new QPushButton(this);

		ui.seriesLayout->addWidget(item.visibleChckBox, i + 1, 0, Qt::AlignLeft);
		//ui.seriesLayout->addWidget(item.nameLbl, i + 1, 1);
		ui.seriesLayout->addWidget(item.colorBtn, i + 1, 2, Qt::AlignLeft);

		btnGr->addButton(item.colorBtn, i);
		seriesItems[i] = item;

		item.visibleChckBox->setChecked(item.visible);
		//item.nameLbl->setText(item.name);
		item.visibleChckBox->setText(item.name);
		setBtnColor(i, item.color);
		item.visibleChckBox->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
		item.colorBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
		item.colorBtn->setFixedSize(13, 13);
	}
}

std::vector<ChartPropertiesDialog::SerieItem> ChartPropertiesDialog::getSeries() {
	for (auto & item : seriesItems) {
		item.visible = item.visibleChckBox->isChecked();
	}
	std::vector<SerieItem> items;
	items.resize(seriesItems.size());
	std::copy(seriesItems.begin(), seriesItems.end(), items.begin());
	return items;
}

int ChartPropertiesDialog::getSecsInRange() {
	return currentPeriod;
}

void ChartPropertiesDialog::clear() {
	for (auto & item : seriesItems) {
		ui.seriesLayout->removeWidget(item.visibleChckBox);
		//ui.seriesLayout->removeWidget(item.nameLbl);
		ui.seriesLayout->removeWidget(item.colorBtn);
		delete item.visibleChckBox;
		//delete item.nameLbl;
		delete item.colorBtn;
	}
	seriesItems.clear();
	ui.periodBox->setCurrentIndex(0);
}

void ChartPropertiesDialog::setBtnColor(int btnId, const QColor & color) {
	if (btnId >= seriesItems.size()) return;
	seriesItems.at(btnId).color = color;
	seriesItems.at(btnId).colorBtn->setStyleSheet(QString("background-color: %1").arg(
		color.name()
	));
}

void ChartPropertiesDialog::colorPicked() {
	setBtnColor(currentyEditedColor, colorDialog->selectedColor());
}

void ChartPropertiesDialog::dialogAccepted() {
	currentPeriod = PLOT_PERIOD.at(ui.periodBox->currentIndex());
}

void ChartPropertiesDialog::colorBtnClicked(int id) {
	currentyEditedColor = id;
	colorDialog->setCurrentColor(seriesItems.at(id).color);
	colorDialog->open();
}