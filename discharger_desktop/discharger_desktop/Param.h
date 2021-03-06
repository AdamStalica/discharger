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
	//Param() {}
	Param(const std::string & name = "") : NAME(name) {};

	T & operator=(T _val) {
		isUsed = true;
		return (val_ = _val);
	}
	bool isSet() const {
		return isUsed;
	}
	operator T() const {
		return val_;
	}
	T get() const {
		return val_;
	}
	std::string name() const {
		return NAME;
	}
	QString qName() const {
		return NAME.c_str();
	}
	void clear() {
		val_ = T();
		isUsed = false;
	}
};