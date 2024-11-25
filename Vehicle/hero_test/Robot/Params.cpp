#include "./Params.h"
#include "./Robot.h"

using namespace robo_lib;

/***********************************************************************
** 函 数 名： Params::initMotorsParams()
** 函数说明： 初始化各个电机参数，PID参数和任务时间周期参数
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
***********************************************************************/
void Params::initMotorsParams(uint8_t ROBOT_ID)
{
	/************* 超级电容 MINIpc CAN包 *************/
	
	
  /************** RM 电机 CAN总线地址 **************/
	 this->device_params.chassis_motor_1 ={.can_tx_id = 0x200, .can_rx_id = 0x202, .can_tx_data_start_pos = 2, .canx = 1};
	

  /************** RM 电机 CAN总线地址 **************/


  /**************  电机参数  **************/
	  device_params.chassis_motor_1.reduction_ratio = 13.5f;
    device_params.chassis_motor_1.output_radius = .075f;
    device_params.chassis_motor_1.direction = MOTOR_CW;
    device_params.chassis_motor_1.max_value_ecd = 8192;
    device_params.chassis_motor_1.offset_ecd = 0;

  /**************  电机参数  **************/



  /************** 电机PID参数 **************/
	  device_params.chassis_motor_1_ang_vel.type_selection = PID_DELTA;
    device_params.chassis_motor_1_ang_vel.kp = 10000;
    device_params.chassis_motor_1_ang_vel.ki = 400000;
    device_params.chassis_motor_1_ang_vel.kd_fb = 0;
    device_params.chassis_motor_1_ang_vel.kd_ex = 0;
    device_params.chassis_motor_1_ang_vel.k_ff = 0;
    device_params.chassis_motor_1_ang_vel.max_out_value = 16300;
    device_params.chassis_motor_1_ang_vel.min_out_value = -16300;
    device_params.chassis_motor_1_ang_vel.limit_output = true;
    device_params.chassis_motor_1_ang_vel.max_integral = 0;
    device_params.chassis_motor_1_ang_vel.min_integral = -0;
    device_params.chassis_motor_1_ang_vel.limit_integral = true;
    device_params.chassis_motor_1_ang_vel.add = &simple_adder_instance_f;
    device_params.chassis_motor_1_ang_vel.kd_able_error_range = 0;
    device_params.chassis_motor_1_ang_vel.ki_able_error_range = 0;
	 

  /************** 电机PID参数 **************/


  /************** 任务频率 **************/
	device_params.chassis_motor_1.interval = 1e6f / 400.0f;
  device_params.chassis_motor_1_ang_vel.interval = 1e6f / 400.0f;
	
	    // CAN1 0x200地址发送任务
   device_params.control_tasks_interval.can1_send_0x200_task_interval = 1e6f / 400.0f;
	
	


  /************** 任务频率 **************/


}

