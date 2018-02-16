#ifndef OUTPUTCARD_H
#define OUTPUTCARD_H
#include <stdint.h>
#include "Output.hpp"
#include <vector>

class OutputCard
{
public:
	OutputCard() = default;
	virtual ~OutputCard() = default;
	void Init();
	void Process(volatile uint8_t* const pData);

private:
	std::vector<Output*> outputVector;
};

#endif // OUTPUTCARD_H
