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
#ifndef __ROBO_LIB_ADVANCED_ADD_H__
#define __ROBO_LIB_ADVANCED_ADD_H__

#include "Libraries/Math/CommonMath.h"

namespace robo_lib
{
/* �߼��ļӷ� BEGIN */
template<class T>
class AdvancedAdd_Base
{
public:
  AdvancedAdd_Base() {}
  virtual T operator() (T a, T b) = 0;
};

// �����ļӷ�
template<class T>
class SimpleAdd : public AdvancedAdd_Base<T>
{
public:
  SimpleAdd() {}
  virtual T operator() (T a, T b)
  {
    return a + b;
  }
};

// �������ýǶȼӼ��� (-PI, PI]
template<class T>
class PolarAdd : public AdvancedAdd_Base<T>
{
public:
  PolarAdd()
  {
    this->min = -PI;
    this->max = PI;
  }
  virtual T operator() (T a, T b)
  {
    T c = a + b;
    uint8_t loop_check; // whileѭ�����������
    loop_check = 10;
    len = max - min;
//    c -= (int32_t)(c/len) * len;
//    c += min;
    while(c <= min && loop_check != 0)
    {
      c += len;
      loop_check --;
    }
    while(c > max && loop_check != 0)
    {
      c -= len;
      loop_check --;
    }
    return c;
  }
protected:
  T min, max, len;
};
extern SimpleAdd<float> simple_adder_instance_f;
extern PolarAdd<float> polar_adder_instance_f;
/* �߼��ļӷ� END */
}

#endif