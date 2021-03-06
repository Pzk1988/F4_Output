#ifndef CAN_HPP
#define CAN_HPP

#include <ICommunication.hpp>
#include <stdint.h>

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
	bool AbortTx();

private:
	uint8_t ownId;
};

} // namespace Driver

#endif // CAN_HPP
