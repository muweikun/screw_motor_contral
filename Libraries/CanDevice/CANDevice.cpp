/**
  ******************************************************************************
  * @file    CanDevice.cpp
  * @version 2.0
  * @author  DUT-Lingbug Embedded Group
  * @brief   CanͨѶ�豸
  *
  ******************************************************************************
  * @attention
  *
  * Copyright 2023 DUT-Lingbug.
  * All rights reserved.
  *
  ******************************************************************************
  */

#include "Libraries/CanDevice/CanDevice.h"
#include "main.h"
#include "stm32f4xx_hal_can.h"
#include "stdlib.h"

extern CAN_HandleTypeDef hcan1;
extern CAN_HandleTypeDef hcan2;

namespace robo_lib
{

CanDevice::CanDevice()
{

}

/**
  * @brief  CAN_filter��ʼ��
  * @note   None
  * @param  CAN_HandleTypeDef *_hcanx���ָ��
  * @retval None
  */
void CanDevice::init(CAN_HandleTypeDef *_hcanx, CAN_Tx_Data_Pack_t* _can_tx_buffer, uint16_t _can_tx_buffer_len)
{
  // Ӳ����ʼ��
  CAN_FilterTypeDef can_filter_st;
  can_filter_st.FilterActivation = ENABLE;
  can_filter_st.FilterMode = CAN_FILTERMODE_IDMASK; // �����˲�
  can_filter_st.FilterScale = CAN_FILTERSCALE_32BIT; // 32λһ���˲�
  can_filter_st.FilterIdHigh = 0x0000;
  can_filter_st.FilterIdLow = 0x0000;
  can_filter_st.FilterMaskIdHigh = 0x0000;
  can_filter_st.FilterMaskIdLow = 0x0000;
  can_filter_st.FilterBank = 0;
  hcanx = _hcanx;
  can_filter_st.FilterFIFOAssignment = CAN_RX_FIFO0;
  if(_hcanx == &hcan1)
  {

    HAL_CAN_ConfigFilter(&hcan1, &can_filter_st);
    HAL_CAN_Start(&hcan1);
    HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);
  }
  else if(_hcanx == &hcan2)
  {

    can_filter_st.SlaveStartFilterBank = 14;
    can_filter_st.FilterBank = 14;
    HAL_CAN_ConfigFilter(&hcan2, &can_filter_st);
    HAL_CAN_Start(&hcan2);
    HAL_CAN_ActivateNotification(&hcan2, CAN_IT_RX_FIFO0_MSG_PENDING);
  }

  // ���ͻ�������ʼ��
  can_tx_buffer = _can_tx_buffer;
  queue.Queue_Init(&hqueue, can_tx_buffer, _can_tx_buffer_len);

}

bool CanDevice::sendAsync(CAN_Tx_Data_Pack_t *data)
{
  return push(*data);
}

//void CanDevice::send(CAN_TxHeaderTypeDef *header, uint8_t *data){
//  push_msg.data = data;
//

//}
//void CanDevice::send(uint16_t std_id, uint8_t *data){

//}
//void CanDevice::send(CAN_Rx_Data_Pack_t *data){

//}

/**
  * @brief  CAN_filter��ʼ��
  * @note   CAN���ͺ���������һ����Ƶ��������
  * @param  CAN_TxHeaderTypeDef *header, uint8_t *data����Ҫ���͵����ݣ�
  * @retval None
  */
void CanDevice::update(timeus_t dT_us)
{
//  pop(&send_msg);
//  send_msg.header.DLC = send_msg.dlc;;
//  send_msg.header.StdId = send_msg.std_id;
//  send_msg.header.IDE = CAN_ID_STD;
//  send_msg.header.RTR = CAN_RTR_DATA;

//  static int16_t WaitTime;//��������������ʱ�򣬵ȴ�һ�ᣬ������仹�������жϳ�ʱ���ȴ���
//	if((HAL_CAN_GetTxMailboxesFreeLevel(this->hcanx)==0) && (WaitTime>0) )
//	{
//		WaitTime--;
//    return;
//	}
  //����Ƿ��п��з������䣬���û���з������䣬���֡���ݺ��Ե���ǰ������ѹ��˳�ʱʱ�䣩

  if(HAL_CAN_GetTxMailboxesFreeLevel(this->hcanx) > 0 && pop(&send_msg))//CAN����ʽ������Ҫ�ȼ�鷢�������Ƿ�ǿ�
  {
    HAL_CAN_AddTxMessage(hcanx, &send_msg.header, send_msg.data, &send_mail_box);
  }
}

///***********************************************************************
//** �� �� ���� CanDevice::send
//** ����˵���� can���ͺ�����ʹ����standard_tx_header��
//**---------------------------------------------------------------------
//** ��������� uint16_t std_id�����Ͷ����ID��, uint8_t *data����Ҫ���͵����ݣ�
//** ���ز����� ��
//***********************************************************************/
//void CanDevice::send(uint16_t std_id, uint8_t *data)
//{
//  CAN_TxHeaderTypeDef tx_header = standard_tx_header;
//  tx_header.StdId = std_id;

//  send(&tx_header, data);
//}



