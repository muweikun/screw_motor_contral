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

#include "Libraries/RCProtocol/RCProtocol_DBUS.h"
#include "main.h"
namespace robo_lib
{
/***********************************************************************
** 函 数 名： RCProtocol_DBUS::init
** 函数说明： 初始化
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
***********************************************************************/
void RCProtocol_DBUS::init(void)
{

}

/***********************************************************************
** 函 数 名： RCProtocol_DBUS::processByte
** 函数说明： 数据包解析
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
***********************************************************************/
bool RCProtocol_DBUS::processByte(volatile const uint8_t *buf)
{
  if(buf == NULL) return false;
  rc_data.timestamp_us = micros();
  rc_data.ch0 = (buf[0] | (buf[1] << 8)) & 0x07ff;
  rc_data.ch1 = ((buf[1] >> 3) | (buf[2] << 5)) & 0x07ff;
  rc_data.ch2 = ((buf[2] >> 6) | (buf[3] << 2) |          //!< Channel 2
                 (buf[4] << 10)) & 0x07ff;
  rc_data.ch3 = ((buf[4] >> 1) | (buf[5] << 7)) & 0x07ff;
  rc_data.sw_right = ((buf[5] >> 4) & 0x0003);
  rc_data.sw_left = ((buf[5] >> 4) & 0x000C) >> 2;
  rc_data.mouse.vx = buf[6] | (buf[7] << 8);
  rc_data.mouse.vy = buf[8] | (buf[9] << 8);
  rc_data.mouse.vz = buf[10] | (buf[11] << 8);
  rc_data.mouse.press_l = buf[12];
  rc_data.mouse.press_r = buf[13];
  rc_data.keyboard.key_code = buf[14] | (buf[15] << 8);
  rc_data.wheel = buf[16] | (buf[17] << 8);

  rc_data.ch0 -= RC_CH_VALUE_OFFSET;
  rc_data.ch1 -= RC_CH_VALUE_OFFSET;
  rc_data.ch2 -= RC_CH_VALUE_OFFSET;
  rc_data.ch3 -= RC_CH_VALUE_OFFSET;
  rc_data.wheel -= RC_CH_VALUE_OFFSET;

  rc_data.rc_type = RC_TYPE_DBUS;

  publishRCData(rc_data);

  return true;
}


void RCProtocol_DBUS::uninit(void)
{

}
}