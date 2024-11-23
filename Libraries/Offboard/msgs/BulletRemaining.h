#pragma once

#include "OffboardLink.h"

#ifdef DEBUG_MODE
#include "Libraries/UART/UARTDriver.h"
#endif

namespace olk
{
struct BulletRemaining : public MessageBase
{
public:
  uint16_t bullet_remaining_num_17mm;
  uint16_t bullet_remaining_num_42mm;
  uint16_t coin_remaining_num;

  BulletRemaining() : MessageBase(0x17, 6)
  {

  }

  virtual void decode(uint8_t *buf) override
  {

  }

  virtual void packData(uint8_t *buf) override
  {
    buf[4] = bullet_remaining_num_17mm;
    buf[5] = bullet_remaining_num_17mm >> 8;
    buf[6] = bullet_remaining_num_42mm;
    buf[7] = bullet_remaining_num_42mm >> 8;
    buf[8] = coin_remaining_num;
    buf[9] = coin_remaining_num >> 8;
  }
};
}
