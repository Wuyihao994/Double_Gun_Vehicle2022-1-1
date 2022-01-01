#ifndef __MECANUM_H
#define __MECANUM_H

#include "stm32f4xx.h"

#define CHASSIS_WZ_SET_SCALE 0.0f
#define MOTOR_DISTANCE_TO_CENTER 1.0f

#define MAX_CHASSIS_VX_SPEED 10000   // 底盘前后最大速度 3300mm/s = 8000rpm
#define MAX_CHASSIS_VY_SPEED 10000   // 底盘左右最大速度 3300mm/s = 8000rpm
#define MAX_CHASSIS_WZ_SPEED 6000    // 底盘旋转最大速度 300rad/s = 5000rpm

typedef struct{
	
	float vx_headless;
  float vy_headless;
  float wz_headless;
  float relative_angle;//相对角度--范围化，单位度
	
	float vx_set;       //底盘设定速度 前后方向 前为正，单位m/s
  float vy_set;       //底盘设定速度 左右方向 左为正，单位m/s
  float wz_set;       //底盘设定旋转角速度 逆时针为正，单位rad/s
	float relative_yaw_angle_set;    // 底盘相对于云台的设定角度
  float offset_degree;  //底盘转动超前角度
	
	int16_t chassis_wheel_speed[4];
}chassis_typedef;

extern chassis_typedef chassis_speed_resolution;
extern uint16_t count;

void chassis_dbus_control(void);
void chassis_speed_resolve(void);

#endif
