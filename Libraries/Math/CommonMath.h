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
#ifndef __ROBO_LIB_COMMONMATH_H__
#define __ROBO_LIB_COMMONMATH_H__

#include "stdint.h"
#include "math.h"
#include "float.h"
#include "arm_math.h"

// 安全除法
#define safeDiv(numerator,denominator,safe_value) ( (denominator == 0)? (safe_value) : ((numerator)/(denominator)) )

// 返回限制最大值后的数值
#define limitMax(x, max) (x > max ? max : x)

// 返回限制最小值后的数值
#define limitMin(x, min) (x < min ? min : x)

// 返回限制了最大和最小值后的数值
#define limit(x, min, max) ((x > max ? max : x) < min ? min : (x > max ? max : x))

//

namespace robo_lib
{

// 绝对值
template<class T>
T abs(T x)
{
  return x < 0 ? -x : x;
}

// 判断是否为0
inline bool isZero(const float x)
{
  return (x < FLT_EPSILON && x > - FLT_EPSILON);
}


inline float invSqrt(float x)
{
  float halfx = 0.5f * x;
  float y = x;
  long i = *(long*)&y;
  i = 0x5f3759df - (i >> 1);
  y = *(float*)&i;
  y = y * (1.5f - (halfx * y * y));
  return y;
}

inline float sq(float x)
{
  return x * x;
}

}
#endif
