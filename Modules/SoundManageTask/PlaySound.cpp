#include "Modules/SoundManageTask/PlaySound.h"
 #include "Vehicle/hero_test/Robot/Robot.h"
/***********************************************************************
** �� �� ���� PlaySoundTask::init
** ����˵���� ��ʼ��
**---------------------------------------------------------------------
** ��������� ��
** ���ز����� ��
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
    // �����ǰ�������������������ȣ����� true ��ʾ�����������
    if(bzply_n >= song_length){
        return true;
    }
    else{
        // ��ȡ��ǰ�����ĸ������
        off_delay = ((song[bzply_n] & 0xF000) >> 12) * 6; // �����ر�ʱ���ӳ٣���λΪ6ms��
        on_delay = ((song[bzply_n] & 0x0F00) >> 8);       // ��������ʱ���ӳ٣���λΪ6ms��
        level = ((song[bzply_n] & 0x00F0) >> 4);           // ����/Ч������
        step = (song[bzply_n] & 0x000F);                    // ���������ߣ�������

        // �жϵ�ǰ�Ĳ��Ž��� bzply_count �Ƿ�С�������Ŀ����ӳ�
        if(bzply_count < on_delay){
            // ���÷�������Ƶ��Ϊ��ǰ������Ƶ��
            robot.getHelper().setBuzzerFrequence(music_steps[level][step]);
            bzply_count++; // ���ż���������
        }
        else if(bzply_count < (on_delay + off_delay)){
            // ���÷�����Ƶ��Ϊ 0����ʾ�رշ�����
            robot.getHelper().setBuzzerOff();
            bzply_count++; // ���ż���������
        }
        else{
            // �������������ϣ�׼��������һ������
            bzply_n++;    // ��һ������
            bzply_count = 0;  // ���ü�����
        }
    }

    return false; // ���� false ��ʾ����û�в�����
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
































