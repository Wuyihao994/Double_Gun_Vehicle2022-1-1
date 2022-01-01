#ifndef __ROBOMASTER_PROTOCOL_H
#define __ROBOMASTER_PROTOCOL_H

#include "stm32f4xx_conf.h"

#define RX_LENGTH 128
#define TX_LENGTH 30
//rm的数据按低位在前写的
#define    	Cmd_sof          0xA5

#define client_custom_data_length  19		//客户端自定义字节长度 6+12+1

#define Ext_game_state  0X0001	//比赛状态信息
#define	Ext_game_result 0X0002	//比赛结果数据
#define Ext_game_robot_HP 0X0003		//机器人血量数据
#define Ext_dart_status  0x0004  //飞镖发射状态
#define Ext_ICRA_buff_debuff_zone_status  0x0005   //人工智能挑战赛加成与惩罚区状态
#define Ext_event_data 0X0101	//场地事件数据
#define Ext_supply_projectile_action 0X0102	//补给站动作标识
//#define Ext_supply_projectile_booking 0x0103 ////请求补给站补弹子弹：cmd_id (0x0103)
#define Ext_referee_warning  0x0104  //裁判警告信息
#define Ext_dart_remaining_time  0x0105  //飞镖发射口倒计时
#define Ext_game_robot_status	0x0201 //比赛机器人状态
#define Ext_power_heat_data 0x0202	//实时功率热量数据
#define	Ext_game_robot_pos  0x0203 //机器人位置：0x0203
#define Ext_buff 0x0204 //机器人增益：0x0204
#define	Aerial_robot_energy 0x0205	//空中机器人能量状态：0x0205
#define Ext_robot_hurt 0x0206 //伤害状态
#define Ext_shoot_data 0x0207 //实时射击信息：0x0207
#define Ext_bullet_remaining  0x0208  //子弹剩余发射数
#define Ext_rfid_status  0x0209  //机器人RFID状态
#define Ext_dart_client_cmd  0x020A  //飞镖机器人客户端指令数据
#define Ext_student_interactive_header_data 0x0301 //机器人间交互数据
#define Robot_interactive_receive_data  0x0302  //交互数据接收信息
#define Ext_robot_command  0x0303  //小地图交互信息标识
#define Ext_robot_control_command 0x0304  //图传遥控信息
//机器人间交互数据 内容id
#define		Ext_client_custom_data 0xD180		//0xD180   ,客户端自定义数据,内容 ID
#define		Ext_robot_interactive_data 0x020B 	//0x0200~0x02F ,交互数据，内容 ID,
//机器人间交互数据 内容id
#define	Ext_client_custom_graphic_delete 0x0100		//ID说明 客户端删除图形 机器人间通信:0x0301
#define	Ext_client_custom_graphic_single 0x0101		//ID说明 客户端绘制一个图形 机器人间通信: 0x0301
#define	Ext_client_custom_graphic_double 0x0102	 //ID说明 客户端绘制二个图形 机器人间通信: 0x0301
#define	Ext_client_custom_graphic_five 0x0103		//ID说明 客户端绘制五个图形 机器人间通信: 0x0301
#define	Ext_client_custom_character 0x0110		//ID说明 客户端绘制字符 机器人间通信: 0x0301
#define Ext_client_custom_graphic_seven 0x0104		//ID说明 客户端绘制七个图形 机器人间通信: 0x0301
typedef struct
{
    //针头数据,判断是否等于0xa5
    u8 SOF;
    u16 data_length;
    u8 seq;
    u8 CRC8;
    u16 rm_cmd_id;
} Frame_heade;

//比赛状态信息 0X0001
typedef __packed struct
{
    uint8_t game_type : 4;
    uint8_t game_progress : 4;
    uint16_t stage_remain_time;
	  uint64_t SyncTimeStamp;
} ext_game_status_t;

//比赛结果数据 0X0002
typedef __packed struct
{
    uint8_t winner;
} ext_game_result_t;

