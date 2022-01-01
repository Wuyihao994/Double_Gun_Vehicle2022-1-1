#include "filter.h"

void first_order_filter_init(first_order_filter_type_t *first_order_filter_type, fp32 frame_period,fp32 num)
{
    first_order_filter_type->frame_period = frame_period;
    first_order_filter_type->num = num;
    first_order_filter_type->input = 0.0f;
    first_order_filter_type->out = 0.0f;
}

void first_order_filter_cali(first_order_filter_type_t *first_order_filter_type, fp32 input)
{
    first_order_filter_type->input = input;
    first_order_filter_type->out =
		first_order_filter_type->num / (first_order_filter_type->num + first_order_filter_type->frame_period) * first_order_filter_type->out + 
		first_order_filter_type->frame_period / (first_order_filter_type->num + first_order_filter_type->frame_period) * first_order_filter_type->input;
}

float kalman_filter( float ResrcData,float ProcessNiose_Q,float MeasureNoise_R)
{
	float R = MeasureNoise_R;
  float Q = ProcessNiose_Q;

  static float x_last;
  float x_mid = x_last;
  float x_now;

  static float p_last;
  float p_mid ;
  float p_now;

  float kg;

  x_mid=x_last;                       //x_last=x(k-1|k-1),x_mid=x(k|k-1)
  p_mid=p_last+Q;                     //p_mid=p(k|k-1),p_last=p(k-1|k-1),Q=����

  /*
   *  �������˲��������Ҫ��ʽ
   */
  kg=p_mid/(p_mid+R);                 //kgΪkalman filter��R Ϊ����
  x_now=x_mid+kg*(ResrcData-x_mid);   //���Ƴ�������ֵ
  p_now=(1-kg)*p_mid;                 //����ֵ��Ӧ��covariance
  p_last = p_now;                     //����covariance ֵ
  x_last = x_now;                     //����ϵͳ״ֵ̬

  return x_now;
}
