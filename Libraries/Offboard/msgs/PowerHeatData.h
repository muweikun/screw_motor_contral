#pragma once

#include "OffboardLink.h"

#ifdef DEBUG_MODE
#include "Libraries/UART/UARTDriver.h"
#endif

namespace olk
{
struct PowerHeatData : public MessageBase
{
public:
  uint16_t chassis_volt;
  uint16_t chassis_current;
  float chassis_power;
  uint16_t chassis_power_buffer;
  uint16_t shooter_id1_17mm_cooling_heat;
  uint16_t shooter_id2_17mm_cooling_heat;
  uint16_t shooter_id1_42mm_cooling_heat;

  PowerHeatData() : MessageBase(0x13, 14)
  {

  }

  virtual void decode(uint8_t *buf) override
  {

  }

  virtual void packData(uint8_t *buf) override
  {
    buf[4] = chassis_volt;
    buf[5] = chassis_volt >> 8;
    buf[6] = chassis_current;
    buf[7] = chassis_current >> 8;
    buf[8] = ((uint8_t *)(&chassis_power))[0];
    buf[9] = ((uint8_t *)(&chassis_power))[1];
    buf[10] = ((uint8_t *)(&chassis_power))[2];
    buf[11] = ((uint8_t *)(&chassis_power))[3];
    buf[12] = shooter_id1_17mm_cooling_heat;
    buf[13] = shooter_id1_17mm_cooling_heat >> 8;
    buf[14] = shooter_id2_17mm_cooling_heat;
    buf[15] = shooter_id2_17mm_cooling_heat >> 8;
    buf[16] = shooter_id1_42mm_cooling_heat;
    buf[17] = shooter_id1_42mm_cooling_heat >> 8;
  }
};
}
