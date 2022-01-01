#include "FreeRTOS.h"
#include "task.h"
#include "sys.h"
#include "delay.h"
#include "arm_math.h"

#include "start_task.h"
#include "init.h"
//	系统时钟 = HSE(12MHz)*N(180)/(M(6)*P(4)) = 180MHz
//	ClocksTypeDef.SYSCLK_Frequency = 180000000
//	ClocksTypeDef.HCLK_Frequency = 180000000
//	ClocksTypeDef.PCLK1_Frequency = 45000000
//	ClocksTypeDef.PCLK2_Frequency = 90000000
//	APB1 45M
//	APB2 90M
//	PLL_Q = 8
RCC_ClocksTypeDef RCC_Clocks;
int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//设置系统中断优先级分组4
    delay_init(180);//初始化延时函数
    RCC_GetClocksFreq(&RCC_Clocks);//验证工程时钟
	
		bsp_init();
	
		filter_init();
	
		pid_parameter_init();
	
		mode_init();
	
		delay_ms(1000);
	
		create_start_task();//创建开始任务	
		vTaskStartScheduler();//开启任务调度
    while(1){}
}





