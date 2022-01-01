#ifndef __DBUS_H
#define __DBUS_H

#include "stm32f4xx_conf.h"

/* ----------------------- RC Channel Definition---------------------------- */
#define RC_CH_VALUE_MIN ((uint16_t)364 )
#define RC_CH_VALUE_OFFSET ((uint16_t)1024)
#define RC_CH_VALUE_MAX ((uint16_t)1684)
/* ----------------------- RC Switch Definition----------------------------- */
#define RC_SW_UP ((uint16_t)1)
#define RC_SW_MID ((uint16_t)3)
#define RC_SW_DOWN ((uint16_t)2)
/* ----------------------- PC Key Definition-------------------------------- */
#define KEY_PRESSED_OFFSET_W ((uint16_t)0x01<<0)
#define KEY_PRESSED_OFFSET_S ((uint16_t)0x01<<1)
#define KEY_PRESSED_OFFSET_A ((uint16_t)0x01<<2)
#define KEY_PRESSED_OFFSET_D ((uint16_t)0x01<<3)
#define KEY_PRESSED_OFFSET_SHIFT ((uint16_t)0x01<<4)
#define KEY_PRESSED_OFFSET_Ctrl ((uint16_t)0x01<<5)
#define KEY_PRESSED_OFFSET_Q ((uint16_t)0x01<<6)
#define KEY_PRESSED_OFFSET_E ((uint16_t)0x01<<7)
#define KEY_PRESSED_OFFSET_R ((uint16_t)1 << 8)
#define KEY_PRESSED_OFFSET_F ((uint16_t)1 << 9)
#define KEY_PRESSED_OFFSET_G ((uint16_t)1 << 10)
#define KEY_PRESSED_OFFSET_Z ((uint16_t)1 << 11)
#define KEY_PRESSED_OFFSET_X ((uint16_t)1 << 12)
#define KEY_PRESSED_OFFSET_C ((uint16_t)1 << 13)
#define KEY_PRESSED_OFFSET_V ((uint16_t)1 << 14)
#define KEY_PRESSED_OFFSET_B ((uint16_t)1 << 15)

#define DBUS_RESOLUTION 660.0f

typedef __packed struct
{
	__packed struct
	{
		int16_t ch0;
		int16_t ch1;
		int16_t ch2;
		int16_t ch3;
		uint8_t s1;
		uint8_t s2;
	}rc;
	__packed struct
	{
		int16_t x;
		int16_t y;
		int16_t z;
		uint8_t press_l;
		uint8_t press_r;
	}mouse;
	__packed struct
	{
		uint16_t key_code;
	}keyboard;
	
	enum{
		Dbus_NoKey,
    Dbus_Key,
	}dbus_mode;
	
  int16_t wheel;
}RC_Ctrl_t;

typedef struct{
	enum{
		friction_stop_sign ,				//Ä¦²ÁÂÖ¿ªÆô
		friction_start_sign,				//Ä¦²ÁÂÖ¹Ø±Õ
	}friction_state;							//Ä¦²ÁÂÖ×´Ì¬

	enum{
		revolver_stop_sign ,				//²¦ÅÌ¿ªÆô
		revolver_start_sign,				//²¦ÅÌ¹Ø±Õ
	}revolver_state;							//²¦ÅÌ×´Ì¬
	
	enum{
		cover_close_sign ,				//²¦ÅÌ¿ªÆô
		cover_open_sign,				//²¦ÅÌ¹Ø±Õ
	}cover_state;							//²¦ÅÌ×´Ì¬
	
	enum{
		left,
		right,
	}gyro_state;
	
	enum{
		free_mode,
		visual_mode,
		gyro_mode,
	}gimbal_mode;
	
	enum{
		rotate_mode,
		back_middle_mode,
	}chassis_mode;
	
	float gimbal_yaw;
	float gimbal_pitch;
	float gimbal_sensitivity;
	
	float speed_vx;
	float speed_vy;
	float speed_wz;
	float speed_gear;//ËÙ¶ÈµµÎ»
}dbus_info_typedef;

extern dbus_info_typedef dbus_infomation;
extern RC_Ctrl_t RC_CtrlData;

void dbus_data_process(uint8_t *pData);
void dbus_control(void);

#endif
