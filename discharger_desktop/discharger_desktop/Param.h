#pragma once
#include <QDateTime>


template<class T>
class Param {
private:
	T val_ = T();
	const std::string NAME;
	bool isUsed = false;
public:
	//Param(Param &&) = delete;
	//Param(const Param &) = delete;
	Param(const std::string & name = "") : NAME(name) {};

	T & operator=(T _val) {
		isUsed = true;
		return (val_ = _val);
	}
	operator bool() const {
		return isUsed;
	}
	T val() const {
		return val_;
	}
	std::string name() const {
		return NAME;
	}
	QString qName() {
		return NAME.c_str();
	}
};