#include "ChartGraphPropsWgt.h"
#include <QColorDialog>

ChartGraphPropsWgt::ChartGraphPropsWgt(QWidget *parent, ChartGraphProps * props)
	: QWidget(parent),
	props(props)
{
	ui.setupUi(this);
	connect(ui.boxVisible, &QCheckBox::toggled, this, &ChartGraphPropsWgt::handleBoxVisibilty);
	connect(ui.btnColor, &QPushButton::clicked, this, &ChartGraphPropsWgt::handleBtnColor);
}

void ChartGraphPropsWgt::reload() {
	this->setVisible(props->isUsed());
	setBtnColor(props->getColor());
	ui.boxVisible->setChecked(props->isVisible());
	ui.boxVisible->setText(props->getName());
}

void ChartGraphPropsWgt::setBtnColor(const QColor & color) {
	ui.btnColor->setStyleSheet(QString("background-color: %1").arg(
		color.name()
	));
}

void ChartGraphPropsWgt::handleBoxVisibilty(bool visible) {
	props->setVisible(visible);
	emit graphVisibilityHasChanged(props->getId(), visible);
}

void ChartGraphPropsWgt::handleBtnColor() {
	QColor newColor = QColorDialog::getColor(
		props->getColor(),
		this,
		props->getName() + tr(" Graph Color")
	);
	setBtnColor(newColor);
	props->setColor(newColor);
	emit graphColorHasChanged(props->getId(), newColor);
}