/***********************************************************************
** �� �� ���� CanDevice::addRxLink
** ����˵���� ����µ�CAN_Rx_Data_Pack_tָ��
**---------------------------------------------------------------------
** ��������� CAN_Rx_Data_Pack_t* addr
** ���ز����� ��ӳɹ�����true�����ʧ�ܷ���false
***********************************************************************/
bool CanDevice::addRxLink(CAN_Rx_Data_Pack_t* rx_data_pack)
{
  //�����Ŀ�Ѿ�����MAX_CAN_RX_ID_NUM���߿�ָ�룬����
  if(!rx_data_pack || can_rx_link_count >= MAX_CAN_RX_LINK_NUM)
  {
#ifdef DEBUG_MODE
    error.error_code.can_tx_id_num_out_of_range = 1;
    error.Error_Handler();
#endif
    return false;
  }
  can_rx_data_p[can_rx_link_count++] = rx_data_pack;
  return true;
}

/***********************************************************************
** �� �� ���� CanDevice::addTxLink
** ����˵���� ����µ�can_tx_dataָ��
**---------------------------------------------------------------------
** ���������
** ���ز����� ��ӳɹ�����true�����ʧ�ܷ���false
***********************************************************************/
bool CanDevice::addTxLink(
  uint16_t can_tx_id,   // ����id
  uint8_t can_tx_dlc,   // ���ݳ���[bytes]
  uint8_t start_pos,    // ��ʼλ�ã������±꣩
  uint8_t** data_p,       // ���ص�data_p
  uint8_t size         // ��С
)
{
  // ����Ѿ�����MAX_CAN_TX_ID_NUM��Ŀ������
  if(can_tx_link_count >= MAX_CAN_TX_LINK_NUM)
  {
#ifdef DEBUG_MODE
    error.error_code.can_rx_id_num_out_of_range = 1;
    error.Error_Handler();
#endif
    return false;
  }


  // DLC̫���ˣ�����
  if(can_tx_dlc > 8)
  {
#ifdef DEBUG_MODE
    error.error_code.can_tx_dlc_out_of_range = 1;
    error.Error_Handler();
#endif
    return false;
  }


  for(int i = 0; i < can_tx_link_count; i++)
  {
    // ������е�tx_link��������ͬid��
    if(can_tx_data[i].header.StdId == can_tx_id)
    {
      if(start_pos + size - 1 >= can_tx_dlc)
      {
#ifdef DEBUG_MODE
        // ����Խ�磬����
        error.error_code.can_tx_data_out_of_range = 1;
        error.Error_Handler();
#endif
      }
      *data_p = &can_tx_data[i].data[start_pos];
      return true;
    }
  }

  // ������е�tx_link������ͬid�ģ����½�
  can_tx_data[can_tx_link_count].header.StdId = can_tx_id;
  can_tx_data[can_tx_link_count].header.DLC = can_tx_dlc;
  can_tx_data[can_tx_link_count].header.IDE = CAN_ID_STD;
  can_tx_data[can_tx_link_count].header.RTR = CAN_RTR_DATA;
  can_tx_link_count++;

  // ����Ѿ�����MAX_CAN_TX_ID_NUM��Ŀ������
  if(can_tx_link_count >= MAX_CAN_TX_LINK_NUM)
  {
#ifdef DEBUG_MODE
    error.error_code.can_rx_id_num_out_of_range = 1;
    error.Error_Handler();
#endif
    return false;
  }

  for(int i = 0; i < can_tx_link_count; i++)
  {
    // ������е�tx_link��������ͬid��
    if(can_tx_data[i].header.StdId == can_tx_id)
    {
      if(start_pos + size - 1 >= can_tx_dlc)
      {
#ifdef DEBUG_MODE
        // ����Խ�磬����
        error.error_code.can_tx_data_out_of_range = 1;
        error.Error_Handler();
#endif
      }
      *data_p = &can_tx_data[i].data[start_pos];
      return true;
    }
  }
  return true;


//  // ����tx_link
//  can_tx_data_p[can_tx_link_count].std_id = can_tx_id;
//  can_tx_data_p[can_tx_link_count].dlc = can_tx_dlc;
//  for(int j = 0; j < size; j++)
//  {
//    // ����Խ�磬����
//    if(start_pos + j >= can_tx_dlc)
//    {
//#ifdef DEBUG_MODE
//      error.error_code.can_tx_data_out_of_range = 1;
//      error.Error_Handler();
//#endif
//    }
//    // id��ͻ������
//    else if(can_tx_data_p[can_tx_link_count]->data[start_pos + j] != NULL)
//    {
//#ifdef DEBUG_MODE
//      error.error_code.can_tx_data_conflict.error = 1;
//      error.error_code.can_tx_data_conflict.error_can_addr = can_tx_data_p[can_tx_link_count]->std_id;
//      error.error_code.can_tx_data_conflict.error_data_pos = start_pos + j;
//      if(this->hcanx == &hcan1)
//        error.error_code.can_tx_data_conflict.can_device_id = 1;
//      else if(this->hcanx == &hcan2)
//        error.error_code.can_tx_data_conflict.can_device_id = 2;
//      error.Error_Handler();
//#endif
//    }
//    // Ϊ�µ�tx_link�������
//    else
//    {
//      *can_tx_data_p[can_tx_link_count]->data[start_pos + j] = data_p + j;
////      can_tx_data[can_tx_link_count].dlc = can_tx_dlc;
//    }
//  }
//  can_tx_link_count++;
//  return true;
}

}