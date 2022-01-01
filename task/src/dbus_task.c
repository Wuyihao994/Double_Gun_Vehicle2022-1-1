#include "dbus_task.h"

#include "dbus_task.h"
#include "dbus.h"

#define DBUS_PERIOD 5

void dbus_task(void *pvParameters)
{
	TickType_t PreviousWakeTime;
	TickType_t mxTimeIncrement=pdMS_TO_TICKS(DBUS_PERIOD);
	PreviousWakeTime = xTaskGetTickCount();
	while(1)
	{
		/*键鼠遥控模式切换*/
		if((RC_CtrlData.keyboard.key_code!=0)|
		(RC_CtrlData.mouse.x!=0)|
		(RC_CtrlData.mouse.y!=0)|
		(RC_CtrlData.mouse.z!=0)|
		(RC_CtrlData.mouse.press_l!=0)|
		(RC_CtrlData.mouse.press_r!=0)
		)
		{
			RC_CtrlData.dbus_mode = Dbus_Key;
		}
		if((RC_CtrlData.keyboard.key_code&KEY_PRESSED_OFFSET_B)!=0)
		{
			RC_CtrlData.dbus_mode = Dbus_NoKey;
		}//默认遥控模式，键鼠数据不为零切换键鼠模式，按下B键切换遥控模式
		/*控制模式条件判断*/
//		if(RC_CtrlData.dbus_mode==Dbus_Key)
//		{
//			speed_control_init();//函数功能是为了防止速度量改变后不清零
//			keyboard_mouse_control();
//		}
//		else if(RC_CtrlData.dbus_mode==Dbus_NoKey)
//		{
			dbus_control();
//		}
		vTaskDelayUntil(&PreviousWakeTime,mxTimeIncrement);
	}
}

