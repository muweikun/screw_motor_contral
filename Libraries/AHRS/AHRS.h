/**
  ******************************************************************************
  * @file    AHRS.h
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
#ifndef __ROBO_LIB_AHRS_H__
#define __ROBO_LIB_AHRS_H__

#include "stdint.h"
#include "/Libraries/Math/Vector3.h"
#include "/Libraries/Math/Quaternion.h"
#include "/Libraries/Math/Matrix3.h"
#include "/Libraries/Math/EulerAngle.h"

namespace robo_lib
{
class AHRS
{
  friend class MahonyAHRS;
public:
  virtual void init(void) = 0;
  virtual void update(robo_lib::Vector3f accel, robo_lib::Vector3f gyro) = 0; // 加速度计，角速度计
  virtual void update(robo_lib::Vector3f accel, robo_lib::Vector3f gyro, robo_lib::Vector3f mag) = 0; // 加速度计，角速度计，磁力计
  robo_lib::QuaternionF getIMUQuat(void) const;
  robo_lib::EulerAngleF getIMUEuler(void) const;
  robo_lib::Matrix3f getIMUCoordinateSystem(void) const;

protected:
  robo_lib::QuaternionF imu_quat;
  robo_lib::EulerAngleF imu_euler;
  robo_lib::Matrix3f imu_coordinate_system;
};

}
#endif
