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
		/*����ң��ģʽ�л�*/
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
		}//Ĭ��ң��ģʽ���������ݲ�Ϊ���л�����ģʽ������B���л�ң��ģʽ
		/*����ģʽ�����ж�*/
//		if(RC_CtrlData.dbus_mode==Dbus_Key)
//		{
//			speed_control_init();//����������Ϊ�˷�ֹ�ٶ����ı������
//			keyboard_mouse_control();
//		}
//		else if(RC_CtrlData.dbus_mode==Dbus_NoKey)
//		{
			dbus_control();
//		}
		vTaskDelayUntil(&PreviousWakeTime,mxTimeIncrement);
	}
}

