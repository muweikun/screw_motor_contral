#pragma once

#include "OffboardLink.h"

#ifdef DEBUG_MODE
#include "Libraries/UART/UARTDriver.h"
#endif

namespace olk
{
struct RobotsHealth : public MessageBase
{
public:
  uint16_t red_1_robot_HP;
  uint16_t red_2_robot_HP;
  uint16_t red_3_robot_HP;
  uint16_t red_4_robot_HP;
  uint16_t red_5_robot_HP;
  uint16_t red_7_robot_HP;
  uint16_t red_outpost_HP;
  uint16_t red_base_HP;

  uint16_t blue_1_robot_HP;
  uint16_t blue_2_robot_HP;
  uint16_t blue_3_robot_HP;
  uint16_t blue_4_robot_HP;
  uint16_t blue_5_robot_HP;
  uint16_t blue_7_robot_HP;
  uint16_t blue_outpost_HP;
  uint16_t blue_base_HP;

  RobotsHealth() : MessageBase(0x11, 32)
  {

  }

  virtual void decode(uint8_t *buf) override
  {

  }

  virtual void packData(uint8_t *buf) override
  {
    buf[4] = red_1_robot_HP;
    buf[5] = red_1_robot_HP >> 8;
    buf[6] = red_2_robot_HP;
    buf[7] = red_2_robot_HP >> 8;
    buf[8] = red_3_robot_HP;
    buf[9] = red_3_robot_HP >> 8;
    buf[10] = red_4_robot_HP;
    buf[11] = red_4_robot_HP >> 8;
    buf[12] = red_5_robot_HP;
    buf[13] = red_5_robot_HP >> 8;
    buf[14] = red_7_robot_HP;
    buf[15] = red_7_robot_HP >> 8;
    buf[16] = red_outpost_HP;
    buf[17] = red_outpost_HP >> 8;
    buf[18] = red_base_HP;
    buf[19] = red_base_HP >> 8;
    buf[20] = blue_1_robot_HP;
    buf[21] = blue_1_robot_HP >> 8;
    buf[22] = blue_2_robot_HP;
    buf[23] = blue_2_robot_HP >> 8;
    buf[24] = blue_3_robot_HP;
    buf[25] = blue_3_robot_HP >> 8;
    buf[26] = blue_4_robot_HP;
    buf[27] = blue_4_robot_HP >> 8;
    buf[28] = blue_5_robot_HP;
    buf[29] = blue_5_robot_HP >> 8;
    buf[30] = blue_7_robot_HP;
    buf[31] = blue_7_robot_HP >> 8;
    buf[32] = blue_outpost_HP;
    buf[33] = blue_outpost_HP >> 8;
    buf[34] = blue_base_HP;
    buf[35] = blue_base_HP >> 8;
  }
};
}
