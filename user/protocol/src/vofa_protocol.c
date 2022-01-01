#include "vofa_protocol.h"
#include "usart.h"

/*VOFA串口调试助手通信协议*/

/*VOFA烈酒协议*/
//void vofa_firewater_output(float data1,float data2,float data3)
//{
//	printf("d:%f,%f,%f\n",data1,data2,data3);
//}

/*VOFA浮点协议*/
void vofa_justfloat_output(float *data,uint8_t num)
{
	uint8_t i;
	send_float temp[num];//定义缓冲区数组
	uint8_t send_data[4*num+4];//定义通过串口传出去的数组，数量是所传数据的字节数加上4个字节的尾巴
	for(i=0;i<num;i++)
	{
		temp[i].float_t=data[i];//将所传数据移到缓冲区数组
	}
	for(i=0;i<num;i++)
	{
		send_data[4*i]=temp[i].uint8_t[0];
		send_data[4*i+1]=temp[i].uint8_t[1];
		send_data[4*i+2]=temp[i].uint8_t[2];
		send_data[4*i+3]=temp[i].uint8_t[3];//将缓冲区数组内的浮点型数据转成4个字节的无符号整型，之后传到要通过串口传出的数组里
	}
	send_data[4*num]=0x00;
	send_data[4*num+1]=0x00;
	send_data[4*num+2]=0x80;
	send_data[4*num+3]=0x7f;//加上协议要求的4个尾巴
	for(i=0;i<4*num+4;i++)
	{
		USART_SendData(UART7,send_data[i]);//用串口1传送数据
		while(USART_GetFlagStatus(UART7,USART_FLAG_TXE)==RESET);
	}
}
