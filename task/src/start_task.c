#include "start_task.h"
#include "FreeRTOS.h"
#include "task.h"
#include "delay.h"

#include "pid_task.h"
#include "shoot_task.h"
#include "dbus_task.h"
#include "visual_task.h"

#define START_TASK_PRIO 1
#define START_TASK_STK_SIZE 128
TaskHandle_t Start_Task_Handler;

#define PID_CHASSIS_CACULATE_TASK_PRIO 2
#define PID_CHASSIS_CACULATE_TASK_STK_SIZE 256
TaskHandle_t Pid_Chassis_Caculate_Task_Handler;

#define PID_GIMBAL_CACULATE_TASK_PRIO 3
#define PID_GIMBAL_CACULATE_TASK_STK_SIZE 512
TaskHandle_t Pid_Gimbal_Caculate_Task_Handler;

#define SHOOT_TASK_PRIO 4
#define SHOOT_TASK_STK_SIZE 256
TaskHandle_t Shoot_Task_Handler;

#define DBUS_TASK_PRIO 5
#define DBUS_TASK_STK_SIZE 256
TaskHandle_t Dbus_Task_Handler;

#define VISUAL_TASK_PRIO 6
#define VISUAL_TASK_STK_SIZE 256
TaskHandle_t Visual_Task_Handler;

void create_start_task(void)
{
			xTaskCreate((TaskFunction_t)start_task,
                (char*         )"start_task",
                (uint16_t      )START_TASK_STK_SIZE,
                (void *        )NULL,
                (UBaseType_t   )START_TASK_PRIO,
                (TaskHandle_t*)&Start_Task_Handler);
}

void start_task(void *pvParameters)
{
	taskENTER_CRITICAL();//进入临界区		
						
	xTaskCreate((TaskFunction_t)pid_chassis_caculate_task,
                (char*         )"pid_chassis_caculate_task",
                (uint16_t      )PID_CHASSIS_CACULATE_TASK_STK_SIZE,
                (void *        )NULL,
                (UBaseType_t   )PID_CHASSIS_CACULATE_TASK_PRIO,
                (TaskHandle_t*)&Pid_Chassis_Caculate_Task_Handler);
								
	xTaskCreate((TaskFunction_t)pid_gimbal_caculate_task,
                (char*         )"pid_gimbal_caculate_task",
                (uint16_t      )PID_GIMBAL_CACULATE_TASK_STK_SIZE,
                (void *        )NULL,
                (UBaseType_t   )PID_GIMBAL_CACULATE_TASK_PRIO,
                (TaskHandle_t*)&Pid_Gimbal_Caculate_Task_Handler);
								
	xTaskCreate((TaskFunction_t)shoot_task,
                (char*         )"shoot_task",
                (uint16_t      )SHOOT_TASK_STK_SIZE,
                (void *        )NULL,
                (UBaseType_t   )SHOOT_TASK_PRIO,
                (TaskHandle_t*)&Shoot_Task_Handler);
								
	xTaskCreate((TaskFunction_t)dbus_task,
                (char*         )"dbus_task",
                (uint16_t      )DBUS_TASK_STK_SIZE,
                (void *        )NULL,
                (UBaseType_t   )DBUS_TASK_PRIO,
                (TaskHandle_t*)&Dbus_Task_Handler);
								
	
	vTaskDelete(Start_Task_Handler);//删除开始任务
	taskEXIT_CRITICAL();//退出临界区
}
