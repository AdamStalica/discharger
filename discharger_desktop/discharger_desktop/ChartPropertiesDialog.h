#pragma once

#include <QDialog>
#include "ui_ChartPropertiesDialog.h"

class QCheckBox;
class QLabel;
class QPushButton;
class QButtonGroup;
class QColorDialog;

class ChartPropertiesDialog : public QDialog
{
	Q_OBJECT

public:
	ChartPropertiesDialog(QWidget *parent = Q_NULLPTR);
	~ChartPropertiesDialog();

    struct SerieItem {
		int id = 0;
		bool visible = false;
		QString name = QString();
		QColor color = QColor();
		SerieItem(int id, bool visible, const QString & name, const QColor & color) :
			id(id),
			visible(visible),
			name(name),
			color(color)
		{}
		SerieItem() {}
	};

	void setSeries(const std::vector<SerieItem> & series);
	std::vector<SerieItem> getSeries();
	int getSecsInRange();
	void clear();

private:
	Ui::ChartPropertiesDialog ui;
	QButtonGroup * btnGr;
	QColorDialog * colorDialog;
	int currentyEditedColor = 0;

	struct SerieItemInner : SerieItem {
		SerieItemInner(const SerieItem & si) : SerieItem(si) {}
		SerieItemInner() {}
		QCheckBox * visibleChckBox;
		QLabel * nameLbl;
		QPushButton * colorBtn;
	};
	std::vector<SerieItemInner> seriesItems;

	void setBtnColor(int btnId, const QColor & color);

private slots:
	void colorBtnClicked(int id);
	void colorPicked();
};
