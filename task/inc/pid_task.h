#ifndef __PID_TASK_H
#define __PID_TASK_H

#include "FreeRTOS.h"
#include "task.h"
#include "pid.h"
#include "filter.h"
#include "mecanum.h"

extern pid_typedef chassis_current_pid[4];
extern pid_typedef chassis_speed_pid[4];
extern pid_typedef gimbal_speed_pid[2];
extern pid_typedef gimbal_angle_pid[2];
extern pid_typedef revolver_angle_pid;
extern pid_typedef revolver_speed_pid;

extern first_order_filter_type_t chassis_set_filter[4];

void pid_chassis_caculate_task(void *pvParameters);
void pid_gimbal_caculate_task(void *pvParameters);
void pid_shoot_caculate_task(void *pvParameters);

void gimbal_init(void);
void gimbal_limit(float max_set,float min_set);
void pid_gimbal_yaw_change_init(void);

#endif
