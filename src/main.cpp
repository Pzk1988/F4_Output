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
	can = new Driver::Can();
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
			printf("Can 0x%x, len %d, 0x%x, 0x%x, 0x%x, 0x%x\r\n", RxMessage.StdId,
																   RxMessage.DLC,
																   ((RxMessage.Data[0]) | RxMessage.Data[1] << 8),
																   ((RxMessage.Data[2]) | RxMessage.Data[3] << 8),
																   ((RxMessage.Data[4]) | RxMessage.Data[5] << 8),
																   ((RxMessage.Data[6]) | RxMessage.Data[7] << 8));
			outputCard.Process(&RxMessage.Data[0]);
		}
	}
}
