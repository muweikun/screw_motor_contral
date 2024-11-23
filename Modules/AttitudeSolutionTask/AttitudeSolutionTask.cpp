/***************************************************************************
**   					             ��������ѧ ��BUGս��
**   					               �������ƣ����Լ���!
**-------------------------------------------------------------------------
** ��    Ŀ��   robo_template
** �� �� ����   AttitudeSolutionTask.cpp
** �ļ�˵����   ��̬��������
**-------------------------------------------------------------------------
**						*�޶�*
**	*�汾*							*�޸�����*							*�޸���*      			 *����*
**	 1.0							   ��ʼ�汾						     ���לB     	   2022-07-08
**   1.1              ����IMU��������            ���Ӻ�          2022-07-25
**	 1.2							   ����ע��						     ����Դ     	   2022-12-10
***************************************************************************/

#include "Modules/AttitudeSolutionTask/AttitudeSolutionTask.h"
#include "Modules/RoboBase/RoboBase.h"
#include "arm_math.h"

extern TIM_HandleTypeDef htim10;


/***********************************************************************
** �� �� ���� AttitudeSolutionTask::init()
** ����˵���� ��ʼ�����Բ�������������̬�����㷨��
              ����IMU��������PID������ʼ��
**---------------------------------------------------------------------
** ��������� ��
** ���ز����� ��
***********************************************************************/
void AttitudeSolutionTask::init(void)
{
	robot.getInertialSensor().findBackendById(0);
	
  pid_gyrotemp_task_p ->init(); // ��ʼ����������
//  robot.scheduler.registerTask(pid_gyrotemp_task_p);
//
  robot.getInertialSensor().init(); // ��ʼ��IMU

//  while(robot.getInertialSensor().getTemperature() < 45.0f)
//  {
//    HAL_Delay(100);
//  }
//  robot.getInertialSensor().calibGyro();


  ahrs.init(); // ��ʼ��AHRS
	inited = true;
}

/***********************************************************************
** �� �� ���� AttitudeSolutionTask::update(timeus_t dT_us)
** ����˵���� ���´�������ȡ����̬����
**---------------------------------------------------------------------
** ��������� ����ʱ������us��
** ���ز����� ��
***********************************************************************/
void AttitudeSolutionTask::update(timeus_t dT_us)
{
  update_freq = 1e6f / dT_us;
  robot.getInertialSensor().update(); // IMU����
  ahrs.update(robot.getInertialSensor().getAccel(), robot.getInertialSensor().getGyro()); // ��̬�������
}

/***********************************************************************
** �� �� ���� AttitudeSolutionTask::uninit()
** ����˵���� ���񷴳�ʼ��
**---------------------------------------------------------------------
** ��������� ��
** ���ز����� ��
***********************************************************************/
void AttitudeSolutionTask::uninit(void)
{

}


// IMU����


/***********************************************************************
** �� �� ���� PID_GyrotempTask::init()
** ����˵���� ��ʼ��IMU��������PID����
**---------------------------------------------------------------------
** ��������� ��
** ���ز����� ��
***********************************************************************/
void PID_GyrotempTask::init(void)
{
  robo_lib::PID_Params_t pid_params_instance;
  pid_params_instance.type_selection = robo_lib::PID_ABSOLUTE;
  pid_params_instance.kp = 2000;
  pid_params_instance.ki = 50;
  pid_params_instance.kd_fb = 500;
  pid_params_instance.kd_ex = 0.0;
  pid_params_instance.k_ff = 0;
  pid_params_instance.max_out_value = 2000;
  pid_params_instance.min_out_value = 100;
  pid_params_instance.limit_output = true;
  pid_params_instance.max_integral = 5;
  pid_params_instance.min_integral = -5;
  pid_params_instance.limit_integral = true;
  pid_params_instance.add = &(robo_lib::simple_adder_instance_f);
  pid_params_instance.kd_able_error_range = 0;
  pid_params_instance.ki_able_error_range = 0;

  pid_controller.setParams(pid_params_instance);
}

/***********************************************************************
** �� �� ���� PID_GyrotempTask::update(timeus_t dT_us)
** ����˵���� ����IMU��������PID����
**---------------------------------------------------------------------
** ��������� ����ʱ����
** ���ز����� ��
***********************************************************************/
void PID_GyrotempTask::update(timeus_t dT_us)
{
  bmi088_temperature = robot.getInertialSensor().getTemperature();

  if(bmi088_temperature < 42.0f)
  {
    __HAL_TIM_SetCompare(&htim10, TIM_CHANNEL_1, 2000);
  }
  else
  {
    pid_controller.calculateWithCPU(dT_us, 45.0f, bmi088_temperature, 0);
    __HAL_TIM_SetCompare(&htim10, TIM_CHANNEL_1, pid_controller.getOutput());
  }
}

/***********************************************************************
** �� �� ���� PID_GyrotempTask::uninit()
** ����˵���� ���񷴳�ʼ��
**---------------------------------------------------------------------
** ��������� ��
** ���ز����� ��
***********************************************************************/
void PID_GyrotempTask::uninit(void)
{

}
