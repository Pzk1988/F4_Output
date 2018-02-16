// System includes
#include <string.h>

// Project includes
#include "Serial.hpp"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"

namespace Driver
{

void Serial::Init(int baudRate)
{
	// Enable gpio clock
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	// Set alternate functions to pins
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1);

	// Init gpio struct
	GPIO_InitTypeDef gpioInitTypeDef;
	gpioInitTypeDef.GPIO_Mode = GPIO_Mode_AF;
	gpioInitTypeDef.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	gpioInitTypeDef.GPIO_Speed = GPIO_Speed_100MHz;
	gpioInitTypeDef.GPIO_OType = GPIO_OType_PP;
	gpioInitTypeDef.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &gpioInitTypeDef);

	// Enable usart clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	USART_InitTypeDef usart_InitStruct;
	usart_InitStruct.USART_BaudRate = baudRate;
	usart_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	usart_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	usart_InitStruct.USART_Parity = USART_Parity_No;
	usart_InitStruct.USART_StopBits = USART_StopBits_1;
	usart_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1, &usart_InitStruct);
	USART_Cmd(USART1, ENABLE);
}

int Serial::Write(const char* str)
{
	size_t len = strlen(str);
	for(size_t i = 0; i < len; i++)
	{
		Put(*str++);
	}

	return len;
}

int Serial::Put(char c)
{
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET){}
	USART_SendData(USART1, c);
	return 1;
}

};
