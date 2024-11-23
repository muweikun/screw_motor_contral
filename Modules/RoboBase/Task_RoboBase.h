#pragma once

#include "Libraries/Scheduler/Task.h"
#include "Modules/RoboBase/RoboBase.h"

class Task_RoboBase : public robo_lib::Task_Base
{
public:
	Task_RoboBase(RoboBase& robot0) : robo_lib::Task_Base(), robot(robot0)
	{

	}	
protected:
	RoboBase& robot;
};

