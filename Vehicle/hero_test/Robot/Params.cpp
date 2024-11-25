#include "./Params.h"
#include "./Robot.h"

using namespace robo_lib;

/***********************************************************************
** �� �� ���� Params::initMotorsParams()
** ����˵���� ��ʼ���������������PID����������ʱ�����ڲ���
**---------------------------------------------------------------------
** ��������� ��
** ���ز����� ��
***********************************************************************/
void Params::initMotorsParams(uint8_t ROBOT_ID)
{
	/************* �������� MINIpc CAN�� *************/
	
	
  /************** RM ��� CAN���ߵ�ַ **************/
	 this->device_params.chassis_motor_1 ={.can_tx_id = 0x200, .can_rx_id = 0x202, .can_tx_data_start_pos = 2, .canx = 1};
	

  /************** RM ��� CAN���ߵ�ַ **************/


  /**************  �������  **************/
	  device_params.chassis_motor_1.reduction_ratio = 13.5f;
    device_params.chassis_motor_1.output_radius = .075f;
    device_params.chassis_motor_1.direction = MOTOR_CW;
    device_params.chassis_motor_1.max_value_ecd = 8192;
    device_params.chassis_motor_1.offset_ecd = 0;

  /**************  �������  **************/



  /************** ���PID���� **************/
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
	 

  /************** ���PID���� **************/


  /************** ����Ƶ�� **************/
	device_params.chassis_motor_1.interval = 1e6f / 400.0f;
  device_params.chassis_motor_1_ang_vel.interval = 1e6f / 400.0f;
	
	    // CAN1 0x200��ַ��������
   device_params.control_tasks_interval.can1_send_0x200_task_interval = 1e6f / 400.0f;
	
	


  /************** ����Ƶ�� **************/


}

