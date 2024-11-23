/**
  ******************************************************************************
  * @file    AHRS.cpp
  * @version 2.0
  * @author  DUT-Lingbug Embedded Group
  * @brief   ◊ÀÃ¨Ω‚À„AHRSª˘¿‡
  *
  ******************************************************************************
  * @attention
  *
  * Copyright 2023 DUT-Lingbug.
  * All rights reserved.
  *
  ******************************************************************************
  */
#ifndef __ROBO_LIB_BINARY_OPERATIONS_H__
#define __ROBO_LIB_BINARY_OPERATIONS_H__

#include "stdint.h"

namespace robo_lib
{
union helper_float_u32
{
  float f;
  uint8_t u[4];
};
}

#endif