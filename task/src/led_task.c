#include "led_task.h"
#include "led.h"

void led_blue_task(void *pvParameters)
{
	while(1)
	{
		led_blue_off();
		vTaskDelay(500);
		led_blue_on();
		vTaskDelay(500);
	}
}

void led_red_task(void *pvParameters)
{
	while(1)
	{
		led_red_off();
		vTaskDelay(500);
		led_red_on();
		vTaskDelay(500);
	}
}

void led_green_task(void *pvParameters)
{
	while(1)
	{
		led_green_off();
		vTaskDelay(500);
		led_green_on();
		vTaskDelay(500);
	}
}

