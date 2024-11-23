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


#include "Modules/PIDTask/PIDControlTask.h"
#include "Libraries/UART/UARTDriver.h"

/***********************************************************************
** �� �� ���� PIDControlTask::update(timeus_t dT_us)
** ����˵���� �������
**---------------------------------------------------------------------
** ��������� ����ʱ������us��
** ���ز����� ��
***********************************************************************/
void PIDControlTask::update(timeus_t dT_us)
{
  calculatePID(dT_us);

}

/***********************************************************************
** �� �� ���� PIDControlTask::init()
** ����˵���� �����ʼ��
**---------------------------------------------------------------------
** ��������� ��
** ���ز����� ��
***********************************************************************/
void PIDControlTask::init()
{

}

/***********************************************************************
** �� �� ���� PIDControlTask::uninit()
** ����˵���� ���񷴳�ʼ��
**---------------------------------------------------------------------
** ��������� ��
** ���ز����� ��
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
