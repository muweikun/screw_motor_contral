#ifndef PARAMS_H
#define PARAMS_H

#include <stdint.h>
#include "Libraries/Motor/Motor_RM.h"            
#include "Libraries/Motor/Motor_DM.h"
#include "Modules/MotorTask/Motor_RM_Tasks.h"
#include "Modules/MotorTask/Motor_DM_Task.h"
#include "Libraries/PID/PID_Controller.h"

typedef struct _Control_Tasks_Interval_t
{
	  float can1_send_0x200_task_interval;
	  float screw_task_interval;
  
} Control_Tasks_Interval_t;


typedef struct _Init_Params_t
{
  Control_Tasks_Interval_t control_tasks_interval;
	robo_lib::Motor_RM_Params_t chassis_motor_1;
	int16_t motor_rpm_expect[4]={200,200,200,200};
	robo_lib::PID_Params_t chassis_motor_1_ang_vel;
} Init_Params_t;

class Robot;
class Params
{
public:

  Params(){}
  void initMotorsParams(uint8_t ROBOT_ID);
  Init_Params_t device_params;
	
protected:
	

};




#endif