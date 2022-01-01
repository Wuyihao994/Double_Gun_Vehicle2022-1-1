#include "led.h"

void led_blue_init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Speed=GPIO_High_Speed;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
	
	GPIO_Init(GPIOH,&GPIO_InitStruct);
	
	GPIO_SetBits(GPIOH,GPIO_Pin_10);
}

void led_red_init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_12;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Speed=GPIO_High_Speed;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
	
	GPIO_Init(GPIOH,&GPIO_InitStruct);
	
	GPIO_SetBits(GPIOH,GPIO_Pin_12);
}

void led_green_init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_11;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Speed=GPIO_High_Speed;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
	
	GPIO_Init(GPIOH,&GPIO_InitStruct);
	
	GPIO_SetBits(GPIOH,GPIO_Pin_11);
}

void laser_init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_8;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Speed=GPIO_High_Speed;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
	
	GPIO_Init(GPIOC,&GPIO_InitStruct);
	
	GPIO_SetBits(GPIOC,GPIO_Pin_8);
}

void led_blue_on(void)
{
	GPIO_ResetBits(GPIOH,GPIO_Pin_10);
}

void led_blue_off(void)
{
	GPIO_SetBits(GPIOH,GPIO_Pin_10);
}

void led_blue_toggle(void)
{
	GPIO_ToggleBits(GPIOH,GPIO_Pin_10);
}

void led_red_on(void)
{
	GPIO_ResetBits(GPIOH,GPIO_Pin_12);
}

void led_red_off(void)
{
	GPIO_SetBits(GPIOH,GPIO_Pin_12);
}

void led_red_toggle(void)
{
	GPIO_ToggleBits(GPIOH,GPIO_Pin_12);
}

void led_green_on(void)
{
	GPIO_ResetBits(GPIOH,GPIO_Pin_11);
}

void led_green_off(void)
{
	GPIO_SetBits(GPIOH,GPIO_Pin_11);
}

void led_green_toggle(void)
{
	GPIO_ToggleBits(GPIOH,GPIO_Pin_11);
}
