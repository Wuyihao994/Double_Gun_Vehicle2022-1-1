#include "comm.h"
#include "usart.h"
#include "delay.h"
//全部为高位在前写的
u8 comm_usart_rx_buf[RX_LENGTH];
u8 comm_usart_tx_buf[TX_LENGTH];
u8 uart8_len_cr;
u8 send_data_length;
uint16_t  wExpected = 0;
RoboMaster rm_info;

const unsigned char CRC8_INIT=0xff;
const uint16_t CRC16_INIT = 0xffff;

const RoboMaster* get_robomaster_info_point(void)
{
	return &rm_info;
}

const unsigned char CRC8_TAB[256]=
{
    0x00, 0x5e, 0xbc, 0xe2, 0x61, 0x3f, 0xdd, 0x83, 0xc2, 0x9c, 0x7e, 0x20, 0xa3, 0xfd, 0x1f, 0x41,
    0x9d, 0xc3, 0x21, 0x7f, 0xfc, 0xa2, 0x40, 0x1e, 0x5f, 0x01, 0xe3, 0xbd, 0x3e, 0x60, 0x82, 0xdc,
    0x23, 0x7d, 0x9f, 0xc1, 0x42, 0x1c, 0xfe, 0xa0, 0xe1, 0xbf, 0x5d, 0x03, 0x80, 0xde, 0x3c, 0x62,
    0xbe, 0xe0, 0x02, 0x5c, 0xdf, 0x81, 0x63, 0x3d, 0x7c, 0x22, 0xc0, 0x9e, 0x1d, 0x43, 0xa1, 0xff,
    0x46, 0x18, 0xfa, 0xa4, 0x27, 0x79, 0x9b, 0xc5, 0x84, 0xda, 0x38, 0x66, 0xe5, 0xbb, 0x59, 0x07,
    0xdb, 0x85, 0x67, 0x39, 0xba, 0xe4, 0x06, 0x58, 0x19, 0x47, 0xa5, 0xfb, 0x78, 0x26, 0xc4, 0x9a,
    0x65, 0x3b, 0xd9, 0x87, 0x04, 0x5a, 0xb8, 0xe6, 0xa7, 0xf9, 0x1b, 0x45, 0xc6, 0x98, 0x7a, 0x24,
    0xf8, 0xa6, 0x44, 0x1a, 0x99, 0xc7, 0x25, 0x7b, 0x3a, 0x64, 0x86, 0xd8, 0x5b, 0x05, 0xe7, 0xb9,
    0x8c, 0xd2, 0x30, 0x6e, 0xed, 0xb3, 0x51, 0x0f, 0x4e, 0x10, 0xf2, 0xac, 0x2f, 0x71, 0x93, 0xcd,
    0x11, 0x4f, 0xad, 0xf3, 0x70, 0x2e, 0xcc, 0x92, 0xd3, 0x8d, 0x6f, 0x31, 0xb2, 0xec, 0x0e, 0x50,
    0xaf, 0xf1, 0x13, 0x4d, 0xce, 0x90, 0x72, 0x2c, 0x6d, 0x33, 0xd1, 0x8f, 0x0c, 0x52, 0xb0, 0xee,
    0x32, 0x6c, 0x8e, 0xd0, 0x53, 0x0d, 0xef, 0xb1, 0xf0, 0xae, 0x4c, 0x12, 0x91, 0xcf, 0x2d, 0x73,
    0xca, 0x94, 0x76, 0x28, 0xab, 0xf5, 0x17, 0x49, 0x08, 0x56, 0xb4, 0xea, 0x69, 0x37, 0xd5, 0x8b,
    0x57, 0x09, 0xeb, 0xb5, 0x36, 0x68, 0x8a, 0xd4, 0x95, 0xcb, 0x29, 0x77, 0xf4, 0xaa, 0x48, 0x16,
    0xe9, 0xb7, 0x55, 0x0b, 0x88, 0xd6, 0x34, 0x6a, 0x2b, 0x75, 0x97, 0xc9, 0x4a, 0x14, 0xf6, 0xa8,
    0x74, 0x2a, 0xc8, 0x96, 0x15, 0x4b, 0xa9, 0xf7, 0xb6, 0xe8, 0x0a, 0x54, 0xd7, 0x89, 0x6b, 0x35,
};

const uint16_t wCRC_Table[256] =
{
    0x0000, 0x1189, 0x2312, 0x329b, 0x4624, 0x57ad, 0x6536, 0x74bf,
    0x8c48, 0x9dc1, 0xaf5a, 0xbed3, 0xca6c, 0xdbe5, 0xe97e, 0xf8f7,
    0x1081, 0x0108, 0x3393, 0x221a, 0x56a5, 0x472c, 0x75b7, 0x643e,
    0x9cc9, 0x8d40, 0xbfdb, 0xae52, 0xdaed, 0xcb64, 0xf9ff, 0xe876,
    0x2102, 0x308b, 0x0210, 0x1399, 0x6726, 0x76af, 0x4434, 0x55bd,
    0xad4a, 0xbcc3, 0x8e58, 0x9fd1, 0xeb6e, 0xfae7, 0xc87c, 0xd9f5,
    0x3183, 0x200a, 0x1291, 0x0318, 0x77a7, 0x662e, 0x54b5, 0x453c,
    0xbdcb, 0xac42, 0x9ed9, 0x8f50, 0xfbef, 0xea66, 0xd8fd, 0xc974,
    0x4204, 0x538d, 0x6116, 0x709f, 0x0420, 0x15a9, 0x2732, 0x36bb,
    0xce4c, 0xdfc5, 0xed5e, 0xfcd7, 0x8868, 0x99e1, 0xab7a, 0xbaf3,
    0x5285, 0x430c, 0x7197, 0x601e, 0x14a1, 0x0528, 0x37b3, 0x263a,
    0xdecd, 0xcf44, 0xfddf, 0xec56, 0x98e9, 0x8960, 0xbbfb, 0xaa72,
    0x6306, 0x728f, 0x4014, 0x519d, 0x2522, 0x34ab, 0x0630, 0x17b9,
    0xef4e, 0xfec7, 0xcc5c, 0xddd5, 0xa96a, 0xb8e3, 0x8a78, 0x9bf1,
    0x7387, 0x620e, 0x5095, 0x411c, 0x35a3, 0x242a, 0x16b1, 0x0738,
    0xffcf, 0xee46, 0xdcdd, 0xcd54, 0xb9eb, 0xa862, 0x9af9, 0x8b70,
    0x8408, 0x9581, 0xa71a, 0xb693, 0xc22c, 0xd3a5, 0xe13e, 0xf0b7,
    0x0840, 0x19c9, 0x2b52, 0x3adb, 0x4e64, 0x5fed, 0x6d76, 0x7cff,
    0x9489, 0x8500, 0xb79b, 0xa612, 0xd2ad, 0xc324, 0xf1bf, 0xe036,
    0x18c1, 0x0948, 0x3bd3, 0x2a5a, 0x5ee5, 0x4f6c, 0x7df7, 0x6c7e,
    0xa50a, 0xb483, 0x8618, 0x9791, 0xe32e, 0xf2a7, 0xc03c, 0xd1b5,
    0x2942, 0x38cb, 0x0a50, 0x1bd9, 0x6f66, 0x7eef, 0x4c74, 0x5dfd,
    0xb58b, 0xa402, 0x9699, 0x8710, 0xf3af, 0xe226, 0xd0bd, 0xc134,
    0x39c3, 0x284a, 0x1ad1, 0x0b58, 0x7fe7, 0x6e6e, 0x5cf5, 0x4d7c,
    0xc60c, 0xd785, 0xe51e, 0xf497, 0x8028, 0x91a1, 0xa33a, 0xb2b3,
    0x4a44, 0x5bcd, 0x6956, 0x78df, 0x0c60, 0x1de9, 0x2f72, 0x3efb,
    0xd68d, 0xc704, 0xf59f, 0xe416, 0x90a9, 0x8120, 0xb3bb, 0xa232,
    0x5ac5, 0x4b4c, 0x79d7, 0x685e, 0x1ce1, 0x0d68, 0x3ff3, 0x2e7a,
    0xe70e, 0xf687, 0xc41c, 0xd595, 0xa12a, 0xb0a3, 0x8238, 0x93b1,
    0x6b46, 0x7acf, 0x4854, 0x59dd, 0x2d62, 0x3ceb, 0x0e70, 0x1ff9,
    0xf78f, 0xe606, 0xd49d, 0xc514, 0xb1ab, 0xa022, 0x92b9, 0x8330,
    0x7bc7, 0x6a4e, 0x58d5, 0x495c, 0x3de3, 0x2c6a, 0x1ef1, 0x0f78
};

