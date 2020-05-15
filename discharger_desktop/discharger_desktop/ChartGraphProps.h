#pragma once
#include "QString"
#include "QColor"

class ChartGraphProps {
	int id, width;
	const QString name{ "" }, 
		unit{ "" };
	QColor color = QColor();
	Qt::PenStyle penStyle = Qt::PenStyle::SolidLine;
	bool visible = false,
		used = false;

public:

	ChartGraphProps(int id, const QString & name, const QString & unit, const QColor & color, Qt::PenStyle penStyle = Qt::SolidLine, int width = 1) 
		: id(id), name(name), unit(unit), color(color), penStyle(penStyle), width(width)
	{}

	void setColor(const QColor & color) {
		this->color = color;
	}

	void setVisible(bool visible) {
		this->visible = visible;
	}

	void setUsed(bool used) {
		this->used = used;
	}

	int getId() const {
		return id;
	}

	QString getName() const {
		return name;
	}

	QString getUnit() const {
		return unit;
	}

	QColor getColor() const {
		return color;
	}

	Qt::PenStyle getPenStyle() const {
		return penStyle;
	}

	int getWidth() const {
		return width;
	}

	bool isVisible() const {
		return visible;
	}

	bool isUsed() const {
		return used;
	}
};