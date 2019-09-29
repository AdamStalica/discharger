#pragma once
#include <string>

class DeviceError
{
	int code;
public:
	DeviceError(int code);
	std::string what() const;
	~DeviceError();
};

inline std::string DeviceError::what() const { 
	return "Error no. " + std::to_string(code); 
}


inline DeviceError::DeviceError(int code) : code(code) {

}

inline DeviceError::~DeviceError() {

}
