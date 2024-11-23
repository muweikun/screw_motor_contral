#pragma once

#include "OffboardLink.h"

#ifdef DEBUG_MODE
#include "Libraries/UART/UARTDriver.h"
#endif

namespace olk
{
struct Buff : public MessageBase
{
public:
  uint8_t power_rune_buff;

  Buff() : MessageBase(0x14, 1)
  {

  }

  virtual void decode(uint8_t *buf) override
  {

  }

  virtual void packData(uint8_t *buf) override
  {
    buf[4] = power_rune_buff;
  }
};
}
