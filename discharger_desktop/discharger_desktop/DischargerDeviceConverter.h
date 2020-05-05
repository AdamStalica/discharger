#pragma once

namespace dischargerDevice {
	unsigned int constexpr VOLT_RATIO = 1000;
	unsigned int constexpr CURRENT_RATIO = 100;
	unsigned int constexpr TEMP_RATIO = 100;

	class Converter {
	public:
		static int voltToDeviceVolt(double volt) {
			return volt * VOLT_RATIO + 0.5;
		}

		static double deviceVoltToVolt(int deviceVolt) {
			return deviceVolt / VOLT_RATIO;
		}

		static int currentToDeviceCurrent(double current) {
			return current * VOLT_RATIO + 0.5;
		}

		static double deviceCurrentToCurrent(int deviceCurrent) {
			return deviceCurrent / CURRENT_RATIO;
		}

		static int tempToDeviceTemp(double temp) {
			return temp * TEMP_RATIO + 0.5;
		}

		static double deviceTempToTemp(int deviceTemp) {
			return deviceTemp / TEMP_RATIO;
		}
	};
}	
