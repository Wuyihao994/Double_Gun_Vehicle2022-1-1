#include "vofa_protocol.h"
#include "usart.h"

/*VOFA���ڵ�������ͨ��Э��*/

/*VOFA�Ҿ�Э��*/
//void vofa_firewater_output(float data1,float data2,float data3)
//{
//	printf("d:%f,%f,%f\n",data1,data2,data3);
//}

/*VOFA����Э��*/
void vofa_justfloat_output(float *data,uint8_t num)
{
	uint8_t i;
	send_float temp[num];//���建��������
	uint8_t send_data[4*num+4];//����ͨ�����ڴ���ȥ�����飬�������������ݵ��ֽ�������4���ֽڵ�β��
	for(i=0;i<num;i++)
	{
		temp[i].float_t=data[i];//�����������Ƶ�����������
	}
	for(i=0;i<num;i++)
	{
		send_data[4*i]=temp[i].uint8_t[0];
		send_data[4*i+1]=temp[i].uint8_t[1];
		send_data[4*i+2]=temp[i].uint8_t[2];
		send_data[4*i+3]=temp[i].uint8_t[3];//�������������ڵĸ���������ת��4���ֽڵ��޷������ͣ�֮�󴫵�Ҫͨ�����ڴ�����������
	}
	send_data[4*num]=0x00;
	send_data[4*num+1]=0x00;
	send_data[4*num+2]=0x80;
	send_data[4*num+3]=0x7f;//����Э��Ҫ���4��β��
	for(i=0;i<4*num+4;i++)
	{
		USART_SendData(UART7,send_data[i]);//�ô���1��������
		while(USART_GetFlagStatus(UART7,USART_FLAG_TXE)==RESET);
	}
}
