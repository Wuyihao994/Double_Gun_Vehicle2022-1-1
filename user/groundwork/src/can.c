#include "can.h"

float default_yaw = 208.0;

moto_info moto_chassis_info[4];
moto_info moto_gimbal_info[2];
moto_info moto_revolver_info;
bmi088_info bmi088_infomation;

CanRxMsg RxMessage;

void can1_init(void)
{
	GPIO_InitTypeDef GPIO_Initstruct;
	CAN_InitTypeDef CAN1_Initstruct;
	CAN_FilterInitTypeDef CAN1_FilterInitstruct;
	NVIC_InitTypeDef NVIC_Initstruct;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1,ENABLE);
	
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource0,GPIO_AF_CAN1);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource1,GPIO_AF_CAN1);
	
	GPIO_Initstruct.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;
	GPIO_Initstruct.GPIO_Mode=GPIO_Mode_AF;
	GPIO_Initstruct.GPIO_OType=GPIO_OType_PP;
	GPIO_Initstruct.GPIO_Speed=GPIO_High_Speed;
	GPIO_Initstruct.GPIO_PuPd=GPIO_PuPd_NOPULL;
	
	GPIO_Init(GPIOD,&GPIO_Initstruct);
	
	CAN1_Initstruct.CAN_Prescaler=5;
	CAN1_Initstruct.CAN_BS1=CAN_BS1_3tq;
	CAN1_Initstruct.CAN_BS2=CAN_BS2_5tq;
	CAN1_Initstruct.CAN_SJW=CAN_SJW_1tq;
	CAN1_Initstruct.CAN_Mode=CAN_Mode_Normal;
	CAN1_Initstruct.CAN_ABOM=ENABLE;
	CAN1_Initstruct.CAN_AWUM=DISABLE;
	CAN1_Initstruct.CAN_NART=DISABLE;
	CAN1_Initstruct.CAN_RFLM=DISABLE;
	CAN1_Initstruct.CAN_TTCM=DISABLE;
	CAN1_Initstruct.CAN_TXFP=DISABLE;
	
	CAN_Init(CAN1,&CAN1_Initstruct);
	
	CAN1_FilterInitstruct.CAN_FilterIdHigh=(0x205<<21&0xFFFF0000)>>16;//Î´½â
	CAN1_FilterInitstruct.CAN_FilterIdLow=0;//Î´½â
	CAN1_FilterInitstruct.CAN_FilterMaskIdHigh=0x0000;
	CAN1_FilterInitstruct.CAN_FilterMaskIdLow=0x0000;
	CAN1_FilterInitstruct.CAN_FilterFIFOAssignment=CAN_Filter_FIFO0;
	CAN1_FilterInitstruct.CAN_FilterNumber=0;
	CAN1_FilterInitstruct.CAN_FilterMode=CAN_FilterMode_IdMask;
	CAN1_FilterInitstruct.CAN_FilterScale=CAN_FilterScale_32bit;
	CAN1_FilterInitstruct.CAN_FilterActivation=ENABLE;
	
	CAN_FilterInit(&CAN1_FilterInitstruct);
	
	CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);
  CAN_ITConfig(CAN1,CAN_IT_TME,ENABLE); 
	
  NVIC_Initstruct.NVIC_IRQChannel = CAN1_RX0_IRQn;
  NVIC_Initstruct.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_Initstruct.NVIC_IRQChannelSubPriority = 0;
  NVIC_Initstruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_Initstruct);
}

