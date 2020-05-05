#pragma once

#include <nlohmann/json.h>
#include <DischargerDeviceConverter.h>

namespace dischargerDevice {
	class Device;

	class SimDrivingData {
		unsigned int id = 0;
		double current = 0.0,
			tempLimit = 0.0,
			voltLimit = 0.0;
		const std::string sim = "drive";

		friend class dischargerDevice::Device;
		friend void to_json(nlohmann::json & j, const SimDrivingData & data);
		friend void from_json(const nlohmann::json & json, SimDrivingData & data);
	
	public:
		SimDrivingData() {}
		SimDrivingData(unsigned int id, double current, double tempLimit, double voltLimit) :
			id(id), current(current), tempLimit(tempLimit), voltLimit(voltLimit) {};

		unsigned int getId() const {
			return id;
		}

		double getCurrent() const {
			return current;
		}

		double getTempLimit() const {
			return tempLimit;
		}

		double getVoltLimit() const {
			return tempLimit;
		}
	};

	class SimData {
		unsigned int id = 0;
		double current = 0.0,
			batteryLeftVolt = 0.0,
			batteryRightVolt = 0.0,
			batteryLeftTemp = 0.0,
			batteryRightTemp = 0.0,
			heatSinkTemp = 0.0;

		friend class dischargerDevice::Device;
		friend void to_json(nlohmann::json & j, const SimData & data);
		friend void from_json(const nlohmann::json & json, SimData & data);

	public:
		SimData() {}
		SimData(unsigned int id, double current, double battLeftVolt, double battRightVolt,
			double battLeftTemp, double battRightTemp, double heatSinkTemp) :
			id(id), current(current), batteryLeftVolt(battLeftVolt), batteryRightVolt(battRightVolt), batteryLeftTemp(battLeftTemp),
			batteryRightTemp(battRightTemp), heatSinkTemp(heatSinkTemp) {}

		unsigned int getId() const {
			return id;
		}

		double getCurrent() const {
			return current;
		}

		double getBatteryLeftVolt() const {
			return batteryLeftVolt;
		}

		double getBatteryRightVolt() const {
			return batteryRightVolt;
		}

		double getBatteryLeftTemp() const {
			return batteryLeftTemp;
		}

		double getBatteryRightTemp() const {
			return batteryRightTemp;
		}

		double getHeatSinkTemp() const {
			return heatSinkTemp;
		}
	};

	class CharacteristicPoint {
		unsigned int id = 0.0;
		double voltage = 0.0,
			current = 0.0;

		friend class dischargerDevice::Device;
		friend void to_json(nlohmann::json & j, const CharacteristicPoint & point);
		friend void from_json(const nlohmann::json & json, CharacteristicPoint & point);

	public:
		CharacteristicPoint() {}
		CharacteristicPoint(unsigned int id, double volt, double curr) :
			id(id), voltage(volt), current(curr) {};

		unsigned int getId() const {
			return id;
		}

		double getCurrent() const {
			return current;
		}

		double getVoltage() const {
			return voltage;
		}
	};

	inline void to_json(nlohmann::json & j, const SimDrivingData & data) {
		j = nlohmann::json {
			{ "sim", data.sim },
			{ "id", data.id },
			{ "I", Converter::currentToDeviceCurrent(data.current) },
			{ "TL", Converter::tempToDeviceTemp(data.tempLimit) },
			{ "VL", Converter::voltToDeviceVolt(data.voltLimit) }
		};
	}

	inline void to_json(nlohmann::json & j, const SimData & data) {
		j = nlohmann::json{
			{ "id", data.id },
			{ "bLV", Converter::voltToDeviceVolt(data.batteryLeftVolt) },
			{ "bRV", Converter::voltToDeviceVolt(data.batteryRightVolt) },
			{ "bLT", Converter::voltToDeviceVolt(data.batteryLeftTemp) },
			{ "bRT", Converter::voltToDeviceVolt(data.batteryRightTemp) },
			{ "HST", Converter::voltToDeviceVolt(data.heatSinkTemp) },
		};
	}

	inline void to_json(nlohmann::json & j, const CharacteristicPoint & point) {
		j = nlohmann::json{
			{ "id", point.id },
			{ "mV", Converter::voltToDeviceVolt(point.voltage) },
			{ "I", Converter::currentToDeviceCurrent(point.current) }
		};
	}

	inline void from_json(const nlohmann::json & j, SimDrivingData & data) {
		j.at("id").get_to(data.id);
		data.current = Converter::deviceCurrentToCurrent(j.at("I").get<int>());
		data.tempLimit = Converter::deviceTempToTemp(j.at("TL").get<int>());
		data.voltLimit = Converter::deviceVoltToVolt(j.at("VL").get<int>());
	}

	inline void from_json(const nlohmann::json & j, SimData & data) {
		j.at("id").get_to(data.id);
		data.current = Converter::deviceCurrentToCurrent(j.at("I").get<int>());
		data.batteryLeftVolt = Converter::deviceVoltToVolt(j.at("bLV").get<int>());
		data.batteryRightVolt = Converter::deviceVoltToVolt(j.at("bRV").get<int>());
		data.batteryLeftTemp = Converter::deviceTempToTemp(j.at("bLT").get<int>());
		data.batteryRightTemp = Converter::deviceTempToTemp(j.at("bRT").get<int>());
		data.heatSinkTemp = Converter::deviceTempToTemp(j.at("HST").get<int>());
	}

	inline void from_json(const nlohmann::json & j, CharacteristicPoint & point) {
		j.at("id").get_to(point.id);
		point.current = Converter::deviceCurrentToCurrent(j.at("I").get<int>());
		point.voltage = Converter::deviceVoltToVolt(j.at("bLV").get<int>());
	}

}

Q_DECLARE_METATYPE(dischargerDevice::SimData)
Q_DECLARE_METATYPE(dischargerDevice::SimDrivingData)
Q_DECLARE_METATYPE(dischargerDevice::CharacteristicPoint)