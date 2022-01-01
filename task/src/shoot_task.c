#include "shoot_task.h"
#include "dbus.h"
#include "delay.h"


/*friction init*/
void shoot_init(void)
{
	TIM_SetCompare1(TIM4,1000);
	TIM_SetCompare2(TIM4,1000);
	TIM_SetCompare3(TIM4,1000);
	TIM_SetCompare4(TIM4,1000);
	delay_ms(3500);
}

void shoot_task(void *pvParameters)
{
	while(1)
	{
		if(		dbus_infomation.friction_state == friction_start_sign)
	  {
			TIM_SetCompare1(TIM8,1150);
			TIM_SetCompare2(TIM8,1150);
			TIM_SetCompare3(TIM8,1150);
			TIM_SetCompare4(TIM8,1150);
	  }
		else if(dbus_infomation.friction_state == friction_stop_sign)
		{
			TIM_SetCompare1(TIM8,1000);
			TIM_SetCompare2(TIM8,1000);
			TIM_SetCompare3(TIM8,1000);
			TIM_SetCompare4(TIM8,1000);
		}		
	}
}



