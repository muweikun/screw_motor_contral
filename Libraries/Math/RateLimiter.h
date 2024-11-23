/**
  ******************************************************************************
  * @file    RateLimiter.h
  * @version 1.0
  * @author  DUT-Lingbug Embedded Group
  * @brief   �仯���޷���
  *
  ******************************************************************************
  * @attention
  *
  * Copyright 2023 DUT-Lingbug.
  * All rights reserved.
  *
  ******************************************************************************
  */


#ifndef __ROBO_LIB_RATE_LIMITER_H__
#define __ROBO_LIB_RATE_LIMITER_H__

#include "Libraries/Math/CommonMath.h"
#include "Libraries/Math/AdvancedAdd.h"

namespace robo_lib
{
/* �仯���޷����� BEGIN */
template<class T>
class RateLimiter_Base
{
public:
  RateLimiter_Base() {}
  RateLimiter_Base(T _x_now, T _x_exp, T _x_rate)
  {
    x_now = _x_now;
    x_exp = _x_exp;
    x_rate = _x_rate;
  }
  virtual T operator() (T x_exp, T x_rate, float dT_us) = 0;
  virtual T operator() (T x_exp, float dT_us) = 0;
  // �Ա����Ʊ仯�ʵı���ֱ�Ӹ�ֵ�������б仯������
  virtual void setValueDirectly(T _x_now)
  {
    x_now = _x_now;
  }
  // �Ա����Ʊ仯�ʵı���������ֵ
  virtual void setValueExpect(T _x_exp)
  {
    x_exp = _x_exp;
  }
  // �Ա����Ʊ仯�ʵı����仯�ʽ��и�ֵ
  virtual void setValueRate(T _x_rate)
  {
    x_rate = _x_rate;
  }
  T getXNow()
  {
    return x_now;
  }
  T getValue()
  {
    return x_now;
  }
  virtual void set_dT_us(float t)
  {
    dT_us = t;
  }
protected:
  T x_now; // �����Ʊ仯�ʵı���
  T x_exp; // �����Ʊ仯�ʵı�������Ҫ��������ֵ
  T x_err; // �����Ʊ仯�ʵı������
  T x_rate; // �����Ƶı仯��[1/us]
  float dT_us; // ��������[us]
};

// һ�ױ仯������
template<class T>
class RateLimiterFirstOrder : public RateLimiter_Base<T>
{
public:
  RateLimiterFirstOrder() {}
  RateLimiterFirstOrder(T _x_now, T _x_exp, T _x_rate): RateLimiter_Base<T>(_x_now, _x_exp, _x_rate) {};
  virtual T operator() (T _x_exp, T _x_rate, float _dT_us)
  {
    this->x_exp = _x_exp;
    this->x_rate = _x_rate;
    this->dT_us = _dT_us;

    this->x_err = this->x_exp - this->x_now;
    adjust();
    return this->x_now;
  }
  virtual T operator() (T _x_exp, float _dT_us)
  {
    this->x_exp = _x_exp;
    this->dT_us = _dT_us;
    this->x_err = this->x_exp - this->x_now;
    adjust();
    return this->x_now;
  }
protected:
  void adjust()
  {
    if(robo_lib::abs<T>(this->x_err) <= this->x_rate * this->dT_us) // ����Сһ����ɵ���
    {
      this->x_now += this->x_err;
    }
    else if(this->x_err > this->x_rate * this->dT_us)
    {
      this->x_now += this->x_rate * this->dT_us;
    }
    else if(this->x_err < -this->x_rate * this->dT_us)
    {
      this->x_now -= this->x_rate * this->dT_us;
    }
  }
};

// һ�׼��Ƿ�Χ���ٶ��޷���
template<class T>
class RateLimiterPolarFirstOrder : public RateLimiter_Base<T>
{

public:
  RateLimiterPolarFirstOrder() {}
  RateLimiterPolarFirstOrder(T _x_now, T _x_exp, T _x_rate): RateLimiter_Base<T>(_x_now, _x_exp, _x_rate) {};
  virtual T operator() (T _x_exp, T _x_rate, float _dT_us)
  {
    this->x_exp = _x_exp;
    this->x_rate = _x_rate;
    this->dT_us = _dT_us;

    this->x_err = add(this->x_exp, - this->x_now);
    adjust();
    return this->x_now;
  }
  virtual T operator() (T _x_exp, float _dT_us)
  {
    this->x_exp = _x_exp;
    this->dT_us = _dT_us;
    this->x_err = add(this->x_exp, - this->x_now);
    adjust();
    return this->x_now;
  }

protected:
  robo_lib::PolarAdd<T> add;
  void adjust()
  {
    if(add(robo_lib::abs<T>(this->x_err), -this->x_rate * this->dT_us) <= 0) // ����Сһ����ɵ���
    {
      this->x_now = add(this->x_now, this->x_err);
    }
    else if(add(robo_lib::abs<T>(this->x_err), -this->x_rate * this->dT_us) > 0)
    {
      this->x_now = add(this->x_now, this->x_rate * this->dT_us);
    }
    else if(add(robo_lib::abs<T>(this->x_err), -this->x_rate * this->dT_us) < 0)
    {
      this->x_now = add(this->x_now, -this->x_rate * this->dT_us);
    }
  }
};

}

/* �仯���޷����� END */

#define _RATE_LIMITER_H_
#endif