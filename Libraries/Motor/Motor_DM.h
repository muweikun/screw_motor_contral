#ifndef __MOTOR_DM_H__
#define __MOTOR_DM_H__

#include "main.h"
#include "stdint.h"

#include "Libraries/Motor/Motor_Backend.h"
#include "Libraries/Math/Vector3.h"
#include "Libraries/CanDevice/CanDevice.h"
#include "Libraries/PID/PID_Controller.h"
class Robot;
namespace robo_lib
{

typedef enum
{
  Motor_Off = 0 , 
  Motor_Disconnected = 1, // DM电机上电复位中
  Motor_Normal = 2,// DM电机正常工作

} Motor_Condition;

//DM电机参数
typedef struct _Motor_DM_Params_t
{
  float reduction_ratio; // 减速比 = 转子转速/输出轴转速
  float output_radius; // 电机输出轴所连接同步轮半径（m），用于计算线速度
  int8_t direction; // 方向，与实际坐标轴同向为1，否则为-1
  uint16_t max_value_ecd; // 电机编码器最大的数值
  uint16_t half_max_value_ecd; // 电机编码器最大的数值的一半
  int16_t offset_ecd; // 电机编码器偏移值（原始数值）
  uint16_t can_tx_id; // CAN总线发送给电机用的ID
  uint16_t can_rx_id; // CAN总线电机发送给开发板用的ID
  uint8_t can_tx_data_start_pos; // CAN总线发送数据起始下标
  uint8_t canx; // CAN总线标号
	
  float offset_angle;
  float interval; // 编码器数据解算频率
} Motor_DM_Params_t;

//DM电机测量值
typedef struct _Motor_DM_Measurement_t
{
  // 时间戳
  timeus_t timestamp; // 本次时间戳
  // 原始电机数据
  uint8_t CAN_ID = 0;
  uint8_t ERR;
  int32_t ecd_int; // 当前编码器数值
  int32_t ecd_save; // 初始上电的编码器数值
  uint16_t speed_rad_int; // 当前转速
  uint16_t torque_int; // 转矩
  float ecd;//解码后位置，单位rad
  float speed_rad;//解码后转速，单位rad/s
  float torque;
  float t_mos;
  float t_rotor;
  int16_t last_ecd; // 上次编码器数值

  // 初步计算的电机数据
  int32_t delta_ecd; // 编码器增量
  int32_t round_cnt; // 圈数
  int32_t last_round_cnt; // 上次圈数
  int32_t delta_round_cnt; // 圈数增量
  // int32_t total_ecd; // 总计的编码器数值（可能会溢出）

} Motor_DM_Measurement_t;


class Motor_DM : public Motor_Backend
{
public:
  friend class Motor_Backend;
//  friend class Arm_ControlTask;
//	friend class RemoteControlTask;
#define P_MIN -12.5f
#define P_MAX 12.5f
#define V_MIN -10.0f
#define V_MAX 10.0f
#define KP_MIN 0.0f
#define KP_MAX 500.0f
#define KD_MIN 0.0f
#define KD_MAX 5.0f
#define T_MIN -28.0f
#define T_MAX 28.0f

  Motor_DM(Motor &motor0,
           CanDevice &_can_device,
           uint16_t _can_tx_id,
           uint16_t _can_rx_id,
           uint8_t _can_tx_data_start_pos,
           int8_t _motor_type);

  // 通过编码器测量、计算电机角度值
  void updateMotorMeasurement();
  virtual bool update(timeus_t dT_us); // 更新电机输出
  virtual void init(void); // 初始化变量
  virtual void uninit(void); // 反初始化

  virtual void updateMeasurement(void);




  void setMotorInput(int16_t input)
  {
    motor_input = input * params.direction;
  }

