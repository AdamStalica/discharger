#ifndef DEVICE_DEF
#include "DeviceEventsDef.h"
#endif // !DEVICE_DEF
#include <string>

namespace Device {
	std::string getErrorDescription(Error error) {
		return "Error no. " + std::to_string(error);
	}

	std::string getWarningDescription(Warning warn) {
		return "Warning no. " + std::to_string(warn);
	}
}