float float_data_get(u8 *dat)
{
    u8 data[4];
    data[0] = *(dat+0);
    data[1] = *(dat+1);
    data[2] = *(dat+2);
    data[3] = *(dat+3);
    return *(float*)data;
}

//获取crc8
unsigned char Get_CRC8_Check_Sum(unsigned char *pchMessage,unsigned int dwLength,unsigned char ucCRC8)
{
    unsigned char ucIndex;
    while (dwLength--)
        {
            ucIndex = ucCRC8^(*pchMessage++);
            ucCRC8 = CRC8_TAB[ucIndex];
        }
    return(ucCRC8);
}

//验证crc8
unsigned int Verify_CRC8_Check_Sum(unsigned char *pchMessage, unsigned int dwLength)
{
    unsigned char ucExpected = 0;
    if ((pchMessage == 0) || (dwLength <= 2)) return 0;
    ucExpected = Get_CRC8_Check_Sum (pchMessage, dwLength-1, CRC8_INIT);
    return ( ucExpected == pchMessage[dwLength-1] );
}

//获取crc16
uint16_t Get_CRC16_Check_Sum(uint8_t *pchMessage,uint32_t dwLength,uint16_t wCRC)
{
    u8 chData;
    if (pchMessage == 0)
        {
            return 0xFFFF;
        }
    while(dwLength--)
        {
            chData = *pchMessage++;
            (wCRC) = ((uint16_t)(wCRC) >> 8) ^ wCRC_Table[((uint16_t)(wCRC) ^ (uint16_t)(chData)) & 0x00ff];
        }
    return wCRC;
}

//检验crc16
uint32_t Verify_CRC16_Check_Sum(uint8_t *pchMessage, uint32_t dwLength)
{
    if ((pchMessage == 0) || (dwLength <= 2))
        {
            return 0;
        }
    wExpected = Get_CRC16_Check_Sum ( pchMessage, dwLength - 2, CRC16_INIT);
    return (((wExpected & 0xff) == pchMessage[dwLength - 2] )&& (((wExpected >> 8) & 0xff) == pchMessage[dwLength - 1]));
}

//针头检验------字节偏移量 0-6
u8 robomaster_heade_Check()
{
    if(comm_usart_rx_buf[0] == Cmd_sof)
        {
            rm_info.rm_head.SOF = comm_usart_rx_buf[0];
            if(Verify_CRC8_Check_Sum(&comm_usart_rx_buf[0],5))
                {
                    rm_info.rm_head.data_length = (comm_usart_rx_buf[2]<<8) | comm_usart_rx_buf[1];
                    rm_info.rm_head.seq = comm_usart_rx_buf[3];
                    rm_info.rm_head.CRC8 = comm_usart_rx_buf[4];
                    rm_info.rm_head.rm_cmd_id = (comm_usart_rx_buf[6]<<8) | comm_usart_rx_buf[5];
                    return  1;
                }
        }
    else
        {
            uart8_len_cr = 0;
        }
    return 0;
}

//比赛状态信息 字节偏移量 7-17
void game_state_get()
{
    rm_info.game_status.game_type = comm_usart_rx_buf[7] & 0x0f;
    rm_info.game_status.game_progress = (comm_usart_rx_buf[7]>>4) & 0x0f;
    rm_info.game_status.stage_remain_time = (comm_usart_rx_buf[9] << 8) | comm_usart_rx_buf[8];
	  int i;
	  for(i=0;i<8;i++)
    {
			rm_info.game_status.SyncTimeStamp = (comm_usart_rx_buf[10+i] << i*8) | rm_info.game_status.SyncTimeStamp;
		}
}

//比赛结果数据 字节偏移量 7
void game_result_get()
{
    rm_info.game_result.winner = comm_usart_rx_buf[7];
}

