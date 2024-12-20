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
#ifndef __ROBO_LIB_MOTOR_RM_H__
#define __ROBO_LIB_MOTOR_RM_H__

#include "stdint.h"

#include "Libraries/Motor/Motor_Backend.h"
#include "Libraries/Math/Vector3.h"
#include "Libraries/CanDevice/CanDevice.h"
#include "Libraries/PID/PID_Controller.h"

namespace robo_lib
{

// RM电机参数
typedef struct _Motor_RM_Params_t
{
  float reduction_ratio; // 减速比 = 转子转速/输出轴转速
  float output_radius; // 电机输出轴所连接同步轮半径（m），用于计算线速度
  int8_t direction; // 方向，与实际坐标轴同向为1，否则为-1
  int16_t max_value_ecd; // 电机编码器最大的数值
  int16_t half_max_value_ecd; // 电机编码器最大的数值
  int16_t offset_ecd; // 电机编码器偏移值（原始数值）
  uint16_t can_tx_id; // CAN总线发送给电机用的ID
  uint16_t can_rx_id; // CAN总线电机发送给开发板用的ID
  uint8_t can_tx_data_start_pos; // CAN总线发送数据起始下标
  uint8_t canx; // CAN总线标号
  float interval; // 编码器数据解算频率
} Motor_RM_Params_t;

// RM电机测量值
typedef struct _Motor_RM_Measurement_t
{
  // 时间戳
  timeus_t timestamp; // 本次时间戳

  // 原始电机数据
  int16_t ecd; // 当前编码器数值
  int16_t speed_rpm; // 当前转速（rpm）
  int16_t given_current; // 电流
  uint8_t temperate; // 温度
  int16_t last_ecd; // 上次编码器数值

  // 初步计算的电机数据
  int16_t delta_ecd; // 编码器增量
  int32_t round_cnt; // 圈数
  int32_t last_round_cnt; // 上次圈数
  int32_t delta_round_cnt; // 圈数增量
  // int32_t total_ecd; // 总计的编码器数值（可能会溢出）

} Motor_RM_Measurement_t;


class Motor_RM : public Motor_Backend
{
public:
  friend class Motor_Backend;
//  friend class Motor_RM_PIDControlTask;
//  friend class ChassisControlTask;

  Motor_RM(Motor &motor0,
           CanDevice &_can_device,
           uint16_t _can_tx_id,
           uint16_t _can_rx_id,
           uint8_t _can_tx_data_start_pos,
           int8_t _motor_type);



  // 通过编码器测量、计算电机角度值
  void updateMotorMeasurement();
//  // 计算电机角度值
//  void updateMotorAngle(Motor_RM_Measurement_t *msr_p,
//                        Motor_RM_Params_t *params_p,
//                        Motor_Common_Measurement_t *com_p);

  //virtual void process(void); // 处理编码器数据
  virtual bool update(timeus_t dT_us); // 更新电机输出
  virtual void init(void); // 初始化变量
  virtual void uninit(void); // 反初始化

  virtual void updateMeasurement(void);

  void setParams(Motor_RM_Params_t _params)
  {
    params = _params;
    params.half_max_value_ecd = params.max_value_ecd / 2;
  }
  Motor_RM_Measurement_t getMeasurement()
  {
    return msr;
  }
  void setMeasurement_ecd(uint16_t motor_ecd);

  void setMotorInput(int16_t input)
  {
    motor_input = input * params.direction;
    syncCANData();
  }

  void setAngularVelocityIMU(float ang_v)
  {
    com_msr.rotor.angular_velocity_imu = ang_v;
  }
  robo_lib::Motor_RM_Params_t* getParams_p()
  {
    return &params;
  }
protected:

  void syncCANData()
  {
    can_tx_data[0] = motor_input >> 8;
    can_tx_data[1] = motor_input;
  }

  Motor_RM_Measurement_t msr;
  Motor_RM_Params_t params;

  uint8_t* can_tx_data;
  int16_t motor_input;
  uint8_t can_tx_data_start_pos;
  CAN_Rx_Data_Pack_t can_rx_data;
  CanDevice &can_device;
};
}
#endif
