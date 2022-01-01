#ifndef __USART_H
#define __USART_H

#include "stm32f4xx_conf.h"

#define USART_REC_LEN  			1  	//定义最大接收字节数 200
#define EN_USART1_RX 			1		//使能（1）/禁止（0）串口1接收
#define RC_FRAME_LENGTH 18u
#define BSP_USART1_DMA_RX_BUF_LEN 36u

extern u8  USART_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符
extern u16 USART_RX_STA;         		//接收状态标记
extern u8 get_d;

extern uint8_t USART1_RX_BUF[2][BSP_USART1_DMA_RX_BUF_LEN];
extern u16 length;

void usart1_init(void);

#endif
