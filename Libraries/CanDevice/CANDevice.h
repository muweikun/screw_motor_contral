/**
  ******************************************************************************
  * @file    CanDevice.h
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

#ifndef __ROBO_LIB_CANDEVICE_H__
#define __ROBO_LIB_CANDEVICE_H__

#include "main.h"
#include "Libraries/Error/Error.h"
#include "Libraries/Scheduler/Scheduler_Common.h"
#include "Libraries/DataStructure/Queue/Queue.h"

#define MAX_CAN_RX_LINK_NUM 20 // ������id����
#define MAX_CAN_TX_LINK_NUM 20 // �����id����

namespace robo_lib
{
//CAN�����ݽṹ��
typedef struct _CAN_Rx_Data_Pack_t
{
  CAN_RxHeaderTypeDef header;
  uint8_t data[8];     // ���ݣ���� 8 bytes
  uint64_t rec_cnt;    // ���մ���
  timeus_t timestamp;  // ���յ�����ʱ��ʱ���
	timeus_t timestamp_start_count; // 
	float hz;
	uint64_t rec_cnt_start_count;
} CAN_Rx_Data_Pack_t;

typedef struct _CAN_Tx_Data_Pack_t
{
  CAN_TxHeaderTypeDef header;
  uint8_t data[8];     // ���ݣ���� 8 bytes
//  uint64_t rec_cnt;    // ���մ���
//  timeus_t timestamp;  // ���յ�����ʱ��ʱ���
} CAN_Tx_Data_Pack_t;

////CAN�����ݽṹ��
//typedef struct _CAN_Tx_Data_Pack_t
//{
//  uint16_t std_id;     // ��׼id
//  uint8_t dlc;         // ���ݳ���[byte]
//  uint8_t *data[8];     // ���ݣ���� 8 bytes
//  uint64_t rec_cnt;    // ���մ���
//  timeus_t timestamp;  // ���յ�����ʱ��ʱ���
//  timeus_t dT_us;      // ��������[us]
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

  // ���RX���ӣ���ش��������CAN�ж���
  bool addRxLink(CAN_Rx_Data_Pack_t* rx_data_pack);

  // ���TX���ӣ������ǽ�ĳ���ض���ַ��ĳ�����ֽ����ⲿ����can_tx_data������ͬ��ַ��data��
  bool addTxLink(
    uint16_t can_tx_id,   // ����id
    uint8_t can_tx_dlc,   // ���ݳ���[bytes]
    uint8_t start_pos,    // ��ʼλ�ã������±꣩
	  uint8_t** data_p,       // ���ص�data_p
    uint8_t size         // ��С

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
  
  // CAN�������ݰ��ṹ��ָ�����飬ÿ��id��Ӧһ�������������涨�壬�����Ǵ���ָ��
  CAN_Rx_Data_Pack_t* can_rx_data_p[MAX_CAN_RX_LINK_NUM];
  // CAN�������ݰ��ṹ�����飬ÿ��id��Ӧһ�������¼����ã�
  CAN_Tx_Data_Pack_t can_tx_data[MAX_CAN_TX_LINK_NUM];

  // CAN���ͻ������������棬���Ǵ���ָ��
  CAN_Tx_Data_Pack_t* can_tx_buffer;

protected:
  // ��ǰҪ���͵�
  uint32_t send_mail_box;
  CAN_Tx_Data_Pack_t send_msg;
  CAN_TxHeaderTypeDef send_header;

  // ��ǰҪ���ӵ���������
  CAN_Tx_Data_Pack_t push_msg;
  CAN_TxHeaderTypeDef push_header;

  // CAN�豸����������洫��ָ��
  CAN_HandleTypeDef *hcanx;

  // ���ͻ���������
  robo_lib::QUEUE_HandleTypeDef<CAN_Tx_Data_Pack_t> hqueue;
  robo_lib::Queue<CAN_Tx_Data_Pack_t> queue;

};
}

#endif
