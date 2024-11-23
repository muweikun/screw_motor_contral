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
#ifndef __ROBO_LIB_RCPROTOCOL_CAN_H__
#define __ROBO_LIB_RCPROTOCOL_CAN_H__


#include "Libraries/RCProtocol/RCProtocol_Backend.h"
#include "Libraries/CanDevice/CanDevice.h"
namespace robo_lib
{
// 后台基类的子类
class RCProtocol_CAN : public RCProtocol_Backend
{
public:
  RCProtocol_CAN(RCProtocol &rc_protocol0, CanDevice &_can_device) : RCProtocol_Backend(rc_protocol0)
  {
//		can_rx_data_0x220.std_id = 0x220;
//		_can_device.addRxLink(&can_rx_data_0x220);
//		can_rx_data_0x221.std_id = 0x221;
//		_can_device.addRxLink(&can_rx_data_0x221);
//		can_rx_data_0x222.std_id = 0x222;
//		_can_device.addRxLink(&can_rx_data_0x222);
  }
  virtual void init(void);
  virtual bool processByte(volatile const uint8_t *buf);
  virtual void uninit(void);
protected:
  //CAN_Rx_Data_Pack_t can_rx_data_0x220, can_rx_data_0x221, can_rx_data_0x222;

};
}
#endif
