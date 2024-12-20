/***************************************************************************
**   					             大连理工大学 凌BUG战队
**   					               凌以青云，翥以极心!
**-------------------------------------------------------------------------
** 项    目：   robo_template
** 文 件 名：   AttitudeSolutionTask.cpp
** 文件说明：   姿态解算任务
**-------------------------------------------------------------------------
**						*修订*
**	*版本*							*修改内容*							*修改人*      			 *日期*
**	 1.0							   初始版本						     季献淏     	   2022-07-08
**   1.1              加入IMU控温任务            林子涵          2022-07-25
**	 1.2							   补充注释						     赵钟源     	   2022-12-10
***************************************************************************/

#include "Modules/AttitudeSolutionTask/AttitudeSolutionTask.h"
#include "Modules/RoboBase/RoboBase.h"
#include "arm_math.h"

extern TIM_HandleTypeDef htim10;


/***********************************************************************
** 函 数 名： AttitudeSolutionTask::init()
** 函数说明： 初始化惯性测量传感器、姿态解算算法，
              创建IMU控温任务（PID）并初始化
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
***********************************************************************/
void AttitudeSolutionTask::init(void)
{
	robot.getInertialSensor().findBackendById(0);
	
  pid_gyrotemp_task_p ->init(); // 初始化控温任务
//  robot.scheduler.registerTask(pid_gyrotemp_task_p);
//
  robot.getInertialSensor().init(); // 初始化IMU

//  while(robot.getInertialSensor().getTemperature() < 45.0f)
//  {
//    HAL_Delay(100);
//  }
//  robot.getInertialSensor().calibGyro();


  ahrs.init(); // 初始化AHRS
	inited = true;
}

/***********************************************************************
** 函 数 名： AttitudeSolutionTask::update(timeus_t dT_us)
** 函数说明： 更新传感器读取、姿态解算
**---------------------------------------------------------------------
** 输入参数： 更新时间间隔（us）
** 返回参数： 无
***********************************************************************/
void AttitudeSolutionTask::update(timeus_t dT_us)
{
  update_freq = 1e6f / dT_us;
  robot.getInertialSensor().update(); // IMU更新
  ahrs.update(robot.getInertialSensor().getAccel(), robot.getInertialSensor().getGyro()); // 姿态解算更新
}

/***********************************************************************
** 函 数 名： AttitudeSolutionTask::uninit()
** 函数说明： 任务反初始化
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
***********************************************************************/
void AttitudeSolutionTask::uninit(void)
{

}


// IMU控温


/***********************************************************************
** 函 数 名： PID_GyrotempTask::init()
** 函数说明： 初始化IMU控温任务PID参数
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
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
** 函 数 名： PID_GyrotempTask::update(timeus_t dT_us)
** 函数说明： 更新IMU控温任务PID计算
**---------------------------------------------------------------------
** 输入参数： 更新时间间隔
** 返回参数： 无
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
** 函 数 名： PID_GyrotempTask::uninit()
** 函数说明： 任务反初始化
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
***********************************************************************/
void PID_GyrotempTask::uninit(void)
{

}
