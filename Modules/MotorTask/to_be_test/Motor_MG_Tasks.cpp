/***************************************************************************
**   					             大连理工大学 凌BUG战队
**   					               凌以青云，翥以极心!
**-------------------------------------------------------------------------
** 项    目：   robo_template
** 文 件 名：   MotorMG_ControlTask.cpp
** 文件说明：   电机控制任务
**-------------------------------------------------------------------------
**						*修订*
**	*版本*							*修改内容*							*修改人*      			 *日期*
**	 1.0							   初始版本						       沈申浩     	     2022-12-22
**  1.1                                                      孔明骏
***************************************************************************/

#include "Modules/MotorTask/Motor_MG_Tasks.h"
#include "Modules/RoboBase/RoboBase.h"
#include "Libraries/Motor/Motor_MG.h"

/***********************************************************************
** 函 数 名： Motor_MG_PIDControlTask构造函数
** 函数说明： 指定robot引用，CAN设备引用，指定电机CAN总线id
**            和CAN总线数据包发送起始下标，指定电机类型，
**            实例化并注册电机角度环和速度环PID_Motor_MG_ControlTask任务，
**            实例化Motor_MG基类，并在robot0引用中添加Backend
**---------------------------------------------------------------------
** 输入参数： robot引用、CAN设备引用、电机CAN总线id、
**            CAN总线数据包发送起始下标、电机类型
** 返回参数： 无
***********************************************************************/
Motor_MG_ControlTask::Motor_MG_ControlTask(
  RoboBase &robot0,
  robo_lib::CanDevice &_can_device,
  uint16_t _can_rx_id, uint16_t _can_tx_id,
  uint8_t  _can_tx_data_start_pos,
  int8_t   _motor_type,
  timeus_t interval_tick_us0
)
  : Task_RoboBase(robot0), can_device(_can_device)
{

  this->interval_tick_us = interval_tick_us0; // 电机编码器解算频率
  can_tx_data_start_pos = _can_tx_data_start_pos;
  motor_backend_p = new robo_lib::Motor_MG(robot0.getMotors(), _can_device, _can_tx_id, _can_rx_id, _can_tx_data_start_pos, _motor_type);
  robot0.getMotors().addBackend(motor_backend_p);
}




/***********************************************************************
** 函 数 名： Motor_MC_ControlTask::init()
** 函数说明： 任务初始化
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
***********************************************************************/
void Motor_MG_ControlTask::init(void)
{
//		motor_backend_p->cmdMotorStop();
//	   motor_backend_p->cmdMotorShutOff();
}

/***********************************************************************
** 函 数 名： Motor_MC_ControlTask::uninit()
** 函数说明： 任务反初始化
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
***********************************************************************/
void Motor_MG_ControlTask::uninit(void)
{

}




/***********************************************************************
** 函 数 名： Motor_MC_ControlTask::update(timeus_t dT_us)
** 函数说明： 任务更新，运行motor_backend_p->update()
**---------------------------------------------------------------------
** 输入参数： 更新时间间隔（us）
** 返回参数： 无
***********************************************************************/
void Motor_MG_ControlTask::update(timeus_t dT_us)
{
  if(motor_backend_p != NULL)
  {
    motor_backend_p->update(dT_us);
  }


//  //修改PID值
//  //写入RAM掉电不保存
//    if(motor_backend_p->PIDchange_flag == 1)
//  {
//     motor_backend_p->setPIDParams_RAM(motor_backend_p->pid_params);
//  }
//    if(motor_backend_p->getCANRxDataPointer()->data[0] == 0x31)
//    {
//	  motor_backend_p->MG_motor_reply();
//	  motor_backend_p->PIDchange_flag = 0;
//    }
//
//  //写入ROM掉电保存
//  if(motor_backend_p->PIDchange_flag == 2)
//  {
//     motor_backend_p->setPIDParams_ROM(motor_backend_p->pid_params);
//  }
//    if(motor_backend_p->getCANRxDataPointer()->data[0] == 0x32)
//    {
//	  motor_backend_p->MG_motor_reply();
//	  motor_backend_p->PIDchange_flag = 0;
//    }
  //读取多圈编码器数据
  //关闭电机输出，同时清除电机运行状态和之前接收的控制指令(0x80)


//以下要用
  if(motor_backend_p->getCANRxDataPointer()->data[0] == 0x80)
  {
    motor_backend_p->MG_motor_reply();
  }

  if(motor_backend_p->getCANRxDataPointer()->data[0] == 0x81)
  {
    motor_backend_p->MG_motor_reply();
  }

  motor_backend_p->getMultiLoopAngle();
  if(motor_backend_p->getCANRxDataPointer()->data[0] == 0x92)
  {
    motor_backend_p->MG_motor_reply();
  }
  motor_backend_p->getSingleLoopAngle();
  if(motor_backend_p->getCANRxDataPointer()->data[0] == 0x94)
  {
    motor_backend_p->MG_motor_reply();
  }

  if(motor_backend_p->can_update_flag == 0)
  {
    motor_backend_p->cmdAngleControl(motor_backend_p->getParams_p()->max_speed, motor_backend_p->getParams_p()->angle_control);
    motor_backend_p->angle_update_flag = 0;
  }
  if(motor_backend_p->getCANRxDataPointer()->data[0] == 0xA4)
  {
    motor_backend_p->MG_motor_reply();
  }



}
/***********************************************************************
** 函 数 名： Motor_MG_ControlTask::setHomePosition()
** 函数说明： 上电复位
**---------------------------------------------------------------------
** 输入参数： 更新时间间隔（us）
** 返回参数： 无
***********************************************************************/
void Motor_MG_ControlTask::setHomePosition()
{
  motor_backend_p->getParams_p()->angle_control = 0;
}
