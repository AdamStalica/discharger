#include "ChartPropertiesDialog.h"
#include <QCheckBox>
#include <QLabel>
#include <QPushButton>
#include <QButtonGroup>
#include <QColorDialog>

int ChartPropertiesDialog::getSecsInRange() {
	return PLOT_PERIOD.at(ui.periodBox->currentIndex());
}

void ChartPropertiesDialog::showEvent(QShowEvent * event) {
	QDialog::showEvent(event);

	for (auto & child : this->children()) {
		ChartGraphPropsWgt * propsWgt = dynamic_cast<ChartGraphPropsWgt *>(child);
		if (propsWgt != nullptr)
			propsWgt->reload();
	}
}
