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

#ifndef __ROBO_LIB_EULER_ANGLE_H__
#define __ROBO_LIB_EULER_ANGLE_H__

#include "stdint.h"
#include "math.h"
#include "Libraries/Math/Vector3.h"
#include "Libraries/Math/CommonMath.h"

namespace robo_lib
{

template <typename T> // 模板头，template关键字告诉编译器开始泛型编程

/* 包含欧拉角类的构造函数，各种运算方法 */
struct EulerAngleT // 模板结构体
{

  T pitch, roll, yaw;

  EulerAngleT<T>() // 无参构造函数
  {
    pitch = 0;
    roll = 0;
    yaw = 0;
  }

  EulerAngleT<T>(const EulerAngleT<T> &e0) // 拷贝构造函数
  {
    pitch = e0.pitch;
    roll = e0.roll;
    yaw = e0.yaw;
  }

  EulerAngleT<T>(const T pitch0, const T roll0, const T yaw0) // 构造函数
  {
    pitch = pitch0;
    roll = roll0;
    yaw = yaw0;
  }

  void set(const T pitch0, const T roll0, const T yaw0) // 赋值
  {
    pitch = pitch0;
    roll = roll0;
    yaw = yaw0;
  }

  void set(const EulerAngleT<T> &e0) // 拷贝赋值
  {
    pitch = e0.pitch;
    roll = e0.roll;
    yaw = e0.yaw;
  }

  void set(const robo_lib::Vector3<T> vec)
  {
    yaw = atan2(vec.y, vec.x) / PI * 180.0;
    pitch = -atan2(vec.z, sqrtf(vec.x * vec.x + vec.y * vec.y)) / PI * 180.0;
  }

};

typedef EulerAngleT<float> EulerAngleF;
typedef EulerAngleT<double> EulerAngleD;

}
#endif