//机器人血量数据 0X0003
typedef __packed struct
{	
		uint16_t red_1_robot_HP;
		uint16_t red_2_robot_HP;
		uint16_t red_3_robot_HP;
		uint16_t red_4_robot_HP;
		uint16_t red_5_robot_HP;
		uint16_t red_7_robot_HP;
		uint16_t red_outpost_HP;
		uint16_t red_base_HP;
		uint16_t blue_1_robot_HP;
		uint16_t blue_2_robot_HP;
		uint16_t blue_3_robot_HP;
		uint16_t blue_4_robot_HP;
		uint16_t blue_5_robot_HP;
		uint16_t blue_7_robot_HP;
		uint16_t blue_outpost_HP;
		uint16_t blue_base_HP;
} ext_game_robot_HP_t;

//飞镖发射状态 0X0004
typedef __packed struct
{	
		uint8_t dart_belong; 
		uint16_t stage_remaining_time;
} ext_dart_status_t;

//人工智能挑战赛加成与惩罚区状态 0x0005
typedef __packed struct 
{
		uint8_t F1_zone_status:1;
		uint8_t F1_zone_buff_debuff_status:3; 
		uint8_t F2_zone_status:1; 
		uint8_t F2_zone_buff_debuff_status:3; 
		uint8_t F3_zone_status:1;
		uint8_t F3_zone_buff_debuff_status:3;
		uint8_t F4_zone_status:1; 
		uint8_t F4_zone_buff_debuff_status:3;
		uint8_t F5_zone_status:1; 
		uint8_t F5_zone_buff_debuff_status:3;
		uint8_t F6_zone_status:1;
		uint8_t F6_zone_buff_debuff_status:3;
		uint16_t red1_bullet_left;
		uint16_t red2_bullet_left;
		uint16_t blue1_bullet_left;
		uint16_t blue2_bullet_left;
} ext_ICRA_buff_debuff_zone_status_t;

//场地事件数据 0x0101
typedef __packed struct
{
    uint32_t event_type;
} ext_event_data_t;

//补给站动作标识 0x0102
typedef __packed struct
{
    uint8_t supply_projectile_id;
    uint8_t supply_robot_id;
    uint8_t supply_projectile_step;
    uint8_t supply_projectile_num;
} ext_supply_projectile_action_t;

//请求补给站补弹子弹 0x0103
typedef __packed struct
{
    uint8_t supply_projectile_id;
    uint8_t supply_robot_id;
    uint8_t supply_num;
} ext_supply_projectile_booking_t;

//裁判警告信息 cmd_id(0x0104)
typedef __packed struct
{	
		uint8_t level;
		uint8_t foul_robot_id; 
}	ext_referee_warning_t;

//飞镖发射口倒计时 cmd_id(0x0105)
typedef __packed struct
{	
		uint8_t dart_remaining_time;
} ext_dart_remaining_time_t;

//比赛机器人状态 0x0201
typedef __packed struct
{	
		uint8_t robot_id;
		uint8_t robot_level;
		uint16_t remain_HP;
		uint16_t max_HP;
		uint16_t shooter_id1_17mm_cooling_rate; 
		uint16_t shooter_id1_17mm_cooling_limit;
		uint16_t shooter_id1_17mm_speed_limit;
		uint16_t shooter_id2_17mm_cooling_rate; 
		uint16_t shooter_id2_17mm_cooling_limit;
		uint16_t shooter_id2_17mm_speed_limit;
		uint16_t shooter_id1_42mm_cooling_rate; 
		uint16_t shooter_id1_42mm_cooling_limit;
		uint16_t shooter_id1_42mm_speed_limit;
		uint16_t chassis_power_limit;
		uint8_t mains_power_gimbal_output : 1;
		uint8_t mains_power_chassis_output : 1; 
		uint8_t mains_power_shooter_output : 1; 
} ext_game_robot_status_t;

