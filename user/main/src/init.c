#include "init.h"
#include "delay.h"

/*板级底层初始化*/
void bsp_init(void)
{
	usart1_init();
	can1_init();
	can2_init();
	tim5_init();
	tim8_init();
	power_init();
	shoot_init();
}
/*模式初始化*/
void mode_init(void)
{
	RC_CtrlData.dbus_mode=Dbus_NoKey;//初始控制模式为遥控控制
	dbus_infomation.gimbal_mode=free_mode;//初始云台运动模式为自由模式
	dbus_infomation.chassis_mode=back_middle_mode;//初始底盘运动模式为回中模式
	dbus_infomation.gyro_state=left;//小陀螺运动向左
	dbus_infomation.gimbal_sensitivity=1000.0;//云台灵敏度
}
/*外设初始化*/
void moudles_init(void)
{
}
/*滤波初始化*/
void filter_init(void)
{
	int i;
	/*底盘设定值一阶低通滤波初始化*/
	for(i=0;i<4;i++)
		{
			first_order_filter_init(&chassis_set_filter[i],1,45);
		}	
}
/*PID参数初始化*/
void pid_parameter_init(void)
{
	pid_chassis_init();
	pid_gimbal_yaw_free_init();
	pid_gimbal_pitch_free_init();
	pid_revolver_init();
}
/*底盘PID参数初始化*/
void pid_chassis_init(void)
{
	int i;
	for(i=0;i<4;i++)
		{
			pid_init(&chassis_speed_pid[i],20,5,5,10000,5000);
			pid_init(&chassis_current_pid[i],0.7,0.1,0,15000,8000);
		}
}
/*云台YAW自由模式PID参数初始化*/
void pid_gimbal_yaw_free_init(void)
{
	pid_init(&gimbal_angle_pid[0],3,0,0,1000,50);
	pid_init(&gimbal_speed_pid[0],520,0,0,27000,10000);
}
/*云台YAW陀螺模式PID参数初始化*/
void pid_gimbal_yaw_gyro_init(void)
{
	pid_init(&gimbal_angle_pid[0],2.3,0,0,1000,50);
	pid_init(&gimbal_speed_pid[0],250,0,0,20000,10000);
}
/*云台PITCH自由模式PID参数初始化*/
void pid_gimbal_pitch_free_init(void)
{
	pid_init(&gimbal_angle_pid[1],2,0.0,0,1000,50);
	pid_init(&gimbal_speed_pid[1],150,0,0,27000,10000);
}

void pid_revolver_init(void)
{
	pid_init(&revolver_angle_pid,7,0.4,0,10000,8000);
	pid_init(&revolver_speed_pid,10,0.7,5,10000,8000);
}
/*friction init*/
//void shoot_init(void)
//{
//	TIM_SetCompare1(TIM4,1000);
//	TIM_SetCompare2(TIM4,1000);
//	TIM_SetCompare3(TIM4,1000);
//	TIM_SetCompare4(TIM4,1000);
//	delay_ms(3500);
//}
