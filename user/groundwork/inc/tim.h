#ifndef __TIM_H
#define __TIM_H

#include "stm32f4xx_conf.h"

void tim5_init(void);
void tim8_init(void);

void set_servo_pwm(uint32_t pwm_set);
void set_friction_pwm(uint32_t pwm_set);

#endif
