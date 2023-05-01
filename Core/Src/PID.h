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

    float max_output;      //����޷�
    float intergral_limit; //�����޷�

    float set[2];				//Ŀ��ֵ,����NOW�� LAST�� LLAST���ϴ�
    float get[2];				//����ֵ
    float err[2];				//���
	
    float pout;							//p���
    float iout;							//i���
    float dout;							//d���
    
    float out;						//���
}pid_t;

void pid_struct_init(pid_t *pid,
                            float max_output, float intergral_limit, float kp, float ki, float kd);

float pid_calculate(pid_t *pid, float measure, float target);
extern float PP;
extern float II;
extern float DD;

#endif

