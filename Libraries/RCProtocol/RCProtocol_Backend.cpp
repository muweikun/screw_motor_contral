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


#include "Libraries/RCProtocol/RCProtocol_Backend.h"
namespace robo_lib
{
/***********************************************************************
** �� �� ���� RCProtocol_Backend::RCProtocol_Backend
** ����˵���� ���캯������������ñ���rc_protocol��ʼ��
**---------------------------------------------------------------------
** ��������� ���ñ���rc_protocol0
** ���ز����� ��
***********************************************************************/
RCProtocol_Backend::RCProtocol_Backend(RCProtocol &rc_protocol0) : rc_protocol(rc_protocol0)
{

}

/***********************************************************************
** �� �� ���� RCProtocol_Backend::publishRCData
** ����˵���� ��ǰ̨�ϴ��ṹ��rc_data�ĳ�Ա����
**---------------------------------------------------------------------
** ��������� rc_data
** ���ز����� ��
***********************************************************************/
void RCProtocol_Backend::publishRCData(RC_Data rc_data)
{
  rc_protocol.rc_data_last = rc_protocol.rc_data;
  rc_protocol.rc_data = rc_data;
}
}