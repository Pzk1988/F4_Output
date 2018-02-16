#include <Output.hpp>

Output::Output(uint8_t Id, GPIO_TypeDef* Port, uint16_t GPIO_Pin) : Id(Id), Port(Port), GPIO_Pin(GPIO_Pin)
{
	GPIO_InitTypeDef gpioInit;
	gpioInit.GPIO_Mode = GPIO_Mode_OUT;
	gpioInit.GPIO_OType = GPIO_OType_PP;
	gpioInit.GPIO_Pin = GPIO_Pin;
	gpioInit.GPIO_PuPd = GPIO_PuPd_NOPULL;
	gpioInit.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(Port, &gpioInit);
}

void Output::SetState(bool state)
{
	if(state == true)
	{
		Port->ODR |= GPIO_Pin;
	}
	else
	{
		Port->ODR &= ~GPIO_Pin;
	}
}
