#pragma once
#include "Libraries/Scheduler/Task.h"
#include "Libraries/Scheduler/Scheduler_Common.h"
#include "Libraries/Helper/Helper.h"
#include "Vehicle/hero_test/Robot/Task_Robot.h"
#include "Modules/SoundManageTask/PlaySound.h"
class Robot;  

struct Sound
{
    uint16_t *song_buf;
    uint16_t song_length;
    uint16_t priority;
    bool is_loop;
};

class PlaySoundManageTask:public Task_Robot{
public:
	
	PlaySoundManageTask(Robot &robot0,timeus_t interval_tick_us0=10e6f/40.0f):Task_Robot(robot0){
		interval_tick_us = interval_tick_us0;
		self_kill = false;
		inited = false;
	}
	virtual void init(void);
	virtual void uninit(void);
	virtual void update(timeus_t dT_us);
	bool playSound(Sound sound);
	void shutdown(void);
	
protected:
	PlaySoundTask *sound_play_task_p;
  int8_t priority;
  
	
	
	
};