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

#include "Libraries/Motor/Motor_RM.h"
#include "Libraries/Motor/Motor.h"
#include "Libraries/Motor/Motor_Backend.h"
#include "Libraries/CanDevice/CanDevice.h"
#include "arm_math.h"

namespace robo_lib
{

/***********************************************************************
** �� �� ���� Motor_RM::Motor_RM()
** ����˵���� ������ĵ�������CAN�Ľ����뷢�����ݵ�ַ��ӵ�can_device��
**---------------------------------------------------------------------
** ��������� �����������ָ�롢�������ָ�롢CAN���ݰ�ָ�롢��ʱ��us��
** ���ز����� ��
***********************************************************************/
Motor_RM::Motor_RM(Motor &motor0,
                   CanDevice &_can_device,
                   uint16_t _can_tx_id,
                   uint16_t _can_rx_id,
                   uint8_t _can_tx_data_start_pos,
                   int8_t _motor_type):
  Motor_Backend(motor0),
  can_device(_can_device)
{
  can_tx_data_start_pos = _can_tx_data_start_pos;
  can_rx_data.header.StdId = _can_rx_id;
  can_device.addTxLink(_can_tx_id, 8, can_tx_data_start_pos, &can_tx_data, 2);
  can_device.addRxLink(&can_rx_data);

  motor_type = _motor_type;
}

/***********************************************************************
** �� �� ���� updateMotorMeasurement()0
** ����˵���� ��CAN���ݸ��µ��������Ϣ
**---------------------------------------------------------------------
** ��������� �����������ָ�롢�������ָ�롢CAN���ݰ�ָ�롢��ʱ��us��
** ���ز����� ��
***********************************************************************/
void Motor_RM::updateMotorMeasurement()
{
  static bool first_update = 1;

  // ʱ���
  com_msr.timestamp = msr.timestamp = micros();

  msr.ecd = (uint16_t)((can_rx_data.data)[0] << 8 | (can_rx_data.data)[1]);
  msr.speed_rpm = (uint16_t)((can_rx_data.data)[2] << 8 | (can_rx_data.data)[3]);
  msr.given_current = (uint16_t)((can_rx_data.data)[4] << 8 | (can_rx_data.data)[5]);
  msr.temperate = (can_rx_data.data)[6];

  // ��ӳ�������ֵ
  if(msr.ecd >= 0 && msr.ecd < params.offset_ecd + params.half_max_value_ecd)
    msr.ecd = msr.ecd - params.offset_ecd;
  else if(msr.ecd >= params.offset_ecd + params.half_max_value_ecd && msr.ecd < params.max_value_ecd)
    msr.ecd = msr.ecd - params.max_value_ecd - params.offset_ecd;

  // �������������ֵ
  msr.delta_ecd = msr.ecd - msr.last_ecd;

  // ��������ֵ���䴦��
  if (msr.delta_ecd < -params.half_max_value_ecd)
  {
    msr.round_cnt++;
    msr.delta_ecd += params.max_value_ecd;
  }
  else if (msr.delta_ecd > params.half_max_value_ecd)
  {
    msr.round_cnt--;
    msr.delta_ecd -= params.max_value_ecd;
  }

  // ����Ȧ������ֵ
  msr.delta_round_cnt = msr.round_cnt - msr.last_round_cnt;

  // ת�ӽ�λ��
  com_msr.rotor.angle = 2 * params.direction * PI *
                        (msr.round_cnt +
                         1.0f * msr.ecd / params.max_value_ecd);

  com_msr.rotor.angular_velocity = msr.speed_rpm / 60.0f * 2 * PI * params.direction;

  // ������ԭʼ����תΪ�����������
  com_msr.rotor.polar_angle = msr.ecd * PI * params.direction / params.half_max_value_ecd;

  /*  TODO: ���������ļ���
  */
  com_msr.output.angle = com_msr.rotor.angle / params.reduction_ratio;
  com_msr.output.angular_velocity = com_msr.rotor.angular_velocity / params.reduction_ratio;
  com_msr.linear.velocity = com_msr.output.angular_velocity * params.output_radius;
  com_msr.linear.displacement = com_msr.output.angle * params.output_radius;
  com_msr.linear.relative_displacement = com_msr.linear.displacement - com_msr.linear.offset;

  // �����ϴε�ֵ
  msr.last_ecd = msr.ecd;
  msr.last_round_cnt = msr.round_cnt;
}

void Motor_RM::setMeasurement_ecd(uint16_t motor_ecd)
{
  msr.ecd = motor_ecd;
}

void Motor_RM::updateMeasurement()
{
  updateMotorMeasurement();
}

void Motor_RM::init(void)
{
  params.half_max_value_ecd = params.max_value_ecd / 2;
}

bool Motor_RM::update(timeus_t dT_us)
{
  updateMotorMeasurement();
  publishMeasurement();
  return true;
}

void Motor_RM::uninit(void) {}
}