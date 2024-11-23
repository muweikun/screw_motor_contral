/***************************************************************************
**   					             ��������ѧ ��BUGս��
**   					               �������ƣ����Լ���!
**-------------------------------------------------------------------------
** ��    Ŀ��   robo_template
** �� �� ����   CANSyncTask.cpp
** �ļ�˵����   ���������CAN�����ض���Ƶ�ʼ���CAN���ͻ�����
**-------------------------------------------------------------------------
**						*�޶�*
**	*�汾*							*�޸�����*							*�޸���*      			 *����*
**	 1.0							   ��ʼ�汾						     ���Ӻ�     	   2022-07-18
**	 1.1							  ����TxLink					     ���Ӻ�     	   2022-07-26
**	 1.2							   ����ע��						     ����Դ     	   2022-12-10
***************************************************************************/

#include "Modules/CanTask/CANSyncTask.h"

/***********************************************************************
** �� �� ���� CANSyncTask���캯��
** ����˵���� ָ��CAN�豸��CAN�������ӣ�CAN_Tx_Data_Link_t����
              ����ʱ����
**---------------------------------------------------------------------
** ��������� CAN�豸��CAN�������ӣ�CAN_Tx_Data_Link_t����
              ����ʱ����
** ���ز����� ��
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
** �� �� ���� CANSyncTask���캯��
** ����˵���� ָ��CAN�豸��CAN�������ӣ�CAN_Tx_Data_Link_t����
              ����ʱ����
**---------------------------------------------------------------------
** ��������� CAN�豸��CAN�������ӣ�CAN_Tx_Data_Link_t����
              ����ʱ����
** ���ز����� ��
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
  // ����ͬ��id����ر�����
  this->interval_tick_us = 0;
}
/***********************************************************************
** �� �� ���� CANSyncTask���캯��
** ����˵���� ָ��CAN�豸��CAN�������ӣ�CAN_Tx_Data_Link_t����
              ����ʱ����
**---------------------------------------------------------------------
** ��������� CAN�豸��CAN�������ӣ�CAN_Tx_Data_Link_t����
              ����ʱ����
** ���ز����� ��
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
  // ����ͬ��id����ر�����
  this->interval_tick_us = 0;
}
/***********************************************************************
** �� �� ���� CANSyncTask::init()
** ����˵���� ��ʼ��CAN��������
**---------------------------------------------------------------------
** ��������� ��
** ���ز����� ��
***********************************************************************/
void CANSyncTask::init(void)
{

}

/***********************************************************************
** �� �� ���� CANSyncTask::update(timeus_t dT_us)
** ����˵���� ����CAN��������
**---------------------------------------------------------------------
** ��������� ����ʱ������us��
** ���ز����� ��
***********************************************************************/
void CANSyncTask::update(timeus_t dT_us)
{
  can_device->sendAsync(push_msg); // ��push_msg�������
}

/***********************************************************************
** �� �� ���� CANSyncTask::uninit()
** ����˵���� ���񷴳�ʼ��
**---------------------------------------------------------------------
** ��������� ��
** ���ز����� ��
***********************************************************************/
void CANSyncTask::uninit(void)
{

}