//机器人血量数据 0X0003 字节偏移量 7-38
void game_robot_HP_get()
{
    rm_info.game_robot_HP.red_1_robot_HP =(comm_usart_rx_buf[8]<<8) | comm_usart_rx_buf[7];
	  rm_info.game_robot_HP.red_2_robot_HP =(comm_usart_rx_buf[10]<<8) | comm_usart_rx_buf[9];
	  rm_info.game_robot_HP.red_3_robot_HP =(comm_usart_rx_buf[12]<<8) | comm_usart_rx_buf[11];
	  rm_info.game_robot_HP.red_4_robot_HP =(comm_usart_rx_buf[14]<<8) | comm_usart_rx_buf[13];
	  rm_info.game_robot_HP.red_5_robot_HP =(comm_usart_rx_buf[16]<<8) | comm_usart_rx_buf[15];
	  rm_info.game_robot_HP.red_7_robot_HP =(comm_usart_rx_buf[18]<<8) | comm_usart_rx_buf[17];
	  rm_info.game_robot_HP.red_outpost_HP =(comm_usart_rx_buf[20]<<8) | comm_usart_rx_buf[19];
	  rm_info.game_robot_HP.red_base_HP =(comm_usart_rx_buf[22]<<8) | comm_usart_rx_buf[21];
	  rm_info.game_robot_HP.blue_1_robot_HP =(comm_usart_rx_buf[24]<<8) | comm_usart_rx_buf[23];
	  rm_info.game_robot_HP.blue_2_robot_HP =(comm_usart_rx_buf[26]<<8) | comm_usart_rx_buf[25];
	  rm_info.game_robot_HP.blue_3_robot_HP =(comm_usart_rx_buf[28]<<8) | comm_usart_rx_buf[27];
	  rm_info.game_robot_HP.blue_4_robot_HP =(comm_usart_rx_buf[30]<<8) | comm_usart_rx_buf[29];
	  rm_info.game_robot_HP.blue_5_robot_HP =(comm_usart_rx_buf[32]<<8) | comm_usart_rx_buf[31];
	  rm_info.game_robot_HP.blue_7_robot_HP =(comm_usart_rx_buf[34]<<8) | comm_usart_rx_buf[33];
	  rm_info.game_robot_HP.blue_outpost_HP =(comm_usart_rx_buf[36]<<8) | comm_usart_rx_buf[35];
	  rm_info.game_robot_HP.blue_base_HP =(comm_usart_rx_buf[38]<<8) | comm_usart_rx_buf[37];
}

//飞镖发射状态 字节偏移量 7-9
void dart_status_get()
{
	  rm_info.dart_status.dart_belong = comm_usart_rx_buf[7];
	  rm_info.dart_status.stage_remaining_time = (comm_usart_rx_buf[9]<<8) | comm_usart_rx_buf[8];
}

//人工智能挑战赛加成与惩罚区状态 字节偏移量 7-17
void ICRA_buff_debuff_zone_status_get()
{
	  uint32_t data = comm_usart_rx_buf[9]<<16 | comm_usart_rx_buf[8]<<8 | comm_usart_rx_buf[7];
	  rm_info.ICRA_buff_debuff_zone_status.F1_zone_status = data & 0x01;
	  rm_info.ICRA_buff_debuff_zone_status.F1_zone_buff_debuff_status = data>>1 & 0x07;
	  rm_info.ICRA_buff_debuff_zone_status.F2_zone_status = data>>4 & 0x01;
	  rm_info.ICRA_buff_debuff_zone_status.F2_zone_buff_debuff_status = data>>5 & 0x07;
	  rm_info.ICRA_buff_debuff_zone_status.F3_zone_status = data>>8 & 0x01;
	  rm_info.ICRA_buff_debuff_zone_status.F3_zone_buff_debuff_status = data>>9 & 0x07;
	  rm_info.ICRA_buff_debuff_zone_status.F4_zone_status = data>>12 & 0x01;
	  rm_info.ICRA_buff_debuff_zone_status.F4_zone_buff_debuff_status = data>>13 & 0x07;
	  rm_info.ICRA_buff_debuff_zone_status.F5_zone_status = data>>16 & 0x01;
	  rm_info.ICRA_buff_debuff_zone_status.F5_zone_buff_debuff_status = data>>17 & 0x07;
	  rm_info.ICRA_buff_debuff_zone_status.F6_zone_status = data>>20 & 0x01;
	  rm_info.ICRA_buff_debuff_zone_status.F6_zone_buff_debuff_status = data>>21 & 0x07;
	  rm_info.ICRA_buff_debuff_zone_status.red1_bullet_left = comm_usart_rx_buf[11]<<8 | comm_usart_rx_buf[10];
	  rm_info.ICRA_buff_debuff_zone_status.red2_bullet_left = comm_usart_rx_buf[13]<<8 | comm_usart_rx_buf[12];
	  rm_info.ICRA_buff_debuff_zone_status.blue1_bullet_left = comm_usart_rx_buf[15]<<8 | comm_usart_rx_buf[14];
	  rm_info.ICRA_buff_debuff_zone_status.blue2_bullet_left = comm_usart_rx_buf[17]<<8 | comm_usart_rx_buf[16];
}

//场地事件数据 字节偏移量 7-10
void event_data_get()
{
    rm_info.event_data.event_type =(comm_usart_rx_buf[10]<<24) | (comm_usart_rx_buf[9]<<16) | (comm_usart_rx_buf[8]<<8) | comm_usart_rx_buf[7];
}

//补给站动作标识 字节偏移量 7-10
void supply_projectile_action_get()
{
    rm_info.supply_projectile_action.supply_projectile_id = comm_usart_rx_buf[7];
    rm_info.supply_projectile_action.supply_robot_id =   comm_usart_rx_buf[8];
    rm_info.supply_projectile_action.supply_projectile_step =   comm_usart_rx_buf[9];
    rm_info.supply_projectile_action.supply_projectile_num = comm_usart_rx_buf[10];
}

//请求补给站补弹子弹：cmd_id (0x0103) 字节偏移量 7-10
//void supply_projectile_booking_get()
//{
//    rm_info.supply_projectile_booking.supply_projectile_id = comm_usart_rx_buf[7];
//    rm_info.supply_projectile_booking.supply_robot_id = comm_usart_rx_buf[8];
//    rm_info.supply_projectile_booking.supply_num = comm_usart_rx_buf[9];
//}

//裁判警告信息 字节偏移量 7-8
void referee_warning_get()
{
	  rm_info.referee_warning.level = comm_usart_rx_buf[7];
	  rm_info.referee_warning.foul_robot_id = comm_usart_rx_buf[8];
}

//飞镖发射口倒计时 字节偏移量 7
void dart_remaining_time_get()
{
	  rm_info.dart_remaining_time.dart_remaining_time = comm_usart_rx_buf[7];
}



