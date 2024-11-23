/**
  ******************************************************************************
  * @file    MahonyAHRS.cpp
  * @version 2.0
  * @author  DUT-Lingbug Embedded Group
  * @brief   姿态解算MahonyAHRS算法
  *
  ******************************************************************************
  * @attention
  *
  * Copyright 2023 DUT-Lingbug.
  * All rights reserved.
  *
  ******************************************************************************
  */

#include "Libraries/AHRS/MahonyAHRS.h"
#include "Libraries/Math/Quaternion.h"
#include "arm_math.h"
namespace robo_lib
{
/**
  * @brief  None
  * @note   None
  * @param  two_kp0, two_ki0
  * @retval None
  */
MahonyAHRS::MahonyAHRS(float two_kp0, float two_ki0): sample_freq(SAMPLE_FREQ_DEF)
{
  two_ki = two_ki0;
  two_kp = two_kp0;
}

/**
  * @brief  初始化参数
  * @note   None
  * @param  None
  * @retval None
  */
void MahonyAHRS::init(void)
{
  integral_fb.zero();

  imu_quat.w = 1.0f;
  imu_quat.x = .0f;
  imu_quat.y = .0f;
  imu_quat.z = .0f;
}

/**
  * @brief  Mahony算法计算出四元数
  * @note   accel in [m/s^2], gyro in [rad/s]
  * @param  三轴加速度，三轴角速度
  * @retval None
  */
void MahonyAHRS::update(robo_lib::Vector3f accel, robo_lib::Vector3f gyro)
{
  float recipNorm;
  robo_lib::Vector3f halfv, halfe, q_temp;
  // accel 为非零向量时方可进入
  if(!accel.isZero())
  {
    accel.normalize(); // 标准化

    // 估计重力方向和垂直于磁通量的矢量
    halfv.x = imu_quat.x * imu_quat.z - imu_quat.w * imu_quat.y;
    halfv.y = imu_quat.w * imu_quat.x + imu_quat.y * imu_quat.z;
    halfv.z = imu_quat.w * imu_quat.w - 0.5f + imu_quat.z * imu_quat.z;

    // 误差是估计的重力方向与测量的重力方向的向量积之和
    halfe.x = accel.y * halfv.z - accel.z * halfv.y;
    halfe.y = accel.z * halfv.x - accel.x * halfv.z;
    halfe.z = accel.x * halfv.y - accel.y * halfv.x;

    if(two_ki > 0.0f)
    {
      integral_fb.x += two_ki * halfe.x * (1.0f / sample_freq);
      integral_fb.y += two_ki * halfe.y * (1.0f / sample_freq);
      integral_fb.z += two_ki * halfe.z * (1.0f / sample_freq);
      gyro.x += integral_fb.x;
      gyro.y += integral_fb.y;
      gyro.z += integral_fb.z;
    }
    else
    {
      integral_fb.zero();
    }
    gyro.x += two_kp * halfe.x;
    gyro.y += two_kp * halfe.y;
    gyro.z += two_kp * halfe.z;
  }

  gyro.x *= (0.5f * (1.0f / sample_freq));
  gyro.y *= (0.5f * (1.0f / sample_freq));
  gyro.z *= (0.5f * (1.0f / sample_freq));

  q_temp.x = imu_quat.w;
  q_temp.y = imu_quat.x;
  q_temp.z = imu_quat.y;

  imu_quat.w += (-q_temp.y * gyro.x - q_temp.z * gyro.y - imu_quat.z * gyro.z);
  imu_quat.x += ( q_temp.x * gyro.x + q_temp.z * gyro.z - imu_quat.z * gyro.y);
  imu_quat.y += ( q_temp.x * gyro.y - q_temp.y * gyro.z + imu_quat.z * gyro.x);
  imu_quat.z += ( q_temp.x * gyro.z + q_temp.y * gyro.y - q_temp.z * gyro.x);

  imu_quat.normalize();

  // pitch
  imu_euler.pitch = asinf(-2.0f * (imu_quat.x * imu_quat.z - imu_quat.w * imu_quat.y));

  // roll
  imu_euler.roll = atan2f(2.0f * (imu_quat.w * imu_quat.x + imu_quat.y * imu_quat.z), 2.0f * (imu_quat.w * imu_quat.w + imu_quat.z * imu_quat.z) - 1.0f);

  // yaw
  imu_euler.yaw = atan2f(2.0f * (imu_quat.w * imu_quat.z + imu_quat.x * imu_quat.y), 2.0f * (imu_quat.w * imu_quat.w + imu_quat.x * imu_quat.x) - 1.0f);

  imu_coordinate_system = imu_quat.toRotationMatrix();

}

void MahonyAHRS::setSampleFreq(float freq)
{
  this->sample_freq = freq;
}

float MahonyAHRS::getSampleFreq(void)
{
  return this->sample_freq;
}

/**
  * @brief  Mahony算法计算出四元数
  * @note   accel in [m/s^2], gyro in [rad/s]
  * @param  三轴加速度，三轴角速度
  * @retval None
  */
void MahonyAHRS::update(robo_lib::Vector3f accel, robo_lib::Vector3f gyro, robo_lib::Vector3f mag)
{
}

}