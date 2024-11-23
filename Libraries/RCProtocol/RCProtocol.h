/**
  ******************************************************************************
  * @file    AHRS.cpp
  * @version 2.0
  * @author  DUT-Lingbug Embedded Group
  * @brief   ×ËÌ¬½âËãAHRS»ùÀà
  *
  ******************************************************************************
  * @attention
  *
  * Copyright 2023 DUT-Lingbug.
  * All rights reserved.
  *
  ******************************************************************************
  */
#ifndef __ROBO_LIB_RCPROTOCOL_H__
#define __ROBO_LIB_RCPROTOCOL_H__

#include "stdint.h"
#include "main.h"
#include "Libraries/Scheduler/Scheduler_Common.h"
#include "Libraries/CanDevice/CanDevice.h"

#ifdef USE_DBUS
#define SBUS_RX_BUF_NUM 36u
#define RC_FRAME_LENGTH 18u
#endif

#ifdef USE_IBUS
#define SBUS_RX_BUF_NUM 50u
#define RC_FRAME_LENGTH 25u
#endif

#ifdef USE_WBUS
#define SBUS_RX_BUF_NUM 50u
#define RC_FRAME_LENGTH 25u
#endif

#define MAX_RCPROTOCOL_BACKEND_NUM 5

#define CLEAR_DEADZONE(value, dz) ((value > dz || value < -dz) ? ((value > dz) ? value - dz : value + dz) : 0)
namespace robo_lib
{

enum RC_TYPE
{
  RC_TYPE_NONE = 0,
  RC_TYPE_DBUS = 1,
  RC_TYPE_IBUS = 2,
  RC_TYPE_CAN  = 3
};

typedef struct
{
  RC_TYPE rc_type;
  // joystick channel value
  int16_t ch0;
  int16_t ch1;
  int16_t ch2;
  int16_t ch3;
  int16_t ch4;
  int16_t ch5;
  int16_t ch6;
  int16_t ch7;
  int16_t ch8;
  int16_t ch9;
  int16_t ch10;
  int16_t ch11;
  int16_t ch12;
  int16_t ch13;
  int16_t ch14;
  int16_t ch15;
  int16_t ch16;
  uint8_t frame_lost;
  uint8_t failsafe; 
  int16_t wheel;
  // three_step switch value
  uint8_t sw_left; //sw1
  uint8_t sw_right; //sw2
  // mouse move_speed and button_press value
  struct
  {
    int16_t vx;
    int16_t vy;
    int16_t vz;

    uint8_t press_l;
    uint8_t press_r;
  } mouse;
  // keyboard key value
  union
  {
    uint16_t key_code;
    struct
    {
      uint16_t W : 1;
      uint16_t S : 1;
      uint16_t A : 1;
      uint16_t D : 1;
      uint16_t SHIFT : 1;
      uint16_t CTRL : 1;
      uint16_t Q : 1;
      uint16_t E : 1;
      uint16_t R : 1;
      uint16_t F : 1;
      uint16_t G : 1;
      uint16_t Z : 1;
      uint16_t X : 1;
      uint16_t C : 1;
      uint16_t V : 1;
      uint16_t B : 1;
    } key_bit;
  } keyboard;
  //left_top courner wheel value

  timeus_t timestamp_us;
} RC_Data;

//typedef __PACKED_STRUCT
//{
//  __PACKED_STRUCT
//  {
//    int16_t ch[5];
//    char s[2];
//  } rc;
//  __PACKED_STRUCT
//  {
//    int16_t x;
//    int16_t y;
//    int16_t z;
//    uint8_t press_l;
//    uint8_t press_r;
//  } mouse;
//  __PACKED_STRUCT
//  {
//    uint16_t v;
//  } key;
//  timeus_t timestamp_us;

//} RC_Data;

class RCProtocol_Backend;

class RCProtocol
{
  friend class RCProtocol_Backend;
public:
  RCProtocol()
  {

  }
  ~RCProtocol()
  {

  }
  void init();
  void init(CanDevice &_can_device);
  void processByte(volatile const uint8_t *buf);
  void addBackend(RCProtocol_Backend *backend);
  bool isValid(void)
  {
    return valid;
  }
  bool isLastValid(void)
  {
    return valid_last;
  }
  void setValid(bool valid0)
  {
    valid_last = valid;
    valid = valid0;
  }
  RC_Data getRCData(void)
  {
    return rc_data;
  }
  RC_Data getLastRCData(void)
  {
    return rc_data_last;
  }

  void uninit(void);
  uint8_t sbus_rx_buf[2][SBUS_RX_BUF_NUM];

protected:
  bool valid;
  bool valid_last;
  RCProtocol_Backend *backend;
  RC_Data rc_data;
  RC_Data rc_data_last;

};
}

#endif
