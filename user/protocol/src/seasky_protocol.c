/*
	@SEASKY---2020/09/05
	���ϴ�ѧRoBoMatster����ͨ��Э��
*/
#include "seasky_protocol.h"
//#include "usart.h"
#include "crc8.h"
#include "crc16.h"

/*��ȡCRC8У����*/
uint8_t Get_CRC8_Check(uint8_t *pchMessage,uint16_t dwLength)
{
    return crc_8(pchMessage,dwLength);
}
/*����CRC8���ݶ�*/
uint8_t CRC8_Check_Sum(uint8_t *pchMessage,uint16_t dwLength)
{
    uint8_t ucExpected = 0;
    if ((pchMessage == 0) || (dwLength <= 2)) return 0;
    ucExpected = Get_CRC8_Check(pchMessage, dwLength-1);
    return ( ucExpected == pchMessage[dwLength-1] );
}
/*��ȡCRC16У����*/
uint16_t Get_CRC16_Check(uint8_t *pchMessage,uint32_t dwLength)
{
    return crc_16(pchMessage,dwLength);
}
/*����CRC16���ݶ�*/
uint16_t CRC16_Check_Sum(uint8_t *pchMessage, uint32_t dwLength)
{
    uint16_t  wExpected = 0;
    if ((pchMessage == 0) || (dwLength <= 2))
        {
            return 0;
        }
    wExpected = Get_CRC16_Check ( pchMessage, dwLength - 2);
    return (((wExpected & 0xff) == pchMessage[dwLength - 2] )&& (((wExpected >> 8) & 0xff) == pchMessage[dwLength - 1]));
}
/*��������֡ͷ*/
uint8_t protocol_heade_Check(
    protocol_rm_struct *pro,
    uint8_t  *rx_buf,
    uint16_t *rx_pos)
{
    if(rx_buf[0] == PROTOCOL_CMD_ID)
        {
            pro->header.sof = rx_buf[0];
            if(CRC8_Check_Sum(&rx_buf[0],4))
                {
                    pro->header.data_length = (rx_buf[2]<<8) | rx_buf[1];
                    pro->header.crc_check = rx_buf[3];
                    pro->cmd_id = (rx_buf[5]<<8) | rx_buf[4];
                    return  1;
                }
        }
    else
        {
            *rx_pos = 0;
        }
    return 0;
}

float float_protocol(uint8_t *dat_t)
{
    uint8_t f_data[4];
    f_data[0] = *(dat_t+0);
    f_data[1] = *(dat_t+1);
    f_data[2] = *(dat_t+2);
    f_data[3] = *(dat_t+3);
    return *(float*)f_data;
}
/*
	�˺������ݴ����͵����ݸ�������֡��ʽ�Լ����ݣ�ʵ�����ݵĴ������
	��������ͨ�Žӿڵķ��ͺ�������tx_buf�еĶ�Ӧ����
*/
void get_protocol_send_data
(uint16_t send_id,	 	  //�ź�id
 uint16_t flags_register, //16λ�Ĵ���
 float    *tx_data,		  //�����͵�float����
 uint8_t  float_length,//float�����ݳ���
 uint8_t  *tx_buf,		  //�����͵�����֡
 uint16_t *tx_buf_len)	  //�����͵�����֡����
{
    uint16_t crc16;
    uint16_t data_len;

    data_len = float_length*4+2;
    /*֡ͷ����*/
    tx_buf[0] = PROTOCOL_CMD_ID;
    tx_buf[1] = data_len & 0xff;		      //��λ��ǰ
    tx_buf[2] = (data_len >> 8) & 0xff;       //��λ��ǰ
    tx_buf[3] = Get_CRC8_Check(&tx_buf[0],3); //��ȡCRC8У��λ

    /*���ݵ��ź�id*/
    tx_buf[4] = send_id & 0xff;
    tx_buf[5] = (send_id>>8) & 0xff;

    /*����16λ�Ĵ���*/
    tx_buf[6] = flags_register & 0xff;
    tx_buf[7] = (flags_register>>8) & 0xff;

    /*float���ݶ�*/
    for(int i=0; i<4*float_length; i++)
        {
            tx_buf[i+8]  = ((uint8_t*)(&tx_data[i/4]))[i%4];
        }

    /*����У��*/
    crc16 = Get_CRC16_Check(&tx_buf[0],data_len+6);
    tx_buf[data_len+6] = crc16 & 0xff;
    tx_buf[data_len+7] = (crc16 >>8) & 0xff;

    *tx_buf_len = data_len+8;
}
/*
	�˺������ڴ����������ݣ�
	�����������ݵ�id
*/
uint16_t get_protocol_info
(uint8_t  *rx_buf,			//���յ���ԭʼ����
 uint16_t *rx_pos,			//ԭʼ����ָ��
 uint16_t *flags_register,	//�������ݵ�16λ�Ĵ�����ַ
 float    *rx_data)			//���յ�float���ݴ洢��ַ
{
	static protocol_rm_struct pro;
	static uint16_t date_length;
    if(protocol_heade_Check(&pro,rx_buf,rx_pos))
        {
            date_length = OFFSET_BYTE + pro.header.data_length;
            while(CRC16_Check_Sum(&rx_buf[0],date_length))
                {
                    *flags_register = (rx_buf[7]<<8) | rx_buf[6];
                    for(int i=0; i<(pro.header.data_length-2)/4; i++)
                        {
                            rx_data[i] = float_protocol(&rx_buf[8+4*i]);
                        }
                    for(int i=0; i<date_length; i++)
                        {
                            rx_buf[i] = 0;
                        }
                    *rx_pos = 0;
                    return pro.cmd_id;
                }
        }
}

/*�����жϽ��պ���*/
void PROTOCOL_RX_IRQ(uint8_t res,uint8_t *rx_buf,uint16_t *rx_buf_pos)
{
    rx_buf[*rx_buf_pos]=res;
    (*rx_buf_pos) +=1;
    if(rx_buf[0]!=PROTOCOL_CMD_ID)
        {
            *rx_buf_pos = 0;
        };
}
