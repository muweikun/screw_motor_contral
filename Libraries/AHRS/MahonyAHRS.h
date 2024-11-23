/**
  ******************************************************************************
  * @file    MahonyAHRS.h
  * @version 2.0
  * @author  DUT-Lingbug Embedded Group
  * @brief   ◊ÀÃ¨Ω‚À„MahonyAHRSÀ„∑®
  *
  ******************************************************************************
  * @attention
  *
  * Copyright 2023 DUT-Lingbug.
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef __ROBO_LIB_MAHONYAHRS_H__
#define __ROBO_LIB_MAHONYAHRS_H__

#include "stdint.h"
#include "/Libraries/Math/Vector3.h"
#include "/Libraries/Math/Quaternion.h"
#include "/Libraries/AHRS/AHRS.h"

#define TWO_KP_DEF	(2.0f * 0.5f)	// 2 * proportional gain
#define TWO_KI_DEF	(2.0f * 0.0f)	// 2 * integral gain
#define SAMPLE_FREQ_DEF 800.0f 		// by default sample frequency is 800Hz
namespace robo_lib
{
class MahonyAHRS : public AHRS
{
public:
  MahonyAHRS(float two_kp0 = TWO_KP_DEF, float two_ki0 = TWO_KI_DEF);
  virtual void init(void);
  virtual void update(robo_lib::Vector3f accel, robo_lib::Vector3f gyro);
  virtual void update(robo_lib::Vector3f accel, robo_lib::Vector3f gyro, robo_lib::Vector3f mag);
  void setSampleFreq(float freq);
  float getSampleFreq(void);

protected:
  float two_kp;
  float two_ki;
  robo_lib::Vector3f integral_fb; // integral error terms scaled by Ki
  float sample_freq;
};
}
#endif
