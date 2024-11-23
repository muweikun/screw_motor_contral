#ifndef MOTOR_MC_TASKS_H
#define MOTOR_MC_TASKS_H

#include "Libraries/Scheduler/Task.h"
#include "stdint.h"
#include "Libraries/PID/PID_Controller.h"
#include "Libraries/Motor/Motor.h"
#include "Libraries/CanDevice/CanDevice.h"
#include "Libraries/Motor/Motor_MC.h"
#include "Modules/CANTask/CANSendTask.h"
#include "Modules/PIDTask/PIDControlTask.h"
#include "Modules/RoboBase/Task_RoboBase.h"

class Motor_MC_ControlTask : public Task_RoboBase
{
public:
//  friend class Robot;
//  friend class Arm_ControlTask;
//  friend class RemoteControlTask;
//  friend class Motor_MC;

  Motor_MC_ControlTask(
    RoboBase &robot0,
    robo_lib::CanDevice &_can_device,
    uint16_t _can_rx_id, uint16_t _can_tx_id,
    uint8_t _can_tx_data_start_pos,
    int8_t _motor_type,
    timeus_t interval_tick_us0 = 0

  );

  virtual ~Motor_MC_ControlTask(void) {}

  virtual void init(void);

  virtual void update(timeus_t dT_us);

  virtual void uninit(void);

  void setHomePosition();//电机上电复位

  PIDControlTask* getAngleTaskPointer()
  {
    return angle_control_task_p;
  }
  PIDControlTask* getAngularVelocityTaskPointer()
  {
    return angular_velocity_control_task_p;
  }

  robo_lib::Motor_MC * get_motor_backend_p()
  {
    return motor_backend_p;
  }

protected:
  robo_lib::Motor_MC *motor_backend_p;
  robo_lib::CanDevice &can_device;
  uint8_t can_tx_data_start_pos;
  // CANSendTask *can_send_task_p;
  // CAN_Rx_Data_Pack_t can_rx_data;
  PIDControlTask *angle_control_task_p;
  PIDControlTask *angular_velocity_control_task_p;

};


#endif
