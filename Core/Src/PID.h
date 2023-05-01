#ifndef __pid_H		//completed
#define __pid_H

enum{
    LAST 	= 0,
    NOW 	= 1,
};

typedef struct __pid_t
{
    float p;
    float i;
    float d;

    float max_output;      //输出限幅
    float intergral_limit; //积分限幅

    float set[2];				//目标值,包含NOW， LAST， LLAST上上次
    float get[2];				//测量值
    float err[2];				//误差
	
    float pout;							//p输出
    float iout;							//i输出
    float dout;							//d输出
    
    float out;						//输出
}pid_t;

void pid_struct_init(pid_t *pid,
                            float max_output, float intergral_limit, float kp, float ki, float kd);

float pid_calculate(pid_t *pid, float measure, float target);
extern float PP;
extern float II;
extern float DD;

#endif

