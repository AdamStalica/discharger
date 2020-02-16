#pragma once
#include <nlohmann/json.h>
#include <QDateTime>

class ReceivedData
{
	nlohmann::json jsonDataObject;
	int id = -1;
	double	current = DBL_MAX,
			battLeftVolt = DBL_MAX,
			battRightVolt = DBL_MAX,
			battLeftTemp = DBL_MAX,
			battRightTemp = DBL_MAX;
	QDateTime timestamp;
public:
	/**
	*	Default constructor.
	*/
	ReceivedData() {};

	/**
	*	Constructor initializing object.
	*	@param data {"id" : int, "bLV": double, "bRV": double, "bLT" : double, "bRT" : double}
	*/
	ReceivedData(const nlohmann::json & data);


	//nlohmann::json getJson() const;

	/**
	*	Method to check object state.
	*	@return True if object contains valid data.
	*/
	bool isValid() const { return id != -1; };

	/**
	*	Method to check current.
	*	@return True if current is set.
	*/
	bool isCurrentNull() const { return current == DBL_MAX; }

	/**
	*	Method to check battery left volt.
	*	@return True if battery left volt is set.
	*/
	bool isBattLeftVoltNull() const { return battLeftVolt == DBL_MAX; }

	/**
	*	Method to check battery right volt.
	*	@return True if battery right volt is set.
	*/
	bool isBattRightVoltNull() const { return battRightVolt == DBL_MAX; }

	/**
	*	Method to check battery left temperature.
	*	@return True if battery left temperature is set.
	*/
	bool isBattLeftTempNull() const { return battLeftTemp == DBL_MAX; }

	/**
	*	Method to check battery right temperature.
	*	@return True if battery right temperature is set.
	*/
	bool isBattRightTempNull() const { return battRightTemp == DBL_MAX; }


	/**
	*	Getter.
	*	@return Received data id.
	*/
	int getId() const { return id; }

	/**
	*	Getter.
	*	@return Simulated current.
	*/
	double getCurrent() const { return current; }

	/**
	*	Getter.
	*	@return Battery left voltage. 
	*/
	double getBattLeftVolt() const { return battLeftVolt; }

	/**
	*	Getter.
	*	@return Battery right voltage.
	*/
	double getBattRightVolt() const { return battRightVolt; }

	/**
	*	Getter.
	*	@return Battery left temperature.
	*/
	double getBattLeftTemp() const { return battLeftTemp; }

	/**
	*	Getter.
	*	@return Battery right temperature.
	*/
	double getBattRightTemp() const { return battRightTemp; }

	/**
	*	Getter.
	*	@return Received time stamp.
	*/
	QDateTime getTimestamp() const { return timestamp; }

	~ReceivedData() {}
};



inline ReceivedData::ReceivedData(const nlohmann::json & data) : jsonDataObject(data)
{
	timestamp = QDateTime::currentDateTime();

	id = data["id"].get<int>();
	current = data["curr"].get<int>() / 10.0;
	battLeftVolt = data["bLV"].get<int>() / 1000.0;
	battRightVolt = data["bRV"].get<int>() / 1000.0;
	battLeftTemp = data["bLT"].get<int>() / 100.0;
	battRightTemp = data["bRT"].get<int>() / 100.0;
}

/*
inline nlohmann::json ReceivedData::getJson() const { 
	return jsonDataObject; 
}
*/
