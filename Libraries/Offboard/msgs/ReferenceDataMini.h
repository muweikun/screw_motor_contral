
/** @file
 *	@brief Offboardlink comm protocol generated from ReferenceDataMini.json
 *  @author Xianhao Ji
 */

#pragma once
#include "OffboardLink.h"

namespace olk
{
    struct ReferenceDataMini : public MessageBase
    {
        public:
        uint8_t game_state;
        uint16_t remaining_time;
        uint8_t self_color;
        uint16_t self_health;
        float bullet_speed_meas;
        uint16_t shoot_heat;
        uint8_t hurt_by_gimbal;
        uint16_t remaining_bullet;
        uint8_t who_is_balance;
        helper_float_u32 h;
            
        ReferenceDataMini() : MessageBase(0x40, 14)
		{
				
		}

        virtual void decode(uint8_t *buf) override
        {

			game_state = buf[OFFBOARDLINK_FRAME_HEAD_LEN + 0];
        
			remaining_time = (buf[OFFBOARDLINK_FRAME_HEAD_LEN + 2] << 8) | buf[OFFBOARDLINK_FRAME_HEAD_LEN + 1];

			self_color = buf[OFFBOARDLINK_FRAME_HEAD_LEN + 3];
        
			self_health = (buf[OFFBOARDLINK_FRAME_HEAD_LEN + 5] << 8) | buf[OFFBOARDLINK_FRAME_HEAD_LEN + 4];

			bullet_speed_meas = (uint16_t)((buf[OFFBOARDLINK_FRAME_HEAD_LEN + 7] << 8) | buf[OFFBOARDLINK_FRAME_HEAD_LEN + 6]) / 655.2;

			shoot_heat = (buf[OFFBOARDLINK_FRAME_HEAD_LEN + 9] << 8) | buf[OFFBOARDLINK_FRAME_HEAD_LEN + 8];

			hurt_by_gimbal = buf[OFFBOARDLINK_FRAME_HEAD_LEN + 10];
        
			remaining_bullet = (buf[OFFBOARDLINK_FRAME_HEAD_LEN + 12] << 8) | buf[OFFBOARDLINK_FRAME_HEAD_LEN + 11];

			who_is_balance = buf[OFFBOARDLINK_FRAME_HEAD_LEN + 13];
        
        }

        virtual void packData(uint8_t *buf) override
        {

			buf[OFFBOARDLINK_FRAME_HEAD_LEN + 0] = game_state;

			buf[OFFBOARDLINK_FRAME_HEAD_LEN + 1] = remaining_time;
            buf[OFFBOARDLINK_FRAME_HEAD_LEN + 2] = (uint16_t)(remaining_time) >> 8;

			buf[OFFBOARDLINK_FRAME_HEAD_LEN + 3] = self_color;

			buf[OFFBOARDLINK_FRAME_HEAD_LEN + 4] = self_health;
            buf[OFFBOARDLINK_FRAME_HEAD_LEN + 5] = (uint16_t)(self_health) >> 8;

			buf[OFFBOARDLINK_FRAME_HEAD_LEN + 6] = (bullet_speed_meas * 655.2);
            buf[OFFBOARDLINK_FRAME_HEAD_LEN + 7] = (uint16_t)((bullet_speed_meas * 655.2)) >> 8;

			buf[OFFBOARDLINK_FRAME_HEAD_LEN + 8] = shoot_heat;
            buf[OFFBOARDLINK_FRAME_HEAD_LEN + 9] = (uint16_t)(shoot_heat) >> 8;

			buf[OFFBOARDLINK_FRAME_HEAD_LEN + 10] = hurt_by_gimbal;

			buf[OFFBOARDLINK_FRAME_HEAD_LEN + 11] = remaining_bullet;
            buf[OFFBOARDLINK_FRAME_HEAD_LEN + 12] = (uint16_t)(remaining_bullet) >> 8;

			buf[OFFBOARDLINK_FRAME_HEAD_LEN + 13] = who_is_balance;

        }
    };
}
        