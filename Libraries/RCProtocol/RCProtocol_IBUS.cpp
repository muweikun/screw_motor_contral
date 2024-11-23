/**
  ******************************************************************************
  * @file    AHRS.cpp
  * @version 2.0
  * @author  DUT-Lingbug Embedded Group
  * @brief   ��̬����AHRS����
  *
  ******************************************************************************
  * @attention
  *
  * Copyright 2023 DUT-Lingbug.
  * All rights reserved.
  *
  ******************************************************************************
  */

// ʵ������SBUS
#include "main.h"
#include "Libraries/RCProtocol/RCProtocol_IBUS.h"
#include "Libraries/UART/UARTDriver.h"

namespace robo_lib
{
/***********************************************************************
** �� �� ���� RCProtocol_DBUS::init
** ����˵���� ��ʼ��
**---------------------------------------------------------------------
** ��������� ��
** ���ز����� ��
***********************************************************************/
void RCProtocol_IBUS::init(void)
{

}

/***********************************************************************
** �� �� ���� RCProtocol_DBUS::processByte
** ����˵���� ���ݰ�����
**---------------------------------------------------------------------
** ��������� ��
** ���ز����� ��
***********************************************************************/
bool RCProtocol_IBUS::processByte(volatile const uint8_t *buf)
{
  if(buf == NULL) return false;
  rc_data.timestamp_us = micros();
  //rc_data.ch0 = (buf[0] | (buf[1] << 8)) & 0x07ff;
  buf = buf - 1;
  rc_data.ch1 = ((int16_t)buf[ 2] >> 0 | ((int16_t)buf[ 3] << 8 )) & 0x07FF;//;(uint16_t)((buf[3] << 8) | buf[2]);
  rc_data.ch2 = ((int16_t)buf[ 3] >> 3 | ((int16_t)buf[ 4] << 5 )) & 0x07FF;//((buf[2] >> 6) | (buf[3] << 2) |          //!< Channel 2
//                      (buf[4] << 10)) & 0x07ff;
  rc_data.ch3 = ((int16_t)buf[ 4] >> 6 | ((int16_t)buf[ 5] << 2 )  | (int16_t)buf[ 6] << 10 ) & 0x07FF;//((buf[4] >> 1) | (buf[5] << 7)) & 0x07ff;
  rc_data.ch4 = ((int16_t)buf[ 6] >> 1 | ((int16_t)buf[ 7] << 7 )) & 0x07FF;
  rc_data.ch5 = ((int16_t)buf[ 7] >> 4 | ((int16_t)buf[ 8] << 4 )) & 0x07FF;
  rc_data.ch6 = ((int16_t)buf[ 8] >> 7 | ((int16_t)buf[ 9] << 1 )  | (int16_t)buf[10] <<  9 ) & 0x07FF;
  rc_data.ch7 =  ((int16_t)buf[10] >> 2 | ((int16_t)buf[11] << 6 )) & 0x07FF;
  rc_data.ch8 = ((int16_t)buf[11] >> 5 | ((int16_t)buf[12] << 3 )) & 0x07FF;
  rc_data.ch9 = ((int16_t)buf[13] << 0 | ((int16_t)buf[14] << 8 )) & 0x07FF;
  rc_data.ch10 = ((int16_t)buf[14] >> 3 | ((int16_t)buf[15] << 5 )) & 0x07FF;


//	USART1_DMA_Debug_Printf("%d \t%d \t%d \t%d\n", rc_data.ch1, rc_data.ch2, rc_data.ch3, rc_data.ch4);
  //  rc_data.sw_right = ((buf[5] >> 4) & 0x0003);
//  rc_data.sw_left = ((buf[5] >> 4) & 0x000C) >> 2;
//  rc_data.mouse.vx = buf[6] | (buf[7] << 8);
//  rc_data.mouse.vy = buf[8] | (buf[9] << 8);
//  rc_data.mouse.vz = buf[10] | (buf[11] << 8);
//  rc_data.mouse.press_l = buf[12];
//  rc_data.mouse.press_r = buf[13];
//  rc_data.keyboard.key_code = buf[14] | (buf[15] << 8);
//  rc_data.wheel = buf[16] | (buf[17] << 8);

// rc_data.ch0 -= RC_CH_VALUE_OFFSET;
  rc_data.ch1 -= 1028;
  rc_data.ch2 -= 1023;
  rc_data.ch3 -= 1022;
  rc_data.ch4 -= 1024;
  rc_data.ch5 -= 1000;
  rc_data.ch6 -= 1000;
  rc_data.ch7 -= 1000;
  rc_data.ch8 -= 1000;
  rc_data.ch9 -= 1000;
  rc_data.ch10 -= 1000;

  rc_data.rc_type = RC_TYPE_IBUS;

  publishRCData(rc_data);

  return true;
}


void RCProtocol_IBUS::uninit(void)
{

}
}