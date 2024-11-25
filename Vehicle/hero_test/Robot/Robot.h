#pragma once
#include "Modules/ScrewMotorTask/ScrewMotorTask.h"
#include "Libraries/Error/Error.h"
#include "Params.h"
#include "Libraries/Scheduler/Scheduler.h"
#include "Modules/CanTask/CanSendTask.h"
#include "Modules/CanTask/CANSyncTask.h"
#include "Modules/RoboBase/RoboBase.h"
#define CAN1_TX_BUF_LEN 20
#define CAN2_TX_BUF_LEN 20

class Robot : public RoboBase
{
	public:
	virtual void init(void) override;
	virtual void run(void) override;
	
	Params get_Params()
	{
		return params;
	}

	protected:
	robo_lib::CAN_Tx_Data_Pack_t can1_queue_data[CAN1_TX_BUF_LEN];
  robo_lib::CAN_Tx_Data_Pack_t can2_queue_data[CAN2_TX_BUF_LEN];
	uint8_t robot_id = 0;
	Params params;
	CANSendTask *can1_send_task_p, *can2_send_task_p;
  CANSyncTask *can1_sync_task_0x200_p;
  
	Srew_Motor_PIDControlTask *srew_motor1_p;
	
	


};
