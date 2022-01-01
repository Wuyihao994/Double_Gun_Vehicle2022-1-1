#ifndef __VOFA_PROTOCOL_H
#define __VOFA_PROTOCOL_H

#include "stdio.h"
#include "stm32f4xx_conf.h"

typedef union
{
    float float_t;
    uint8_t uint8_t[4];
} send_float;

void vofa_firewater_output(float data1,float data2,float data3);
void vofa_justfloat_output(float *data,uint8_t num); 

#endif
