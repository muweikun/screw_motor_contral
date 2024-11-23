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

#include "Libraries/InertialSensor/InertialSensor.h"
#include "Libraries/InertialSensor/InertialSensor_BMI088.h"
#include "Libraries/InertialSensor/InertialSensor_Backend.h"
#include "Libraries/Error/Error.h"
namespace robo_lib
{
InertialSensor::InertialSensor()
{
  backend_count = 0;
}

/***********************************************************************
** �� �� ���� InertialSensor::addBackend()
** ����˵���� ��ӹ��Դ�����backend����
**---------------------------------------------------------------------
** ��������� ���Դ�����backend����
** ���ز����� �Ƿ���ӳɹ����ɹ��򷵻�backend�±꣬���򷵻�-1
***********************************************************************/
uint8_t InertialSensor::addBackend(InertialSensor_Backend *backend)
{
  if(!backend || backend_count >= MAX_INERTIALSENSOR_BACKEND_NUM)
  {
#ifdef DEBUG_MODE
    error.error_code.inertial_sensor_backend_id_out_of_range = 1;
    error.Error_Handler();
#endif
  }
  backend->id = backend_count;
  backends[backend_count++] = backend;
  backend->init();
  return backend_count - 1;
}

/***********************************************************************
** �� �� ���� InertialSensor::detectBackend()
** ����˵���� �ֶ����Զ������Դ����������backend
**---------------------------------------------------------------------
** ��������� ��
** ���ز����� ��
***********************************************************************/
void InertialSensor::detectBackend(void)
{
//  addBackend(new InertialSensor_BMI088(*this, ROTATION_YAW_270)); // BMI088 ����ת����
}

void InertialSensor::init()
{
  detectBackend();
}

/***********************************************************************
** �� �� ���� InertialSensor::update()
** ����˵���� ��ѯÿ�����Դ������ĸ��º��������ж������Ƿ���Ч
**---------------------------------------------------------------------
** ��������� ��
** ���ز����� ��
***********************************************************************/
void InertialSensor::update()
{
  for(uint16_t i = 0; i < backend_count; i ++)
  {
    valid[i] = backends[i]->update();
  }
}

/***********************************************************************
** �� �� ���� InertialSensor::getTemperature
** ����˵���� ��ѯ��ӦID�Ĺ��Դ��������¶�
**---------------------------------------------------------------------
** ��������� ��
** ���ز����� ��
***********************************************************************/
float InertialSensor::getTemperature(uint16_t id)
{
  return backends[id]->getTemperature();
}

/***********************************************************************
** �� �� ���� InertialSensor::calibGyro
** ����˵���� �����ӦID�Ĺ��Դ������ۼ�cnt�κ��õ���Ưֵ
**---------------------------------------------------------------------
** ��������� ��
** ���ز����� ��
***********************************************************************/
void InertialSensor::calibGyro(uint16_t id, uint32_t cnt)//Ĭ��IDΪ0��cntΪ10000
{
  backends[id]->calibGyro(cnt);
}
}