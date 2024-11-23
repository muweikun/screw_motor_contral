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

#include "main.h"
#include "Libraries/RCProtocol/RCProtocol_WBUS.h"
#include "Libraries/UART/UARTDriver.h"

namespace robo_lib
{
/***********************************************************************
** �� �� ���� RCProtocol_DBUS::init
** ����˵���� ��ʼ��
**---------------------------------------------------------------------
** ��������� ��
** ���ز����� ��
***********************************************************************/
void RCProtocol_WBUS::init(void)
{

}

/***********************************************************************
** �� �� ���� RCProtocol_DBUS::processByte
** ����˵���� ���ݰ�����
**---------------------------------------------------------------------
** ��������� ��
** ���ز����� ��
***********************************************************************/
bool RCProtocol_WBUS::processByte(volatile const uint8_t *buf)
{
    if(buf == NULL) return false;

    rc_data.timestamp_us = micros();

    rc_data.ch1 = ((int16_t)buf[ 1] >> 0 | ((int16_t)buf[ 2] << 8 )) & 0x07FF;
    rc_data.ch2 = ((int16_t)buf[ 2] >> 3 | ((int16_t)buf[ 3] << 5 )) & 0x07FF;
    rc_data.ch3 = ((int16_t)buf[ 3] >> 6 | ((int16_t)buf[ 4] << 2 )  | (int16_t)buf[ 5] << 10 ) & 0x07FF;
    rc_data.ch4 = ((int16_t)buf[ 5] >> 1 | ((int16_t)buf[ 6] << 7 )) & 0x07FF;
    rc_data.ch5 = ((int16_t)buf[ 6] >> 4 | ((int16_t)buf[ 7] << 4 )) & 0x07FF;
    rc_data.ch6 = ((int16_t)buf[ 7] >> 7 | ((int16_t)buf[ 8] << 1 )  | (int16_t)buf[ 9] <<  9 ) & 0x07FF;
    rc_data.ch7 = ((int16_t)buf[ 9] >> 2 | ((int16_t)buf[10] << 6 )) & 0x07FF;
    rc_data.ch8 = ((int16_t)buf[10] >> 5 | ((int16_t)buf[11] << 3 )) & 0x07FF;
    rc_data.ch9 = ((int16_t)buf[12] << 0 | ((int16_t)buf[13] << 8 )) & 0x07FF;
    rc_data.ch10 = ((int16_t)buf[13] >> 3 | ((int16_t)buf[14] << 5 )) & 0x07FF;
    rc_data.ch11 = ((int16_t)buf[14] >> 6 | ((int16_t)buf[15] << 2 )  | (int16_t)buf[16] << 10 ) & 0x07FF;
    rc_data.ch12 = ((int16_t)buf[16] >> 1 | ((int16_t)buf[17] << 7 )) & 0x07FF;
    rc_data.ch13 = ((int16_t)buf[17] >> 4 | ((int16_t)buf[18] << 4 )) & 0x07FF;
    rc_data.ch14 = ((int16_t)buf[18] >> 7 | ((int16_t)buf[19] << 1 )  | (int16_t)buf[20] <<  9 ) & 0x07FF;
    rc_data.ch15 = ((int16_t)buf[20] >> 2 | ((int16_t)buf[21] << 6 )) & 0x07FF;
    rc_data.ch16 = ((int16_t)buf[21] >> 5 | ((int16_t)buf[22] << 3 )) & 0x07FF;
    
    rc_data.failsafe = (buf[23] & 0x08) >> 3;     // �ж� failsafe ��־λ (��4λ)
    rc_data.frame_lost = (buf[23] & 0x04) >> 2;    // �ж� frame lost ��־λ (��3λ)


    rc_data.ch1 -= 1024;
    rc_data.ch2 -= 1024;
    rc_data.ch3 -= 1024;
    rc_data.ch4 -= 1024;
    rc_data.ch5 -= 1024;
    rc_data.ch6 -= 1024;
    rc_data.ch7 -= 1024;
    rc_data.ch8 -= 1024;
    rc_data.ch9 -= 1024;
    rc_data.ch10 -= 1024;

    rc_data.rc_type = RC_TYPE_IBUS;

    publishRCData(rc_data);

    return true;
}


void RCProtocol_WBUS::uninit(void)
{

}
}