/**
  ******************************************************************************
  * @file    CanDevice.h
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

#ifndef __ROBO_LIB_CANDEVICE_H__
#define __ROBO_LIB_CANDEVICE_H__

#include "main.h"
#include "Libraries/Error/Error.h"
#include "Libraries/Scheduler/Scheduler_Common.h"
#include "Libraries/DataStructure/Queue/Queue.h"

#define MAX_CAN_RX_LINK_NUM 20 // 最大接收id数量
#define MAX_CAN_TX_LINK_NUM 20 // 最大发送id数量

namespace robo_lib
{
//CAN包数据结构体
typedef struct _CAN_Rx_Data_Pack_t
{
  CAN_RxHeaderTypeDef header;
  uint8_t data[8];     // 数据，最大 8 bytes
  uint64_t rec_cnt;    // 接收次数
  timeus_t timestamp;  // 接收到数据时的时间戳
	timeus_t timestamp_start_count; // 
	float hz;
	uint64_t rec_cnt_start_count;
} CAN_Rx_Data_Pack_t;

typedef struct _CAN_Tx_Data_Pack_t
{
  CAN_TxHeaderTypeDef header;
  uint8_t data[8];     // 数据，最大 8 bytes
//  uint64_t rec_cnt;    // 接收次数
//  timeus_t timestamp;  // 接收到数据时的时间戳
} CAN_Tx_Data_Pack_t;

////CAN包数据结构体
//typedef struct _CAN_Tx_Data_Pack_t
//{
//  uint16_t std_id;     // 标准id
//  uint8_t dlc;         // 数据长度[byte]
//  uint8_t *data[8];     // 数据，最大 8 bytes
//  uint64_t rec_cnt;    // 接收次数
//  timeus_t timestamp;  // 接收到数据时的时间戳
//  timeus_t dT_us;      // 发送周期[us]
//} CAN_Tx_Data_Pack_t;

class CanDevice
{
public:
  CanDevice();
  void init(CAN_HandleTypeDef *_hcanx, CAN_Tx_Data_Pack_t* _can_tx_buffer, uint16_t _can_tx_buffer_len);

//  void setRxPointerNum(uint16_t num);
  bool sendAsync(CAN_Tx_Data_Pack_t *data);

//  void send(CAN_TxHeaderTypeDef *header, uint8_t *data);
//  void send(uint16_t std_id, uint8_t *data);
//  void send(CAN_Rx_Data_Pack_t *data);

  // 添加RX链接，相关处理过程在CAN中断里
  bool addRxLink(CAN_Rx_Data_Pack_t* rx_data_pack);

  // 添加TX链接，作用是将某个特定地址的某几个字节由外部引入can_tx_data数组中同地址的data中
  bool addTxLink(
    uint16_t can_tx_id,   // 发送id
    uint8_t can_tx_dlc,   // 数据长度[bytes]
    uint8_t start_pos,    // 开始位置（数组下标）
	  uint8_t** data_p,       // 返回的data_p
    uint8_t size         // 大小

  );
  
  void update(timeus_t dT_us);

  bool push(CAN_Tx_Data_Pack_t msg)
  {
    robo_lib::QUEUE_StatusTypeDef status = queue.Queue_Push(&hqueue, msg);
    if(status == robo_lib::QUEUE_OK) return true;
    else return false;
  }
  bool pop(CAN_Tx_Data_Pack_t *msg_p)
  {
    robo_lib::QUEUE_StatusTypeDef status = queue.Queue_Pop(&hqueue, msg_p);
    if(status == robo_lib::QUEUE_OK) return true;
    else return false;
  }
  bool peak(CAN_Tx_Data_Pack_t *msg_p)
  {
    robo_lib::QUEUE_StatusTypeDef status = queue.Queue_Peek(&hqueue, msg_p);
    if(status == robo_lib::QUEUE_OK) return true;
    else return false;
  }

  const CAN_TxHeaderTypeDef standard_tx_header =
  {
    .IDE = CAN_ID_STD,
    .RTR = CAN_RTR_DATA,
    .DLC = 0x08
  };

  uint16_t can_rx_link_count;
  uint16_t can_tx_link_count;
  
  // CAN接收数据包结构体指针数组，每个id对应一个，真身在外面定义，这里是传入指针
  CAN_Rx_Data_Pack_t* can_rx_data_p[MAX_CAN_RX_LINK_NUM];
  // CAN发送数据包结构体数组，每个id对应一个（向下兼容用）
  CAN_Tx_Data_Pack_t can_tx_data[MAX_CAN_TX_LINK_NUM];

  // CAN发送缓冲区放在外面，这是传入指针
  CAN_Tx_Data_Pack_t* can_tx_buffer;

protected:
  // 当前要发送的
  uint32_t send_mail_box;
  CAN_Tx_Data_Pack_t send_msg;
  CAN_TxHeaderTypeDef send_header;

  // 当前要被加到缓冲区的
  CAN_Tx_Data_Pack_t push_msg;
  CAN_TxHeaderTypeDef push_header;

  // CAN设备句柄，由外面传入指针
  CAN_HandleTypeDef *hcanx;

  // 发送缓冲区队列
  robo_lib::QUEUE_HandleTypeDef<CAN_Tx_Data_Pack_t> hqueue;
  robo_lib::Queue<CAN_Tx_Data_Pack_t> queue;

};
}

#endif
