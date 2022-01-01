#ifndef __ROBOMASTER_PROTOCOL_H
#define __ROBOMASTER_PROTOCOL_H

#include "stm32f4xx_conf.h"

#define RX_LENGTH 128
#define TX_LENGTH 30
//rm�����ݰ���λ��ǰд��
#define    	Cmd_sof          0xA5

#define client_custom_data_length  19		//�ͻ����Զ����ֽڳ��� 6+12+1

#define Ext_game_state  0X0001	//����״̬��Ϣ
#define	Ext_game_result 0X0002	//�����������
#define Ext_game_robot_HP 0X0003		//������Ѫ������
#define Ext_dart_status  0x0004  //���ڷ���״̬
#define Ext_ICRA_buff_debuff_zone_status  0x0005   //�˹�������ս���ӳ���ͷ���״̬
#define Ext_event_data 0X0101	//�����¼�����
#define Ext_supply_projectile_action 0X0102	//����վ������ʶ
//#define Ext_supply_projectile_booking 0x0103 ////���󲹸�վ�����ӵ���cmd_id (0x0103)
#define Ext_referee_warning  0x0104  //���о�����Ϣ
#define Ext_dart_remaining_time  0x0105  //���ڷ���ڵ���ʱ
#define Ext_game_robot_status	0x0201 //����������״̬
#define Ext_power_heat_data 0x0202	//ʵʱ������������
#define	Ext_game_robot_pos  0x0203 //������λ�ã�0x0203
#define Ext_buff 0x0204 //���������棺0x0204
#define	Aerial_robot_energy 0x0205	//���л���������״̬��0x0205
#define Ext_robot_hurt 0x0206 //�˺�״̬
#define Ext_shoot_data 0x0207 //ʵʱ�����Ϣ��0x0207
#define Ext_bullet_remaining  0x0208  //�ӵ�ʣ�෢����
#define Ext_rfid_status  0x0209  //������RFID״̬
#define Ext_dart_client_cmd  0x020A  //���ڻ����˿ͻ���ָ������
#define Ext_student_interactive_header_data 0x0301 //�����˼佻������
#define Robot_interactive_receive_data  0x0302  //�������ݽ�����Ϣ
#define Ext_robot_command  0x0303  //С��ͼ������Ϣ��ʶ
#define Ext_robot_control_command 0x0304  //ͼ��ң����Ϣ
//�����˼佻������ ����id
#define		Ext_client_custom_data 0xD180		//0xD180   ,�ͻ����Զ�������,���� ID
#define		Ext_robot_interactive_data 0x020B 	//0x0200~0x02F ,�������ݣ����� ID,
//�����˼佻������ ����id
#define	Ext_client_custom_graphic_delete 0x0100		//ID˵�� �ͻ���ɾ��ͼ�� �����˼�ͨ��:0x0301
#define	Ext_client_custom_graphic_single 0x0101		//ID˵�� �ͻ��˻���һ��ͼ�� �����˼�ͨ��: 0x0301
#define	Ext_client_custom_graphic_double 0x0102	 //ID˵�� �ͻ��˻��ƶ���ͼ�� �����˼�ͨ��: 0x0301
#define	Ext_client_custom_graphic_five 0x0103		//ID˵�� �ͻ��˻������ͼ�� �����˼�ͨ��: 0x0301
#define	Ext_client_custom_character 0x0110		//ID˵�� �ͻ��˻����ַ� �����˼�ͨ��: 0x0301
#define Ext_client_custom_graphic_seven 0x0104		//ID˵�� �ͻ��˻����߸�ͼ�� �����˼�ͨ��: 0x0301
typedef struct
{
    //��ͷ����,�ж��Ƿ����0xa5
    u8 SOF;
    u16 data_length;
    u8 seq;
    u8 CRC8;
    u16 rm_cmd_id;
} Frame_heade;

//����״̬��Ϣ 0X0001
typedef __packed struct
{
    uint8_t game_type : 4;
    uint8_t game_progress : 4;
    uint16_t stage_remain_time;
	  uint64_t SyncTimeStamp;
} ext_game_status_t;

//����������� 0X0002
typedef __packed struct
{
    uint8_t winner;
} ext_game_result_t;

//������Ѫ������ 0X0003
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

//���ڷ���״̬ 0X0004
typedef __packed struct
{	
		uint8_t dart_belong; 
		uint16_t stage_remaining_time;
} ext_dart_status_t;

//�˹�������ս���ӳ���ͷ���״̬ 0x0005
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

//�����¼����� 0x0101
typedef __packed struct
{
    uint32_t event_type;
} ext_event_data_t;

//����վ������ʶ 0x0102
typedef __packed struct
{
    uint8_t supply_projectile_id;
    uint8_t supply_robot_id;
    uint8_t supply_projectile_step;
    uint8_t supply_projectile_num;
} ext_supply_projectile_action_t;

