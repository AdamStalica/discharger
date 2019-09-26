#pragma once
class DeviceError
{
protected:
	int code;
public:
	DeviceError(int code);
	std::string what() const;
	~DeviceError();
};



DeviceError::DeviceError(int code) : code(code) 
{

}

inline std::string DeviceError::what() const
{
	return "Error no. " + std::to_string(code);
}


DeviceError::~DeviceError()
{

}
