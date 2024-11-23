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
#ifndef _PIDCONTROLTASK_H_
#define _PIDCONTROLTASK_H_

#include "Libraries/Scheduler/Task.h"
#include "stdint.h"
#include "Libraries/PID/PID_Controller.h"

class PIDControlTask : public robo_lib::Task_Base
{
public:
  PIDControlTask(RoboBase &robot0, timeus_t interval_tick_us0 = 0) : Task_Base()
  {
    this->interval_tick_us = interval_tick_us0;
  }

  virtual void init(void);
  virtual void update(timeus_t dT_us);
  virtual void uninit(void);

  // 设置PID参数结构体引用
  void setPIDControllerParams(const robo_lib::PID_Params_t &params)
  {
    pid_controller.setParams(params);
  }
  // 设置PID期望值
  void setPIDControllerExpect(float expect)
  {
    pid_controller.setExpect(expect);
  }
  // 设置PID反馈值
  void setPIDControllerFeedback(float feedback)
  {
    pid_controller.setFeedback(feedback);
  }
  // 设置PID前馈值
  void setPIDControllerFeedforward(float feedforward)
  {
    pid_controller.setFeedforward(feedforward);
  }
  // 设置PID输入值
  void setPIDControllerInput(float expect, float feedback, float feedforward)
  {
    pid_controller.setInput(expect, feedback, feedforward);
  }
  float getOutput()
  {
    return pid_controller.getOutput();
  }
  float getLimitedOutput()
  {
    return pid_controller.getLimitedOutput();
  }
  void limitOutput()
  {
    pid_controller.limitOutput();
  }
  void clearPID()
  {
    pid_controller.clear();
  }
  // 计算PID
  void calculatePID(timeus_t _dT_us,           //周期（us）
                    float _expect,			       //期望值
                    float _feedback,           //反馈值
                    float _feedforward = 0.0f  //前馈值
                   )
  {
    pid_controller.calculateWithCPU(_dT_us, _expect, _feedback, _feedforward);
  }
  // 计算PID
  void calculatePID(timeus_t _dT_us)     //周期（us）
  {
    pid_controller.calculateWithCPU(_dT_us);
//    pid_controller.calculateWithCPU(_dT_us,
//                             pid_controller.getPidData().expect,
//                             pid_controller.getPidData().feedback,
//                             pid_controller.getPidData().feedforward
//                            );
  }
  void printPID(void);

protected:
  robo_lib::PID_Controller pid_controller;
};

#endif