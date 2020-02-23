#pragma once

#include <QObject>

class TestDriver : public QObject
{
	Q_OBJECT

public:
	TestDriver(QObject *parent);
	~TestDriver();
};
