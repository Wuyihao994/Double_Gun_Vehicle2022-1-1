#include "mecanum.h"
#include "can.h"
#include "arm_math.h"
#include "dbus.h"

#define ANGLE_TO_RADDINS 57.2957795F

chassis_typedef chassis_speed_resolution;

uint16_t count=0;
/*�����ٶȿ���*/
void chassis_dbus_control(void)
{
	if((-moto_gimbal_info[0].moto_angle+default_yaw)>=0&&(-moto_gimbal_info[0].moto_angle+default_yaw)<=180)
	{
		chassis_speed_resolution.relative_angle = (moto_gimbal_info[0].moto_angle-default_yaw)/ANGLE_TO_RADDINS;
	}
	else if((-moto_gimbal_info[0].moto_angle+default_yaw)>180)
	{
		chassis_speed_resolution.relative_angle = (360+moto_gimbal_info[0].moto_angle-default_yaw)/ANGLE_TO_RADDINS;
	}
	/*�����ٶȿ���*/
	chassis_speed_resolution.vx_headless=dbus_infomation.speed_vx*MAX_CHASSIS_VX_SPEED;
	chassis_speed_resolution.vy_headless=dbus_infomation.speed_vy*MAX_CHASSIS_VY_SPEED;
//	if(dbus_infomation.chassis_mode==gyro_mode)
//	{
		chassis_speed_resolution.wz_headless=dbus_infomation.speed_wz*MAX_CHASSIS_WZ_SPEED;
//	}
//	else if(dbus_infomation.chassis_mode==back_middle_mode) 
//	{
//		if(chassis_speed_resolution.relative_angle>=0)
//		{
//			chassis_speed_resolution.wz_headless=-chassis_angle_pid.OUT;
//		}
//		else if(chassis_speed_resolution.relative_angle<0)
//		{
//			chassis_speed_resolution.wz_headless=chassis_angle_pid.OUT;
//		}
//	}
//	else if(dbus_infomation.chassis_mode==stop_mode)
//	{
//		chassis_speed_resolution.wz_headless=0;
//	}
	/*����ģʽ�л�����ͬģʽ�ٶȷֽ�*/
		chassis_speed_resolution.vx_set=chassis_speed_resolution.vy_headless*sin(chassis_speed_resolution.relative_angle)
																	 +chassis_speed_resolution.vx_headless*cos(chassis_speed_resolution.relative_angle);
		chassis_speed_resolution.vy_set=chassis_speed_resolution.vy_headless*cos(chassis_speed_resolution.relative_angle)
																	 -chassis_speed_resolution.vx_headless*sin(chassis_speed_resolution.relative_angle);
		chassis_speed_resolution.wz_set=chassis_speed_resolution.wz_headless;
}
/*�����ٶ�ת�������ٶ�*/
void chassis_speed_resolve(void)
{
	chassis_speed_resolution.chassis_wheel_speed[0] =
	chassis_speed_resolution.vy_set + chassis_speed_resolution.vx_set +  (-CHASSIS_WZ_SET_SCALE - 1.0f) * MOTOR_DISTANCE_TO_CENTER * chassis_speed_resolution.wz_set;
	chassis_speed_resolution.chassis_wheel_speed[1] =
	- chassis_speed_resolution.vy_set + chassis_speed_resolution.vx_set +  (-CHASSIS_WZ_SET_SCALE - 1.0f) * MOTOR_DISTANCE_TO_CENTER * chassis_speed_resolution.wz_set;
	chassis_speed_resolution.chassis_wheel_speed[2] =
	- chassis_speed_resolution.vy_set - chassis_speed_resolution.vx_set +  (CHASSIS_WZ_SET_SCALE - 1.0f) * MOTOR_DISTANCE_TO_CENTER * chassis_speed_resolution.wz_set;
	chassis_speed_resolution.chassis_wheel_speed[3] =
	chassis_speed_resolution.vy_set - chassis_speed_resolution.vx_set +  (CHASSIS_WZ_SET_SCALE - 1.0f) * MOTOR_DISTANCE_TO_CENTER * chassis_speed_resolution.wz_set;
}
