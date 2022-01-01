#ifndef __CAN_H
#define __CAN_H

#include "stm32f4xx_conf.h"

#define REDUCTION_RATIO_3508 3591.0f/187.0f;

extern float default_yaw;

typedef struct{
	int16_t moto_current;
	int16_t moto_speed;
	int8_t moto_temperature;
	int32_t moto_total_angle;
	int32_t moto_total_angle_yaw;
	float zero_total_angle;
	
	uint16_t moto_raw_angle;
	uint16_t moto_raw_last_angle;
	uint16_t moto_angle;
	uint16_t moto_offset_angle;
	uint16_t default_zero_angle;//ƒ¨»œ¡„µ„
	int32_t round_count;
}moto_info;

typedef struct{
	uint16_t cap_power_set;
	uint16_t cap_power_output;
	uint16_t cap_voltage_output;
	uint16_t cap_current_output;
	
}supercap_info;

typedef struct{
	uint16_t res;
	uint16_t can;
	float x;
	float y;
	float z;
	float yaw;
	float gyro;
}bmi088_info;

typedef enum{
	CAN_TX_MOTO3508_1_4 = 0x200,
	CAN_TX_MOTO6020_1_4 = 0x1FF,
	
	CAN_RX_MOTO3508_LF = 0x201,
	CAN_RX_MOTO3508_LB = 0x202,
	CAN_RX_MOTO3508_RB = 0x203,
	CAN_RX_MOTO3508_RF = 0x204,
	
	CAN_RX_MOTO6020_Y = 0x205,
	CAN_RX_MOTO6020_P = 0x206,
	CAN_RX_MOTO2006_RV = 0x207,
	CAN_RX_MOTO3508_6 = 0x208,
	
	CAN_RX_BMI088_Z = 0x303,
	CAN_RX_BMI088_YAW = 0x304,
}CAN_Message_ID;

typedef union
{
	float power_float_t;
	uint8_t power_uint8_t[4];
}send_power_float;

typedef union
{
  float bmi088_float_t;
  uint8_t bmi088_uint8_t[4];
}bmi088_float;

extern moto_info moto_chassis_info[4];
extern moto_info moto_gimbal_info[2];
extern bmi088_info bmi088_infomation;
extern moto_info moto_revolver_info;

void can1_init(void);
void can2_init(void);
void power_init(void);
void can_mes_send(CAN_TypeDef* CANx,uint32_t StdId,int16_t *info);
void supercap_infomation_process(supercap_info *supercap_infomation,CanRxMsg *RxMessage);
void bmi088_z_infomation_process(bmi088_info *bmi088_infomation,CanRxMsg *RxMessage);
void bmi088_yaw_infomation_process(bmi088_info *bmi088_infomation,CanRxMsg *RxMessage);
void moto_infomation_process(moto_info *moto_infomation,CanRxMsg *RxMessage);

#endif
