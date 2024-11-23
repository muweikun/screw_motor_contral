#pragma once

#include "OffboardLink.h"

#ifdef DEBUG_MODE
#include "Libraries/UART/UARTDriver.h"
#endif

namespace olk
{
struct RobotStatus : public MessageBase
{
public:
  uint8_t robot_id;
  uint8_t robot_level;
  uint16_t remain_HP;
  uint16_t max_HP;
  uint16_t shooter_id1_17mm_cooling_rate;
  uint16_t shooter_id1_17mm_cooling_limit;
  uint16_t shooter_id1_17mm_speed_limit;
  uint16_t shooter_id2_17mm_cooling_rate;
  uint16_t shooter_id2_17mm_cooling_limit;
  uint16_t shooter_id2_17mm_speed_limit;
  uint16_t shooter_id1_42mm_cooling_rate;
  uint16_t shooter_id1_42mm_cooling_limit;
  uint16_t shooter_id1_42mm_speed_limit;
  uint16_t chassis_power_limit;
  uint16_t mains_power_gimbal_output;
  uint16_t mains_power_chassis_output;
  uint16_t mains_power_shooter_output;

  RobotStatus() : MessageBase(0x12, 29)
  {

  }

  virtual void decode(uint8_t *buf) override
  {

  }

  virtual void packData(uint8_t *buf) override
  {
    buf[4] = robot_id;
    buf[5] = robot_level;
    buf[6] = remain_HP;
    buf[7] = remain_HP >> 8;
    buf[8] = max_HP;
    buf[9] = max_HP >> 8;
    buf[10] = shooter_id1_17mm_cooling_rate;
    buf[11] = shooter_id1_17mm_cooling_rate >> 8;
    buf[12] = shooter_id1_17mm_cooling_limit;
    buf[13] = shooter_id1_17mm_cooling_limit >> 8;
    buf[14] = shooter_id1_17mm_speed_limit;
    buf[15] = shooter_id1_17mm_speed_limit >> 8;
    buf[16] = shooter_id2_17mm_cooling_rate;
    buf[17] = shooter_id2_17mm_cooling_rate >> 8;
    buf[18] = shooter_id2_17mm_cooling_limit;
    buf[19] = shooter_id2_17mm_cooling_limit >> 8;
    buf[20] = shooter_id2_17mm_speed_limit;
    buf[21] = shooter_id2_17mm_speed_limit >> 8;
    buf[22] = shooter_id1_42mm_cooling_rate;
    buf[23] = shooter_id1_42mm_cooling_rate >> 8;
    buf[24] = shooter_id1_42mm_cooling_limit;
    buf[25] = shooter_id1_42mm_cooling_limit >> 8;
    buf[26] = shooter_id1_42mm_speed_limit;
    buf[27] = shooter_id1_42mm_speed_limit >> 8;
    buf[28] = chassis_power_limit;
    buf[29] = chassis_power_limit >> 8;
    buf[30] = mains_power_gimbal_output;
    buf[31] = mains_power_chassis_output;
    buf[32] = mains_power_shooter_output;
  }
};
}