//比赛机器人状态 size14 字节偏移量 7-21
void game_robot_status_get()
{
    rm_info.game_robot_status.robot_id = comm_usart_rx_buf[7];
    rm_info.game_robot_status.robot_level = comm_usart_rx_buf[8];
    rm_info.game_robot_status.remain_HP =(comm_usart_rx_buf[10]<<8) | comm_usart_rx_buf[9];
    rm_info.game_robot_status.max_HP = (comm_usart_rx_buf[12]<<8) | comm_usart_rx_buf[11];
    rm_info.game_robot_status.shooter_id1_17mm_cooling_rate = (comm_usart_rx_buf[14]<<8) | comm_usart_rx_buf[13];
    rm_info.game_robot_status.shooter_id1_17mm_cooling_limit = (comm_usart_rx_buf[16]<<8) | comm_usart_rx_buf[15];
    rm_info.game_robot_status.shooter_id1_17mm_speed_limit = (comm_usart_rx_buf[18]<<8) | comm_usart_rx_buf[17];
    rm_info.game_robot_status.shooter_id2_17mm_cooling_rate = (comm_usart_rx_buf[20]<<8) | comm_usart_rx_buf[19];
    rm_info.game_robot_status.shooter_id2_17mm_cooling_limit = (comm_usart_rx_buf[22]<<8) | comm_usart_rx_buf[21];
    rm_info.game_robot_status.shooter_id2_17mm_speed_limit = (comm_usart_rx_buf[24]<<8) | comm_usart_rx_buf[23];
    rm_info.game_robot_status.shooter_id1_42mm_cooling_rate = (comm_usart_rx_buf[26]<<8) | comm_usart_rx_buf[25];
	  rm_info.game_robot_status.shooter_id1_42mm_cooling_limit = (comm_usart_rx_buf[28]<<8) | comm_usart_rx_buf[27];
	  rm_info.game_robot_status.shooter_id1_42mm_speed_limit = (comm_usart_rx_buf[30]<<8) | comm_usart_rx_buf[29];
	  rm_info.game_robot_status.chassis_power_limit = (comm_usart_rx_buf[26]<<8) | comm_usart_rx_buf[25];
	  rm_info.game_robot_status.mains_power_gimbal_output = comm_usart_rx_buf[27] & 0x01;
	  rm_info.game_robot_status.mains_power_chassis_output = comm_usart_rx_buf[27] & 0x02;
	  rm_info.game_robot_status.mains_power_shooter_output = comm_usart_rx_buf[27] & 0x04;
}

//实时功率热量数据 size 12 字节偏移量 7 - 20
void power_heat_data_get()
{
//	u8 data[4];
    rm_info.power_heat_data.chassis_volt = (comm_usart_rx_buf[8]<<8) | comm_usart_rx_buf[7]; //单位mv
    rm_info.power_heat_data.chassis_current = (comm_usart_rx_buf[10]<<8) | comm_usart_rx_buf[9]; //单位mA

    //获取float型数据
    rm_info.power_heat_data.chassis_power =float_data_get(&comm_usart_rx_buf[11]);	//单位W

    rm_info.power_heat_data.chassis_power_buffer = (comm_usart_rx_buf[16]<<8) | comm_usart_rx_buf[15]; //底盘功率缓冲 单位J
    rm_info.power_heat_data.shooter_id1_17mm_cooling_heat = (comm_usart_rx_buf[18]<<8) | comm_usart_rx_buf[17];
    rm_info.power_heat_data.shooter_id2_17mm_cooling_heat = (comm_usart_rx_buf[20]<<8) | comm_usart_rx_buf[19];
	  rm_info.power_heat_data.shooter_id1_42mm_cooling_heat = (comm_usart_rx_buf[22]<<8) | comm_usart_rx_buf[21];
}

//机器人位置：0x0203 字节偏移量 7-22
void game_robot_pos_get()
{
    //float
    rm_info.game_robot_pos.x = float_data_get(&comm_usart_rx_buf[7]);
    rm_info.game_robot_pos.y = float_data_get(&comm_usart_rx_buf[11]);
    rm_info.game_robot_pos.yaw = float_data_get(&comm_usart_rx_buf[19]);
    rm_info.game_robot_pos.z = float_data_get(&comm_usart_rx_buf[15]);
}

//机器人增益：0x0204 字节偏移量 7
void buff_get()
{
    rm_info.buff.power_rune_buff = comm_usart_rx_buf[7];
}

//空中机器人能量状态：0x0205
void Aerial_robot_energy_get()
{
    rm_info.aerial_robot_energy.attack_time = (comm_usart_rx_buf[8]<<8) | comm_usart_rx_buf[7];;  //可攻击时间
}

//伤害状态
void robot_hurt_get()
{
    rm_info.robot_hurt.armor_id = comm_usart_rx_buf[7] &0x0f;
    rm_info.robot_hurt.hurt_type = (comm_usart_rx_buf[7]>>4) & 0x0f;
}

//实时射击信息：0x0207 字节偏移量 7-12
void shoot_data()
{
    rm_info.shoot_data.bullet_type = comm_usart_rx_buf[7];
	  rm_info.shoot_data.shooter_id = comm_usart_rx_buf[8];
    rm_info.shoot_data.bullet_freq = comm_usart_rx_buf[9];
    //float
    rm_info.shoot_data.bullet_speed = float_data_get(&comm_usart_rx_buf[10]);
}

//子弹剩余发射数:0x0208 字节偏移量7-12
void bullet_remaining_get()
{
	  rm_info.bullet_remaining.bullet_remaining_num_17mm = (comm_usart_rx_buf[8]<<8) | comm_usart_rx_buf[7];
	  rm_info.bullet_remaining.bullet_remaining_num_42mm = (comm_usart_rx_buf[10]<<8) | comm_usart_rx_buf[9];
	  rm_info.bullet_remaining.coin_remaining_num = (comm_usart_rx_buf[12]<<8) | comm_usart_rx_buf[11];
}

//机器人RFID状态:0x0209 字节偏移量 7
void rfid_status_get()
{
	  rm_info.rfid_status.rfid_status = comm_usart_rx_buf[7];
}

//飞镖机器人客户端指令数据:0x020A  字节偏移量 7-18
void dart_client_cmd_get()
{
	  rm_info.dart_client_cmd.dart_launch_opening_status = comm_usart_rx_buf[7];
	  rm_info.dart_client_cmd.dart_attack_target = comm_usart_rx_buf[8];
	  rm_info.dart_client_cmd.target_change_time = (comm_usart_rx_buf[10]<<8) | comm_usart_rx_buf[9];
	  rm_info.dart_client_cmd.first_dart_speed = comm_usart_rx_buf[11];
	  rm_info.dart_client_cmd.second_dart_speed = comm_usart_rx_buf[12];
	  rm_info.dart_client_cmd.third_dart_speed = comm_usart_rx_buf[13];
	  rm_info.dart_client_cmd.fourth_dart_speed = comm_usart_rx_buf[14];
	  rm_info.dart_client_cmd.last_dart_launch_time = (comm_usart_rx_buf[16]<<8) | comm_usart_rx_buf[15];
	  rm_info.dart_client_cmd.operate_launch_cmd_time = (comm_usart_rx_buf[18]<<8) | comm_usart_rx_buf[17];
}