//实时功率热量数据 0x0202
typedef __packed struct
{
    uint16_t chassis_volt;
    uint16_t chassis_current;
    float chassis_power;
    uint16_t chassis_power_buffer;
    uint16_t shooter_id1_17mm_cooling_heat;
    uint16_t shooter_id2_17mm_cooling_heat;
		uint16_t shooter_id1_42mm_cooling_heat;
} ext_power_heat_data_t;

//机器人位置：0x0203
typedef __packed struct
{
    float x;
    float y;
    float z;
    float yaw;
} ext_game_robot_pos_t;

//机器人增益：0x0204
typedef __packed struct
{
    uint8_t power_rune_buff;
} ext_buff_t;

//空中机器人能量状态：0x0205
typedef __packed struct
{
    uint8_t attack_time;
} aerial_robot_energy_t;

//伤害状态：0x0206
typedef __packed struct
{
    uint8_t armor_id : 4;
    uint8_t hurt_type : 4;
} ext_robot_hurt_t;

//实时射击信息：0x0207
typedef __packed struct
{
    uint8_t bullet_type;
	  uint8_t shooter_id;
    uint8_t bullet_freq;
    float bullet_speed;
} ext_shoot_data_t;

//子弹发剩余发射数 0x0208
typedef __packed struct
{	
		uint16_t bullet_remaining_num_17mm; 
	  uint16_t bullet_remaining_num_42mm; 
	  uint16_t coin_remaining_num;
} ext_bullet_remaining_t;

//机器人RFID状态 0x0209
typedef __packed struct
{	
		uint32_t rfid_status;
} ext_rfid_status_t;

//飞镖机器人客户端指令数据 0x020A
typedef	__packed struct
{	
		uint8_t dart_launch_opening_status;
		uint8_t dart_attack_target;
		uint16_t target_change_time;
		uint8_t first_dart_speed;
		uint8_t second_dart_speed;
		uint8_t third_dart_speed;
		uint8_t fourth_dart_speed;
		uint16_t last_dart_launch_time;
		uint16_t operate_launch_cmd_time;
}  ext_dart_client_cmd_t;

//机器人间交互数据
typedef  struct
{
    //内容id
    uint16_t data_cmd_id;
    uint16_t sender_ID;
    uint16_t receiver_ID;
} ext_student_interactive_header_data_t;

//客户端自定义数据cmd_id:0x0301    内容 ID:0xD180。
typedef  struct
{
    float data1;
    float data2;
    float data3;
    uint8_t masks;
} client_custom_data_t;

//数据段 学生机器人间通信 cmdid 0x0301，内容 ID:0x0200~0x02FF

//交互数据
typedef __packed struct
{
    uint8_t data[113];
} robot_interactive_data_t;

//客户端删除图形
typedef __packed struct
{
		uint8_t operate_tpye;
		uint8_t layer;
} ext_client_custom_graphic_delete_t;

//图形数据
typedef __packed struct
{ 
		uint8_t graphic_name[3]; 
		uint32_t operate_tpye:3; 
		uint32_t graphic_tpye:3; 
		uint32_t layer:4; 
		uint32_t color:4; 
		uint32_t start_angle:9;
		uint32_t end_angle:9;
		uint32_t width:10; 
		uint32_t start_x:11; 
		uint32_t start_y:11; 
		uint32_t radius:10; 
		uint32_t end_x:11; 
		uint32_t end_y:11; 
} graphic_data_struct_t;

//客户端绘制一个图形
typedef __packed struct
{
		graphic_data_struct_t grapic_data_struct;
} ext_client_custom_graphic_single_t;

//客户端绘制二个图形
typedef __packed struct
{
		graphic_data_struct_t grapic_data_struct[2];
} ext_client_custom_graphic_double_t;

//客户端绘制五个图形
typedef __packed struct
{
		graphic_data_struct_t grapic_data_struct[5];
} ext_client_custom_graphic_five_t;

