/**
  ******************************************************************************
  * @file    AHRS.cpp
  * @version 2.0
  * @author  DUT-Lingbug Embedded Group
  * @brief   姿态解算AHRS基类
  *
  ******************************************************************************
  * @attention
  *
  * Copyright 2023 DUT-Lingbug.
  * All rights reserved.
  *
  ******************************************************************************
  */
#ifndef __ROBO_LIB_MOTOR_BACKEND_H__
#define __ROBO_LIB_MOTOR_BACKEND_H__

#include "stdint.h"
#include "Libraries/Motor/Motor.h"
#include "Motor_Data.h"

namespace robo_lib
{
class Motor_Backend
{
public:
  friend class Motor;

  Motor_Backend(Motor &motor0);
  virtual void init(void) = 0; // 初始化变量
  virtual bool update(timeus_t dT_us) = 0;
  virtual void uninit(void) = 0; // 初始化变量

  // 获取电机通用测量数据
  Motor_Common_Measurement_t getCommonMeasurement()
  {
    return com_msr;
  }
  // 设置电机线运动基准值
  void setLinearOffset(float offset)
  {
    this->com_msr.linear.offset = offset;
  }

protected:
  Motor &motor;
  virtual void updateMeasurement(void) = 0; // 读取原始数据
  // virtual void processMeasurement(timeus_t dT_us) = 0; // 进一步计算数据
  virtual void publishMeasurement(void);
  uint8_t motor_type;
  uint16_t id;
  uint16_t getId()
  {
    return id;
  }
  Motor_Common_Measurement_t com_msr;

};
}
#endif