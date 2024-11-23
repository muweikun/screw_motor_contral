#include "Modules/ScrewMotorTask/ScrewMotorTask.h"
#include "Vehicle/hero_test/Robot/Robot.h"
#include "Modules/RoboBase/RoboBase.h"
#include "Vehicle/hero_test/Robot/Params.h"

using namespace robo_lib;

/***********************************************************************
** 函 数 名： ScrewMotorTask构造函数
** 函数说明： 指定robot引用，CAN设备引用，指定电机CAN总线id
**            和CAN总线数据包发送起始下标，指定任务更新时间间隔，同时
**            给电机注册Motor_RM_PIDControlTask任务
**---------------------------------------------------------------------
** 输入参数： robot引用、CAN设备引用、电机CAN总线id、
**            CAN总线数据包发送起始下标、任务更新时间间隔
** 返回参数： 无
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
	
	 motor_rpm_expect[0] =robot.get_Params().device_params.motor_rpm_expect[0];
	 motor_rpm[0] = motor_1_pid_task->get_motor_backend_p()->getMeasurement().speed_rpm;
	
	 motor_1_pid_task->getAngularVelocityTaskPointer()->setPIDControllerExpect(motor_rpm_expect[0]);
	 motor_1_pid_task->getAngularVelocityTaskPointer()->setPIDControllerFeedback(motor_rpm[0]);
	 motor_input[0] = motor_1_pid_task->getAngularVelocityTaskPointer()->getOutput();
	 motor_1_pid_task->setMotorInput(motor_input[0]);


}

void Srew_Motor_PIDControlTask::uninit(){

}
