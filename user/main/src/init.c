#include "init.h"
#include "delay.h"

/*�弶�ײ��ʼ��*/
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
/*ģʽ��ʼ��*/
void mode_init(void)
{
	RC_CtrlData.dbus_mode=Dbus_NoKey;//��ʼ����ģʽΪң�ؿ���
	dbus_infomation.gimbal_mode=free_mode;//��ʼ��̨�˶�ģʽΪ����ģʽ
	dbus_infomation.chassis_mode=back_middle_mode;//��ʼ�����˶�ģʽΪ����ģʽ
	dbus_infomation.gyro_state=left;//С�����˶�����
	dbus_infomation.gimbal_sensitivity=1000.0;//��̨������
}
/*�����ʼ��*/
void moudles_init(void)
{
}
/*�˲���ʼ��*/
void filter_init(void)
{
	int i;
	/*�����趨ֵһ�׵�ͨ�˲���ʼ��*/
	for(i=0;i<4;i++)
		{
			first_order_filter_init(&chassis_set_filter[i],1,45);
		}	
}
/*PID������ʼ��*/
void pid_parameter_init(void)
{
	pid_chassis_init();
	pid_gimbal_yaw_free_init();
	pid_gimbal_pitch_free_init();
	pid_revolver_init();
}
/*����PID������ʼ��*/
void pid_chassis_init(void)
{
	int i;
	for(i=0;i<4;i++)
		{
			pid_init(&chassis_speed_pid[i],20,5,5,10000,5000);
			pid_init(&chassis_current_pid[i],0.7,0.1,0,15000,8000);
		}
}
/*��̨YAW����ģʽPID������ʼ��*/
void pid_gimbal_yaw_free_init(void)
{
	pid_init(&gimbal_angle_pid[0],3,0,0,1000,50);
	pid_init(&gimbal_speed_pid[0],520,0,0,27000,10000);
}
/*��̨YAW����ģʽPID������ʼ��*/
void pid_gimbal_yaw_gyro_init(void)
{
	pid_init(&gimbal_angle_pid[0],2.3,0,0,1000,50);
	pid_init(&gimbal_speed_pid[0],250,0,0,20000,10000);
}
/*��̨PITCH����ģʽPID������ʼ��*/
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
