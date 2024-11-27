#pragma once
#include "Libraries/Scheduler/Task.h"
#include "Libraries/Scheduler/Scheduler_Common.h"
#include "Libraries/Helper/Helper.h"
#include "Vehicle/hero_test/Robot/Task_Robot.h"


class Robot;

enum Play_Type
{
  ONCE,    // 播放一次就结束
	LOOP    //循环播放
};

class PlaySoundTask:public Task_Robot{
public:
	friend class PlaySoundManageTask;
	PlaySoundTask(Robot &robot0,uint16_t *song,uint16_t song_length,Play_Type type,timeus_t interval_tick_us0):Task_Robot(robot0)
	{
		this->interval_tick_us = interval_tick_us0;
		this->inited =false;
		this->song = song;
		this->type =type;
		this->song_length = song_length;
		this->end_flage =false;
	}
  virtual void init(void);
  

  virtual void uninit(void);


  virtual void update(timeus_t dT_us);
  
  bool playsong();
  
protected:
	bool end_flage;
  uint16_t *song;  //要播放的音乐数据
  uint16_t bzply_n;  //播放位置计数
  uint16_t bzply_count; //播放时间师叔
  uint16_t song_length;
  Play_Type type;     //播放类型

  uint16_t music_steps[4][12] =
    {
        {131, 139, 147, 156, 165, 175, 185, 196, 208, 220, 233, 247},
        {262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494},
        {523, 554, 587, 622, 659, 698, 740, 784, 831, 880, 932, 988},
        {1047, 1109, 1175, 1245, 1319, 1397, 1480, 1568, 1661, 1760, 1865, 1976}
    };

  
  
  
};