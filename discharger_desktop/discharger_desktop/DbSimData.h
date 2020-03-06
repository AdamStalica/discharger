#pragma once
#include <nlohmann/json.h>
#include <QTextStream>
#include "Param.h"

auto constexpr DB_DATETIME_FORMAT = "yyyy-MM-dd hh:mm:ss.zzz";
auto constexpr DB_TIME_FORMAT = "hh:mm:ss.zzz";

namespace db {
	class SimData {

	public:
		SimData() :
			idSimInfo("id_sim_info"),
			idLogData("id_log_data"),
			idCurrSim("id_curr_sim"),
			currTimestamp("curr_timestamp"),
			timeSinceBeg("time_since_beg"),
			current("current"),
			usedEnergy("used_energy"),
			capacity("capacity"),
			battLeftVolt("batt_left_volt"),
			battRightVolt("batt_right_volt"),
			battLeftTemp("batt_left_temp"),
			battRightTemp("batt_right_temp"),
			heatSinkTemp("heat_sink_temp")
		{}

		Param<QDateTime> currTimestamp;
		Param<QTime> timeSinceBeg;

		Param<unsigned int> idSimInfo;
		Param<unsigned int> idLogData;
		Param<unsigned int> idCurrSim;
		Param<float> current;
		Param<float> usedEnergy;
		Param<float> capacity;
		Param<float> battLeftVolt;
		Param<float> battRightVolt;
		Param<float> battLeftTemp;
		Param<float> battRightTemp;
		Param<float> heatSinkTemp;

		QString getColumnsNames() const {
			QString cols;
			QTextStream(&cols)
				<< idCurrSim.qName() << ";"
				<< idSimInfo.qName() << ";"
				<< idLogData.qName() << ";"
				<< currTimestamp.qName() << ";"
				<< timeSinceBeg.qName() << ";"
				<< current.qName() << ";"
				<< usedEnergy.qName() << ";"
				<< capacity.qName() << ";"
				<< battLeftVolt.qName() << ";"
				<< battRightVolt.qName() << ";"
				<< battLeftTemp.qName() << ";"
				<< battRightTemp.qName() << ";"
				<< heatSinkTemp.qName();			
			return cols;
		}
		QString toCSV() const {
			QString vals;
			QTextStream(&vals)
				<< idCurrSim.val() << ";"
				<< idSimInfo.val() << ";"
				<< idLogData.val() << ";"
				<< currTimestamp.val().toString(DB_DATETIME_FORMAT) << ";"
				<< timeSinceBeg.val().toString(DB_TIME_FORMAT) << ";"
				<< current.val() << ";"
				<< usedEnergy.val() << ";"
				<< capacity.val() << ";"
				<< battLeftVolt.val() << ";"
				<< battRightVolt.val() << ";"
				<< battLeftTemp.val() << ";"
				<< battRightTemp.val() << ";"
				<< heatSinkTemp.val(); ;
			return vals;
		}
	};

	inline void to_json(nlohmann::json &j, const SimData & sd) {
		j = nlohmann::json::object();
		if (sd.idSimInfo) j[sd.idSimInfo.name()] = sd.idSimInfo.val();
		if (sd.idLogData) j[sd.idLogData.name()] = sd.idLogData.val();
		if (sd.idCurrSim) j[sd.idCurrSim.name()] = sd.idCurrSim.val();
		if (sd.currTimestamp)
			j[sd.currTimestamp.name()] = sd.currTimestamp.val().toString(DB_DATETIME_FORMAT).toStdString();
		if (sd.timeSinceBeg)	j[sd.timeSinceBeg.name()] = sd.timeSinceBeg.val().toString(DB_TIME_FORMAT).toStdString();
		if (sd.current)			j[sd.current.name()] = sd.current.val();
		if (sd.usedEnergy)		j[sd.usedEnergy.name()] = sd.usedEnergy.val();
		if (sd.capacity)		j[sd.capacity.name()] = sd.capacity.val();
		if (sd.battLeftVolt)	j[sd.battLeftVolt.name()] = sd.battLeftVolt.val();
		if (sd.battRightVolt)	j[sd.battRightVolt.name()] = sd.battRightVolt.val();
		if (sd.battLeftTemp)	j[sd.battLeftTemp.name()] = sd.battLeftTemp.val();
		if (sd.battRightTemp)	j[sd.battRightTemp.name()] = sd.battRightTemp.val();
		if (sd.heatSinkTemp)	j[sd.heatSinkTemp.name()] = sd.heatSinkTemp.val();
	}
}