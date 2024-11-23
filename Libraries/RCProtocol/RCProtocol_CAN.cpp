/**
  ******************************************************************************
  * @file    AHRS.cpp
  * @version 2.0
  * @author  DUT-Lingbug Embedded Group
  * @brief   姿态解算AHRS基类
  *
  ******************************************************************************
  * @attention
  *
  * Copyright 2023 DUT-Lingbug.
  * All rights reserved.
  *
  ******************************************************************************
  */


#include "Libraries/RCProtocol/RCProtocol_CAN.h"
#include "main.h"
#include "Libraries/UART/UARTDriver.h"
namespace robo_lib
{
/***********************************************************************
** 函 数 名： RCProtocol_DBUS::init
** 函数说明： 初始化
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
***********************************************************************/
void RCProtocol_CAN::init(void)
{
}

/***********************************************************************
** 函 数 名： RCProtocol_DBUS::processByte
** 函数说明： 数据包解析
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
***********************************************************************/
bool RCProtocol_CAN ::processByte(volatile const uint8_t *buf)
{
  if(buf == NULL) return false;
  rc_data.timestamp_us = micros();

#ifdef USE_IBUS
  rc_data.ch1 = buf[1] << 8 | buf[0];
  rc_data.ch2 = buf[3] << 8 | buf[2];
  rc_data.ch3 = buf[5] << 8 | buf[4];
  rc_data.ch4 = buf[7] << 8 | buf[6];
  rc_data.ch5 = buf[9] << 8 | buf[8];
  rc_data.ch6 = buf[11] << 8 | buf[10];
  rc_data.ch7 = buf[13] << 8 | buf[12];
  rc_data.ch8 = buf[15] << 8 | buf[14];
  rc_data.ch9 = buf[17] << 8 | buf[16];
  rc_data.ch10 = buf[19] << 8 | buf[18];
#endif

  rc_data.rc_type = RC_TYPE_IBUS;

  publishRCData(rc_data);

  return true;
}


void RCProtocol_CAN::uninit(void)
{

}
}