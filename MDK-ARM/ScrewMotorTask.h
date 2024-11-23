#pragma once 
#include "Modules/MotorTask/Motor_RM_Tasks.h"
#include "Modules/RoboBase/Task_RoboBase.h"

class Srew_Motor_PIDControlTask : public Task_RoboBase{
public:
	friend class Robot;
		Srew_Motor_PIDControlTask(
	     Robot &robot0,
       robo_lib::Motor_RM_Params_t *m1, robo_lib::PID_Params_t *m1_ang, robo_lib::PID_Params_t *m1_ang_vel,
			 timeus_t interval_tick_us0 = 0);

    virtual void init(void);
    virtual void uninit(void);
    virtual void update(timeus_t dT_us);

protected:
	Motor_RM_PIDControlTask *motor_1_pid_task;
  int16_t motor_input[4];
  int16_t motor_rpm[4];
	
	
};