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

#include "Libraries/InertialSensor/InertialSensor_Backend.h"
namespace robo_lib
{
InertialSensor_Backend::InertialSensor_Backend(InertialSensor &imu0) : imu(imu0)
{
}

/***********************************************************************
** �� �� ���� InertialSensor_Backend::correctAccel()
** ����˵���� �������ٶ�����
**---------------------------------------------------------------------
** ��������� ��
** ���ز����� ��
***********************************************************************/
void InertialSensor_Backend::correctAccel(void)
{

}

/***********************************************************************
** �� �� ���� InertialSensor_Backend::correctGyro()
** ����˵���� ��������������
**---------------------------------------------------------------------
** ��������� ��
** ���ز����� ��
***********************************************************************/
void InertialSensor_Backend::correctGyro(void)
{
//	gyro_calib = gyro;
  gyro_calib.x = gyro.x - gyro_offset.x;
  gyro_calib.y = gyro.y - gyro_offset.y;
  gyro_calib.z = gyro.z - gyro_offset.z;
}

/***********************************************************************
** �� �� ���� InertialSensor_Backend::publishAccel()
** ����˵���� �������ٶ�����
**---------------------------------------------------------------------
** ��������� ��
** ���ز����� ��
***********************************************************************/
void InertialSensor_Backend::publishAccel(void)
{
  imu.accel[id] = accel;
}

/***********************************************************************
** �� �� ���� InertialSensor_Backend::publishAccel()
** ����˵���� ��������������
**---------------------------------------------------------------------
** ��������� ��
** ���ز����� ��
***********************************************************************/
void InertialSensor_Backend::publishGyro(void)
{
  imu.gyro[id] = gyro_calib;
}

}