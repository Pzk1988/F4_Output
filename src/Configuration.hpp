#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP
#include <stdint.h>
#include <stm32f4xx.h>

struct OutputList
{
	uint8_t Id;
	GPIO_TypeDef* Port;
	uint16_t GPIO_Pin;
};

class Configuration
{
public:
	static uint16_t GetOutputAmount()
	{
		return outputAmount;
	}

	static OutputList* GetOutputList()
	{
		return outputs;
	}

	static uint8_t GetId()
	{
		return ID;
	}

private:
	static const uint8_t ID = 2;
	static const uint16_t outputAmount = 4;
	static OutputList outputs[outputAmount];
};

#endif // CONFIGURATION_HPP
