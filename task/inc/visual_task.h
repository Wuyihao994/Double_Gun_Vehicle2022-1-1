#ifndef __VISUAL_TASK_H
#define __VISUAL_TASK_H

#include "FreeRTOS.h"
#include "task.h"

void visual_task(void *pvParameters);
void usart1_send(uint8_t *data,uint16_t len);

#endif
