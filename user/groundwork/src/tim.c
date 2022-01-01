#include "tim.h"

void tim5_init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	GPIO_PinAFConfig(GPIOI,GPIO_PinSource0,GPIO_AF_TIM5);//!!!
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Speed=GPIO_High_Speed;
	
	GPIO_Init(GPIOI,&GPIO_InitStruct);
	
	TIM_TimeBaseStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseStruct.TIM_CounterMode=TIM_CounterMode_Up;//
	TIM_TimeBaseStruct.TIM_Period=2000-1;
	TIM_TimeBaseStruct.TIM_Prescaler=90-1;
	
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseStruct);
	
	TIM_OCInitStructure.TIM_Pulse = 0; 		//��װ�벶��ȽϼĴ���������ֵ
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;  //TIM1�����ȵ���ģʽ1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//ʹ������Ƚ�״̬
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;//ʹ������Ƚ�N״̬
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//TIM1 ����Ƚϼ��Ը�
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;//TIM1 ����Ƚ�N���Ը�
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;//�� MOE=0 ���� TIM1 ����ȽϿ���״̬
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;//�� MOE=0 ���� TIM1 ����Ƚ� N ����״̬
	
	TIM_OC4Init(TIM5,&TIM_OCInitStructure);
	
	TIM_OC4PreloadConfig(TIM5, TIM_OCPreload_Enable);
	
	TIM_ARRPreloadConfig(TIM5,ENABLE);//
	
	TIM_CtrlPWMOutputs(TIM5,ENABLE);
	
	TIM_Cmd(TIM5,ENABLE);
}

void set_servo_pwm(uint32_t pwm_set)
{
	TIM_SetCompare4(TIM5,pwm_set);
}

void tim8_init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	GPIO_PinAFConfig(GPIOI,GPIO_PinSource2,GPIO_AF_TIM8);//!!!
	GPIO_PinAFConfig(GPIOI,GPIO_PinSource5,GPIO_AF_TIM8);//!!!
	GPIO_PinAFConfig(GPIOI,GPIO_PinSource6,GPIO_AF_TIM8);//!!!
	GPIO_PinAFConfig(GPIOI,GPIO_PinSource7,GPIO_AF_TIM8);//!!!
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_2|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Speed=GPIO_High_Speed;
	
	GPIO_Init(GPIOI,&GPIO_InitStruct);
	
	TIM_TimeBaseStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseStruct.TIM_CounterMode=TIM_CounterMode_Up;//
	TIM_TimeBaseStruct.TIM_Period=2000-1;
	TIM_TimeBaseStruct.TIM_Prescaler=90-1;
	
	TIM_TimeBaseInit(TIM8,&TIM_TimeBaseStruct);
	
	TIM_OCInitStructure.TIM_Pulse = 0; 		//��װ�벶��ȽϼĴ���������ֵ
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;  //TIM1�����ȵ���ģʽ1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//ʹ������Ƚ�״̬
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;//ʹ������Ƚ�N״̬
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//TIM1 ����Ƚϼ��Ը�
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;//TIM1 ����Ƚ�N���Ը�
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;//�� MOE=0 ���� TIM1 ����ȽϿ���״̬
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;//�� MOE=0 ���� TIM1 ����Ƚ� N ����״̬
	
	TIM_OC1Init(TIM8,&TIM_OCInitStructure);
	TIM_OC2Init(TIM8,&TIM_OCInitStructure);
	TIM_OC3Init(TIM8,&TIM_OCInitStructure);
	TIM_OC4Init(TIM8,&TIM_OCInitStructure);
	
	TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable);
	
	TIM_ARRPreloadConfig(TIM8,ENABLE);//
	
	TIM_CtrlPWMOutputs(TIM8,ENABLE);
	
	TIM_Cmd(TIM8,ENABLE);
}

//void set_friction_pwm(uint32_t pwm_set)
//{
//	TIM_SetCompare1(TIM8,pwm_set);
//	TIM_SetCompare2(TIM8,pwm_set);
//	TIM_SetCompare3(TIM8,pwm_set);
//	TIM_SetCompare4(TIM8,pwm_set);
//}

