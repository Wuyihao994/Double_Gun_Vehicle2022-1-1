#include "dbus.h"

RC_Ctrl_t RC_CtrlData;
dbus_info_typedef dbus_infomation;

void dbus_data_process(uint8_t *pData)
{
	RC_CtrlData.rc.ch0=(pData[0] | pData[1] << 8)&0x07FF;
	RC_CtrlData.rc.ch0 -=1024;
	RC_CtrlData.rc.ch1=(pData[1] >> 3 | pData[2] << 5)&0x07FF;
	RC_CtrlData.rc.ch1 -=1024;
	RC_CtrlData.rc.ch2=(pData[2] >> 6 | pData[3] << 2 | pData[4] << 10)&0x07FF;
	RC_CtrlData.rc.ch2 -=1024;	
	RC_CtrlData.rc.ch3=(pData[4] >> 1 | pData[5] << 7)&0x07FF;
	RC_CtrlData.rc.ch3 -=1024;
	RC_CtrlData.rc.s1=((pData[5] >> 4)&0x000C) >> 2;
	RC_CtrlData.rc.s2=((pData[5] >> 4)&0x0003);
	
	RC_CtrlData.mouse.x=(pData[6] | pData[7] << 8);
	RC_CtrlData.mouse.y=(pData[8] | pData[9] << 8);
	RC_CtrlData.mouse.z=(pData[10] | pData[11] << 8);
	RC_CtrlData.mouse.press_l=pData[12];
	RC_CtrlData.mouse.press_r=pData[13];
	
	RC_CtrlData.keyboard.key_code= pData[14]| (pData[15] << 8) ;
	RC_CtrlData.wheel = (pData[16] | pData[17] << 8) - 1024;
}

void dbus_control(void)
{
	/*µ×ÅÌËÙ¶È·Ö½âÒ£¿ØÆ÷¿ØÖÆ*/
	dbus_infomation.speed_vx=0.8*RC_CtrlData.rc.ch1/DBUS_RESOLUTION;
	dbus_infomation.speed_vy=0.8*(RC_CtrlData.rc.ch0)/DBUS_RESOLUTION;
//	dbus_infomation.speed_wz=-0.8f;
	dbus_infomation.speed_wz=-0.8*(RC_CtrlData.rc.ch2)/DBUS_RESOLUTION;
	/*ÔÆÌ¨½Ç¶ÈÒ£¿ØÆ÷¿ØÖÆ*/
	dbus_infomation.gimbal_yaw=RC_CtrlData.wheel*24/DBUS_RESOLUTION;
	dbus_infomation.gimbal_pitch=-RC_CtrlData.rc.ch3*24/DBUS_RESOLUTION;
	/*ÔË¶¯Ä£Ê½Ò£¿ØÆ÷Ñ¡Ôñ*/
	if(RC_CtrlData.rc.s1==1)
	{
		dbus_infomation.gimbal_mode=gyro_mode;
		dbus_infomation.chassis_mode=rotate_mode;
	}
	else if(RC_CtrlData.rc.s1==3)
	{
		dbus_infomation.gimbal_mode=free_mode;
		dbus_infomation.chassis_mode=back_middle_mode;
	}
	else if(RC_CtrlData.rc.s1==2)
	{
		dbus_infomation.gimbal_mode=visual_mode;
		dbus_infomation.chassis_mode=back_middle_mode;
	}
	/*·¢Éä×´Ì¬Ò£¿ØÆ÷Ñ¡Ôñ*/
	if(RC_CtrlData.rc.s2==1)
	{
		dbus_infomation.friction_state = friction_start_sign;
		dbus_infomation.revolver_state = revolver_start_sign;
		dbus_infomation.cover_state = cover_close_sign;
	}
	else if(RC_CtrlData.rc.s2==3)
	{
		dbus_infomation.friction_state = friction_start_sign;
		dbus_infomation.revolver_state = revolver_stop_sign;
		dbus_infomation.cover_state = cover_close_sign;
	}
	else if(RC_CtrlData.rc.s2==2)
	{
		dbus_infomation.friction_state = friction_stop_sign;
		dbus_infomation.revolver_state = revolver_stop_sign;
		dbus_infomation.cover_state = cover_open_sign;
	}
}
