#ifndef DEVICE_DEF
#include "DeviceEventsDef.h"
#endif // !DEVICE_DEF
#ifndef DEVICE_EVENTS_DESCRIPTION
#define DEVICE_EVENTS_DESCRIPTION
#include <string>

namespace dischargerDevice {
	
	std::string getErrorDescription(Error error);
	std::string getWarningDescription(Warning warn);

	class Descriptions {
		
		const std::string ERROR_DESCRIPTION[9] = {
			"Device has started.",
			"Device has been stopped by safety button.",
			"Heat sink temperature too high.",
			"Battery voltage too low.",
			"Test currnet too high.",
			"Heat sink thermometer has too many times wrong CRC.",
			"Can not reach heat sink thermometer.",
			"Driving data must contain current to test.",
			"No error, this message should not ever occure."
		};
		
		const std::string WARNING_DESCRIPTION[10] = {
			"Safety button has been pressed.",
			"Heat sink temperature too high.",
			"Battery voltage too low.",
			"Test current too high.",
			"Device has received not standarized data.",
			"Heat sink thermometer has still wrong CRC",
			"Battery left thermometer has still wrong CRC",
			"Battery right thermometer has still wrong CRC",
			"Device about to reset by watchdog.",
			"No worning, this message should not ever occure."
		};

		friend std::string getErrorDescription(Error error);
		friend std::string getWarningDescription(Warning warn);
	};

	inline std::string getErrorDescription(Error error) {
		Descriptions d;
		return "Error no. " + std::to_string(error) + " " + d.ERROR_DESCRIPTION[error];
	}

	inline std::string getWarningDescription(Warning warn) {
		Descriptions d;
		return "Warning no. " + std::to_string(warn) + " " + d.WARNING_DESCRIPTION[warn];
	}
}
#endif