//���󲹸�վ�����ӵ� 0x0103
typedef __packed struct
{
    uint8_t supply_projectile_id;
    uint8_t supply_robot_id;
    uint8_t supply_num;
} ext_supply_projectile_booking_t;

//���о�����Ϣ cmd_id(0x0104)
typedef __packed struct
{	
		uint8_t level;
		uint8_t foul_robot_id; 
}	ext_referee_warning_t;

//���ڷ���ڵ���ʱ cmd_id(0x0105)
typedef __packed struct
{	
		uint8_t dart_remaining_time;
} ext_dart_remaining_time_t;

//����������״̬ 0x0201
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

//ʵʱ������������ 0x0202
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

//������λ�ã�0x0203
typedef __packed struct
{
    float x;
    float y;
    float z;
    float yaw;
} ext_game_robot_pos_t;

//���������棺0x0204
typedef __packed struct
{
    uint8_t power_rune_buff;
} ext_buff_t;

//���л���������״̬��0x0205
typedef __packed struct
{
    uint8_t attack_time;
} aerial_robot_energy_t;

//�˺�״̬��0x0206
typedef __packed struct
{
    uint8_t armor_id : 4;
    uint8_t hurt_type : 4;
} ext_robot_hurt_t;

//ʵʱ�����Ϣ��0x0207
typedef __packed struct
{
    uint8_t bullet_type;
	  uint8_t shooter_id;
    uint8_t bullet_freq;
    float bullet_speed;
} ext_shoot_data_t;

//�ӵ���ʣ�෢���� 0x0208
typedef __packed struct
{	
		uint16_t bullet_remaining_num_17mm; 
	  uint16_t bullet_remaining_num_42mm; 
	  uint16_t coin_remaining_num;
} ext_bullet_remaining_t;

//������RFID״̬ 0x0209
typedef __packed struct
{	
		uint32_t rfid_status;
} ext_rfid_status_t;

//���ڻ����˿ͻ���ָ������ 0x020A
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

//�����˼佻������
typedef  struct
{
    //����id
    uint16_t data_cmd_id;
    uint16_t sender_ID;
    uint16_t receiver_ID;
} ext_student_interactive_header_data_t;

//�ͻ����Զ�������cmd_id:0x0301    ���� ID:0xD180��
typedef  struct
{
    float data1;
    float data2;
    float data3;
    uint8_t masks;
} client_custom_data_t;

//���ݶ� ѧ�������˼�ͨ�� cmdid 0x0301������ ID:0x0200~0x02FF

//��������
typedef __packed struct
{
    uint8_t data[113];
} robot_interactive_data_t;

//�ͻ���ɾ��ͼ��
typedef __packed struct
{
		uint8_t operate_tpye;
		uint8_t layer;
} ext_client_custom_graphic_delete_t;

//ͼ������
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

//�ͻ��˻���һ��ͼ��
typedef __packed struct
{
		graphic_data_struct_t grapic_data_struct;
} ext_client_custom_graphic_single_t;

//�ͻ��˻��ƶ���ͼ��
typedef __packed struct
{
		graphic_data_struct_t grapic_data_struct[2];
} ext_client_custom_graphic_double_t;

//�ͻ��˻������ͼ��
typedef __packed struct
{
		graphic_data_struct_t grapic_data_struct[5];
} ext_client_custom_graphic_five_t;

//�ͻ��˻����ַ�
typedef __packed struct
{
		graphic_data_struct_t grapic_data_struct;
		uint8_t data[30];
} ext_client_custom_character_t;

//�ͻ��˻����߸�ͼ��
typedef __packed struct
{
		graphic_data_struct_t grapic_data_struct[7];
} ext_client_custom_graphic_seven_t;

//�������ݽ�����Ϣ��0x0302  ����Ƶ�ʣ�����30HZ
typedef __packed struct
{
		uint8_t data[30];
} robot_interactive_receive_data_t;

//С��ͼ������Ϣ��ʶ��0x0303
typedef __packed struct
{
		float target_position_x;
		float target_position_y;
		float target_position_z;
		uint8_t commd_keyboard;
		uint16_t target_robot_ID;
} ext_robot_command_t;

//ͼ��ң����Ϣ��0x0304
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
    ext_game_status_t  game_status; //����״̬��Ϣ 0X0001
    ext_game_result_t game_result; //����������� 0X0002
    ext_game_robot_HP_t  game_robot_HP; //������Ѫ������ 0X0003
    ext_dart_status_t  dart_status;  //���ڷ���״̬ 0x0004
	  ext_ICRA_buff_debuff_zone_status_t  ICRA_buff_debuff_zone_status;  //�˹�������ս���ӳ���ͷ���״̬  0x0005
	  ext_event_data_t event_data; //�����¼����� 0X0101
    ext_supply_projectile_action_t  supply_projectile_action; //����վ������ʶ 0X0102
