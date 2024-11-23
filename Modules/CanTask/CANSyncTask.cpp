/***************************************************************************
**   					             大连理工大学 凌BUG战队
**   					               凌以青云，翥以极心!
**-------------------------------------------------------------------------
** 项    目：   robo_template
** 文 件 名：   CANSyncTask.cpp
** 文件说明：   这个任务负责将CAN包以特定的频率加入CAN发送缓冲区
**-------------------------------------------------------------------------
**						*修订*
**	*版本*							*修改内容*							*修改人*      			 *日期*
**	 1.0							   初始版本						     林子涵     	   2022-07-18
**	 1.1							  加入TxLink					     林子涵     	   2022-07-26
**	 1.2							   补充注释						     赵钟源     	   2022-12-10
***************************************************************************/

#include "Modules/CanTask/CANSyncTask.h"

/***********************************************************************
** 函 数 名： CANSyncTask构造函数
** 函数说明： 指定CAN设备、CAN发送链接（CAN_Tx_Data_Link_t）、
              发送时间间隔
**---------------------------------------------------------------------
** 输入参数： CAN设备、CAN发送链接（CAN_Tx_Data_Link_t）、
              发送时间间隔
** 返回参数： 无
***********************************************************************/
CANSyncTask::CANSyncTask(Robot &robot0, robo_lib::CanDevice *can_device0, robo_lib::CAN_Tx_Data_Pack_t *tx_data, timeus_t interval_tick_us0) : Task_Base()
{
  push_msg = tx_data;
  can_device = can_device0;
  this->interval_tick_us = interval_tick_us0;
}
CANSyncTask::CANSyncTask(Robot &robot0, robo_lib::CanDevice &can_device0, robo_lib::CAN_Tx_Data_Pack_t *tx_data, timeus_t interval_tick_us0) : Task_Base()
{
  push_msg = tx_data;
  can_device = &can_device0;
  this->interval_tick_us = interval_tick_us0;
}
/***********************************************************************
** 函 数 名： CANSyncTask构造函数
** 函数说明： 指定CAN设备、CAN发送链接（CAN_Tx_Data_Link_t）、
              发送时间间隔
**---------------------------------------------------------------------
** 输入参数： CAN设备、CAN发送链接（CAN_Tx_Data_Link_t）、
              发送时间间隔
** 返回参数： 无
***********************************************************************/
CANSyncTask::CANSyncTask(Robot &robot0, robo_lib::CanDevice *can_device0, uint16_t id, timeus_t interval_tick_us0) : Task_Base()
{
  can_device = can_device0;
  this->interval_tick_us = interval_tick_us0;
  for(int i = 0; i < can_device->can_tx_link_count;i++)
  {
    if(can_device->can_tx_data[i].header.StdId == id)
    {
      push_msg = &can_device->can_tx_data[i];
      return;
    }
  }
  // 若无同样id，则关闭任务
  this->interval_tick_us = 0;
}
/***********************************************************************
** 函 数 名： CANSyncTask构造函数
** 函数说明： 指定CAN设备、CAN发送链接（CAN_Tx_Data_Link_t）、
              发送时间间隔
**---------------------------------------------------------------------
** 输入参数： CAN设备、CAN发送链接（CAN_Tx_Data_Link_t）、
              发送时间间隔
** 返回参数： 无
***********************************************************************/
CANSyncTask::CANSyncTask(Robot &robot0, robo_lib::CanDevice &can_device0, uint16_t id, timeus_t interval_tick_us0) : Task_Base()
{
  can_device = &can_device0;
  this->interval_tick_us = interval_tick_us0;
  for(int i = 0; i < can_device->can_tx_link_count;i++)
  {
    if(can_device->can_tx_data[i].header.StdId == id)
    {
      push_msg = &can_device->can_tx_data[i];
      return;
    }
  }
  // 若无同样id，则关闭任务
  this->interval_tick_us = 0;
}
/***********************************************************************
** 函 数 名： CANSyncTask::init()
** 函数说明： 初始化CAN发送任务
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
***********************************************************************/
void CANSyncTask::init(void)
{

}

/***********************************************************************
** 函 数 名： CANSyncTask::update(timeus_t dT_us)
** 函数说明： 更新CAN发送任务
**---------------------------------------------------------------------
** 输入参数： 更新时间间隔（us）
** 返回参数： 无
***********************************************************************/
void CANSyncTask::update(timeus_t dT_us)
{
  can_device->sendAsync(push_msg); // 将push_msg加入队列
}

/***********************************************************************
** 函 数 名： CANSyncTask::uninit()
** 函数说明： 任务反初始化
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
***********************************************************************/
void CANSyncTask::uninit(void)
{

}