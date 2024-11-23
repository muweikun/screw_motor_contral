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
#ifndef __ROBO_LIB_INERTIALSENSOR_BMI088_H__
#define __ROBO_LIB_INERTIALSENSOR_BMI088_H__

#include "main.h"
#include "stdint.h"

#include "Libraries/InertialSensor/InertialSensor_Backend.h"
#include "Libraries/Math/Vector3.h"
#include "Libraries/PID/PID_Controller.h"
#include "Libraries/Scheduler/Scheduler.h"
namespace robo_lib
{
#define BMI088_BUF_LEN 6
#define BMI088_ACCEL_SCALE 0.00718260498046875f
#define BMI088_GYRO_SCALE 0.00106526443603169529841533860381f

// BMI088 backend类
class InertialSensor_BMI088 : public InertialSensor_Backend
{
public:
  InertialSensor_BMI088(InertialSensor &imu0, RotationPreset rotation_preset0);
  virtual bool init(void);
  virtual bool update(void);
  int16_t* getAccelRawPointer()
  {
    return accel_raw;
  }
  int16_t* getGyroRawPointer()
  {
    return gyro_raw;
  }
protected:
  RotationPreset rotation_preset;
  int16_t accel_raw[3];
  int16_t gyro_raw[3];

private:
  uint8_t readWriteByte(uint8_t tx_data);
  void writeSingleRegAccel(uint8_t reg, uint8_t data);
  uint8_t readSingleRegAccel(uint8_t reg);
  void readMultiRegAccel(uint8_t reg, uint8_t* buf, uint8_t num);
  void writeSingleRegGyro(uint8_t reg, uint8_t data);
  uint8_t readSingleRegGyro(uint8_t reg);
  void readMultiRegGyro(uint8_t reg, uint8_t* buf, uint8_t num);
  virtual void updateAccel(void);
  virtual void updateGyro(void);
  virtual float getTemperature(void);
  virtual void calibGyro(uint32_t cnt = 10000.0f);
  void rotateAccel(void);
  void rotateGyro(void);
};
}
#endif

