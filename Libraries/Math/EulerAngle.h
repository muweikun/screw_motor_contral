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

#ifndef __ROBO_LIB_EULER_ANGLE_H__
#define __ROBO_LIB_EULER_ANGLE_H__

#include "stdint.h"
#include "math.h"
#include "Libraries/Math/Vector3.h"
#include "Libraries/Math/CommonMath.h"

namespace robo_lib
{

template <typename T> // ģ��ͷ��template�ؼ��ָ��߱�������ʼ���ͱ��

/* ����ŷ������Ĺ��캯�����������㷽�� */
struct EulerAngleT // ģ��ṹ��
{

  T pitch, roll, yaw;

  EulerAngleT<T>() // �޲ι��캯��
  {
    pitch = 0;
    roll = 0;
    yaw = 0;
  }

  EulerAngleT<T>(const EulerAngleT<T> &e0) // �������캯��
  {
    pitch = e0.pitch;
    roll = e0.roll;
    yaw = e0.yaw;
  }

  EulerAngleT<T>(const T pitch0, const T roll0, const T yaw0) // ���캯��
  {
    pitch = pitch0;
    roll = roll0;
    yaw = yaw0;
  }

  void set(const T pitch0, const T roll0, const T yaw0) // ��ֵ
  {
    pitch = pitch0;
    roll = roll0;
    yaw = yaw0;
  }

  void set(const EulerAngleT<T> &e0) // ������ֵ
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
