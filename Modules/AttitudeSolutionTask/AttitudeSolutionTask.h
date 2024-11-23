#ifndef __ATTITUDESOLUTIONTASK_H__
#define __ATTITUDESOLUTIONTASK_H__

#include "Libraries/Scheduler/Task.h"
#include "Libraries/InertialSensor/InertialSensor.h"
#include "stdint.h"
#include "Libraries/AHRS/AHRS.h"
#include "Libraries/AHRS/MahonyAHRS.h"
#include "Libraries/PID/PID_Controller.h"
#include "Modules/RoboBase/Task_RoboBase.h"

class RoboBase;

// ÍÓÂÝÒÇ¿ØÎÂ
class PID_GyrotempTask : public Task_RoboBase
{
public:
  friend class AttitudeSolutionTask;
  PID_GyrotempTask(RoboBase &robot0, timeus_t interval_tick_us0 = 1e6f / 5.0f) : Task_RoboBase(robot0) // 5 Hz
  {
    this->interval_tick_us = interval_tick_us0;
  }

  virtual void init(void);
  virtual void update(timeus_t dT_us);
  virtual void uninit(void);

protected:
  robo_lib::PID_Controller pid_controller;
  float bmi088_temperature;
};


class AttitudeSolutionTask : public Task_RoboBase
{
public:
  friend class PID_GyrotempTask;
  friend class RoboBase;
  AttitudeSolutionTask(RoboBase &robot0) : Task_RoboBase(robot0)
  {
    inited = true;
    pid_gyrotemp_task_p = new PID_GyrotempTask(robot, 1e6f / 5.0f); // ´´½¨PID¿ØÎÂIMUÈÎÎñ£¬5Hz
  }

  virtual ~AttitudeSolutionTask(void) {}

  virtual void init(void);

  virtual void update(timeus_t dT_us);

  virtual void uninit(void);

  PID_GyrotempTask *getPIDGyrotempTaskPointer(void)
  {
    return pid_gyrotemp_task_p;
  }

  robo_lib::QuaternionF getIMUQuat(void) const
  {
    return ahrs.getIMUQuat();
  }

  robo_lib::EulerAngleF getIMUEuler() const
  {
    return ahrs.getIMUEuler();
  }
  robo_lib::Matrix3f getIMUCoord() const
  {
    return ahrs.getIMUCoordinateSystem();
  }

protected:
  robo_lib::MahonyAHRS ahrs;
  PID_GyrotempTask *pid_gyrotemp_task_p;
};

#endif
