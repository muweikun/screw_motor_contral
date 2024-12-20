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


#include "Libraries/PID/PID_Controller.h"
#include "Libraries/Math/CommonMath.h"
#include "Libraries/Scheduler/Task.h"
#include "Libraries/Error/Error.h"
namespace robo_lib
{
/***********************************************************************
** 函 数 名： PID_Controller::PID_Controller()
** 函数说明： 声明PID的加法运算为普通加法
**---------------------------------------------------------------------
** 输入参数： 电机测量数据指针、电机参数指针、CAN数据包指针、耗时（us）
** 返回参数： 无
***********************************************************************/
PID_Controller::PID_Controller()
{

}

/***********************************************************************
** 函 数 名： PID_Controller::PID_Controller
** 函数说明： PID参数初始化的构造函数
**---------------------------------------------------------------------
** 输入参数： _PID_Params_t 结构体的参数
** 返回参数： 无
***********************************************************************/
PID_Controller::PID_Controller(PID_Type _type_selection,
                               robo_lib::AdvancedAdd_Base<float> *adder,
                               float _kp, float _ki,
                               float _kd_fb, float _kd_ex, float _k_ff,
                               float _max_out_value, float _min_out_value, bool _limit_output,
                               float _max_integral, float _min_integral, bool _limit_integral,
                               float _interval,
                               float _ki_able_error_range,
                               float _kd_able_error_range
                              )
{
  pid_params.type_selection = _type_selection;
  pid_params.kp = _kp;
  pid_params.ki = _ki;
  pid_params.kd_fb = _kd_fb;
  pid_params.kd_fb = _kd_ex;
  pid_params.k_ff = _k_ff;
  pid_params.min_integral = _min_integral;
  pid_params.max_integral = _max_integral;
  pid_params.ki_able_error_range = _ki_able_error_range;
  pid_params.kd_able_error_range = _kd_able_error_range;
  pid_params.max_out_value = _max_out_value;
  pid_params.min_out_value = _min_out_value;
  pid_params.add = adder;
  pid_params.interval = _interval;
}


/***********************************************************************
** 函 数 名： PID_Controller::PID_Controller
** 函数说明： 输入PID_Data_t结构体，PID_Params_t结构体的构造函数
**---------------------------------------------------------------------
** 输入参数： _PID_Params_t 结构体的参数
** 返回参数： 无
***********************************************************************/
PID_Controller::PID_Controller(PID_Data_t &_pid_data, PID_Params_t &_pid_params)
{
  pid_data = _pid_data;
  pid_params = _pid_params;
}


/***********************************************************************
** 函 数 名： PID_Controller::PID_Controller
** 函数说明： 拷贝构造函数
**---------------------------------------------------------------------
** 输入参数： PID_Controller类的对象
** 返回参数： 无
***********************************************************************/
PID_Controller::PID_Controller(const PID_Controller & _pid_controller)
{
  this->pid_data = _pid_controller.pid_data;
  this->pid_params = _pid_controller.pid_params;
}

/***********************************************************************
** 函 数 名： PID_Controller::setParams
** 函数说明： 设置PID_Params_t结构体参数
**---------------------------------------------------------------------
** 输入参数： PID_Controller类的对象
** 返回参数： 无
***********************************************************************/
void PID_Controller::setParams(PID_Type _type_selection,
                               robo_lib::AdvancedAdd_Base<float> *adder,
                               float _kp, float _ki,
                               float _kd_fb, float _kd_ex, float _k_ff,
                               float _max_out_value, float _min_out_value, bool _limit_output,
                               float _max_integral, float _min_integral, bool _limit_integral,
                               float _interval,
                               float _ki_able_error_range,
                               float _kd_able_error_range

                              )
{
  pid_params.type_selection = _type_selection;
  pid_params.kp = _kp;
  pid_params.ki = _ki;
  pid_params.kd_fb = _kd_fb;
  pid_params.kd_fb = _kd_ex;
  pid_params.k_ff = _k_ff;
  pid_params.min_integral = _min_integral;
  pid_params.max_integral = _max_integral;
  pid_params.ki_able_error_range = _ki_able_error_range;
  pid_params.kd_able_error_range = _kd_able_error_range;
  pid_params.max_out_value = _max_out_value;
  pid_params.min_out_value = _min_out_value;
  pid_params.add = adder;
  pid_params.interval = _interval;
}

/***********************************************************************
** 函 数 名： PID_Controller::setParams
** 函数说明： 拷贝函数
**---------------------------------------------------------------------
** 输入参数： _pid_params结构体
** 返回参数： 无
***********************************************************************/
void PID_Controller::setParams(const PID_Params_t &_pid_params)
{
  pid_params = _pid_params;
}

/***********************************************************************
** 函 数 名： PID_Controller::clear
** 函数说明： pid_data结构体的成员清零
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
***********************************************************************/
void PID_Controller::clear()
{
  pid_data.expect            = 0;            // 期望
  pid_data.d_expect          = 0;            // 期望增量
  pid_data.dd_expect         = 0;            // 期望增量的增量
  pid_data.last_expect       = 0;            // 上次期望
  pid_data.last_d_expect     = 0;            // 上次（期望增量）

  pid_data.feedback          = 0;            // 反馈
  pid_data.d_feedback        = 0;            // 反馈增量
  pid_data.dd_feedback       = 0;            // 反馈增量的增量
  pid_data.last_feedback     = 0;            // 上次反馈
  pid_data.last_d_feedback   = 0;            // 上次（反馈增量）

  pid_data.feedforward       = 0;            // 前馈

  pid_data.error             = 0;            // 误差
  pid_data.last_error        = 0;            // 上次误差

  pid_data.last_dT_s         = 0;            // 上次时间增量
  pid_data.last_freq         = 0;            // 上次频率（用空间换时间）

  pid_data.integral          = 0;            // 误差积分

  pid_data.out               = 0;            // 输出值

}

/***********************************************************************
** 函 数 名： PID_Controller::calculateWithCPU
** 函数说明： PID运算函数
**---------------------------------------------------------------------
** 输入参数： 计算周期，期望值，反馈值，前馈值
** 返回参数： 无
***********************************************************************/
float PID_Controller::calculateWithCPU(
  timeus_t _dT_us,     //周期（us）
  float _expect,				//期望值
  float _feedback,     //反馈值
  float _feedforward	//前馈值
)
{
  pid_data.expect = _expect;
  pid_data.feedback = _feedback;
  pid_data.feedforward = _feedforward;
  float _dT_s = safeDiv(_dT_us, 1e6f, 0);
  float _freq = safeDiv(1, _dT_s, 0);
  float _kp = 0.0f;
  float _ki = 0.0f;
  float _kd_fb = 0.0f;
  float _kd_ex = 0.0f;
  float _k_ff = 0.0f;

#ifdef DEBUG_MODE
  //判断PID加法指针是否空
  if(pid_params.add == NULL)
  {
    error.error_code.pid_controller_adder_not_initialized  = 1;
    error.Error_Handler();
  }
#endif
#define add (*pid_params.add)

  switch(pid_params.type_selection)
  {
  case 0://增量式：计算公式OUT = kp*(e(k)-e(k-1))+ki*(e(k)*dt)+kd_ex*[(x(k)-x(k-1))-(x(k-1)-x(k-2))]/dt-kd_fb*[(y(k)-y(k-1))-(y(k-1)-y(k-2))]/dt+k_ff*feedforward

    // 微分项 _kd_ex
    pid_data.d_expect = add(pid_data.expect, -pid_data.last_expect);
    _kd_ex = pid_data.d_expect * pid_params.kd_ex * _freq - pid_data.last_d_expect * pid_params.kd_ex * pid_data.last_freq;

    pid_data.d_feedback = add(pid_data.feedback, - pid_data.last_feedback);
    _kd_fb = pid_data.d_feedback * pid_params.kd_fb * _freq - pid_data.last_d_feedback * pid_params.kd_fb * pid_data.last_freq;

    _kd_ex -= _kd_fb;

    // 比例项 _kp
    pid_data.error = add(pid_data.expect, - pid_data.feedback);
    _kp = pid_params.kp * (pid_data.error - pid_data.last_error);

    // 积分项 _ki
    _ki = pid_data.error * _dT_s * pid_params.ki;

    // 前馈项 _k_ff
    _k_ff = pid_data.feedforward * pid_params.k_ff;

    // 求和
    _kp += _kd_ex;
    _ki += _kp;

    // 输出限幅
    if(pid_params.limit_output)
      pid_data.out = limit(pid_data.out + _ki + _k_ff, pid_params.min_out_value, pid_params.max_out_value);
    else
      pid_data.out += _ki + _k_ff;

    pid_data.last_expect = pid_data.expect;
    pid_data.last_feedback = pid_data.feedback;
    pid_data.last_d_feedback = pid_data.d_feedback;
    pid_data.last_d_expect = pid_data.d_expect;
    pid_data.last_dT_s = _dT_s;
    pid_data.last_freq = _freq;
    pid_data.last_error = pid_data.error;

    break;

  case 1: // 位置式：计算公式OUT = kp*e(k)+ki*(Σ(e(k)*dt))+kd_ex*(x(k)-x(k-1))/dt-kd_fb*(y(k)-y(k-1))/dt+k_ff*feedforward

    // 微分项 _kd_ex
    pid_data.d_expect = add(pid_data.expect, - pid_data.last_expect);
    _kd_ex = pid_data.d_expect * pid_params.kd_ex * _freq;

    pid_data.d_feedback = add(pid_data.feedback, - pid_data.last_feedback);
    _kd_fb = pid_data.d_feedback * pid_params.kd_fb * _freq;

    _kd_ex -= _kd_fb;

    // 比例项 _kp
    pid_data.error = add(pid_data.expect, - pid_data.feedback);
    _kp = pid_params.kp * pid_data.error;

    // 积分项 _ki
    _ki = pid_data.error * _dT_s;
//    pid_data.integral += _ki;

    // 积分限幅
    if(pid_params.limit_integral)
      pid_data.integral = limit(pid_data.integral + _ki, pid_params.min_integral, pid_params.max_integral);
    else
      pid_data.integral += _ki;

    _ki = pid_data.integral * pid_params.ki;

    // 前馈项 _k_ff
    _k_ff = pid_data.feedforward * pid_params.k_ff;


    // 求和
    _kp += _kd_ex;
    _ki += _kp;

    // 输出限幅
    if(pid_params.limit_output)
      pid_data.out = limit(_ki + _k_ff, pid_params.min_out_value, pid_params.max_out_value);
    else
      pid_data.out = _ki + _k_ff;


    pid_data.last_expect = pid_data.expect;
    pid_data.last_feedback = pid_data.feedback;
    pid_data.last_d_feedback = pid_data.d_feedback;
    pid_data.last_d_expect = pid_data.d_expect;

    break;
  default:
    break;
  }
  return pid_data.out;
}

}