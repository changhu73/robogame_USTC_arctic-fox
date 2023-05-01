#include "PID.h"
#include <math.h>
float PP;
float II;
float DD;
void abs_limit(float *a, float ABS_MAX)   //��aֵ��������ֵ֮��
{
    if (*a > ABS_MAX)
        *a = ABS_MAX;
    if (*a < -ABS_MAX)
        *a = -ABS_MAX;
}

/*������ʼ��--------------------------------------------------------------*/
void pid_struct_init(pid_t *pid,
                            float max_output, float intergral_limit, float kp, float ki, float kd)
{
    pid->intergral_limit = intergral_limit;
    pid->max_output = max_output;

    pid->p = kp;
    pid->i = ki;
    pid->d = kd;
}

/*pid����--------------------------------------------------------------*/
float pid_calculate(pid_t *pid, float measure, float target)
{
    //  ��������ֵ
    pid->get[NOW] = measure;
    pid->set[NOW] = target;
    pid->err[NOW] = target - measure;
    
    // PID����
    pid->pout = pid->p * pid->err[NOW];
    pid->iout += pid->i * pid->err[NOW];
    pid->dout = pid->d * (pid->err[NOW] - pid->err[LAST]);
	
		// ��������
		if(pid->i==0)pid->iout=0;

    // �����޷�
    abs_limit(&(pid->iout), pid->intergral_limit);
    
    // ���
    pid->out = pid->pout + pid->iout + pid->dout;

    //  ����޷�
    abs_limit(&(pid->out), pid->max_output);

    // ������ʷֵ
    pid->err[LAST] = pid->err[NOW];
    pid->get[LAST] = pid->get[NOW];
    pid->set[LAST] = pid->set[NOW];

    return pid->out;
}
