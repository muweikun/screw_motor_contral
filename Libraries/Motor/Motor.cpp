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


#include "Libraries/Motor/Motor.h"
#include "Libraries/Motor/Motor_Backend.h"

namespace robo_lib
{
/***********************************************************************
** 函 数 名： Motor::addBackend
** 函数说明： 添加电机backend
**---------------------------------------------------------------------
** 输入参数： Motor_Backend *backend
** 返回参数： ture or false
***********************************************************************/
bool Motor::addBackend(Motor_Backend *backend)
{
  if(!backend || backend_count >= MAX_MOTOR_BACKEND_NUM)
  {
#ifdef DEBUG_MODE

#endif
    return false;
  }
  backend->id = backend_count;
  backends[backend_count++] = backend;
  backend->init();
  return true;
}


/***********************************************************************
** 函 数 名： Motor::init
** 函数说明：
**---------------------------------------------------------------------
** 输入参数： Motor_Backend *backend
** 返回参数： 无
***********************************************************************/
void Motor::init(Motor_Backend *backend)
{

}

/***********************************************************************
** 函 数 名： Motor::update
** 函数说明： 轮询每个电机的更新函数，并判断数据是否有效
**---------------------------------------------------------------------
** 输入参数： timeus_t dT_us
** 返回参数： 无
***********************************************************************/
void Motor::update(timeus_t dT_us)
{
  for(uint16_t i = 0; i < backend_count; i ++)
  {
    valid[i] = backends[i]->update(dT_us);
  }
}
}