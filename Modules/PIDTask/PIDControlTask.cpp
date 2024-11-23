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


#include "Modules/PIDTask/PIDControlTask.h"
#include "Libraries/UART/UARTDriver.h"

/***********************************************************************
** 函 数 名： PIDControlTask::update(timeus_t dT_us)
** 函数说明： 任务更新
**---------------------------------------------------------------------
** 输入参数： 更新时间间隔（us）
** 返回参数： 无
***********************************************************************/
void PIDControlTask::update(timeus_t dT_us)
{
  calculatePID(dT_us);

}

/***********************************************************************
** 函 数 名： PIDControlTask::init()
** 函数说明： 任务初始化
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
***********************************************************************/
void PIDControlTask::init()
{

}

/***********************************************************************
** 函 数 名： PIDControlTask::uninit()
** 函数说明： 任务反初始化
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
***********************************************************************/
void PIDControlTask::uninit(void)
{

}

void PIDControlTask::printPID(void)
{
  robo_lib::USART1_DMA_Debug_Printf("%-16f%-16f%-16f%-16f%-16f%-16f%-16f%-16f\r\n",
                                    pid_controller.getPidData().feedback,
                                    pid_controller.getPidData().d_feedback,
                                    pid_controller.getPidData().expect	,
                                    pid_controller.getPidData().d_expect,
                                    pid_controller.getPidData().error,
                                    pid_controller.getPidData().feedforward,
                                    pid_controller.getPidData().out
                                   );
}
