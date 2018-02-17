#ifndef CAN_HPP
#define CAN_HPP

#include <stdint.h>
#include "ICan.hpp"

namespace Driver
{

class Can : public ICan
{
public:
	Can(uint8_t ownId);
	virtual ~Can() = default;
	uint8_t Init();
	uint8_t Init(uint8_t filterId);
	bool DataFrame(uint16_t id, uint8_t* pData, uint8_t len);
	bool RemoteFrame(uint16_t id);

private:
	uint8_t ownId;
};

} // namespace Driver

#endif // CAN_HPP
