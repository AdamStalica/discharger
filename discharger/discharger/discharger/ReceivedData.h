#pragma once
#include "json.h"

class ReceivedData
{
	nlohmann::json jsonDataObject;
	int id = -1;
	double current, battLeftVolt, battRightVolt, battLeftTemp, battRightTemp;
public:
	ReceivedData() {};
	ReceivedData(const nlohmann::json & data);

	nlohmann::json getJson() const;
	int getId() const { return id; }

	bool isValid() const { return id == -1; };

	~ReceivedData();
};



inline ReceivedData::ReceivedData(const nlohmann::json & data) : jsonDataObject(data)
{
	id = data["id"].get<int>();
	current = data["curr"].get<double>();
	battLeftVolt = data["bLV"].get<double>();
	battRightVolt = data["bRV"].get<double>();
	battLeftTemp = data["bLT"].get<double>();
	battRightTemp = data["bRT"].get<double>();
}

inline ReceivedData::~ReceivedData()
{
}
 
inline nlohmann::json ReceivedData::getJson() const { 
	return jsonDataObject; 
}
