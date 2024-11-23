#pragma once

#include "OffboardLink.h"

#ifdef DEBUG_MODE
#include "Libraries/UART/UARTDriver.h"
#endif

namespace olk
{
struct GameState : public MessageBase
{
public:
  uint8_t game_type;
  uint8_t game_progress;
  uint16_t stage_remain_time;

  GameState() : MessageBase(0x10, 4)
  {

  }

  virtual void decode(uint8_t *buf) override
  {

  }

  virtual void packData(uint8_t *buf) override
  {
    buf[4] = game_type;
    buf[5] = game_progress;
    buf[6] = stage_remain_time;
    buf[7] = stage_remain_time >> 8;
  }
};
}
