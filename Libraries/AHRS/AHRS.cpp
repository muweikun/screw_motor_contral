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

#include "Libraries/AHRS/AHRS.h"
namespace robo_lib
{
/**
  * @brief  返回imu四元数
  * @note   None
  * @param  None
  * @retval None
  */
robo_lib::QuaternionF AHRS::getIMUQuat(void) const
{
  return imu_quat;
}

/**
  * @brief  返回imu欧拉角
  * @note   None
  * @param  None
  * @retval None
  */
robo_lib::EulerAngleF AHRS::getIMUEuler(void) const
{
  return imu_euler;
}

/**
  * @brief  返回imu坐标系
  * @note   None
  * @param  None
  * @retval None
  */
robo_lib::Matrix3f AHRS::getIMUCoordinateSystem(void) const
{
  return imu_coordinate_system; // imu基向量在世界坐标系中的坐标
}
}
