#pragma once
#include <nlohmann/json.h>
#include <QTextStream>
#include "Param.h"
#include "DischargerDeviceData.h"

//TODO: Move it into one header
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

		inline static SimData fromDeviceSimData(const dischargerDevice::SimData & data);

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
				<< idCurrSim.get() << ";"
				<< idSimInfo.get() << ";"
				<< idLogData.get() << ";"
				<< currTimestamp.get().toString(DB_DATETIME_FORMAT) << ";"
				<< timeSinceBeg.get().toString(DB_TIME_FORMAT) << ";"
				<< current.get() << ";"
				<< usedEnergy.get() << ";"
				<< capacity.get() << ";"
				<< battLeftVolt.get() << ";"
				<< battRightVolt.get() << ";"
				<< battLeftTemp.get() << ";"
				<< battRightTemp.get() << ";"
				<< heatSinkTemp.get(); ;
			return vals;
		}
	};

	SimData SimData::fromDeviceSimData(const dischargerDevice::SimData & devData) {
		SimData dbData;
		dbData.idCurrSim = devData.getId();
		dbData.current = devData.getCurrent();
		dbData.battLeftVolt = devData.getBatteryLeftVolt();
		dbData.battRightVolt = devData.getBatteryRightVolt();
		dbData.battLeftTemp = devData.getBatteryLeftTemp();
		dbData.battRightTemp = devData.getBatteryRightTemp();
		dbData.heatSinkTemp = devData.getHeatSinkTemp();
		return dbData;
	}

	inline void to_json(nlohmann::json &j, const SimData & sd) {
		j = nlohmann::json::object();
		if (sd.idSimInfo.isSet()) j[sd.idSimInfo.name()] = sd.idSimInfo.get();
		if (sd.idLogData.isSet()) j[sd.idLogData.name()] = sd.idLogData.get();
		if (sd.idCurrSim.isSet()) j[sd.idCurrSim.name()] = sd.idCurrSim.get();
		if (sd.currTimestamp.isSet())
			j[sd.currTimestamp.name()] = sd.currTimestamp.get().toString(DB_DATETIME_FORMAT).toStdString();
		if (sd.timeSinceBeg.isSet())	j[sd.timeSinceBeg.name()] = sd.timeSinceBeg.get().toString(DB_TIME_FORMAT).toStdString();
		if (sd.current.isSet())			j[sd.current.name()] = sd.current.get();
		if (sd.usedEnergy.isSet())		j[sd.usedEnergy.name()] = sd.usedEnergy.get();
		if (sd.capacity.isSet())		j[sd.capacity.name()] = sd.capacity.get();
		if (sd.battLeftVolt.isSet())	j[sd.battLeftVolt.name()] = sd.battLeftVolt.get();
		if (sd.battRightVolt.isSet())	j[sd.battRightVolt.name()] = sd.battRightVolt.get();
		if (sd.battLeftTemp.isSet())	j[sd.battLeftTemp.name()] = sd.battLeftTemp.get();
		if (sd.battRightTemp.isSet())	j[sd.battRightTemp.name()] = sd.battRightTemp.get();
		if (sd.heatSinkTemp.isSet())	j[sd.heatSinkTemp.name()] = sd.heatSinkTemp.get();
	}
}

Q_DECLARE_METATYPE(db::SimData)