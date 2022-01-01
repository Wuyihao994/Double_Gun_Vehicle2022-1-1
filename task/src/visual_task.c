#include "visual_task.h"
#include "vofa_protocol.h"
#include "seasky_protocol.h"

#define VISUAL_PERIOD 5
#define DATA_NUM 5

//���ջ���
uint16_t usart1_rx_pos = 0;	//usart6_rx_pos��λָ��
const uint16_t usart1_rx_len = 100;
uint8_t usart1_rx_buf[usart1_rx_len] = {0};
//���ͻ���
uint16_t usart1_tx_length = 0;//�������ݳ���
const uint16_t usart1_tx_len = 100;
uint8_t  usart1_tx_buf[usart1_tx_len] = {0};

uint16_t rx_it;
float visual_rx_data[20];
float visual_tx_data[20]={20,35,60};

uint16_t flag_visual=0x000A;

void visual_task(void *pvParameters)
{
	float data[DATA_NUM];
	
	TickType_t PreviousWakeTime;
	TickType_t mxTimeIncrement=pdMS_TO_TICKS(VISUAL_PERIOD);
	PreviousWakeTime = xTaskGetTickCount();
	
	while(1)
	{
		
		vofa_justfloat_output(data,DATA_NUM);//�����Ǵ��ڳ���
		
//		/*���͵з���������ɫ*/
//		get_protocol_send_data
//		(0x0001,	 	  //�ź�id
//		flag_visual, //16λ�Ĵ���
//		visual_tx_data,		  //�����͵�float����
//		3,//float�����ݳ���
//		usart1_tx_buf,		  //�����͵�����֡
//		&usart1_tx_length);	  //�����͵�����֡����
//		usart1_send(usart1_tx_buf,usart1_tx_length);//��PC��������
//		
//		/*��ȡ�Ӿ�����*/
//		get_protocol_info(usart1_rx_buf,&usart1_rx_pos,&rx_it,visual_rx_data);//���մ�PC���ص�����
//		
		vTaskDelayUntil(&PreviousWakeTime,mxTimeIncrement);
	}
}

/*PCͨѶ����*/
//void usart1_send(uint8_t *data,uint16_t len)
//{
//	for(uint16_t i=0; i<len; i++)
//        {
//            while((USART1->SR&USART_FLAG_TC)==0);//�������
//            USART_SendData(USART1,data[i]);
//        }
//}

//void protocol_rx_irq_usart1(uint8_t res)
//{
//    PROTOCOL_RX_IRQ(res,usart1_rx_buf,&usart1_rx_pos);
//    if(usart1_rx_pos>=usart1_rx_len)usart1_rx_pos=0;
//}

//void USART1_IRQHandler()
//{
//    uint8_t Res;
//    if(USART_GetITStatus(USART6, USART_IT_RXNE) != RESET)//�����ж�
//        {
//            Res = USART_ReceiveData(USART1);//(USART1->DR);//��ȡ���յ�������
//            protocol_rx_irq_usart1(Res);
//        }
//    USART_ClearITPendingBit(USART1, USART_IT_RXNE);
//    USART_ClearFlag(USART1, USART_IT_RXNE);
//}
