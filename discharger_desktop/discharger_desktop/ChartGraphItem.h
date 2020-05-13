#pragma once
#include "QString"
#include "QColor"

class ChartGraphProps {
	const QString name, unit;
	QColor color;
	bool visible = false,
		used = false;

public:
	ChartGraphProps(const QString & name, const QString & unit, const QColor & color) 
		: name(name), unit(unit), color(color)
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

	QString getName() const {
		return name;
	}

	QString getUnit() const {
		return unit;
	}

	QColor getColor() const {
		return color;
	}

	bool isVisible() const {
		return visible;
	}

	bool isUsed() const {
		return used;
	}
};

