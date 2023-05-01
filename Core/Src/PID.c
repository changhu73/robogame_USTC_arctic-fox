#include "PID.h"
#include <math.h>
float PP;
float II;
float DD;
void abs_limit(float *a, float ABS_MAX)   //将a值限制在阈值之内
{
    if (*a > ABS_MAX)
        *a = ABS_MAX;
    if (*a < -ABS_MAX)
        *a = -ABS_MAX;
}

/*参数初始化--------------------------------------------------------------*/
void pid_struct_init(pid_t *pid,
                            float max_output, float intergral_limit, float kp, float ki, float kd)
{
    pid->intergral_limit = intergral_limit;
    pid->max_output = max_output;

    pid->p = kp;
    pid->i = ki;
    pid->d = kd;
}

/*pid计算--------------------------------------------------------------*/
float pid_calculate(pid_t *pid, float measure, float target)
{
    //  保存最新值
    pid->get[NOW] = measure;
    pid->set[NOW] = target;
    pid->err[NOW] = target - measure;
    
    // PID计算
    pid->pout = pid->p * pid->err[NOW];
    pid->iout += pid->i * pid->err[NOW];
    pid->dout = pid->d * (pid->err[NOW] - pid->err[LAST]);
	
		// 积分清零
		if(pid->i==0)pid->iout=0;

    // 积分限幅
    abs_limit(&(pid->iout), pid->intergral_limit);
    
    // 求和
    pid->out = pid->pout + pid->iout + pid->dout;

    //  输出限幅
    abs_limit(&(pid->out), pid->max_output);

    // 保存历史值
    pid->err[LAST] = pid->err[NOW];
    pid->get[LAST] = pid->get[NOW];
    pid->set[LAST] = pid->set[NOW];

    return pid->out;
}
