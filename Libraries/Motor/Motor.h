/**
  ******************************************************************************
  * @file    AHRS.cpp
  * @version 2.0
  * @author  DUT-Lingbug Embedded Group
  * @brief   ��̬����AHRS����
  *
  ******************************************************************************
  * @attention
  *
  * Copyright 2023 DUT-Lingbug.
  * All rights reserved.
  *
  ******************************************************************************
  */
#ifndef __ROBO_LIB_MOTOR_H__
#define __ROBO_LIB_MOTOR_H__

#include "Motor_Data.h"
#include "stdint.h"

#define MAX_MOTOR_BACKEND_NUM 20

namespace robo_lib
{
class Motor_Backend;

class Motor
{
public:
  Motor() {}
  friend class Motor_Backend;

  void init(Motor_Backend *backend);
  void update(timeus_t dT_us);
  Motor_Common_Measurement_t getMeasurement(uint16_t id = 0)
  {
    return measurement[id];
  }
  Motor_Backend *backends[MAX_MOTOR_BACKEND_NUM];

  bool addBackend(Motor_Backend *backend);

protected:
  uint16_t backend_count;
//  void detectBackend(CanDevice &can_device0);


  Motor_Common_Measurement_t measurement[MAX_MOTOR_BACKEND_NUM];
  bool valid[MAX_MOTOR_BACKEND_NUM];
  bool inited[MAX_MOTOR_BACKEND_NUM];
};
}
#endif
