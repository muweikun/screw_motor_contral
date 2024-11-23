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
#ifndef __ROBO_LIB_RCPROTOCOL_DBUS_H__
#define __ROBO_LIB_RCPROTOCOL_DBUS_H__

#define RC_CH_VALUE_MIN         ((uint16_t)364)
#define RC_CH_VALUE_OFFSET      ((uint16_t)1024)
#define RC_CH_VALUE_MAX         ((uint16_t)1684)

#include "Libraries/RCProtocol/RCProtocol_Backend.h"
namespace robo_lib
{
// 后台基类的子类
class RCProtocol_DBUS : public RCProtocol_Backend
{
public:
  RCProtocol_DBUS(RCProtocol &rc_protocol0) : RCProtocol_Backend(rc_protocol0)
  {

  }
  virtual void init(void);
  virtual bool processByte(volatile const uint8_t *buf);
  virtual void uninit(void);

};
}
#endif
