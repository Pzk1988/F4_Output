#include <stddef.h>
#include <stdio.h>
#include "stm32f4xx.h"
#include "Serial.hpp"
#include "Can.hpp"
#include "Configuration.hpp"
#include "OutputCard.hpp"

Driver::ISerial* serial;
Driver::ICan* can;
volatile uint8_t sem = 0;
volatile CanRxMsg RxMessage;

int main(void)
{
	// System clock
	SysTick_Config(SystemCoreClock / 1000);

	// Serial driver
	serial = new Driver::Serial();
	serial->Init(115200);

	// Can driver
	can = new Driver::Can(Configuration::GetId());
	can->Init(Configuration::GetId());

	// OutpuCard
	OutputCard outputCard;
	outputCard.Init();

	printf("Stm32F407VT Hello World\r\n");

	while (1)
	{
		if(sem == 1)
		{
			sem = 0;
			printf("Can 0x%x from 0x%x, len %d", (RxMessage.StdId & 0x1F), RxMessage.StdId >> 5, RxMessage.DLC);
			for(size_t i = 0; i < RxMessage.DLC; i++)
			{
				printf(", %x", RxMessage.Data[i]);
			}
			printf("\r\n");

			// Process outputs
			outputCard.Process(&RxMessage.Data[0]);

			// Send response
			can->DataFrame(0x01, nullptr, 0);
		}
	}
}