//    ext_supply_projectile_booking_t supply_projectile_booking; //���󲹸�վ�����ӵ�0x0103
    ext_referee_warning_t  referee_warning;  //���о�����Ϣ  0x0104
	  ext_dart_remaining_time_t  dart_remaining_time;  //���ڷ���ڵ���ʱ 0x0105
	  ext_game_robot_status_t  game_robot_status; //����������״̬ 0x0201
    ext_power_heat_data_t power_heat_data; //ʵʱ������������ 0x0202
    ext_game_robot_pos_t  game_robot_pos; //������λ�ã�0x0203
    ext_buff_t buff;  //���������棺0x0204
    aerial_robot_energy_t aerial_robot_energy; ////���л���������״̬��0x0205
    ext_robot_hurt_t robot_hurt; //�˺�״̬��0x0206
    ext_shoot_data_t shoot_data; //ʵʱ�����Ϣ��0x0207
	  ext_bullet_remaining_t  bullet_remaining;  //�ӵ�ʣ�෢����  0x0208
	  ext_rfid_status_t  rfid_status;  //������RFID״̬  0x0209
	  ext_dart_client_cmd_t  dart_client_cmd;  //���ڻ����˿ͻ���ָ�������  0x020A
		
    //�ͻ����Զ�������cmd_id:0x0301
    ext_student_interactive_header_data_t  student_interactive_header_data;
    client_custom_data_t client_custom_data; //�ͻ����Զ�������cmd_id:0x0301    ���� ID:0xD180
    robot_interactive_data_t robot_interactive_data;  //��������
		ext_client_custom_graphic_delete_t  client_custom_graphic_delete;  //�ͻ���ɾ��ͼ��
		graphic_data_struct_t  graphic_data_struct;  //ͼ������
    ext_client_custom_graphic_single_t  client_custom_graphic_single;  //�ͻ��˻���һ��ͼ��
    ext_client_custom_graphic_double_t  client_custom_graphic_double;  //�ͻ��˻��ƶ���ͼ��
    ext_client_custom_graphic_five_t  client_custom_graphic_five;  //�ͻ��˻������ͼ��
    ext_client_custom_character_t  client_custom_character;  //�ͻ��˻����ַ�
    ext_client_custom_graphic_seven_t  client_custom_graphic_seven;  //�ͻ��˻����߸�ͼ��
		robot_interactive_receive_data_t  robot_interactive_receive_data;  //�������ݽ�����Ϣ  0x0302
    ext_robot_command_t  robot_command;  //С��ͼ������Ϣ��ʶ  0x0303
		ext_robot_control_command_t  robot_control_command;  //ͼ��ң����Ϣ  0x0304
} RoboMaster;


u8 robomaster_heade_Check(void);			//��ͷ����------�ֽ�ƫ���� 0-6
void game_state_get(void);					//����״̬��Ϣ
void game_result_get(void);					//�����������
void game_robot_HP_get(void);		//������Ѫ������
void event_data_get(void);					//�����¼�����
void supply_projectile_action_get(void); 	//����վ������ʶ
void supply_projectile_booking_get(void);   //���󲹸�վ�����ӵ���cmd_id (0x0103)
void game_robot_status_get(void);			//����������״̬
void power_heat_data_get(void);				//ʵʱ������������
void game_robot_pos_get(void);				//������λ�ã�0x0203
void buff_get(void);					//���������棺0x0204
void Aerial_robot_energy_get(void);			//���л���������״̬��0x0205
void robot_hurt_get(void);					//�˺�״̬
void shoot_data(void);						//ʵʱ�����Ϣ��0x0207
void dart_status_get(void);       //���ڷ���״̬: 0x0004
void ICRA_buff_debuff_zone_status_get(void);  //�˹�������ս���ӳ���ͷ���״̬:0x0005
void referee_warning_get(void);   //���о�����Ϣ:0x0104
void dart_remaining_time_get(void);   //���ڷ���ڵ���ʱ 0x0105
void bullet_remaining_get(void);  //�ӵ�ʣ�෢����:0x0208
void rfid_status_get(void);  //������RFID״̬:0x0209 
void dart_client_cmd_get(void);  //���ڻ����˿ͻ���ָ������:0x020A

void client_custom_graphic_delete_get(void);    //ID˵�� �ͻ���ɾ��ͼ��  �����˼�ͨ��:0x0301 ��������ID:0x0100 �ֽ�ƫ���� 
void client_custom_graphic_single_get(void);		//ID˵�� �ͻ��˻���һ��ͼ��
void client_custom_graphic_double_get(void);		//ID˵�� �ͻ��˻��ƶ���ͼ��
void client_custom_graphic_five_get(void);		//ID˵�� �ͻ��˻������ͼ��
void client_custom_character_get(void);		//ID˵�� �ͻ��˻����ַ�
void robot_interactive_receive_data_get(void);		//�Զ����������������
void robot_command_get(void);		//С��ͼ������Ϣ
void robot_control_command_get(void);		//ͼ��ң����Ϣ

void student_interactive_header_data_get(void); //�ͻ����Զ�������cmd_id:0x0301

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
