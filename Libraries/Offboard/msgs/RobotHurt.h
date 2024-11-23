#pragma once

#include "OffboardLink.h"

#ifdef DEBUG_MODE
#include "Libraries/UART/UARTDriver.h"
#endif

namespace olk
{
struct RobotHurt : public MessageBase
{
public:
  uint8_t armor_id;
  uint8_t hurt_type;

  RobotHurt() : MessageBase(0x15, 2)
  {

  }

  virtual void decode(uint8_t *buf) override
  {

  }

  virtual void packData(uint8_t *buf) override
  {
    buf[4] = armor_id;
    buf[5] = hurt_type;
  }
};
}
