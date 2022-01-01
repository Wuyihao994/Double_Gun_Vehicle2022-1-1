#ifndef __MECANUM_H
#define __MECANUM_H

#include "stm32f4xx.h"

#define CHASSIS_WZ_SET_SCALE 0.0f
#define MOTOR_DISTANCE_TO_CENTER 1.0f

#define MAX_CHASSIS_VX_SPEED 10000   // ����ǰ������ٶ� 3300mm/s = 8000rpm
#define MAX_CHASSIS_VY_SPEED 10000   // ������������ٶ� 3300mm/s = 8000rpm
#define MAX_CHASSIS_WZ_SPEED 6000    // ������ת����ٶ� 300rad/s = 5000rpm

typedef struct{
	
	float vx_headless;
  float vy_headless;
  float wz_headless;
  float relative_angle;//��ԽǶ�--��Χ������λ��
	
	float vx_set;       //�����趨�ٶ� ǰ���� ǰΪ������λm/s
  float vy_set;       //�����趨�ٶ� ���ҷ��� ��Ϊ������λm/s
  float wz_set;       //�����趨��ת���ٶ� ��ʱ��Ϊ������λrad/s
	float relative_yaw_angle_set;    // �����������̨���趨�Ƕ�
  float offset_degree;  //����ת����ǰ�Ƕ�
	
	int16_t chassis_wheel_speed[4];
}chassis_typedef;

extern chassis_typedef chassis_speed_resolution;
extern uint16_t count;

void chassis_dbus_control(void);
void chassis_speed_resolve(void);

#endif
