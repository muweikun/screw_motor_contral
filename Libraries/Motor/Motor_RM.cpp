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

#include "Libraries/Motor/Motor_RM.h"
#include "Libraries/Motor/Motor.h"
#include "Libraries/Motor/Motor_Backend.h"
#include "Libraries/CanDevice/CanDevice.h"
#include "arm_math.h"

namespace robo_lib
{

/***********************************************************************
** 函 数 名： Motor_RM::Motor_RM()
** 函数说明： 将定义的电机对象的CAN的接收与发送数据地址添加到can_device中
**---------------------------------------------------------------------
** 输入参数： 电机测量数据指针、电机参数指针、CAN数据包指针、耗时（us）
** 返回参数： 无
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
** 函 数 名： updateMotorMeasurement()0
** 函数说明： 从CAN数据更新电机测量信息
**---------------------------------------------------------------------
** 输入参数： 电机测量数据指针、电机参数指针、CAN数据包指针、耗时（us）
** 返回参数： 无
***********************************************************************/
void Motor_RM::updateMotorMeasurement()
{
  static bool first_update = 1;

  // 时间戳
  com_msr.timestamp = msr.timestamp = micros();

  msr.ecd = (uint16_t)((can_rx_data.data)[0] << 8 | (can_rx_data.data)[1]);
  msr.speed_rpm = (uint16_t)((can_rx_data.data)[2] << 8 | (can_rx_data.data)[3]);
  msr.given_current = (uint16_t)((can_rx_data.data)[4] << 8 | (can_rx_data.data)[5]);
  msr.temperate = (can_rx_data.data)[6];

  // 重映射编码器值
  if(msr.ecd >= 0 && msr.ecd < params.offset_ecd + params.half_max_value_ecd)
    msr.ecd = msr.ecd - params.offset_ecd;
  else if(msr.ecd >= params.offset_ecd + params.half_max_value_ecd && msr.ecd < params.max_value_ecd)
    msr.ecd = msr.ecd - params.max_value_ecd - params.offset_ecd;

  // 计算编码器增量值
  msr.delta_ecd = msr.ecd - msr.last_ecd;

  // 编码器数值跳变处理
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

  // 计算圈数增量值
  msr.delta_round_cnt = msr.round_cnt - msr.last_round_cnt;

  // 转子角位移
  com_msr.rotor.angle = 2 * params.direction * PI *
                        (msr.round_cnt +
                         1.0f * msr.ecd / params.max_value_ecd);

  com_msr.rotor.angular_velocity = msr.speed_rpm / 60.0f * 2 * PI * params.direction;

  // 编码器原始数据转为电机极角数据
  com_msr.rotor.polar_angle = msr.ecd * PI * params.direction / params.half_max_value_ecd;

  /*  TODO: 计算输出轴的极角
  */
  com_msr.output.angle = com_msr.rotor.angle / params.reduction_ratio;
  com_msr.output.angular_velocity = com_msr.rotor.angular_velocity / params.reduction_ratio;
  com_msr.linear.velocity = com_msr.output.angular_velocity * params.output_radius;
  com_msr.linear.displacement = com_msr.output.angle * params.output_radius;
  com_msr.linear.relative_displacement = com_msr.linear.displacement - com_msr.linear.offset;

  // 保存上次的值
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