/**
  ******************************************************************************
  * @file    CanDevice.cpp
  * @version 2.0
  * @author  DUT-Lingbug Embedded Group
  * @brief   Can通讯设备
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
  * @brief  CAN_filter初始化
  * @note   None
  * @param  CAN_HandleTypeDef *_hcanx句柄指针
  * @retval None
  */
void CanDevice::init(CAN_HandleTypeDef *_hcanx, CAN_Tx_Data_Pack_t* _can_tx_buffer, uint16_t _can_tx_buffer_len)
{
  // 硬件初始化
  CAN_FilterTypeDef can_filter_st;
  can_filter_st.FilterActivation = ENABLE;
  can_filter_st.FilterMode = CAN_FILTERMODE_IDMASK; // 掩码滤波
  can_filter_st.FilterScale = CAN_FILTERSCALE_32BIT; // 32位一对滤波
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

  // 发送缓冲区初始化
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
  * @brief  CAN_filter初始化
  * @note   CAN发送函数，放入一个高频的任务中
  * @param  CAN_TxHeaderTypeDef *header, uint8_t *data（需要发送的数据）
  * @retval None
  */
void CanDevice::update(timeus_t dT_us)
{
//  pop(&send_msg);
//  send_msg.header.DLC = send_msg.dlc;;
//  send_msg.header.StdId = send_msg.std_id;
//  send_msg.header.IDE = CAN_ID_STD;
//  send_msg.header.RTR = CAN_RTR_DATA;

//  static int16_t WaitTime;//当发送邮箱满的时候，等待一会，如果邮箱还满，就判断超时不等待了
//	if((HAL_CAN_GetTxMailboxesFreeLevel(this->hcanx)==0) && (WaitTime>0) )
//	{
//		WaitTime--;
//    return;
//	}
  //检查是否有空闲发送邮箱，如果没空闲发送邮箱，则此帧数据忽略掉（前面代码已过了超时时间）

  if(HAL_CAN_GetTxMailboxesFreeLevel(this->hcanx) > 0 && pop(&send_msg))//CAN阻塞式发送需要先检查发送邮箱是否非空
  {
    HAL_CAN_AddTxMessage(hcanx, &send_msg.header, send_msg.data, &send_mail_box);
  }
}

///***********************************************************************
//** 函 数 名： CanDevice::send
//** 函数说明： can发送函数（使用了standard_tx_header）
//**---------------------------------------------------------------------
//** 输入参数： uint16_t std_id（发送对象的ID）, uint8_t *data（需要发送的数据）
//** 返回参数： 无
//***********************************************************************/
//void CanDevice::send(uint16_t std_id, uint8_t *data)
//{
//  CAN_TxHeaderTypeDef tx_header = standard_tx_header;
//  tx_header.StdId = std_id;

//  send(&tx_header, data);
//}



/***********************************************************************
** 函 数 名： CanDevice::addRxLink
** 函数说明： 添加新的CAN_Rx_Data_Pack_t指针
**---------------------------------------------------------------------
** 输入参数： CAN_Rx_Data_Pack_t* addr
** 返回参数： 添加成功返回true，添加失败返回false
***********************************************************************/
bool CanDevice::addRxLink(CAN_Rx_Data_Pack_t* rx_data_pack)
{
  //如果数目已经大于MAX_CAN_RX_ID_NUM或者空指针，报错
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
** 函 数 名： CanDevice::addTxLink
** 函数说明： 添加新的can_tx_data指针
**---------------------------------------------------------------------
** 输入参数：
** 返回参数： 添加成功返回true，添加失败返回false
***********************************************************************/
bool CanDevice::addTxLink(
  uint16_t can_tx_id,   // 发送id
  uint8_t can_tx_dlc,   // 数据长度[bytes]
  uint8_t start_pos,    // 开始位置（数组下标）
  uint8_t** data_p,       // 返回的data_p
  uint8_t size         // 大小
)
{
  // 如果已经大于MAX_CAN_TX_ID_NUM数目，报错
  if(can_tx_link_count >= MAX_CAN_TX_LINK_NUM)
  {
#ifdef DEBUG_MODE
    error.error_code.can_rx_id_num_out_of_range = 1;
    error.Error_Handler();
#endif
    return false;
  }


  // DLC太大了，报错
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
    // 如果已有的tx_link中已有相同id的
    if(can_tx_data[i].header.StdId == can_tx_id)
    {
      if(start_pos + size - 1 >= can_tx_dlc)
      {
#ifdef DEBUG_MODE
        // 数组越界，报错
        error.error_code.can_tx_data_out_of_range = 1;
        error.Error_Handler();
#endif
      }
      *data_p = &can_tx_data[i].data[start_pos];
      return true;
    }
  }

  // 如果已有的tx_link中无相同id的，则新建
  can_tx_data[can_tx_link_count].header.StdId = can_tx_id;
  can_tx_data[can_tx_link_count].header.DLC = can_tx_dlc;
  can_tx_data[can_tx_link_count].header.IDE = CAN_ID_STD;
  can_tx_data[can_tx_link_count].header.RTR = CAN_RTR_DATA;
  can_tx_link_count++;

  // 如果已经大于MAX_CAN_TX_ID_NUM数目，报错
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
    // 如果已有的tx_link中已有相同id的
    if(can_tx_data[i].header.StdId == can_tx_id)
    {
      if(start_pos + size - 1 >= can_tx_dlc)
      {
#ifdef DEBUG_MODE
        // 数组越界，报错
        error.error_code.can_tx_data_out_of_range = 1;
        error.Error_Handler();
#endif
      }
      *data_p = &can_tx_data[i].data[start_pos];
      return true;
    }
  }
  return true;


//  // 新增tx_link
//  can_tx_data_p[can_tx_link_count].std_id = can_tx_id;
//  can_tx_data_p[can_tx_link_count].dlc = can_tx_dlc;
//  for(int j = 0; j < size; j++)
//  {
//    // 数组越界，报错
//    if(start_pos + j >= can_tx_dlc)
//    {
//#ifdef DEBUG_MODE
//      error.error_code.can_tx_data_out_of_range = 1;
//      error.Error_Handler();
//#endif
//    }
//    // id冲突，报错
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
//    // 为新的tx_link添加数据
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