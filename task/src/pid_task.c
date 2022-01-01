#include "pid_task.h"
#include "can.h"
#include "tim.h"

#include "mecanum.h"
#include "dbus.h"
#include "init.h"

#define PID_CHASSIS_CACULATE_PERIOD 5
#define PID_GIMBAL_CACULATE_PERIOD 5
#define PID_SHOOT_CACULATE_PERIOD 5

pid_typedef chassis_current_pid[4];
pid_typedef chassis_speed_pid[4];
pid_typedef gimbal_speed_pid[2];
pid_typedef gimbal_angle_pid[2];
pid_typedef revolver_angle_pid;
pid_typedef revolver_speed_pid;

first_order_filter_type_t chassis_set_filter[4];

void pid_chassis_caculate_task(void *pvParameters)
{
	int i;
	int16_t chassis_current_set[4];
	
	TickType_t PreviousWakeTime;
	TickType_t mxTimeIncrement=pdMS_TO_TICKS(PID_CHASSIS_CACULATE_PERIOD);
	PreviousWakeTime = xTaskGetTickCount();
	
	while(1)
	{
		chassis_dbus_control();
		chassis_speed_resolve();
		for(i=0;i<4;i++)
		{
			first_order_filter_cali(&chassis_set_filter[i],chassis_speed_resolution.chassis_wheel_speed[i]);
			
			pid_caculate_position(&chassis_speed_pid[i],chassis_set_filter[i].out,moto_chassis_info[i].moto_speed);
			
			pid_caculate_position(&chassis_current_pid[i],chassis_speed_pid[i].out,moto_chassis_info[i].moto_current);
			
			chassis_current_set[i]=chassis_current_pid[i].out;
		}
		
		can_mes_send(CAN1,CAN_TX_MOTO3508_1_4,chassis_current_set);
		
		vTaskDelayUntil(&PreviousWakeTime,mxTimeIncrement);
	}
}

float gimbal_angle_set[2];
float gimbal_yaw_free_set;
float gimbal_yaw_gyro_set;

void pid_gimbal_caculate_task(void *pvParameters)
{
	int16_t gimbal_voltage_set[4];
	float revolver_angle_set;
	int s2_gear_up=1;
	
	TickType_t PreviousWakeTime;
	TickType_t mxTimeIncrement=pdMS_TO_TICKS(PID_CHASSIS_CACULATE_PERIOD);
	PreviousWakeTime = xTaskGetTickCount();
	
	gimbal_init();
	
	while(1)
	{
		gimbal_limit(138,72);
		/**/
		if(dbus_infomation.gimbal_mode != gyro_mode)
		{
			gimbal_angle_set[0] += 0.1*dbus_infomation.gimbal_yaw;
			gimbal_yaw_gyro_set = bmi088_infomation.yaw;
		}
		else
		{
			gimbal_yaw_gyro_set += 0.08*dbus_infomation.gimbal_yaw;
			gimbal_angle_set[0] = moto_gimbal_info[0].moto_total_angle;
		}

		pid_gimbal_yaw_change_init();
		
		if(dbus_infomation.gimbal_mode == gyro_mode)
		{			
				pid_caculate_delta(&gimbal_angle_pid[0],gimbal_yaw_gyro_set,bmi088_infomation.yaw);
				pid_caculate_delta(&gimbal_speed_pid[0],gimbal_angle_pid[0].out,15*bmi088_infomation.z);
			
				gimbal_voltage_set[0] = gimbal_speed_pid[0].out;
		}
		else if(dbus_infomation.gimbal_mode == free_mode)
		{	
				pid_caculate_delta(&gimbal_angle_pid[0],gimbal_angle_set[0],moto_gimbal_info[0].moto_total_angle);
				pid_caculate_delta(&gimbal_speed_pid[0],gimbal_angle_pid[0].out,moto_gimbal_info[0].moto_speed);
			
				gimbal_voltage_set[0] = gimbal_speed_pid[0].out;
		}
		else if(dbus_infomation.gimbal_mode == visual_mode)
		{	
				pid_caculate_delta(&gimbal_angle_pid[0],gimbal_angle_set[0],moto_gimbal_info[0].moto_total_angle);
				pid_caculate_delta(&gimbal_speed_pid[0],gimbal_angle_pid[0].out,moto_gimbal_info[0].moto_speed);
			
				gimbal_voltage_set[0] = gimbal_speed_pid[0].out;
		}
		/**/
		gimbal_angle_set[1] += dbus_infomation.gimbal_pitch;
		
		pid_caculate_delta(&gimbal_angle_pid[1],gimbal_angle_set[1],moto_gimbal_info[1].moto_total_angle);
		pid_caculate_delta(&gimbal_speed_pid[1],gimbal_angle_pid[1].out,moto_gimbal_info[1].moto_speed);
		
		gimbal_voltage_set[1] = gimbal_speed_pid[1].out;
		/**/
		if(dbus_infomation.cover_state == cover_close_sign)
		{
			set_servo_pwm(1350);
		}
		else if(dbus_infomation.cover_state == cover_open_sign)
		{
			set_servo_pwm(520);
		}
		
//		if(dbus_infomation.friction_state == friction_start_sign)
//		{
//			set_friction_pwm(1350);
//		}
//		else if(dbus_infomation.friction_state == friction_stop_sign)
//		{
//			set_friction_pwm(1000);
//		}
			
		if(dbus_infomation.revolver_state == revolver_start_sign)
		{
			revolver_angle_set += 50;
		}
		else if(dbus_infomation.revolver_state == revolver_stop_sign)
		{
			revolver_angle_set += 0;
		}
		
//		if((dbus_infomation.revolver_state == revolver_start_sign)&&s2_gear_up)
//		{
//			revolver_angle_set += 1280;
//			s2_gear_up = 0;
//		}
//		else if(dbus_infomation.revolver_state == revolver_stop_sign)
//		{
//			revolver_angle_set += 0;
//			s2_gear_up = 1;
//		}
		
		pid_caculate_delta(&revolver_angle_pid,revolver_angle_set,moto_revolver_info.moto_total_angle);
		pid_caculate_delta(&revolver_speed_pid,revolver_angle_pid.out,moto_revolver_info.moto_speed);
			
		gimbal_voltage_set[2] = revolver_speed_pid.out;
		/**/	
		can_mes_send(CAN1,CAN_TX_MOTO6020_1_4,gimbal_voltage_set);
		
		vTaskDelayUntil(&PreviousWakeTime,mxTimeIncrement);
	}
}

