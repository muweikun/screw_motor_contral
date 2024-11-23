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


#include "Libraries/RCProtocol/RCProtocol_Backend.h"
namespace robo_lib
{
/***********************************************************************
** 函 数 名： RCProtocol_Backend::RCProtocol_Backend
** 函数说明： 构造函数，并完成引用变量rc_protocol初始化
**---------------------------------------------------------------------
** 输入参数： 引用变量rc_protocol0
** 返回参数： 无
***********************************************************************/
RCProtocol_Backend::RCProtocol_Backend(RCProtocol &rc_protocol0) : rc_protocol(rc_protocol0)
{

}

/***********************************************************************
** 函 数 名： RCProtocol_Backend::publishRCData
** 函数说明： 向前台上传结构体rc_data的成员数据
**---------------------------------------------------------------------
** 输入参数： rc_data
** 返回参数： 无
***********************************************************************/
void RCProtocol_Backend::publishRCData(RC_Data rc_data)
{
  rc_protocol.rc_data_last = rc_protocol.rc_data;
  rc_protocol.rc_data = rc_data;
}
}