void can2_init(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
    CAN_InitTypeDef CAN_InitStructure;
    CAN_FilterInitTypeDef CAN_FilterInitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN2, ENABLE);

		RCC_APB1PeriphResetCmd(RCC_APB1Periph_CAN2, ENABLE);
		RCC_APB1PeriphResetCmd(RCC_APB1Periph_CAN2, DISABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_PinAFConfig(GPIOB, GPIO_PinSource12, GPIO_AF_CAN2);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_CAN2);

    CAN_InitStructure.CAN_TTCM = DISABLE;
    CAN_InitStructure.CAN_ABOM = ENABLE;
    CAN_InitStructure.CAN_AWUM = DISABLE;
    CAN_InitStructure.CAN_NART = DISABLE;
    CAN_InitStructure.CAN_RFLM = DISABLE;
    CAN_InitStructure.CAN_TXFP = DISABLE;
    CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;
    CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
    CAN_InitStructure.CAN_BS1 = CAN_BS1_6tq;
    CAN_InitStructure.CAN_BS2 = CAN_BS2_2tq;
    CAN_InitStructure.CAN_Prescaler = 5;
    CAN_Init(CAN2, &CAN_InitStructure);

    CAN_FilterInitStructure.CAN_FilterNumber = 14;
    CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
    CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
    CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;
    CAN_FilterInitStructure.CAN_FilterIdLow =  0x0000;
    CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;
    CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
    CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;
    CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
    CAN_FilterInit(&CAN_FilterInitStructure);

    CAN_ITConfig(CAN2, CAN_IT_FMP0, ENABLE);
		CAN_ITConfig(CAN2,CAN_IT_TME,ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel = CAN2_RX0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
		
		NVIC_InitStructure.NVIC_IRQChannel = CAN2_TX_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
}

void can_mes_send(CAN_TypeDef* CANx,uint32_t StdId,int16_t *info)
{
	CanTxMsg TxMessage;
	TxMessage.StdId= StdId;
	TxMessage.IDE = 0;
	TxMessage.RTR = 0;
	TxMessage.DLC = 8;
	TxMessage.Data[0] = info[0] >> 8;
	TxMessage.Data[1] = info[0];
	TxMessage.Data[2] = info[1] >> 8;
	TxMessage.Data[3] = info[1];
	TxMessage.Data[4] = info[2] >> 8;
	TxMessage.Data[5] = info[2];
	TxMessage.Data[6] = info[3] >> 8;
	TxMessage.Data[7] = info[3];
	CAN_Transmit(CANx, &TxMessage);
}

void power_init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH,ENABLE);
	GPIO_InitTypeDef GPIO_Initstruct;
  GPIO_Initstruct.GPIO_Pin=GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
	GPIO_Initstruct.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_Initstruct.GPIO_Speed=GPIO_Low_Speed;
	GPIO_Initstruct.GPIO_OType=GPIO_OType_PP;
	GPIO_Initstruct.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOH,&GPIO_Initstruct);
	
	GPIO_SetBits(GPIOH, GPIO_Pin_2);
	GPIO_SetBits(GPIOH, GPIO_Pin_3);
	GPIO_SetBits(GPIOH, GPIO_Pin_4);
	GPIO_SetBits(GPIOH, GPIO_Pin_5);
}

void moto_infomation_process(moto_info *moto_infomation,CanRxMsg *RxMessage)
{
	moto_infomation->moto_raw_last_angle=moto_infomation->moto_raw_angle;
	moto_infomation->moto_raw_angle=((RxMessage->Data[0]<<8)|RxMessage->Data[1]);
	moto_infomation->moto_angle=moto_infomation->moto_raw_angle*360/8192;
	if(moto_infomation->moto_raw_angle-moto_infomation->moto_raw_last_angle>4096)
		moto_infomation->round_count--;
	else if(moto_infomation->moto_raw_angle-moto_infomation->moto_raw_last_angle<-4096)
		moto_infomation->round_count++;
	moto_infomation->moto_total_angle=moto_infomation->round_count*360+(moto_infomation->moto_raw_angle-moto_infomation->moto_offset_angle)*360/8192;
	moto_infomation->zero_total_angle=((float)moto_infomation->round_count*360.0f+(float)(moto_infomation->moto_raw_angle-moto_infomation->default_zero_angle)*(360.0f/8192.0f))/REDUCTION_RATIO_3508;
	
	moto_infomation->moto_speed=((RxMessage->Data[2]<<8)|RxMessage->Data[3]);
	moto_infomation->moto_current=((RxMessage->Data[4]<<8)|RxMessage->Data[5]);
	moto_infomation->moto_temperature=RxMessage->Data[6];
}

