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


#include "Libraries/Motor/Motor.h"
#include "Libraries/Motor/Motor_Backend.h"

namespace robo_lib
{
/***********************************************************************
** �� �� ���� Motor::addBackend
** ����˵���� ��ӵ��backend
**---------------------------------------------------------------------
** ��������� Motor_Backend *backend
** ���ز����� ture or false
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
** �� �� ���� Motor::init
** ����˵����
**---------------------------------------------------------------------
** ��������� Motor_Backend *backend
** ���ز����� ��
***********************************************************************/
void Motor::init(Motor_Backend *backend)
{

}

/***********************************************************************
** �� �� ���� Motor::update
** ����˵���� ��ѯÿ������ĸ��º��������ж������Ƿ���Ч
**---------------------------------------------------------------------
** ��������� timeus_t dT_us
** ���ز����� ��
***********************************************************************/
void Motor::update(timeus_t dT_us)
{
  for(uint16_t i = 0; i < backend_count; i ++)
  {
    valid[i] = backends[i]->update(dT_us);
  }
}
}