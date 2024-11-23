/**
  ******************************************************************************
  * @file    AHRS.cpp
  * @version 2.0
  * @author  DUT-Lingbug Embedded Group
  * @brief   ◊ÀÃ¨Ω‚À„AHRSª˘¿‡
  *
  ******************************************************************************
  * @attention
  *
  * Copyright 2023 DUT-Lingbug.
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef _CANSENDTASK_H_
#define _CANSENDTASK_H_

#include "Libraries/Scheduler/Task.h"
#include "Libraries/CanDevice/CanDevice.h"

class Robot;

class CANSendTask : public robo_lib::Task_Base
{
public:

  CANSendTask(Robot &robot0, robo_lib::CanDevice* device0, timeus_t interval_tick_us0 = 50); // 20kHz

  virtual ~CANSendTask(void) {}

  virtual void init(void);

  virtual void update(timeus_t dT_us);

  virtual void uninit(void);

protected:
  robo_lib::CanDevice* device;
};

#endif