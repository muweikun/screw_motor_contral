#pragma once

#include "Libraries/Scheduler/Scheduler.h"
#include "Libraries/Motor/Motor.h"
#include "Libraries/Helper/Helper.h"
#include "Libraries/CanDevice/CanDevice.h"
#include "Libraries/RCProtocol/RCProtocol.h"
#include "Libraries/InertialSensor/InertialSensor.h"

#include "Modules/RoboBase/ControlBase.h"

class RoboBase : public ControlBase
{
	public:
	robo_lib::Scheduler& getScheduler(void)
	{
		return scheduler;
	}
	
	robo_lib::Helper& getHelper(void)
	{
		return helper;
	}
	
	robo_lib::RCProtocol& getRCProtocol(void)
	{
		return rc_protocol;
	}
	
	robo_lib::Motor& getMotors(void)
	{
		return motors;
	}
	
	robo_lib::InertialSensor& getInertialSensor(void)
	{
		return inertial_sensors;
	}
	
	robo_lib::CanDevice& getCAN1Device(void)
	{
		return can1_device;
	}
	
	robo_lib::CanDevice& getCAN2Device(void)
	{
		return can2_device;
	}
	
	[[deprecated]]
	robo_lib::RCProtocol* getRCProtocolPointer(void)
  {
    return &rc_protocol;
  }
	
	[[deprecated]]
	robo_lib::InertialSensor* getInertialSensorPointer(void)
  {
    return &inertial_sensors;
  }
	
	[[deprecated]]
	robo_lib::CanDevice* getCAN1DevicePointer(void)
	{
		//#warning "function getCAN1DevicePointer will be deprecated in future version, please use getCAN1Device instead";
		return &can1_device;
	}
	
	[[deprecated]]
	robo_lib::CanDevice* getCAN2DevicePointer(void)
	{
		return &can2_device;
	}
	

	
	protected:
	robo_lib::Scheduler scheduler;
	robo_lib::Helper helper;
	robo_lib::RCProtocol rc_protocol;
	robo_lib::Motor motors;
	robo_lib::InertialSensor inertial_sensors;
	robo_lib::CanDevice can1_device, can2_device;
};
