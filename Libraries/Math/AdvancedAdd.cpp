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


#include "Libraries/Math/AdvancedAdd.h"
namespace robo_lib
{
SimpleAdd<float> simple_adder_instance_f;
PolarAdd<float> polar_adder_instance_f;
}