//ID说明 客户端删除图形  机器人间通信:0x0301 数据内容ID:0x0100 字节偏移量 7~14
void client_custom_graphic_delete_get()
{
	rm_info.client_custom_graphic_delete.operate_tpye = comm_usart_rx_buf[13];
	rm_info.client_custom_graphic_delete.layer = comm_usart_rx_buf[14];
}

//ID说明 客户端绘制一个图形 机器人间通信:0x0301 数据内容ID:0x0101 字节偏移量 7~28
void client_custom_graphic_single_get()
{
	rm_info.client_custom_graphic_single.grapic_data_struct.graphic_name[0] = comm_usart_rx_buf[13];
	rm_info.client_custom_graphic_single.grapic_data_struct.graphic_name[1] = comm_usart_rx_buf[14];
	rm_info.client_custom_graphic_single.grapic_data_struct.graphic_name[2] = comm_usart_rx_buf[15];
	
	int j;
	uint32_t a;
	for(j=0;j<4;j++)
	{
		a = a | (comm_usart_rx_buf[16+j] << 8*j);
	}
	rm_info.client_custom_graphic_single.grapic_data_struct.operate_tpye = a & 0x7;
	rm_info.client_custom_graphic_single.grapic_data_struct.graphic_tpye = (a >> 3) & 0x7;
	rm_info.client_custom_graphic_single.grapic_data_struct.layer = (a >> 6) & 0xF;
	rm_info.client_custom_graphic_single.grapic_data_struct.color = (a >> 10) & 0xF;
	rm_info.client_custom_graphic_single.grapic_data_struct.start_angle = (a >> 14) & 0x1FF;
	rm_info.client_custom_graphic_single.grapic_data_struct.end_angle = (a >> 23) & 0x1FF;
	
	uint32_t b;
	for(j=0;j<4;j++)
	{
		b = b | (comm_usart_rx_buf[20+j] << 8*j);
	}
	rm_info.client_custom_graphic_single.grapic_data_struct.width = b & 0x1FF;
	rm_info.client_custom_graphic_single.grapic_data_struct.start_x = (b >> 10) & 0x7FF;
	rm_info.client_custom_graphic_single.grapic_data_struct.start_y = (b >> 21) & 0x7FF;

	uint32_t c;
	for(j=0;j<4;j++)
	{
		c = c | (comm_usart_rx_buf[24+j] << 8*j);
	}
	rm_info.client_custom_graphic_single.grapic_data_struct.radius =  c & 0x3FF;
	rm_info.client_custom_graphic_single.grapic_data_struct.end_x = (c >> 10) & 0x7FF;
	rm_info.client_custom_graphic_single.grapic_data_struct.end_y = (c >> 21) & 0x7FF;
}

//ID说明 客户端绘制二个图形 机器人间通信:0x0301 数据内容ID:0x0102 字节偏移量 7~43
void client_custom_graphic_double_get()
{
	int i,j;
	for(i=0;i<2;i++)
	{
		rm_info.client_custom_graphic_double.grapic_data_struct[i].graphic_name[0] = comm_usart_rx_buf[13+i*15];
		rm_info.client_custom_graphic_double.grapic_data_struct[i].graphic_name[1] = comm_usart_rx_buf[14+i*15];
		rm_info.client_custom_graphic_double.grapic_data_struct[i].graphic_name[2] = comm_usart_rx_buf[15+i*15];
	
		uint32_t a;
		for(j=0;j<4;j++)
		{
			a = a | (comm_usart_rx_buf[16+j+15*i] << 8*j);
		}
		rm_info.client_custom_graphic_double.grapic_data_struct[i].operate_tpye = a & 0x7;
		rm_info.client_custom_graphic_double.grapic_data_struct[i].graphic_tpye = (a >> 3) & 0x7;
		rm_info.client_custom_graphic_double.grapic_data_struct[i].layer = (a >> 6) & 0xF;
		rm_info.client_custom_graphic_double.grapic_data_struct[i].color = (a >> 10) & 0xF;
		rm_info.client_custom_graphic_double.grapic_data_struct[i].start_angle = (a >> 14) & 0x1FF;
		rm_info.client_custom_graphic_double.grapic_data_struct[i].end_angle = (a >> 23) & 0x1FF;
	
		uint32_t b;
		for(j=0;j<4;j++)
		{
			b = b | (comm_usart_rx_buf[20+j+15*i] << 8*j);
		}
		rm_info.client_custom_graphic_double.grapic_data_struct[i].width = b & 0x1FF;
		rm_info.client_custom_graphic_double.grapic_data_struct[i].start_x = (b >> 10) & 0x7FF;
		rm_info.client_custom_graphic_double.grapic_data_struct[i].start_y = (b >> 21) & 0x7FF;
	
		uint32_t c;
		for(j=0;j<4;j++)
		{
			c = c | (comm_usart_rx_buf[24+j+15*i] << 8*j);
		}
		rm_info.client_custom_graphic_double.grapic_data_struct[i].radius =  c & 0x3FF;
		rm_info.client_custom_graphic_double.grapic_data_struct[i].end_x = (c >> 10) & 0x7FF;
		rm_info.client_custom_graphic_double.grapic_data_struct[i].end_y = (c >> 21) & 0x7FF;
	}
}

//ID说明 客户端绘制五个图形 机器人间通信:0x0301 数据内容ID:0x0103 字节偏移量 7~88
void client_custom_graphic_five_get()
{
	int i,j;
	for(i=0;i<5;i++)
	{
		rm_info.client_custom_graphic_five.grapic_data_struct[i].graphic_name[0] = comm_usart_rx_buf[13+i*15];
		rm_info.client_custom_graphic_five.grapic_data_struct[i].graphic_name[1] = comm_usart_rx_buf[14+i*15];
		rm_info.client_custom_graphic_five.grapic_data_struct[i].graphic_name[2] = comm_usart_rx_buf[15+i*15];
	
		uint32_t a;
		for(j=0;j<4;j++)
		{
			a = a | (comm_usart_rx_buf[16+j+15*i] << 8*j);
		}
		rm_info.client_custom_graphic_five.grapic_data_struct[i].operate_tpye = a & 0x7;
		rm_info.client_custom_graphic_five.grapic_data_struct[i].graphic_tpye = (a >> 3) & 0x7;
		rm_info.client_custom_graphic_five.grapic_data_struct[i].layer = (a >> 6) & 0xF;
		rm_info.client_custom_graphic_five.grapic_data_struct[i].color = (a >> 10) & 0xF;
		rm_info.client_custom_graphic_five.grapic_data_struct[i].start_angle = (a >> 14) & 0x1FF;
		rm_info.client_custom_graphic_five.grapic_data_struct[i].end_angle = (a >> 23) & 0x1FF;
	
		uint32_t b;
		for(j=0;j<4;j++)
		{
			b = b | (comm_usart_rx_buf[20+j+15*i] << 8*j);
		}
		rm_info.client_custom_graphic_five.grapic_data_struct[i].width = b & 0x1FF;
		rm_info.client_custom_graphic_five.grapic_data_struct[i].start_x = (b >> 10) & 0x7FF;
		rm_info.client_custom_graphic_five.grapic_data_struct[i].start_y = (b >> 21) & 0x7FF;
	
		uint32_t c;
		for(j=0;j<4;j++)
		{
			c = c | (comm_usart_rx_buf[24+j+15*i] << 8*j);
		}
		rm_info.client_custom_graphic_five.grapic_data_struct[i].radius =  c & 0x3FF;
		rm_info.client_custom_graphic_five.grapic_data_struct[i].end_x = (c >> 10) & 0x7FF;
		rm_info.client_custom_graphic_five.grapic_data_struct[i].end_y = (c >> 21) & 0x7FF;
	}
}

