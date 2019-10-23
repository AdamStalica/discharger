#pragma once
#include <QString>

class HelpAble
{
public:
	virtual QString getPageName() = 0;
	virtual ~HelpAble() {};
};