  void setMotorPosition(float position, float speed)
  {
    uint8_t *pbuf, *vbuf;
    pbuf = (uint8_t*)&position;
    vbuf = (uint8_t*)&speed;
    can_tx_data[0] = *pbuf;
    can_tx_data[1] = *(pbuf + 1);
    can_tx_data[2] = *(pbuf + 2);
    can_tx_data[3] = *(pbuf + 3);
    can_tx_data[4] = *vbuf;
    can_tx_data[5] = *(vbuf + 1);
    can_tx_data[6] = *(vbuf + 2);
    can_tx_data[7] = *(vbuf + 3);

    start_flag++;
    if(start_flag >= 200)
    {
      start_motor();
      start_flag = 0;
    }
  }
   void setMotorTorque(float _torq)
   {
	 uint16_t pos_tmp,vel_tmp,kp_tmp,kd_tmp,tor_tmp;
    pos_tmp =float_to_uint(0, P_MIN, P_MAX, 16);
    vel_tmp = float_to_uint(0, V_MIN, V_MAX, 12);
    kp_tmp =float_to_uint(0, KP_MIN, KP_MAX, 12);
    kd_tmp =float_to_uint(0, KD_MIN, KD_MAX, 12);
    tor_tmp = float_to_uint(_torq,T_MIN, T_MAX, 12);
		
    can_tx_data[0] = (pos_tmp >>8);;
    can_tx_data[1] =  pos_tmp;
    can_tx_data[2] =  (vel_tmp >>4);
    can_tx_data[3] =  ((vel_tmp&0xF)<<4)|(kp_tmp>>8);
    can_tx_data[4] =  kp_tmp;
    can_tx_data[5] = (kd_tmp>> 4);
    can_tx_data[6] = ((kd_tmp&0xF)<<4)|(tor_tmp>>8);
    can_tx_data[7] =  tor_tmp;

    start_flag++;
    if(start_flag >= 200)
    {
      start_motor();
      start_flag = 0;
    }
   }

  void start_motor()
  {
    can_tx_data[0] = 0xFF;
    can_tx_data[1] = 0xFF;
    can_tx_data[2] = 0xFF;
    can_tx_data[3] = 0xFF;
    can_tx_data[4] = 0xFF;
    can_tx_data[5] = 0xFF;
    can_tx_data[6] = 0xFF;
    can_tx_data[7] = 0xFC;
  }
  
  void save_motor_zero()
  {
    can_tx_data[0] = 0xFF;
    can_tx_data[1] = 0xFF;
    can_tx_data[2] = 0xFF;
    can_tx_data[3] = 0xFF;
    can_tx_data[4] = 0xFF;
    can_tx_data[5] = 0xFF;
    can_tx_data[6] = 0xFF;
    can_tx_data[7] = 0xFF;
  }  

  int float_to_uint(float x, float x_min, float x_max, int bits)
  {
    /// Converts a float to an unsigned int, given range and number of bits ///
    //浮点数转化为定点数
    float span = x_max - x_min;
    float offset = x_min;
    return (int) ((x - offset) * ((float)((1 << bits) - 1)) / span);
  }


  float uint_to_float(int x_int, float x_min, float x_max, int bits)
  {
    /// converts unsigned int to float, given range and number of bits ///
    //定点数转化为浮点数
    float span = x_max - x_min;
    float offset = x_min;
    return ((float)x_int) * span / ((float)((1 << bits) - 1)) + offset;
  }

  void setAngularVelocityIMU(float ang_v)
  {
    com_msr.rotor.angular_velocity_imu = ang_v;
  }
  
  Motor_DM_Params_t* getParams_p()
  {
    return &params;
  }
  void setParams(Motor_DM_Params_t _params)
  {
    params = _params;
	params.half_max_value_ecd = params.max_value_ecd / 2 + 1;
  }
 	Motor_DM_Measurement_t getMeasurement()
  {
    return msr;
  }

  CAN_Rx_Data_Pack_t* getCANRxDataPointer()
  {
    return &can_rx_data;
  }
  
protected:

  Motor_DM_Measurement_t msr;
  Motor_DM_Params_t params;//参数与测量值


//  uint32_t motor_position_int;
//  uint32_t motor_speed_int;
//  float motor_position;
//  float motor_speed;

  uint16_t start_flag = 0;

  uint8_t* can_tx_data;
  int16_t motor_input;
  uint8_t can_tx_data_start_pos;
  CAN_Rx_Data_Pack_t can_rx_data;
	uint64_t can_rx_data_last_cnt;

  CanDevice &can_device;
	Motor_Condition motor_condition = Motor_Disconnected,
									motor_last_condition = Motor_Disconnected,
									motor_before_last_condition = Motor_Disconnected;
  float single_angle;
	float last_rotor_angle;
	float reset_angle;
	
	uint8_t test_warning_flag;
};


}


#endif