//客户端绘制字符
typedef __packed struct
{
		graphic_data_struct_t grapic_data_struct;
		uint8_t data[30];
} ext_client_custom_character_t;

//客户端绘制七个图形
typedef __packed struct
{
		graphic_data_struct_t grapic_data_struct[7];
} ext_client_custom_graphic_seven_t;

//交互数据接收信息：0x0302  发送频率：上限30HZ
typedef __packed struct
{
		uint8_t data[30];
} robot_interactive_receive_data_t;

//小地图交互信息标识：0x0303
typedef __packed struct
{
		float target_position_x;
		float target_position_y;
		float target_position_z;
		uint8_t commd_keyboard;
		uint16_t target_robot_ID;
} ext_robot_command_t;

//图传遥控信息：0x0304
typedef __packed struct
{
		int16_t mouse_x;
		int16_t mouse_y;
		int16_t mouse_z;
		int8_t left_button_down;
		int8_t right_button_down;
		uint16_t keyboard_value;
		uint16_t reserved;
} ext_robot_control_command_t;

typedef struct
{
    Frame_heade rm_head;
    ext_game_status_t  game_status; //比赛状态信息 0X0001
    ext_game_result_t game_result; //比赛结果数据 0X0002
    ext_game_robot_HP_t  game_robot_HP; //机器人血量数据 0X0003
    ext_dart_status_t  dart_status;  //飞镖发射状态 0x0004
	  ext_ICRA_buff_debuff_zone_status_t  ICRA_buff_debuff_zone_status;  //人工智能挑战赛加成与惩罚区状态  0x0005
	  ext_event_data_t event_data; //场地事件数据 0X0101
    ext_supply_projectile_action_t  supply_projectile_action; //补给站动作标识 0X0102
//    ext_supply_projectile_booking_t supply_projectile_booking; //请求补给站补弹子弹0x0103
    ext_referee_warning_t  referee_warning;  //裁判警告信息  0x0104
	  ext_dart_remaining_time_t  dart_remaining_time;  //飞镖发射口倒计时 0x0105
	  ext_game_robot_status_t  game_robot_status; //比赛机器人状态 0x0201
    ext_power_heat_data_t power_heat_data; //实时功率热量数据 0x0202
    ext_game_robot_pos_t  game_robot_pos; //机器人位置：0x0203
    ext_buff_t buff;  //机器人增益：0x0204
    aerial_robot_energy_t aerial_robot_energy; ////空中机器人能量状态：0x0205
    ext_robot_hurt_t robot_hurt; //伤害状态：0x0206
    ext_shoot_data_t shoot_data; //实时射击信息：0x0207
	  ext_bullet_remaining_t  bullet_remaining;  //子弹剩余发射数  0x0208
	  ext_rfid_status_t  rfid_status;  //机器人RFID状态  0x0209
	  ext_dart_client_cmd_t  dart_client_cmd;  //飞镖机器人客户端指令交互数据  0x020A
		
    //客户端自定义数据cmd_id:0x0301
    ext_student_interactive_header_data_t  student_interactive_header_data;
    client_custom_data_t client_custom_data; //客户端自定义数据cmd_id:0x0301    内容 ID:0xD180
    robot_interactive_data_t robot_interactive_data;  //交互数据
		ext_client_custom_graphic_delete_t  client_custom_graphic_delete;  //客户端删除图形
		graphic_data_struct_t  graphic_data_struct;  //图形数据
    ext_client_custom_graphic_single_t  client_custom_graphic_single;  //客户端绘制一个图形
    ext_client_custom_graphic_double_t  client_custom_graphic_double;  //客户端绘制二个图形
    ext_client_custom_graphic_five_t  client_custom_graphic_five;  //客户端绘制五个图形
    ext_client_custom_character_t  client_custom_character;  //客户端绘制字符
    ext_client_custom_graphic_seven_t  client_custom_graphic_seven;  //客户端绘制七个图形
		robot_interactive_receive_data_t  robot_interactive_receive_data;  //交互数据接收信息  0x0302
    ext_robot_command_t  robot_command;  //小地图交互信息标识  0x0303
		ext_robot_control_command_t  robot_control_command;  //图传遥控信息  0x0304
} RoboMaster;


