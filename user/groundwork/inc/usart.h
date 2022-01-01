#ifndef __USART_H
#define __USART_H

#include "stm32f4xx_conf.h"

#define USART_REC_LEN  			1  	//�����������ֽ��� 200
#define EN_USART1_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����
#define RC_FRAME_LENGTH 18u
#define BSP_USART1_DMA_RX_BUF_LEN 36u

extern u8  USART_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з�
extern u16 USART_RX_STA;         		//����״̬���
extern u8 get_d;

extern uint8_t USART1_RX_BUF[2][BSP_USART1_DMA_RX_BUF_LEN];
extern u16 length;

void usart1_init(void);

#endif
