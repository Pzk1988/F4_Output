#include "OutputCard.hpp"
#include "Configuration.hpp"
#include <stddef.h>
#include <algorithm>
#include "Output.hpp"

void OutputCard::Init()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	for(size_t i = 0; i < Configuration::GetOutputAmount(); i++)
	{
		outputVector.push_back(new Output(Configuration::GetOutputList()[i].Id,
										  Configuration::GetOutputList()[i].Port,
										  Configuration::GetOutputList()[i].GPIO_Pin));
	}
}
void OutputCard::Process(volatile uint8_t* const pData)
{
	uint16_t outputCard = (pData[0] | pData[1] << 8);

	for(size_t i = 0; i < Configuration::GetOutputAmount(); i++)
	{
		outputVector[i]->SetState(outputCard & (1 << i));
	};
}

