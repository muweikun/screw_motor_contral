#include "Modules/SoundManageTask/SoundManageTask.h"
#include "Vehicle/hero_test/Robot/Robot.h"

void PlaySoundManageTask::init(void){


}


void PlaySoundManageTask::uninit(void){

}

void PlaySoundManageTask::shutdown(void){
	if(sound_play_task_p!=nullptr)
		sound_play_task_p->selfKill();
	sound_play_task_p =nullptr;
	priority =-1;
}


void PlaySoundManageTask::update(timeus_t dT_us){
	if(sound_play_task_p==nullptr){
		priority =-1;
	}
	else{
		if(sound_play_task_p->end_flage){
			priority =-1;
		}
	}
}

bool PlaySoundManageTask::playSound(Sound sound){
	if(priority>=sound.priority){
			return false;
	}
	else{
		if(sound.is_loop)
			sound_play_task_p =new PlaySoundTask(robot,sound.song_buf,sound.song_length,LOOP,18000);
		else 
			sound_play_task_p =new PlaySoundTask(robot,sound.song_buf,sound.song_length,ONCE,18000);
		
		robot.getScheduler().registerTask(sound_play_task_p); //◊¢≤·“Ù¿÷≤•∑≈»ŒŒÒ
		priority = sound.priority;
		
	return true;
	}

}