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
#ifndef __ROBO_LIB_INERTIALSENSOR_BACKEND_H__
#define __ROBO_LIB_INERTIALSENSOR_BACKEND_H__

#include "stdint.h"
#include "Libraries/InertialSensor/InertialSensor.h"
#include "Libraries/Math/Filters.h"
namespace robo_lib
{
// ���Դ�����backend�Ļ���
class InertialSensor_Backend
{
public:
  friend class InertialSensor;
  InertialSensor_Backend(InertialSensor &imu0);
  virtual bool init() = 0;
  virtual bool update() = 0;

protected:
  InertialSensor &imu;
  virtual void updateAccel(void) = 0; // ���¼��ٶ����ݣ���ѯ
  virtual void updateGyro(void) = 0;	// �������������ݣ���ѯ
  void correctAccel(void); // �������ٶ����ݣ���ѯ
  void correctGyro(void);	// �������������ݣ���ѯ
  void publishAccel(void);
  void publishGyro(void);
  virtual float getTemperature(void) = 0;
  virtual void calibGyro(uint32_t cnt) = 0;

  // ����imu��id
  uint16_t getId()
  {
    return id;
  }

  uint16_t id; // ��̨ID

  robo_lib::Vector3f gyro; // ���ٶ�����
  robo_lib::Vector3f accel; // ���ٶ�����
  
  robo_lib::LowPassFilter<robo_lib::Vector3f> accel_lpf;
  robo_lib::LowPassFilter<robo_lib::Vector3f> gyro_lpf;


  robo_lib::Vector3f gyro_offset; // ��������Ưֵ
  robo_lib::Vector3f gyro_calib; // �������������ֵ
};
}
#endif
