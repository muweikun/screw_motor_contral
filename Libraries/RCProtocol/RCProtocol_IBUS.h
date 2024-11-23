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
#ifndef __ROBO_LIB_RCPROTOCOL_IBUS_H__
#define __ROBO_LIB_RCPROTOCOL_IBUS_H__

#include "Libraries/RCProtocol/RCProtocol_Backend.h"

namespace robo_lib
{
// 后台基类的子类
class RCProtocol_IBUS : public RCProtocol_Backend
{
public:
  RCProtocol_IBUS(RCProtocol &rc_protocol0) : RCProtocol_Backend(rc_protocol0)
  {

  }
  virtual void init(void);
  virtual bool processByte(volatile const uint8_t *buf);
  virtual void uninit(void);

};
}

#endif
