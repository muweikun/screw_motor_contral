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

#include "Libraries/AHRS/AHRS.h"
namespace robo_lib
{
/**
  * @brief  ����imu��Ԫ��
  * @note   None
  * @param  None
  * @retval None
  */
robo_lib::QuaternionF AHRS::getIMUQuat(void) const
{
  return imu_quat;
}

/**
  * @brief  ����imuŷ����
  * @note   None
  * @param  None
  * @retval None
  */
robo_lib::EulerAngleF AHRS::getIMUEuler(void) const
{
  return imu_euler;
}

/**
  * @brief  ����imu����ϵ
  * @note   None
  * @param  None
  * @retval None
  */
robo_lib::Matrix3f AHRS::getIMUCoordinateSystem(void) const
{
  return imu_coordinate_system; // imu����������������ϵ�е�����
}
}
