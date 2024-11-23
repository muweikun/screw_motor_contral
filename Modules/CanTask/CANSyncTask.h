/**
  ******************************************************************************
  * @file    CANSyncTask.h
  * @version 2.0
  * @author  DUT-Lingbug Embedded Group
  * @brief   这个任务负责将CAN包以特定的频率加入CAN发送缓冲区
  *
  ******************************************************************************
  * @attention
  *
  * Copyright 2023 DUT-Lingbug.
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef _CAN_SYNC_TASK_H_
#define _CAN_SYNC_TASK_H_

#include "Libraries/Scheduler/Task.h"
#include "Libraries/CanDevice/CanDevice.h"

class Robot;

class CANSyncTask : public robo_lib::Task_Base
{
public:
  // 从现有的tx_data包中指针传递数据发送
  CANSyncTask(Robot &robot0, robo_lib::CanDevice *can_device0, robo_lib::CAN_Tx_Data_Pack_t *tx_data, timeus_t interval_tick_us0 = 0); 
  CANSyncTask(Robot &robot0, robo_lib::CanDevice &can_device0, robo_lib::CAN_Tx_Data_Pack_t *tx_data, timeus_t interval_tick_us0 = 0); 
  // 以特定频率发送can_device中tx_link中特定id的数据
  CANSyncTask(Robot &robot0, robo_lib::CanDevice *can_device0, uint16_t id, timeus_t interval_tick_us0 = 0); 
   CANSyncTask(Robot &robot0, robo_lib::CanDevice &can_device0, uint16_t id, timeus_t interval_tick_us0 = 0); 
//  CANSyncTask(Robot &robot0, robo_lib::CanDevice *can_device0, uint16_t tx_id, timeus_t interval_tick_us0 = 0);

  virtual ~CANSyncTask(void) {}

  virtual void init(void);

  virtual void update(timeus_t dT_us);

  virtual void uninit(void);

protected:
  robo_lib::CanDevice *can_device;

  // 当前要被加到缓冲区的
  robo_lib::CAN_Tx_Data_Pack_t *push_msg;
};
#endif
