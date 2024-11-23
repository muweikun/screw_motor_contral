#pragma once

#include "OffboardLink.h"

#ifdef DEBUG_MODE
#include "Libraries/UART/UARTDriver.h"
#endif

namespace olk
{
struct RefereeWarning : public MessageBase
{
public:
  uint8_t level;
  uint8_t foul_robot_id;

  RefereeWarning() : MessageBase(0x20, 2)
  {

  }

  virtual void decode(uint8_t *buf) override
  {

  }

  virtual void packData(uint8_t *buf) override
  {
    buf[4] = level;
    buf[5] = foul_robot_id;
  }
};
}
