#ifndef DRIVER_SERIAL_HPP
#define DRIVER_SERIAL_HPP

#include "ISerial.hpp"

namespace Driver
{

class Serial: public ISerial
{
public:
	Serial() = default;
	virtual ~Serial() = default;

	void Init(int baudRate);
	int Write(const char* str);
	int Put(char c);
};

};
#endif /* DRIVER_SERIAL_HPP */