void gimbal_init(void)
{
	int i;
	for(i=0;i<2;i++)
	{
		gimbal_angle_set[i] = moto_gimbal_info[i].moto_total_angle;
	}
}

void gimbal_limit(float max_set,float min_set)
{
	if(gimbal_angle_set[1]>=max_set)
	{
		gimbal_angle_set[1]=max_set;
	}
	else if(gimbal_angle_set[1]<=min_set)
	{
		gimbal_angle_set[1]=min_set;
	}
}


uint8_t gyro_off=1;
uint8_t free_off=1;
uint8_t visual_off=1;
void pid_gimbal_yaw_change_init(void)
{
	if((dbus_infomation.gimbal_mode == gyro_mode)&&gyro_off)
			{
					pid_gimbal_yaw_gyro_init();
					gyro_off=0;
			}
	else if(dbus_infomation.gimbal_mode != gyro_mode)
			{
					gyro_off=1;
			}
			
	if((dbus_infomation.gimbal_mode == free_mode)&&free_off)
			{
					pid_gimbal_yaw_free_init();
					free_off=0;
			}
	else if(dbus_infomation.gimbal_mode != free_mode)
			{
					free_off=1;
			}
	
	if((dbus_infomation.gimbal_mode == visual_mode)&&visual_off)
			{
					pid_gimbal_yaw_free_init();
					visual_off=0;
			}
	else if(dbus_infomation.gimbal_mode != visual_mode)
			{
					visual_off=1;
			}
}

void pid_shoot_caculate_task(void *pvParameters)
{
	TickType_t PreviousWakeTime;
	TickType_t mxTimeIncrement=pdMS_TO_TICKS(PID_SHOOT_CACULATE_PERIOD);
	PreviousWakeTime = xTaskGetTickCount();
	
	int i;
	int16_t shoot_current_set[4];
	float shoot_speed_set[2];
	float revolver_angle_set;
	
	{
		while(1)
		{
//			if(dbus_infomation.cover_state == cover_close_sign)
//			{
//				set_servo_pwm(1350);
//			}
//			else if(dbus_infomation.cover_state == cover_open_sign)
//			{
//				set_servo_pwm(520);
//			}
//			if(dbus_infomation.friction_state == friction_start_sign)
//			{
//				shoot_speed_set[0] = -14000;
//				shoot_speed_set[1] = 14000;
//			}
//			else if(dbus_infomation.friction_state == friction_stop_sign)
//			{
//				shoot_speed_set[0] = 0;
//				shoot_speed_set[1] = 0;
//			}
//			if(dbus_infomation.revolver_state == revolver_start_sign)
//			{
//				revolver_angle_set -= 100;
//			}
//			else if(dbus_infomation.revolver_state == revolver_stop_sign)
//			{
//				revolver_angle_set -= 0;
//			}
////			
////			for(i=0;i<2;i++)
////			{
////				pid_caculate_delta(&friction_speed_pid[i],shoot_speed_set[i],moto_friction_info[i].moto_speed);
////				pid_caculate_delta(&friction_current_pid[i],friction_speed_pid[i].out,moto_friction_info[i].moto_current);
////				shoot_current_set[i]=friction_current_pid[i].out;
////			}

//			pid_caculate_delta(&revolver_angle_pid,revolver_angle_set,moto_revolver_info.moto_total_angle);
//			pid_caculate_delta(&revolver_speed_pid,revolver_angle_pid.out,moto_revolver_info.moto_speed);
//		
//			shoot_current_set[2]=revolver_speed_pid.out;
//		
//			can_mes_send(CAN1,CAN_TX_MOTO6020_1_4,shoot_current_set);
			
			vTaskDelayUntil(&PreviousWakeTime,mxTimeIncrement);
		}
	}
}