//ID说明 客户端绘制字符 机器人间通信:0x0301 数据内容ID:0x0110 字节偏移量 7~58
void client_custom_character_get()
{
	rm_info.client_custom_character.grapic_data_struct.graphic_name[0] = comm_usart_rx_buf[13];
	rm_info.client_custom_character.grapic_data_struct.graphic_name[1] = comm_usart_rx_buf[14];
	rm_info.client_custom_character.grapic_data_struct.graphic_name[2] = comm_usart_rx_buf[15];
	
	int i,j;
	uint32_t a;
	for(j=0;j<4;j++)
	{
		a = a | (comm_usart_rx_buf[16+j] << 8*j);
	}
	rm_info.client_custom_character.grapic_data_struct.operate_tpye = a & 0x7;
	rm_info.client_custom_character.grapic_data_struct.graphic_tpye = (a >> 3) & 0x7;
	rm_info.client_custom_character.grapic_data_struct.layer = (a >> 6) & 0xF;
	rm_info.client_custom_character.grapic_data_struct.color = (a >> 10) & 0xF;
	rm_info.client_custom_character.grapic_data_struct.start_angle = (a >> 14) & 0x1FF;
	rm_info.client_custom_character.grapic_data_struct.end_angle = (a >> 23) & 0x1FF;
	
	uint32_t b;
	for(j=0;j<4;j++)
	{
		b = b | (comm_usart_rx_buf[20+j] << 8*j);
	}
	rm_info.client_custom_character.grapic_data_struct.width = b & 0x1FF;
	rm_info.client_custom_character.grapic_data_struct.start_x = (b >> 10) & 0x7FF;
	rm_info.client_custom_character.grapic_data_struct.start_y = (b >> 21) & 0x7FF;

	uint32_t c;
	for(j=0;j<4;j++)
	{
		c = c | (comm_usart_rx_buf[24+j] << 8*j);
	}
	rm_info.client_custom_character.grapic_data_struct.radius =  c & 0x3FF;
	rm_info.client_custom_character.grapic_data_struct.end_x = (c >> 10) & 0x7FF;
	rm_info.client_custom_character.grapic_data_struct.end_y = (c >> 21) & 0x7FF;
	
	for(i=0;i<30;i++)
	{
	  rm_info.client_custom_character.data[i] = comm_usart_rx_buf[28+i];
	}
}

//ID说明 客户端绘制七个图形 机器人间通信:0x0301 数据内容ID:0x0104 字节偏移量 7-103
void client_custom_graphic_seven_get()
{
	int i,j;
	for(i=0;i<7;i++)
	{
		rm_info.client_custom_graphic_seven.grapic_data_struct[i].graphic_name[0] = comm_usart_rx_buf[13+i*15];
		rm_info.client_custom_graphic_seven.grapic_data_struct[i].graphic_name[1] = comm_usart_rx_buf[14+i*15];
		rm_info.client_custom_graphic_seven.grapic_data_struct[i].graphic_name[2] = comm_usart_rx_buf[15+i*15];
	
		uint32_t a;
		for(j=0;j<4;j++)
		{
			a = a | (comm_usart_rx_buf[16+j+15*i] << 8*j);
		}
		rm_info.client_custom_graphic_seven.grapic_data_struct[i].operate_tpye = a & 0x7;
		rm_info.client_custom_graphic_seven.grapic_data_struct[i].graphic_tpye = (a >> 3) & 0x7;
		rm_info.client_custom_graphic_seven.grapic_data_struct[i].layer = (a >> 6) & 0xF;
		rm_info.client_custom_graphic_seven.grapic_data_struct[i].color = (a >> 10) & 0xF;
		rm_info.client_custom_graphic_seven.grapic_data_struct[i].start_angle = (a >> 14) & 0x1FF;
		rm_info.client_custom_graphic_seven.grapic_data_struct[i].end_angle = (a >> 23) & 0x1FF;
	
		uint32_t b;
		for(j=0;j<4;j++)
		{
			b = b | (comm_usart_rx_buf[20+j+15*i] << 8*j);
		}
		rm_info.client_custom_graphic_seven.grapic_data_struct[i].width = b & 0x1FF;
		rm_info.client_custom_graphic_seven.grapic_data_struct[i].start_x = (b >> 10) & 0x7FF;
		rm_info.client_custom_graphic_seven.grapic_data_struct[i].start_y = (b >> 21) & 0x7FF;
	
		uint32_t c;
		for(j=0;j<4;j++)
		{
			c = c | (comm_usart_rx_buf[24+j+15*i] << 8*j);
		}
		rm_info.client_custom_graphic_seven.grapic_data_struct[i].radius =  c & 0x3FF;
		rm_info.client_custom_graphic_seven.grapic_data_struct[i].end_x = (c >> 10) & 0x7FF;
		rm_info.client_custom_graphic_seven.grapic_data_struct[i].end_y = (c >> 21) & 0x7FF;
	}
}

//自定义控制器交互数据 字节偏移量 7
void robot_interactive_receive_data_get()
{
		int i;
	  for(i=0;i<30;i++)
	  {
			rm_info.robot_interactive_receive_data.data[i] = comm_usart_rx_buf[7+i];
		}
}

