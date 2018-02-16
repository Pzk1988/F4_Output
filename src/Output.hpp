#ifndef OUTPUT_HPP
#define OUTPUT_HPP
#include <stdint.h>
#include <stm32f4xx.h>

class Output
{
public:
	Output(uint8_t Id, GPIO_TypeDef* Port, uint16_t GPIO_Pin);
	virtual ~Output() = default;
	void SetState(bool state);
};

#endif // OUTPUT_HPP
