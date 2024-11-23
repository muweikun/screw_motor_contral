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
#ifndef __ROBO_LIB_INERTIALSENSOR_H__
#define __ROBO_LIB_INERTIALSENSOR_H__

#include "Libraries/Error/Error.h"
#include "Libraries/Math/Vector3.h"

#define MAX_INERTIALSENSOR_BACKEND_NUM 3
namespace robo_lib
{

enum RotationPreset
{
  ROTATION_NONE                = 0,
  ROTATION_YAW_45              = 1,
  ROTATION_YAW_90              = 2,
  ROTATION_YAW_135             = 3,
  ROTATION_YAW_180             = 4,
  ROTATION_YAW_225             = 5,
  ROTATION_YAW_270             = 6,
  ROTATION_YAW_315             = 7,
  ROTATION_ROLL_180            = 8,
  ROTATION_ROLL_180_YAW_45     = 9,
  ROTATION_ROLL_180_YAW_90     = 10,
  ROTATION_ROLL_180_YAW_135    = 11,
  ROTATION_PITCH_180           = 12,
  ROTATION_ROLL_180_YAW_225    = 13,
  ROTATION_ROLL_180_YAW_270    = 14,
  ROTATION_ROLL_180_YAW_315    = 15,
  ROTATION_ROLL_90             = 16,
  ROTATION_ROLL_90_YAW_45      = 17,
  ROTATION_ROLL_90_YAW_90      = 18,
  ROTATION_ROLL_90_YAW_135     = 19,
  ROTATION_ROLL_270            = 20,
  ROTATION_ROLL_270_YAW_45     = 21,
  ROTATION_ROLL_270_YAW_90     = 22,
  ROTATION_ROLL_270_YAW_135    = 23,
  ROTATION_PITCH_90            = 24,
  ROTATION_PITCH_270           = 25,
  ROTATION_PITCH_180_YAW_90    = 26, // same as ROTATION_ROLL_180_YAW_270
  ROTATION_PITCH_180_YAW_270   = 27, // same as ROTATION_ROLL_180_YAW_90
  ROTATION_ROLL_90_PITCH_90    = 28,
  ROTATION_ROLL_180_PITCH_90   = 29,
  ROTATION_ROLL_270_PITCH_90   = 30,
  ROTATION_ROLL_90_PITCH_180   = 31,
  ROTATION_ROLL_270_PITCH_180  = 32,
  ROTATION_ROLL_90_PITCH_270   = 33,
  ROTATION_ROLL_180_PITCH_270  = 34,
  ROTATION_ROLL_270_PITCH_270  = 35,
  ROTATION_ROLL_90_PITCH_180_YAW_90 = 36,
  ROTATION_ROLL_90_YAW_270     = 37,
  ROTATION_ROLL_90_PITCH_68_YAW_293 = 38, // this is actually, roll 90, pitch 68.8, yaw 293.3
  ROTATION_PITCH_315           = 39,
  ROTATION_ROLL_90_PITCH_315   = 40,
  ROTATION_PITCH_7             = 41,
  ROTATION_ROLL_45             = 42,
  ROTATION_ROLL_315            = 43,
  ///////////////////////////////////////////////////////////////////////
  // Do not add more rotations without checking that there is not a conflict
  // with the MAVLink spec. MAV_SENSOR_ORIENTATION is expected to match our
  // list of rotations here. If a new rotation is added it needs to be added
  // to the MAVLink messages as well.
  ///////////////////////////////////////////////////////////////////////
  ROTATION_MAX,
  ROTATION_CUSTOM_OLD          = 100,
  ROTATION_CUSTOM_1            = 101,
  ROTATION_CUSTOM_2            = 102,
  ROTATION_CUSTOM_END,
};

// 声明惯性传感器backend类
class InertialSensor_Backend;

// 惯性传感器
class InertialSensor
{
public:
  InertialSensor();
  friend class InertialSensor_Backend;
  friend class InertialSensor_BMI088;
  void init(void);
  void update(void);

  // 获取相应id的imu(单imu时默认id为0)的加速度
robo_lib::Vector3f getAccel(uint16_t id = 0)
  {
    return accel[id];
  }

  // 获取相应id的imu(单imu时默认id为0)的陀螺仪数据
  robo_lib::Vector3f getGyro(uint16_t id = 0)
  {
    return gyro[id];
  }

  // 获取相应id的imu(单imu时默认id为0)的温度
  float getTemperature(uint16_t id = 0);

  // 获取相应id的imu(单imu时默认id为0)的数据有效性
  bool isValid(uint16_t id = 0)
  {
    return valid[id];
  }

  bool isInited(uint16_t id = 0)
  {
    return inited[id];
  }
  InertialSensor_Backend * findBackendById(uint8_t id)
  {
    if(id < backend_count)
      return backends[id];
    else
    {
#ifdef DEBUG_MODE
      error.error_code.inertial_sensor_find_id_out_of_range = 1;
      error.Error_Handler();
      return 0;
#endif
    }
  }

  void calibGyro(uint16_t id = 0, uint32_t cnt = 10000);
  uint8_t addBackend(InertialSensor_Backend *backend);

protected:
  void detectBackend(void);

  InertialSensor_Backend *backends[MAX_INERTIALSENSOR_BACKEND_NUM];
  uint16_t backend_count;

  // 各imu的安装方向
  RotationPreset gyro_orientation[MAX_INERTIALSENSOR_BACKEND_NUM];
  RotationPreset accel_orientation[MAX_INERTIALSENSOR_BACKEND_NUM];

  robo_lib::Vector3f gyro[MAX_INERTIALSENSOR_BACKEND_NUM];
  robo_lib::Vector3f accel[MAX_INERTIALSENSOR_BACKEND_NUM];

  bool valid[MAX_INERTIALSENSOR_BACKEND_NUM];

  bool inited[MAX_INERTIALSENSOR_BACKEND_NUM];

};
}
#endif