//小地图交互信息 0x0303 字节偏移量 7-21
void robot_command_get()
{
		rm_info.robot_command.target_position_x = float_data_get(&comm_usart_rx_buf[7]);
		rm_info.robot_command.target_position_y = float_data_get(&comm_usart_rx_buf[11]);
		rm_info.robot_command.target_position_z = float_data_get(&comm_usart_rx_buf[15]);
		rm_info.robot_command.commd_keyboard = comm_usart_rx_buf[19];
		rm_info.robot_command.target_robot_ID = (comm_usart_rx_buf[21] << 8) | comm_usart_rx_buf[20];
}

//图传遥控信息 0x0304 字节偏移量 7-18
void robot_control_command_get()
{
		rm_info.robot_control_command.mouse_x = (comm_usart_rx_buf[8] << 8) | comm_usart_rx_buf[7];
		rm_info.robot_control_command.mouse_y = (comm_usart_rx_buf[10] << 8) | comm_usart_rx_buf[9];
		rm_info.robot_control_command.mouse_z = (comm_usart_rx_buf[12] << 8) | comm_usart_rx_buf[11];
		rm_info.robot_control_command.left_button_down = comm_usart_rx_buf[13];
		rm_info.robot_control_command.right_button_down = comm_usart_rx_buf[14];
		rm_info.robot_control_command.keyboard_value = (comm_usart_rx_buf[16] << 8) | comm_usart_rx_buf[15];
		rm_info.robot_control_command.reserved = (comm_usart_rx_buf[18] << 8) | comm_usart_rx_buf[17];
}


//客户端自定义数据cmd_id:0x0301
void student_interactive_header_data_get(void)
{
    rm_info.student_interactive_header_data.data_cmd_id = (comm_usart_rx_buf[8]<<8) |comm_usart_rx_buf[7];
    rm_info.student_interactive_header_data.sender_ID = (comm_usart_rx_buf[10]<<8) |comm_usart_rx_buf[9];
    rm_info.student_interactive_header_data.receiver_ID = (comm_usart_rx_buf[12]<<8) |comm_usart_rx_buf[11];
    switch(rm_info.student_interactive_header_data.data_cmd_id )
        {
        //case Ext_client_custom_data: client_custom_data_get();break;
        case Ext_robot_interactive_data:
            robot_interactive_data_get();
            break;
				case Ext_client_custom_graphic_delete:
					  client_custom_graphic_delete_get();
				    break;
				case Ext_client_custom_graphic_single:
					  client_custom_graphic_delete_get();
				    break;
				case Ext_client_custom_graphic_double:
						client_custom_graphic_double_get();
						break;		
				case Ext_client_custom_graphic_five:
						client_custom_graphic_five_get();
						break;		
				case Ext_client_custom_character:
						client_custom_character_get();
						break;		
				case Ext_client_custom_graphic_seven:
						client_custom_graphic_seven_get();
						break;		
        }
}

//机器人通信-客户端自定义数据 0XD180
void client_custom_data_get(void)
{
    rm_info.client_custom_data.data1 = float_data_get(&comm_usart_rx_buf[13]);
    rm_info.client_custom_data.data2 = float_data_get(&comm_usart_rx_buf[17]);
    rm_info.client_custom_data.data3 = float_data_get(&comm_usart_rx_buf[21]);
    rm_info.client_custom_data.masks = comm_usart_rx_buf[25];
}

//机器人通信-机器人间交互数据 n字节
void robot_interactive_data_get(void)
{
    u8 i;
    for(i=0; i<rm_info.rm_head.data_length-6; i++)
        {
            rm_info.robot_interactive_data.data[i] = comm_usart_rx_buf[i+13];
        }
}

void clear_rx_buf(void)
{
    u8 i;
    for(i=0; i<128; i++)
        {
            comm_usart_rx_buf[i]=0;
        }
}

