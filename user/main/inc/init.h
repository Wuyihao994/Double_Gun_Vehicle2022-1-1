#ifndef __INIT_H
#define __INIT_H

#include "usart.h"
#include "can.h"
#include "dbus.h"
#include "tim.h"

#include "pid.h"
#include "filter.h"

#include "pid_task.h"

void bsp_init(void);
void mode_init(void);
void moudles_init(void);
void filter_init(void);
void pid_parameter_init(void);
void pid_chassis_init(void);
void pid_gimbal_yaw_free_init(void);
void pid_gimbal_yaw_gyro_init(void);
void pid_gimbal_pitch_free_init(void);
void pid_revolver_init(void);
void shoot_init(void);


#endif