void supercap_infomation_process(supercap_info *supercap_infomation,CanRxMsg *RxMessage)
{
	supercap_infomation->cap_power_set=((RxMessage->Data[0]<<8)|RxMessage->Data[1])/100;
	supercap_infomation->cap_power_output=((RxMessage->Data[2]<<8)|RxMessage->Data[3])/100;
	supercap_infomation->cap_voltage_output=((RxMessage->Data[4]<<8)|RxMessage->Data[5])/100;
	supercap_infomation->cap_current_output=((RxMessage->Data[6]<<8)|RxMessage->Data[7])/100;
}

void bmi088_z_infomation_process(bmi088_info *bmi088_infomation,CanRxMsg *RxMessage)
{
	int i=0;
	bmi088_float bmi088_z[2];
	for(i=0;i<8;i++)
	{
		bmi088_z[i/4].bmi088_uint8_t[i%4]=RxMessage->Data[i];
	}
	bmi088_infomation->z=bmi088_z[1].bmi088_float_t;
}

void bmi088_yaw_infomation_process(bmi088_info *bmi088_infomation,CanRxMsg *RxMessage)
{
	int i=0;
	bmi088_float bmi088_yaw[2];
	for(i=0;i<8;i++)
	{
		bmi088_yaw[i/4].bmi088_uint8_t[i%4]=RxMessage->Data[i];
	}
	bmi088_infomation->yaw=bmi088_yaw[1].bmi088_float_t;
}

void CAN1_RX0_IRQHandler(void)
{
	int i;
	if(CAN_GetITStatus(CAN1,CAN_IT_FMP0) != RESET)
	{
    CAN_ClearITPendingBit(CAN1, CAN_IT_FF0);
		CAN_ClearFlag(CAN1, CAN_FLAG_FF0); 
		CAN_Receive(CAN1,CAN_FIFO0,&RxMessage);
		switch (RxMessage.StdId)
		{
			case CAN_RX_MOTO3508_LF:
			case CAN_RX_MOTO3508_LB:
			case CAN_RX_MOTO3508_RB:
			case CAN_RX_MOTO3508_RF:
			{
				i=RxMessage.StdId-CAN_RX_MOTO3508_LF;
				moto_infomation_process(&moto_chassis_info[i],&RxMessage);
			}break;
			case CAN_RX_MOTO6020_Y:
			case CAN_RX_MOTO6020_P:
			{
				i=RxMessage.StdId-CAN_RX_MOTO6020_Y;
				moto_infomation_process(&moto_gimbal_info[i],&RxMessage);
			}break;
			case CAN_RX_MOTO2006_RV:
			{
				moto_infomation_process(&moto_revolver_info,&RxMessage);
			}
		}	
	}
}

void CAN2_RX0_IRQHandler(void)
{
	if(CAN_GetITStatus(CAN2,CAN_IT_FMP0) != RESET)
	{
    CAN_ClearITPendingBit(CAN2, CAN_IT_FF0);
		CAN_ClearFlag(CAN2, CAN_FLAG_FF0); 
		CAN_Receive(CAN2,CAN_FIFO0,&RxMessage);
		switch (RxMessage.StdId)
		{
			case CAN_RX_BMI088_Z:
			{
				bmi088_z_infomation_process(&bmi088_infomation,&RxMessage);
			}break;
			case CAN_RX_BMI088_YAW:
			{
				bmi088_yaw_infomation_process(&bmi088_infomation,&RxMessage);
			}break;
		}	
	}
}

void CAN2_TX_IRQHandler(void)
{
	if (CAN_GetITStatus(CAN2,CAN_IT_TME)!= RESET) 
	{
		CAN_ClearITPendingBit(CAN2,CAN_IT_TME);
	}
}
