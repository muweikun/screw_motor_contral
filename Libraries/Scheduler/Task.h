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
#ifndef __ROBO_LIB_TASK_H__
#define __ROBO_LIB_TASK_H__

#include "stdint.h"
#include "Libraries/Scheduler/Scheduler_Common.h"
class RoboBase;
namespace robo_lib
{

// ������࣬���е�������̳��Դ���
class Task_Base//������
{
  // ���õ�������Ϊ��Ԫ�࣬ʹ����������Է����Լ��ķǹ�����Ա
  friend class Scheduler;

public:
#ifdef TASK_BASE_WITH_ROBOT
  Task_Base(RoboBase &robot0) : robot(robot0)//���캯���������ò���&robot0��ֵ������robot
  {
  }
#endif
	
#ifndef TASK_BASE_WITH_ROBOT
	Task_Base() //���캯��
  {
  }
#endif
	
  virtual ~Task_Base(void) {};

  // ���麯�����������ʵ��
  virtual void update(timeus_t dT_us) = 0; // ���interval_tick_usʱ�������ѯ���������dT_usΪʵ�����м��ʱ��
  virtual void init(void) = 0; // �����ʼ��ʱִ�д˺���
  virtual void uninit(void) = 0; // ��������ʱִ�д˺���

  //�Ƿ��Ѿ���ʼ��
  bool isInited(void)
  {
    return inited;
  }

  //�Ƿ���ɱ
  bool isKilledBySelf(void)
  {
    return self_kill;
  }
  //��ɱ!!!!!!!!!!!!!!!!!
  void selfKill(void)
  {
    self_kill = true;
  }
  //����ʱ����
  void setInterval(timeus_t interval)
  {
    interval_tick_us = interval;
  }
  //����ʱ����
  timeus_t getInterval(void)
  {
    return interval_tick_us;
  }
//  void setInitState(bool state)
//  {
//    inited = state;
//  }
protected:
  bool inited;
#ifdef DEBUG_MODE
  float update_freq;
#endif
  timeus_t interval_tick_us; // �������ʱ�䣬�����ó�0���򲻻���Scheduler�����и�����
  timeus_t real_interval_tick_us; // ��ʵ�����м��
  timeus_t last_tick_us;	// �ϴ����е�ʱ���
  timeus_t end_tick_us; // �˴����н���ʱ���
#ifdef TASK_BASE_WITH_ROBOT
  RoboBase &robot; // �����Ļ����˶���
#endif
  bool self_kill;
};
}
#endif
