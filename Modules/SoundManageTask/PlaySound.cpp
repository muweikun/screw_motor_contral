#include "Modules/SoundManageTask/PlaySound.h"
 #include "Vehicle/hero_test/Robot/Robot.h"
/***********************************************************************
** 函 数 名： PlaySoundTask::init
** 函数说明： 初始化
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
***********************************************************************/
void PlaySoundTask::init(void)
{
    bzply_n = 0;
    bzply_count = 1;
    end_flage = false;
    robot.getHelper().setBuzzerOff();
}
void PlaySoundTask::uninit(void)
{

}

bool PlaySoundTask::playsong(void)
{
    uint8_t on_delay, off_delay, step, level;
    // 如果当前音符索引超过歌曲长度，返回 true 表示歌曲播放完毕
    if(bzply_n >= song_length){
        return true;
    }
    else{
        // 提取当前音符的各项参数
        off_delay = ((song[bzply_n] & 0xF000) >> 12) * 6; // 音符关闭时的延迟（单位为6ms）
        on_delay = ((song[bzply_n] & 0x0F00) >> 8);       // 音符开启时的延迟（单位为6ms）
        level = ((song[bzply_n] & 0x00F0) >> 4);           // 音量/效果级别
        step = (song[bzply_n] & 0x000F);                    // 音符的音高（索引）

        // 判断当前的播放进度 bzply_count 是否小于音符的开启延迟
        if(bzply_count < on_delay){
            // 设置蜂鸣器的频率为当前音符的频率
            robot.getHelper().setBuzzerFrequence(music_steps[level][step]);
            bzply_count++; // 播放计数器递增
        }
        else if(bzply_count < (on_delay + off_delay)){
            // 设置蜂鸣器频率为 0，表示关闭蜂鸣器
            robot.getHelper().setBuzzerOff();
            bzply_count++; // 播放计数器递增
        }
        else{
            // 如果音符播放完毕，准备播放下一个音符
            bzply_n++;    // 下一首音符
            bzply_count = 0;  // 重置计数器
        }
    }

    return false; // 返回 false 表示歌曲没有播放完
}

void PlaySoundTask::update(timeus_t dT_us){
	end_flage =playsong();
	if(end_flage){
		robot.getHelper().setBuzzerOff();
		if(type==ONCE){
			selfKill();
		}
		else
			init();
	}
}
































