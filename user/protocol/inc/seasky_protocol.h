#ifndef __SEASKY_PROTOCOL_H
#define __SEASKY_PROTOCOL_H

#include "stm32f4xx_conf.h"

#define PROTOCOL_CMD_ID 0XA5

#define OFFSET_BYTE 8	//�����ݶ��⣬����������ռ�ֽ���

typedef struct{
	__packed struct
 {
 uint8_t sof;
 uint16_t data_length;
 uint8_t crc_check; //֡ͷCRCУ��
 } header; //����֡ͷ
 uint16_t cmd_id; //����ID
 uint16_t frame_tail; //֡βCRCУ��
}protocol_rm_struct;

/*���·�������֡�������㷢������֡����*/
void get_protocol_send_data
(uint16_t send_id,	 	  //�ź�id
 uint16_t flags_register, //16λ�Ĵ���
 float    *tx_data,		  //�����͵�float����
 uint8_t  float_length,//float�����ݳ���
 uint8_t  *tx_buf,		  //�����͵�����֡
 uint16_t *tx_buf_len);	  //�����͵�����֡����

/*�������ݴ���*/
uint16_t get_protocol_info
(uint8_t  *rx_buf,			//���յ���ԭʼ����
 uint16_t *rx_pos,			//ԭʼ����ָ��
 uint16_t *flags_register,	//�������ݵ�16λ�Ĵ�����ַ
 float    *rx_data);		//���յ�float���ݴ洢��ַ


/*�жϺ�����ֵ����*/
void PROTOCOL_RX_IRQ(uint8_t res,uint8_t *rx_buf,uint16_t *rx_buf_pos);
void protocol_rx_irq(uint8_t res);
 
#endif