void clear_tx_buf(void)
{
    u8 i;
    for(i=0; i<128; i++)
        {
            comm_usart_tx_buf[i]=0;
        }
}
void get_robomaster_info()
{
    u16 data_length;
    if(robomaster_heade_Check())
        {
            data_length = 9 + rm_info.rm_head.data_length;
            while(Verify_CRC16_Check_Sum(&comm_usart_rx_buf[0],data_length))
                {
                    switch(rm_info.rm_head.rm_cmd_id)
                        {
                        case Ext_game_state :
                            game_state_get();
                            break;			//比赛状态信息 0X0001
                        case Ext_game_result :
                            game_result_get();
                            break;			//比赛结果数据 0X0002
                        case Ext_game_robot_HP :
                            game_robot_HP_get();
                            break;	//机器人血量数据 0X0003
												case Ext_dart_status :
                            dart_status_get();
                            break;	//飞镖发射状态 0X0004
                        case Ext_ICRA_buff_debuff_zone_status :
                            ICRA_buff_debuff_zone_status_get();
                            break;	//人工智能挑战赛加成与惩罚区状态 0X0005
                        case Ext_event_data :
                            event_data_get();
                            break;	//场地事件数据 0X0101
                        case Ext_supply_projectile_action :
                            supply_projectile_action_get();
                            break;	//补给站动作标识 0X0102
												case Ext_referee_warning :
                            referee_warning_get();
                            break;	//裁判警告信息 0X0104
												case Ext_dart_remaining_time :
                            dart_remaining_time_get();
                            break;	//飞镖发射口倒计时 0X0105
                        case Ext_game_robot_status :
                            game_robot_status_get();
                            break;		 	//比赛机器人状态 0x0201
                        case Ext_power_heat_data :
                            power_heat_data_get();
                            break;			//实时功率热量数据 0x0202
                        case Ext_game_robot_pos :
                            game_robot_pos_get();
                            break;			 //机器人位置 0x0203
                        case Ext_buff :
                            buff_get();
                            break; 				//机器人增益 0x0204
                        case Aerial_robot_energy :
                            Aerial_robot_energy_get();
                            break;			//空中机器人能量状态 0x0205
                        case Ext_robot_hurt :
                            robot_hurt_get();
                            break;		 			//伤害状态 0x0206
                        case Ext_shoot_data :
                            shoot_data();
                            break;					//实时射击信息 0x0207
												case Ext_bullet_remaining :
                            bullet_remaining_get();
                            break;					//子弹剩余发射数 0x0208
												case Ext_rfid_status :
                            rfid_status_get();
                            break;					//机器人RFID状态 0x0209
												case Ext_dart_client_cmd :
                            dart_client_cmd_get();
                            break;					//飞镖机器人客户端指令数据 0x020A
                        case Ext_student_interactive_header_data :
                            student_interactive_header_data_get();
                            break;
												case Robot_interactive_receive_data :
                            robot_interactive_receive_data_get();
                            break;					//交互数据接收信息 0x0302
												case Ext_robot_command :
                            robot_command_get();
                            break;					//小地图交互信息标识 0x0303
												case Ext_robot_control_command :
                            robot_control_command_get();
                            break;					//图传遥控信息 0x0304
                        }
                    clear_rx_buf();
                }
        }
}
//注意发送频率应该为10hz,哨兵不要使用
void client_custom_data_set(float data1,float data2,float data3,u8 data4)
{
    uint16_t i;
    u16 crc16;
    u8 red_or_blue;
    if(rm_info.game_robot_status.robot_id>7)
        {
            red_or_blue = 6;
        }
    else if(rm_info.game_robot_status.robot_id<=7)
        {
            red_or_blue = 0;
        }

    send_data_length = 28;

    comm_usart_tx_buf[0] = 0xA5;
    comm_usart_tx_buf[1] = client_custom_data_length & 0xff;
    comm_usart_tx_buf[2] = (client_custom_data_length >> 8) & 0xff;
    comm_usart_tx_buf[3] = 1;
    comm_usart_tx_buf[4] = Get_CRC8_Check_Sum(&comm_usart_tx_buf[0],4,CRC8_INIT);

    comm_usart_tx_buf[5] = Ext_student_interactive_header_data & 0xff;
    comm_usart_tx_buf[6] = (Ext_student_interactive_header_data>>8) & 0xff;

    comm_usart_tx_buf[7] = Ext_client_custom_data & 0xff;
    comm_usart_tx_buf[8] = (Ext_client_custom_data >> 8 ) & 0xff;


    comm_usart_tx_buf[9] = (rm_info.game_robot_status.robot_id+red_or_blue) & 0xff;
    comm_usart_tx_buf[10] = ((rm_info.game_robot_status.robot_id+red_or_blue) >> 8)  & 0xff;

    comm_usart_tx_buf[11] = (rm_info.game_robot_status.robot_id+red_or_blue) & 0xff;
    comm_usart_tx_buf[12] = 0x01;

    comm_usart_tx_buf[13]  = ((u8*)(&data1))[0];
    comm_usart_tx_buf[14]  = ((u8*)(&data1))[1];
    comm_usart_tx_buf[15]  = ((u8*)(&data1))[2];
    comm_usart_tx_buf[16]  = ((u8*)(&data1))[3];

    comm_usart_tx_buf[17]  = ((u8*)(&data2))[0];
    comm_usart_tx_buf[18]  = ((u8*)(&data2))[1];
    comm_usart_tx_buf[19]  = ((u8*)(&data2))[2];
    comm_usart_tx_buf[20]  = ((u8*)(&data2))[3];

    comm_usart_tx_buf[21]  = ((u8*)(&data3))[0];
    comm_usart_tx_buf[22]  = ((u8*)(&data3))[1];
    comm_usart_tx_buf[23]  = ((u8*)(&data3))[2];
    comm_usart_tx_buf[24]  = ((u8*)(&data3))[3];

    comm_usart_tx_buf[25] = data4;

    crc16 = Get_CRC16_Check_Sum(&comm_usart_tx_buf[0],26,CRC16_INIT);

    comm_usart_tx_buf[26] = crc16 & 0x00ff;
    comm_usart_tx_buf[27] = (crc16>>8) & 0xff;

    for(i=0; i<28; i++)
        {
            while((UART8->SR&USART_FLAG_TC)==0);//发送完成
            USART_SendData(UART8,comm_usart_tx_buf[i]);
        }
}
//数据段 发送数组不超过113
void robot_interactive_data_send(u16 re_id,u8 *dat,u8 size_length)
{
    u8 i,red_or_blue;
    u16 crc16;

    if(rm_info.game_robot_status.robot_id>7)
        {
            red_or_blue = 10;
        }
    else if(rm_info.game_robot_status.robot_id<=7)
        {
            red_or_blue = 0;
        }

    send_data_length = size_length+15;

    comm_usart_tx_buf[0] = Cmd_sof;
    comm_usart_tx_buf[1] = (size_length+6) & 0xff;
    comm_usart_tx_buf[2] = ((size_length+6) >> 8) & 0xff;
    comm_usart_tx_buf[3] = rm_info.rm_head.seq+1;
    comm_usart_tx_buf[4] = Get_CRC8_Check_Sum(&comm_usart_tx_buf[0],4,CRC8_INIT);

    comm_usart_tx_buf[5] = Ext_student_interactive_header_data & 0xff;
    comm_usart_tx_buf[6] = (Ext_student_interactive_header_data>>8) & 0xff;

    comm_usart_tx_buf[7] = Ext_robot_interactive_data & 0xff;
    comm_usart_tx_buf[8] = (Ext_robot_interactive_data >> 8 ) & 0xff;

    comm_usart_tx_buf[9] = (rm_info.game_robot_status.robot_id) & 0xff;
    comm_usart_tx_buf[10] = ((rm_info.game_robot_status.robot_id )>> 8)  & 0xff;


    //接收者的id
    comm_usart_tx_buf[11] = (red_or_blue+re_id) & 0xff;
    comm_usart_tx_buf[12] = ((red_or_blue+re_id )>> 8)  & 0xff;
    for(i=0; i< size_length; i++)
        {
            comm_usart_tx_buf[13+i] = dat[i];
        }
    crc16 = Get_CRC16_Check_Sum(&comm_usart_tx_buf[0],size_length+13,CRC16_INIT);
    comm_usart_tx_buf[size_length+13] = crc16 & 0xff;
    comm_usart_tx_buf[size_length+14] = (crc16>>8) & 0xff;
}

void UART8_IRQHandler(void)
{
    u8 Res;
    //接收中断
    if((USART_GetITStatus(UART8, USART_IT_RXNE) != RESET) )
        {
            Res =USART_ReceiveData(UART8);//(USART1->DR);	//读取接收到的数据
            if((uart8_len_cr&0x8000)==0)//接收未完成
                {
                    if(uart8_len_cr&0x4000)//接收到了0x0d
                        {
                            if(Res!=0x0a)uart8_len_cr=0;//接收错误,重新开始
                            else uart8_len_cr|=0x8000;	//接收完成了
                        }
                    else //还没收到0X0D
                        {
                            if(Res==0x0d)uart8_len_cr|=0x4000;
                            else
                                {
                                    comm_usart_rx_buf[uart8_len_cr&0X3FFF]=Res ;
                                    uart8_len_cr++;
                                    if(uart8_len_cr>(128-1))uart8_len_cr=0;//接收数据错误,重新开始接收
                                }
                        }
                    if(comm_usart_rx_buf[0] != Cmd_sof) //等待数据到来
                        {
                            uart8_len_cr = 0;
                        }
                }
        }
}


