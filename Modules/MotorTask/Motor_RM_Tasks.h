/**
  ******************************************************************************
  * @file    AHRS.cpp
  * @version 2.0
  * @author  DUT-Lingbug Embedded Group
  * @brief   ×ËÌ¬½âËãAHRS»ùÀà
  *
  ******************************************************************************
  * @attention
  *
  * Copyright 2023 DUT-Lingbug.
  * All rights reserved.
  *
  ******************************************************************************
  */
#ifndef _MOTOR_CONTROL_TASKS_H_
#define _MOTOR_CONTROL_TASKS_H_

#include "Libraries/Scheduler/Task.h"
#include "stdint.h"
#include "Libraries/PID/PID_Controller.h"
#include "Libraries/Motor/Motor.h"
#include "Libraries/CanDevice/CanDevice.h"
#include "Libraries/Motor/Motor_RM.h"
#include "Modules/CANTask/CANSendTask.h"
#include "Modules/PIDTask/PIDControlTask.h"
#include "Modules/RoboBase/Task_RoboBase.h"

class Motor_RM_PIDControlTask : public Task_RoboBase
{
public:
//  friend class PID_MotorAngleControlTask;
//  friend class PID_MotorAngularVelocityControlTask;
//  friend class GimbalControlTask;
//  friend class ChassisControlTask;
//  friend class Robot;
//  friend class AmmoRM_ControlTask;

  Motor_RM_PIDControlTask(
    RoboBase &robot0,
    robo_lib::CanDevice &_can_device,
    uint16_t _can_rx_id,
    uint16_t _can_tx_id,
    uint8_t _can_tx_data_start_pos,
    int8_t _motor_type,
    timeus_t interval_tick_us0 = 0
  );

  virtual ~Motor_RM_PIDControlTask(void) {}

  virtual void init(void);

  virtual void update(timeus_t dT_us);

  virtual void uninit(void);

//  PID_MotorRM_ControlTask *getPIDMotorAngleControlTaskPointer(void)
//  {
//    return pid_motor_angle_control_task_p;
//  }
  void setPIDControllerParams(PIDControlTask &task, const robo_lib::PID_Params_t &params)
  {
    task.setPIDControllerParams(params);
  }
  PIDControlTask* getAngleTaskPointer()
  {
    return angle_control_task_p;
  }
  PIDControlTask* getAngularVelocityTaskPointer()
  {
    return angular_velocity_control_task_p;
  }
  robo_lib::Motor_Common_Measurement_t getComMsr()
  {
    return motor_backend_p->getCommonMeasurement();
  }
  robo_lib::Motor_RM_Measurement_t getMsr()
  {
    return motor_backend_p->getMeasurement();
  }
  void setMotorInput(int16_t input)
  {
    motor_backend_p->setMotorInput(input);
  }
  void setParams(robo_lib::Motor_RM_Params_t _params)
  {
    motor_backend_p->setParams(_params);
  }
  void setAngularVelocityIMU(float ang_v)
  {
    motor_backend_p->setAngularVelocityIMU(ang_v);
  }
  robo_lib::Motor_RM * get_motor_backend_p()
  {
    return motor_backend_p;
  }
//  void setPIDControllerInput(PID_MotorRM_ControlTask &task, float expect, float feedback, float in_ff)
//  {
//    task.pid_controller.getPIDDataPointer()->expect = expect;
//    task.pid_controller.getPIDDataPointer()->feedback = feedback;
//    task.pid_controller.getPIDDataPointer()->in_ff = in_ff;
//  }
protected:
  //Motor *motor;
  robo_lib::Motor_RM *motor_backend_p;
  robo_lib::CanDevice &can_device;
  uint8_t can_tx_data_start_pos;
  // CANSendTask *can_send_task_p;
  // CAN_Rx_Data_Pack_t can_rx_data;
  PIDControlTask *angle_control_task_p;
  PIDControlTask *angular_velocity_control_task_p;
};


#endif
