#ifndef MOTOR_M15_TASK_H
#define MOTOR_M15_TASK_H

#include "Libraries/Scheduler/Task.h"
#include "stdint.h"
#include "Libraries/PID/PID_Controller.h"
#include "Libraries/Motor/Motor.h"
#include "Libraries/CanDevice/CanDevice.h"
#include "Libraries/Motor/Motor_M15.h"
#include "Modules/CANTask/CANSendTask.h"
#include "Modules/PIDTask/PIDControlTask.h"
#include "Modules/RoboBase/Task_RoboBase.h"

class Motor_M15_PoControlTask : public Task_RoboBase
{

public:
//	  friend class Arm_ControlTask;

  Motor_M15_PoControlTask(
    RoboBase &robot0,
    robo_lib::CanDevice &_can_device,
    uint16_t _can_rx_id, uint16_t _can_tx_id,
    uint8_t _can_tx_data_start_pos,
    int8_t _motor_type,
    timeus_t interval_tick_us0 = 0
  );

  virtual ~Motor_M15_PoControlTask(void) {}

  virtual void init(void);

  virtual void update(timeus_t dT_us);

  virtual void uninit(void);
  robo_lib::Motor_M15 * get_motor_backend_p()
  {
    return motor_backend_p;
  }


protected:

  robo_lib::Motor_M15 *motor_backend_p;
  robo_lib::CanDevice &can_device;
  uint8_t can_tx_data_start_pos;

};



#endif