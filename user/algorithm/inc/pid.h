#ifndef __PID_H
#define __PID_H

typedef struct
{
	float Sv;
	float Av;

	float Kp;
	float Ki;
	float Kd;

	float err;
	float err_last;
	float err_next;
	float total_err;
	float del_err;
	
	float pout;
	float iout;
	float dout;

	float Pid_err_limit;
	float Pid_out_limit;
	float Pid_integral_limit;
		
	float out;
}pid_typedef;

void pid_abs_limit(float *a,float abs_max);
void pid_init(pid_typedef*pid,float kp,float ki,float kd,float pid_out_limit,float pid_integral_limit);
void pid_caculate_delta(pid_typedef*pid,float Sv,float Av);
void pid_caculate_position(pid_typedef*pid,float Sv,float Av);

#endif 