u8 robomaster_heade_Check(void);			//针头检验------字节偏移量 0-6
void game_state_get(void);					//比赛状态信息
void game_result_get(void);					//比赛结果数据
void game_robot_HP_get(void);		//机器人血量数据
void event_data_get(void);					//场地事件数据
void supply_projectile_action_get(void); 	//补给站动作标识
void supply_projectile_booking_get(void);   //请求补给站补弹子弹：cmd_id (0x0103)
void game_robot_status_get(void);			//比赛机器人状态
void power_heat_data_get(void);				//实时功率热量数据
void game_robot_pos_get(void);				//机器人位置：0x0203
void buff_get(void);					//机器人增益：0x0204
void Aerial_robot_energy_get(void);			//空中机器人能量状态：0x0205
void robot_hurt_get(void);					//伤害状态
void shoot_data(void);						//实时射击信息：0x0207
void dart_status_get(void);       //飞镖发射状态: 0x0004
void ICRA_buff_debuff_zone_status_get(void);  //人工智能挑战赛加成与惩罚区状态:0x0005
void referee_warning_get(void);   //裁判警告信息:0x0104
void dart_remaining_time_get(void);   //飞镖发射口倒计时 0x0105
void bullet_remaining_get(void);  //子弹剩余发射数:0x0208
void rfid_status_get(void);  //机器人RFID状态:0x0209 
void dart_client_cmd_get(void);  //飞镖机器人客户端指令数据:0x020A

void client_custom_graphic_delete_get(void);    //ID说明 客户端删除图形  机器人间通信:0x0301 数据内容ID:0x0100 字节偏移量 
void client_custom_graphic_single_get(void);		//ID说明 客户端绘制一个图形
void client_custom_graphic_double_get(void);		//ID说明 客户端绘制二个图形
void client_custom_graphic_five_get(void);		//ID说明 客户端绘制五个图形
void client_custom_character_get(void);		//ID说明 客户端绘制字符
void robot_interactive_receive_data_get(void);		//自定义控制器交互数据
void robot_command_get(void);		//小地图交互信息
void robot_control_command_get(void);		//图传遥控信息

void student_interactive_header_data_get(void); //客户端自定义数据cmd_id:0x0301

void client_custom_data_get(void);

void robot_interactive_data_get(void);


void client_custom_data_set(float data1,float data2,float data3,u8 data4);

void robot_interactive_data_send(u16 re_id,u8 *dat,u8 size_length);

void clear_rx_buf(void);
void clear_tx_buf(void);
float float_data_get(u8 *dat);

unsigned char Get_CRC8_Check_Sum(unsigned char *pchMessage,unsigned int dwLength,unsigned char ucCRC8);
unsigned int Verify_CRC8_Check_Sum(unsigned char *pchMessage, unsigned int dwLength);
uint16_t Get_CRC16_Check_Sum(uint8_t *pchMessage,uint32_t dwLength,uint16_t wCRC);
uint32_t Verify_CRC16_Check_Sum(uint8_t *pchMessage, uint32_t dwLength);

void get_robomaster_info(void);

extern u8 comm_usart_rx_buf[RX_LENGTH];
extern u8 comm_usart_tx_buf[TX_LENGTH];

extern uint16_t  wExpected;
extern u8 uart8_len_cr;
extern RoboMaster rm_info;
extern u8 send_data_length;
extern u8 info_mode;

extern const unsigned char CRC8_INIT;
extern const uint16_t CRC16_INIT ;
extern const unsigned char CRC8_TAB[256];
extern const uint16_t wCRC_Table[256];

#endif
