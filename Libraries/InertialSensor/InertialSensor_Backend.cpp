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

#include "Libraries/InertialSensor/InertialSensor_Backend.h"
namespace robo_lib
{
InertialSensor_Backend::InertialSensor_Backend(InertialSensor &imu0) : imu(imu0)
{
}

/***********************************************************************
** 函 数 名： InertialSensor_Backend::correctAccel()
** 函数说明： 修正加速度数据
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
***********************************************************************/
void InertialSensor_Backend::correctAccel(void)
{

}

/***********************************************************************
** 函 数 名： InertialSensor_Backend::correctGyro()
** 函数说明： 修正陀螺仪数据
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
***********************************************************************/
void InertialSensor_Backend::correctGyro(void)
{
//	gyro_calib = gyro;
  gyro_calib.x = gyro.x - gyro_offset.x;
  gyro_calib.y = gyro.y - gyro_offset.y;
  gyro_calib.z = gyro.z - gyro_offset.z;
}

/***********************************************************************
** 函 数 名： InertialSensor_Backend::publishAccel()
** 函数说明： 发布加速度数据
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
***********************************************************************/
void InertialSensor_Backend::publishAccel(void)
{
  imu.accel[id] = accel;
}

/***********************************************************************
** 函 数 名： InertialSensor_Backend::publishAccel()
** 函数说明： 发布陀螺仪数据
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
***********************************************************************/
void InertialSensor_Backend::publishGyro(void)
{
  imu.gyro[id] = gyro_calib;
}

}