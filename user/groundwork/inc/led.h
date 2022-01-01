#ifndef __LED_H
#define __LED_H

#include "stm32f4xx_conf.h"

void led_blue_init(void);
void led_red_init(void);
void led_green_init(void);
void laser_init(void);

void led_blue_on(void);
void led_blue_off(void);
void led_blue_toggle(void);

void led_red_on(void);
void led_red_off(void);
void led_red_toggle(void);

void led_green_on(void);
void led_green_off(void);
void led_green_toggle(void);

void laser_on(void);
void laser_off(void);

#endif
