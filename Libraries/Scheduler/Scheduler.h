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
#ifndef __ROBO_LIB_SCHEDULER_H__
#define __ROBO_LIB_SCHEDULER_H__

#include "stdint.h"
#include "Libraries/Scheduler/Task.h"
#include "Libraries/Scheduler/Scheduler_Common.h"
class Robot;

namespace robo_lib
{
struct AsyncFuncBase
{
  timeus_t register_ms;
  timeus_t delay_ms;
  bool run;
  virtual void operator()()
  {
    run = true;
  };
  void reset()
  {
    run = false;
    register_ms = micros() / 1000;
  }
};

class Scheduler
{
public:
  Scheduler();
  void init(void);
  void run(void);
	float getUsage(void) 
	{
		return usage;
	};
  uint16_t getTaskNum(void);
  bool registerTask(Task_Base *task_p);
  bool unregisterTask(Task_Base **task_p_p);
  timeus_t getSysTimeUs(void);
  void startAsync(AsyncFuncBase &func, timeus_t delay_ms)
  {
    func.run = false;
    func.delay_ms = delay_ms;
    func.register_ms = getSysTimeUs() / 1000;
    uint16_t i;
    for(i = 0; i < async_num; i ++)
    {
      if(asyncs[i] == &func) return;
    }
    if(i == async_num) asyncs[async_num++] = &func;
  }


private:
  Task_Base *tasks[MAX_TASK_NUM];
  uint16_t task_num;
  AsyncFuncBase *asyncs[MAX_ASYNC_NUM];
  uint16_t async_num;

	timeus_t used_duration, full_duration = 1000000;
	timeus_t last_usage_cal_t;

	float usage = 0.0;
};
}
#endif

