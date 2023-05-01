#include "PID.h"
#include "motor_control.h"
#include "tim.h"

int encoder_num; // ����������
int encoder_num_1;
int encoder_num_2;
int encoder_num_3;
float measured_motor_speed; // ��õ��ת��
float measured_motor_speed_1;
float measured_motor_speed_2;
float measured_motor_speed_3;
float target_motor_speed; // Ԥ�ڵ��ת��
float target_motor_speed_1;
float target_motor_speed_2;
float target_motor_speed_3;
float target_motor_speed_4;

pid_t pid_motor_speed;  // ����ٶȿ���pid
pid_t pid_motor_speed_1;
pid_t pid_motor_speed_2;
pid_t pid_motor_speed_3;

/*
void set_motor_voltage(float voltage)
{
    // ����ȡֵ��Χ
    if (voltage > VOLTAGE_MAXIMUM)
        voltage = VOLTAGE_MAXIMUM;
    else if (voltage < -VOLTAGE_MAXIMUM)
        voltage = -VOLTAGE_MAXIMUM;

    // �趨PWM
    if (voltage > 0) // ��ѹ
    {
        TIM_SetCompare1(TIM3, voltage);
        TIM_SetCompare2(TIM3, 0);
    }
    else // ��ѹ
    {
        TIM_SetCompare1(TIM3, 0);
        TIM_SetCompare2(TIM3, -voltage);
    }
}

void motor_control(void)
{
    // ����
    measured_motor_speed = encoder_num;  // �Ա�����ֵ����
    encoder_num = 0;    // ���㣬�����´μ���

    // PID����
    pid_calculate(&pid_motor_speed, measured_motor_speed, target_motor_speed);
    set_motor_voltage(pid_motor_speed.out);
}

void set_motor_voltage_1(float voltage)
{
    // ����ȡֵ��Χ
    if (voltage > VOLTAGE_MAXIMUM)
        voltage = VOLTAGE_MAXIMUM;
    else if (voltage < -VOLTAGE_MAXIMUM)
        voltage = -VOLTAGE_MAXIMUM;

    // �趨PWM
    if (voltage > 0) // ��ѹ
    {
        TIM_SetCompare3(TIM3, voltage);
        TIM_SetCompare4(TIM3, 0);
    }
    else // ��ѹ
    {
        TIM_SetCompare3(TIM3, 0);
        TIM_SetCompare4(TIM3, -voltage);
    }
}

void motor_control_1(void)
{
    // ����
    measured_motor_speed_1 = encoder_num_1;  // �Ա�����ֵ����
    encoder_num_1 = 0;    // ���㣬�����´μ���

    // PID����
    pid_calculate(&pid_motor_speed_1, measured_motor_speed_1, target_motor_speed_1);
    set_motor_voltage_1(pid_motor_speed_1.out);
}

void set_motor_voltage_2(float voltage)
{
    // ����ȡֵ��Χ
    if (voltage > VOLTAGE_MAXIMUM)
        voltage = VOLTAGE_MAXIMUM;
    else if (voltage < -VOLTAGE_MAXIMUM)
        voltage = -VOLTAGE_MAXIMUM;

    // �趨PWM
    if (voltage > 0) // ��ѹ
    {
        TIM_SetCompare1(TIM4, voltage);
        TIM_SetCompare2(TIM4, 0);
    }
    else // ��ѹ
    {
        TIM_SetCompare1(TIM4, 0);
        TIM_SetCompare2(TIM4, -voltage);
    }
}

void motor_control_2(void)
{
    // ����
    measured_motor_speed_2 = encoder_num_2;  // �Ա�����ֵ����
    encoder_num_2 = 0;    // ���㣬�����´μ���

    // PID����
    pid_calculate(&pid_motor_speed_2, measured_motor_speed_2, target_motor_speed_2);
    set_motor_voltage_2(pid_motor_speed_2.out);
}

void set_motor_voltage_3(float voltage)
{
    // ����ȡֵ��Χ
    if (voltage > VOLTAGE_MAXIMUM)
        voltage = VOLTAGE_MAXIMUM;
    else if (voltage < -VOLTAGE_MAXIMUM)
        voltage = -VOLTAGE_MAXIMUM;

    // �趨PWM
    if (voltage > 0) // ��ѹ
    {
        TIM_SetCompare3(TIM4, voltage);
        TIM_SetCompare4(TIM4, 0);
    }
    else // ��ѹ
    {
        TIM_SetCompare3(TIM4, 0);
        TIM_SetCompare4(TIM4, -voltage);
    }
}

void motor_control_3(void)
{
    // ����
    measured_motor_speed_3 = encoder_num_3;  // �Ա�����ֵ����
    encoder_num_3 = 0;    // ���㣬�����´μ���

    // PID����
    pid_calculate(&pid_motor_speed_3, measured_motor_speed_3, target_motor_speed_3);
    set_motor_voltage_3(pid_motor_speed_3.out);
}



void motor_control_4(void)
{
	TIM_SetCompare4(TIM5,target_motor_speed_4);
}
*/
