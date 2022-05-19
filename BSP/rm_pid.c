#include "main.h"

PID pid[ALL_PID];		//定义所有PID结构体数组
PID_INCR pid_incr[ALL_PID_INCR];
float out[ALL_PID] = {0};//PID输出值数组
float out_incr[ALL_PID_INCR] = {0};



void pid_incr_init(PID_INCR *pid, const float PID[3], float max_out, float max_iout)
{
	pid->Kp = PID[0];
    pid->Ki = PID[1];
    pid->Kd = PID[2];
    pid->max_out = max_out;
    pid->max_iout = max_iout;
    pid->Dbuf[0] = pid->Dbuf[1] = pid->Dbuf[2] = 0.0f;
    pid->error[0] = pid->error[1] = pid->error[2] = pid->Pout = pid->Iout = pid->Dout = pid->out = 0.0f;
}

float pid_incr_calc(PID_INCR *pid, float ref, float set)
{
	pid->error[2] = pid->error[1];
	pid->error[1] = pid->error[0];
	pid->set = set;
	pid->fdb = ref;
	pid->error[0] = set - ref;

	pid->Pout = pid->Kp * (pid->error[0] - pid->error[1]);
	pid->Iout = pid->Ki * pid->error[0];
	pid->Dbuf[2] = pid->Dbuf[1];
	pid->Dbuf[1] = pid->Dbuf[0];
	pid->Dbuf[0] = (pid->error[0] - 2.0f * pid->error[1] + pid->error[2]);
	pid->Dout = pid->Kd * pid->Dbuf[0];
	pid->out += pid->Pout + pid->Iout + pid->Dout;
	pid->out = pid->out > pid->max_out ? pid->max_out : pid->out;
	pid->out = pid->out < -pid->max_out ? -pid->max_out : pid->out;
	return pid->out;
}

//pid值初始化
static void pid_init(PID *pid, float kp, float ki, float kd, float poutmax, float ioutmax, float doutmax, float outmax)
{	
	pid->kp = kp;
	pid->ki = ki;
	pid->kd = kd;
	
	pid->poutmax = poutmax;
	pid->ioutmax = ioutmax;
	pid->doutmax = doutmax;
	pid->outmax = outmax;
	
	pid->f_pid_reset = pid_reset;
	pid->f_pid_reset(pid);
	
	pid->err = 0;
	pid->err_last = 0;
	pid->err_llast = 0;
	pid->integral = 0;
	
}
//pid输出值重置
static void pid_reset(PID *pid)
{
	
	pid->pout = 0;
	pid->iout = 0;
	pid->dout = 0;
	pid->out  = 0;
	
}

//所有电机pid值初始化（形参需要后续更改，第一次测试形参全为0）
//(&pid[i], kp, ki, kd, poutmax, ioutmax, doutmax, outmax)
void All_Pid_Configuration(PID pid[])
{	
	pid[ANGLE_BOARD].f_pid_init = pid_init;
	pid[ANGLE_BOARD].f_pid_init(&pid[ANGLE_BOARD], 4.5f, 0.0f, 0.0f, 50.0f, 0.0f, 50.0f, 50.0f);
	
	pid[SPEED_BOARD].f_pid_init = pid_init;
	pid[SPEED_BOARD].f_pid_init(&pid[SPEED_BOARD], 10.0f, 0.0f, 0.0f, 300.0f, 0.0f, 300.0f, 300.0f);
	
	pid[ANGLE_WEIGHT].f_pid_init = pid_init;
	pid[ANGLE_WEIGHT].f_pid_init(&pid[ANGLE_WEIGHT], 6.0f, 0.0f, 0.0f, 50.0f, 0.0f, 50.0f, 50.0f);
	
	pid[SPEED_WEIGHT].f_pid_init = pid_init;
	pid[SPEED_WEIGHT].f_pid_init(&pid[SPEED_WEIGHT], 20.0f, 0.0f, 0.0f, 600.0f, 0.0f, 600.0f, 600.0f);
	 
}

//pid计算出输出值 
float Calculate_Current_Value(PID *pid, float set, float real)
{
	//首先置零上一次的输出值
	pid->f_pid_reset = pid_reset;
	pid->f_pid_reset(pid);
	
	pid->set = set ;
	pid->real = real;
	
	pid->err_last = pid->err;
	pid->err = pid->set - pid->real;
	pid->integral += pid->err;
	
	pid->pout = pid->kp * pid->err;
	pid->pout = pid->pout < pid->poutmax ? pid->pout : pid->poutmax;
	pid->pout = pid->pout > -pid->poutmax ? pid->pout : -pid->poutmax;
	
	pid->iout = pid->ki * pid->integral;
	pid->iout = pid->iout < pid->ioutmax  ? pid->iout : pid->ioutmax;
	pid->iout = pid->iout > -pid->ioutmax ? pid->iout : -pid->ioutmax;
	
	pid->dout = pid->kd * (pid->err - pid->err_last);
	pid->dout = pid->dout < pid->doutmax ? pid->dout : pid->doutmax;
	pid->dout = pid->dout > -pid->doutmax ? pid->dout : -pid->doutmax;
	
	pid->out = pid->pout + pid->iout + pid->dout;
	pid->out = pid->out < pid->outmax ? pid->out : pid->outmax;
	pid->out = pid->out > -pid->outmax ? pid->out : -pid->outmax;
	
	return pid->out;
}
float Calculate_Current_Value_For_Err(PID *pid, float err)
{
	pid->f_pid_reset = pid_reset;
	pid->f_pid_reset(pid);
	
	
	pid->err_last = pid->err;
	pid->err = err;
	pid->integral += pid->err;
	
	pid->pout = pid->kp * pid->err;
	pid->pout = pid->pout < pid->poutmax ? pid->pout : pid->poutmax;
	pid->pout = pid->pout > -pid->poutmax ? pid->pout : -pid->poutmax;
	
	pid->iout = pid->ki * pid->integral;
	pid->iout = pid->iout < pid->ioutmax  ? pid->iout : pid->ioutmax;
	pid->iout = pid->iout > -pid->ioutmax ? pid->iout : -pid->ioutmax;
	
	pid->dout = pid->kd * (pid->err - pid->err_last);
	pid->dout = pid->dout < pid->doutmax ? pid->dout : pid->doutmax;
	pid->dout = pid->dout > -pid->doutmax ? pid->dout : -pid->doutmax;
	
	pid->out = pid->pout + pid->iout + pid->dout;
	pid->out = pid->out < pid->outmax ? pid->out : pid->outmax;
	pid->out = pid->out > -pid->outmax ? pid->out : -pid->outmax;
	
	return pid->out;
}

