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
#ifndef __ROBO_LIB_SCHEDULER_COMMON_H__
#define __ROBO_LIB_SCHEDULER_COMMON_H__

#include "main.h"
#include "stdint.h"

//class timeus_t_with_overflow_times
//{
//  int32_t overflow_times;
//  uint32_t t;
//  
//    // ���������-
//  timeus_t_with_overflow_times operator -(const timeus_t_with_overflow_times &v) const
//  {
//    return timeus_t_with_overflow_times(x - v.x, y - v.y, z - v.z);
//  }

//  // �ӷ������+
//  timeus_t_with_overflow_times operator +(const timeus_t_with_overflow_times &v) const
//  {
//    return Vector3<T>(x + v.x, y + v.y, z + v.z);
//  }
//};

#define timeus_t uint32_t
#define TIMEUS_MAX UINT32_MAX
#define MAX_TASK_NUM 100
#define MAX_ASYNC_NUM 500
namespace robo_lib
{
//��ȡϵͳʱ�䣬��λus
timeus_t micros(void);
void DWT_Init(void);
bool isOutOfClock(timeus_t timestamp, timeus_t interval_max = 50000);
}
#endif
