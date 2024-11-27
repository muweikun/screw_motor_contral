#include "./Robot.h"
#include "./Libraries/UART/UARTDriver.h"
#include "tim.h"

using namespace robo_lib;
extern CAN_HandleTypeDef hcan1;
extern CAN_HandleTypeDef hcan2;
/***********************************************************************
** 函 数 名： Robot::init()
** 函数说明： 机器人系统初始化
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
***********************************************************************/
void Robot::init()
{
  // 初始化各项参数
  params.initMotorsParams(robot_id);
	
  srew_motor1_p = new Srew_Motor_PIDControlTask(*this,&params.device_params.chassis_motor_1,NULL,&params.device_params.chassis_motor_1_ang_vel,params.device_params.chassis_motor_1.interval);
	can1_device.init(&hcan1, can1_queue_data, CAN1_TX_BUF_LEN);
	
 // CAN发送任务实例化
	 can1_send_task_p = new CANSendTask(
        *this,
        &this->can1_device);
	 can1_sync_task_0x200_p = new CANSyncTask(
        *this,
        &(this->can1_device),
        0x200,
        params.device_params.control_tasks_interval.can1_send_0x200_task_interval
    );
	// 遥控器任务初始化
	 rc_protocol.init();
	// 播放器初始化
	play_sound_task_p =new PlaySoundManageTask(*this);
 
	
	//注册任务
  HAL_TIM_Base_Start_IT(&htim2);
  HAL_TIM_Base_Start_IT(&htim5);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);  
  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);  
  HAL_TIM_PWM_Start(&htim10, TIM_CHANNEL_1); 
  USART1_DMA_Tx_Init();
				
	srew_motor1_p->setInterval(params.device_params.chassis_motor_1.interval);
	
	/* 注册任务 */
	scheduler.registerTask(srew_motor1_p);
	scheduler.registerTask(can1_send_task_p);
	scheduler.registerTask(can1_sync_task_0x200_p);
	scheduler.registerTask(play_sound_task_p);
	
}

/***********************************************************************
** 函 数 名： Robot::run()
** 函数说明： 机器人系统运行函数，此函数运行在主循环中
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
***********************************************************************/
void Robot::run()
{
  scheduler.run();
}
