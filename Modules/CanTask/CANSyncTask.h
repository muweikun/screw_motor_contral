/**
  ******************************************************************************
  * @file    CANSyncTask.h
  * @version 2.0
  * @author  DUT-Lingbug Embedded Group
  * @brief   ���������CAN�����ض���Ƶ�ʼ���CAN���ͻ�����
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
  // �����е�tx_data����ָ�봫�����ݷ���
  CANSyncTask(Robot &robot0, robo_lib::CanDevice *can_device0, robo_lib::CAN_Tx_Data_Pack_t *tx_data, timeus_t interval_tick_us0 = 0); 
  CANSyncTask(Robot &robot0, robo_lib::CanDevice &can_device0, robo_lib::CAN_Tx_Data_Pack_t *tx_data, timeus_t interval_tick_us0 = 0); 
  // ���ض�Ƶ�ʷ���can_device��tx_link���ض�id������
  CANSyncTask(Robot &robot0, robo_lib::CanDevice *can_device0, uint16_t id, timeus_t interval_tick_us0 = 0); 
   CANSyncTask(Robot &robot0, robo_lib::CanDevice &can_device0, uint16_t id, timeus_t interval_tick_us0 = 0); 
//  CANSyncTask(Robot &robot0, robo_lib::CanDevice *can_device0, uint16_t tx_id, timeus_t interval_tick_us0 = 0);

  virtual ~CANSyncTask(void) {}

  virtual void init(void);

  virtual void update(timeus_t dT_us);

  virtual void uninit(void);

protected:
  robo_lib::CanDevice *can_device;

  // ��ǰҪ���ӵ���������
  robo_lib::CAN_Tx_Data_Pack_t *push_msg;
};
#endif
