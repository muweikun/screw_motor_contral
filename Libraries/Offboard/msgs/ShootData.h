#pragma once

#include "OffboardLink.h"

#ifdef DEBUG_MODE
#include "Libraries/UART/UARTDriver.h"
#endif

namespace olk
{
struct ShootData : public MessageBase
{
public:
  uint8_t bullet_type;
  uint8_t shooter_id;
  uint8_t bullet_freq;
  float bullet_speed;

  ShootData() : MessageBase(0x16, 7)
  {

  }

  virtual void decode(uint8_t *buf) override
  {

  }

  virtual void packData(uint8_t *buf) override
  {
    buf[4] = bullet_type;
    buf[5] = shooter_id;
    buf[6] = bullet_freq;

    buf[7] = ((uint8_t *)&bullet_speed)[0];
    buf[8] = ((uint8_t *)&bullet_speed)[1];
    buf[9] = ((uint8_t *)&bullet_speed)[2];
    buf[10] = ((uint8_t *)&bullet_speed)[3];
  }
};
}
