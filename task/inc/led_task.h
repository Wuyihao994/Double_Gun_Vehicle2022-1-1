#ifndef __LED_TASK_H
#define __LED_TASK_H

#include "FreeRTOS.h"
#include "task.h"

void led_blue_task(void *pvParameters);
void led_red_task(void *pvParameters);
void led_green_task(void *pvParameters);


#endif
