/***************************************************************************
**   					             ��������ѧ ��BUGս��
**   					               �������ƣ����Լ���!
**-------------------------------------------------------------------------
** ��    Ŀ��   robo_template
** �� �� ����   MotorRM_ControlTask.cpp
** �ļ�˵����   �����������
**-------------------------------------------------------------------------
**						*�޶�*
**	*�汾*							*�޸�����*							*�޸���*      			 *����*
**	 1.0							   ��ʼ�汾						       �����     	     2022-12-22
**  1.1                                                      ������
***************************************************************************/

#include "Modules/MotorTask/Motor_MC_Tasks.h"
#include "Modules/RoboBase/RoboBase.h"
#include "Libraries/Motor/Motor_MC.h"

/***********************************************************************
** �� �� ���� Motor_RM_PIDControlTask���캯��
** ����˵���� ָ��robot���ã�CAN�豸���ã�ָ�����CAN����id
**            ��CAN�������ݰ�������ʼ�±ָ꣬��������ͣ�
**            ʵ������ע�����ǶȻ����ٶȻ�PID_MotorRM_ControlTask����
**            ʵ����Motor_RM���࣬����robot0���������Backend
**---------------------------------------------------------------------
** ��������� robot���á�CAN�豸���á����CAN����id��
**            CAN�������ݰ�������ʼ�±ꡢ�������
** ���ز����� ��
***********************************************************************/
Motor_MC_ControlTask::Motor_MC_ControlTask(
  RoboBase &robot0,
  robo_lib::CanDevice &_can_device,
  uint16_t _can_rx_id, uint16_t _can_tx_id,
  uint8_t  _can_tx_data_start_pos,
  int8_t   _motor_type,
  timeus_t interval_tick_us0
)
  : Task_RoboBase(robot0), can_device(_can_device)
{

  angle_control_task_p =
    new PIDControlTask(robot, 0);
  angular_velocity_control_task_p =
    new PIDControlTask(robot, 0);

  this->interval_tick_us = interval_tick_us0; // �������������Ƶ��
  can_tx_data_start_pos = _can_tx_data_start_pos;
  motor_backend_p = new robo_lib::Motor_MC(robot0.getMotors(), _can_device, _can_tx_id, _can_rx_id, _can_tx_data_start_pos, _motor_type);
  robot.getMotors().addBackend(motor_backend_p);



}




/***********************************************************************
** �� �� ���� Motor_MC_ControlTask::init()
** ����˵���� �����ʼ��
**---------------------------------------------------------------------
** ��������� ��
** ���ز����� ��
***********************************************************************/
void Motor_MC_ControlTask::init(void)
{
//		motor_backend_p->cmdMotorStop();
  motor_backend_p->cmdMotorShutOff();
}

/***********************************************************************
** �� �� ���� Motor_MC_ControlTask::uninit()
** ����˵���� ���񷴳�ʼ��
**---------------------------------------------------------------------
** ��������� ��
** ���ز����� ��
***********************************************************************/
void Motor_MC_ControlTask::uninit(void)
{

}




/***********************************************************************
** �� �� ���� Motor_MC_ControlTask::update(timeus_t dT_us)
** ����˵���� ������£�����motor_backend_p->update()
**---------------------------------------------------------------------
** ��������� ����ʱ������us��
** ���ز����� ��
***********************************************************************/
void Motor_MC_ControlTask::update(timeus_t dT_us)
{
  if(motor_backend_p != NULL)
  {
    motor_backend_p->update(dT_us);
  }
  //��ȡPIDֵ
  motor_backend_p->getPIDParams();
  if(motor_backend_p->getCANRxDataPointer()->data[0] == 0x30)
  {
    motor_backend_p->MC_motor_reply();
  }

  //�޸�PIDֵ
  //д��RAM���粻����
  if(motor_backend_p->PIDchange_flag == 1)
  {
    motor_backend_p->setPIDParams_RAM(motor_backend_p->getPIDParamsSt());
  }
  if(motor_backend_p->getCANRxDataPointer()->data[0] == 0x31)
  {
    motor_backend_p->MC_motor_reply();
    motor_backend_p->PIDchange_flag = 0;
  }

  //д��ROM���籣��
  if(motor_backend_p->PIDchange_flag == 2)
  {
    motor_backend_p->setPIDParams_ROM(motor_backend_p->getPIDParamsSt());
  }
  if(motor_backend_p->getCANRxDataPointer()->data[0] == 0x32)
  {
    motor_backend_p->MC_motor_reply();
    motor_backend_p->PIDchange_flag = 0;
  }

  //��ȡ��Ȧ������λ��
  motor_backend_p->getMultiLoopEcdPosition();
  if(motor_backend_p->getCANRxDataPointer()->data[0] == 0x60)
  {
    motor_backend_p->MC_motor_reply();
  }
  //��ȡ��Ȩ��������ʼλ��
  motor_backend_p->getMultiLoopEcdRawPosition();
  if(motor_backend_p->getCANRxDataPointer()->data[0] == 0x61)
  {
    motor_backend_p->MC_motor_reply();
  }

  //��ȡ��Ȧ��������ƫֵ
  motor_backend_p->getMultiLoopEcdOffset();
  if(motor_backend_p->getCANRxDataPointer()->data[0] == 0x62)
  {
    motor_backend_p->MC_motor_reply();
  }
  //��ȡ��Ȧ�Ƕ�
  motor_backend_p->getMultiLoopAngle();
  if(motor_backend_p->getCANRxDataPointer()->data[0] == 0x92)
  {
    motor_backend_p->MC_motor_reply();
  }
  // ��ȡ�������2
  motor_backend_p->getState2();
  if(motor_backend_p->getCANRxDataPointer()->data[0] == 0x9C)
  {
    motor_backend_p->MC_motor_reply();
  }

  // �ж��Ƿ��нǶȱ仯�����У��ı��Ȧ������ֵ
  if(robot.arm_task_p->arm_mode != Arm_OFF)
  {
    if(motor_backend_p->angle_update_flag == 1 && motor_backend_p->can_update_flag == 0)
    {
      motor_backend_p->cmdAngleControl(motor_backend_p->getParams_p()->max_speed, motor_backend_p->getParams_p()->angle_control);
      motor_backend_p->angle_update_flag = 0;
    }
  }
  if(motor_backend_p->getCANRxDataPointer()->data[0] == 0xA4)
  {
    motor_backend_p->MC_motor_reply();
  }

  // ʹ�������
  if(robot.arm_task_p->arm_mode == Arm_OFF)
  {
    motor_backend_p->reset_flag = 0;//�ָ����ó�ʼ״̬��ʶ
    motor_backend_p->cmdMotorStop();
  }

  // �������ظ�
  if(motor_backend_p->getCANRxDataPointer()->data[0] == 0x80)
  {
    motor_backend_p->MC_motor_reply();
  }
  // ��������ظ�
  if(motor_backend_p->getCANRxDataPointer()->data[0] == 0x81)
  {
    motor_backend_p->MC_motor_reply();
  }



}
