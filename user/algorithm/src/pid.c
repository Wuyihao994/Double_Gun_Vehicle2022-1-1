#include "pid.h"

void pid_abs_limit(float *a,float abs_max)
{
	if(*a>abs_max)
		*a=abs_max;
	if(*a<-abs_max)
		*a=-abs_max;
}

void pid_init(pid_typedef*pid,float kp,float ki,float kd,float pid_out_limit,float pid_integral_limit)
{
	pid->Sv=0.0;
	pid->Av=0.0;
	
	pid->Kp=kp;
	pid->Ki=ki;
	pid->Kd=kd;
	
	pid->pout=0.0;
	pid->iout=0.0;
	pid->dout=0.0;
	pid->err=0.0;
	pid->err_last=0.0;
	pid->err_next=0.0;
	pid->del_err=0.0;
	pid->total_err=0.0;
	
//	pid->Pid_err_limit=;
	pid->Pid_out_limit=pid_out_limit;
	pid->Pid_integral_limit=pid_integral_limit;
	
	pid->out=0.0;
}

void pid_caculate_delta(pid_typedef*pid,float Sv_t,float Av_t)
{
	pid->Sv=Sv_t;
	pid->Av=Av_t;
	pid->err=pid->Sv-pid->Av;
	pid->del_err=pid->err_last-pid->err;
	pid->pout=pid->Kp*(pid->err-pid->err_next);
	pid->iout=pid->Ki*pid->err;
	pid->dout=pid->Kd*(pid->err-2*pid->err_next+pid->err_last);
	pid_abs_limit(&pid->iout,pid->Pid_integral_limit);
	pid->out+=pid->pout+pid->iout+pid->dout;
	pid->err_last=pid->err_next;
	pid->err_next=pid->err;
	pid_abs_limit(&pid->out,pid->Pid_out_limit);
}

void pid_caculate_position(pid_typedef*pid,float Sv_t,float Av_t)
{
	pid->Sv=Sv_t;
	pid->Av=Av_t;
	pid->err=pid->Sv-pid->Av;
	pid->total_err+=pid->err;
	pid->pout=pid->Kp*pid->err;
	pid->iout+=pid->Ki*pid->err;
	pid->dout=pid->Kd*(pid->err-pid->err_last);
	pid_abs_limit(&pid->iout,pid->Pid_integral_limit);
	pid->out=pid->pout+pid->iout+pid->dout;
	pid->err_last=pid->err;
	pid_abs_limit(&pid->out,pid->Pid_out_limit);
}
