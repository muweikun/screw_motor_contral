#include "Modules/ScrewMotorTask/ScrewMotorTask.h"
#include "Vehicle/hero_test/Robot/Robot.h"
#include "Modules/RoboBase/RoboBase.h"
#include "Vehicle/hero_test/Robot/Params.h"
#define ABS(x) ((x) > 0 ? (x) : -(x))
using namespace robo_lib;

/***********************************************************************
** �� �� ���� ScrewMotorTask���캯��
** ����˵���� ָ��robot���ã�CAN�豸���ã�ָ�����CAN����id
**            ��CAN�������ݰ�������ʼ�±ָ꣬���������ʱ������ͬʱ
**            �����ע��Motor_RM_PIDControlTask����
**---------------------------------------------------------------------
** ��������� robot���á�CAN�豸���á����CAN����id��
**            CAN�������ݰ�������ʼ�±ꡢ�������ʱ����
** ���ز����� ��
***********************************************************************/
Srew_Motor_PIDControlTask::Srew_Motor_PIDControlTask(
	     Robot &robot0,
       robo_lib::Motor_RM_Params_t *m1, robo_lib::PID_Params_t *m1_ang, robo_lib::PID_Params_t *m1_ang_vel,
			 timeus_t interval_tick_us0): Task_Robot(robot0)
{
	this->interval_tick_us =interval_tick_us0;

		 if(m1 != NULL)
		 {
	        if(m1->canx == 1)
        {
            this->motor_1_pid_task = new Motor_RM_PIDControlTask(robot0,
							  robot.getCAN1Device(),
                m1->can_rx_id,
                m1->can_tx_id,
                m1->can_tx_data_start_pos,
                RoboMaster_2006,
                m1->interval);
        }
        else if(m1->canx == 2)
        {
            this->motor_1_pid_task = new Motor_RM_PIDControlTask(robot0,
                robot.getCAN2Device(),
                m1->can_rx_id,
                m1->can_tx_id,
                m1->can_tx_data_start_pos,
                RoboMaster_2006,
                m1->interval);
        }
				this->motor_1_pid_task->get_motor_backend_p()->setParams(*m1);
		}
	    if(m1_ang_vel != NULL)
    {
        this->motor_1_pid_task->getAngularVelocityTaskPointer()->setPIDControllerParams(*m1_ang_vel);
        this->motor_1_pid_task->getAngularVelocityTaskPointer()->setInterval((*m1_ang_vel).interval);
    }
		

}
void Srew_Motor_PIDControlTask::init(){
	 if(motor_1_pid_task != NULL)
        robot.getScheduler().registerTask(motor_1_pid_task);
	 if(motor_1_pid_task->getAngularVelocityTaskPointer() != NULL)
        robot.getScheduler().registerTask(motor_1_pid_task->getAngularVelocityTaskPointer());

}
void Srew_Motor_PIDControlTask::update(timeus_t dT_us){
	
	 RC_Data rc_data = robot.getRCProtocol().getRCData();
	 if(ABS(rc_data.ch3)<150){
		  motor_rpm_expect[0] =0;
		  motor_1_pid_task->setMotorInput(0);
	
	 }
	 else {
	 if(rc_data.ch3>0){
				motor_rpm_expect[0] =(int16_t)(rc_data.ch3*800.0f/660.0f);
	 }
	  else{
				motor_rpm_expect[0] =(int16_t)(rc_data.ch3*800.0f/660.0f);
	 }
	 motor_rpm[0] = motor_1_pid_task->get_motor_backend_p()->getMeasurement().speed_rpm;
	 motor_1_pid_task->getAngularVelocityTaskPointer()->setPIDControllerExpect(motor_rpm_expect[0]);
	 motor_1_pid_task->getAngularVelocityTaskPointer()->setPIDControllerFeedback(motor_rpm[0]);
	 motor_input[0] = motor_1_pid_task->getAngularVelocityTaskPointer()->getOutput();
	 motor_1_pid_task->setMotorInput((int16_t)(motor_input[0]/10.0f));
	 }
	


	 //motor_1_pid_task->setMotorInput(0);

}

void Srew_Motor_PIDControlTask::uninit(){

}
