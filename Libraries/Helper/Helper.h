/**
  ******************************************************************************
  * @file    AHRS.cpp
  * @version 2.0
  * @author  DUT-Lingbug Embedded Group
  * @brief   ��̬����AHRS����
  *
  ******************************************************************************
  * @attention
  *
  * Copyright 2023 DUT-Lingbug.
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef __ROBO_LIB_HELPER_H__
#define __ROBO_LIB_HELPER_H__

#include "stdint.h"
#include "main.h"
#include "adc.h"

#define PLAYING_STOP 0
#define PLAYING_INIT_MUSIC 1
#define PLAYING_WARNING_SOUND 11
#define PLAYING_ERROR_SOUND 12
#define PLAYING_GYROCALIB_SOUND 21
#define PLAYING_AUTOAIMING_SOUND 22
namespace robo_lib
{
class Helper
{
public:
  Helper(void)
  {
    bzply_n = 0;
    bzply_count = 1;
    buzzer_state = PLAYING_STOP;
  }
  void setLED(uint8_t R, uint8_t G, uint8_t B);
  void toggleLED(uint8_t R, uint8_t G, uint8_t B);
  void toggleAllLED(void);
  void setLaser(void);
  void resetLaser(void);
  void toggleLaser(void);
  void setServo(uint8_t number, float degree);
  void heat(uint16_t out);
  void setBuzzerOff(void);
  void setBuzzerFrequence(uint16_t freq);
  int8_t setBuzzerState(uint8_t state);
  void playingSound(uint8_t *sound, uint16_t len);
  bool playingSong(uint16_t *song, uint16_t len);

private:
  uint16_t bzply_n;
  uint8_t bzply_count;
  uint8_t buzzer_state; // ������״̬

  // ����
  uint16_t music_steps[4][12] =
  {
    {131, 139, 147, 156, 165, 175, 185, 196, 208, 220, 233, 247},
    {262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494},
    {523, 554, 587, 622, 659, 698, 740, 784, 831, 880, 932, 988},
    {1047, 1109, 1175, 1245, 1319, 1397, 1480, 1568, 1661, 1760, 1865, 1976}
  };


  // ����
  uint8_t sound_warning[6] = {0x4B, 0x40, 0x4B, 0x40, 0x4B, 0x40}; //B__B__B__
  // ERROR
  uint8_t sound_error[6] = {0x2B, 0x10, 0x2B, 0x10, 0x2B, 0x10}; //B_B_B_
  // �����ǽ���
  uint8_t sound_gyrocalibrating[6] = {0x2D, 0x40, 0x2D, 0x40, 0x2D, 0x40}; //D__D__D__
  // ����
  uint8_t sound_autoaiming[6] = {0x2D, 0x10, 0x2D, 0x10, 0x2D, 0x10}; //D_D_D_

};
}
#endif
