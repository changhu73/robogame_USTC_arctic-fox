#include "PID.h"
#include "motor_control.h"
#include "tim.h"

int encoder_num; // 编码器计数
int encoder_num_1;
int encoder_num_2;
int encoder_num_3;
float measured_motor_speed; // 测得电机转速
float measured_motor_speed_1;
float measured_motor_speed_2;
float measured_motor_speed_3;
float target_motor_speed; // 预期电机转速
float target_motor_speed_1;
float target_motor_speed_2;
float target_motor_speed_3;
float target_motor_speed_4;

pid_t pid_motor_speed;  // 电机速度控制pid
pid_t pid_motor_speed_1;
pid_t pid_motor_speed_2;
pid_t pid_motor_speed_3;

/*
void set_motor_voltage(float voltage)
{
    // 限制取值范围
    if (voltage > VOLTAGE_MAXIMUM)
        voltage = VOLTAGE_MAXIMUM;
    else if (voltage < -VOLTAGE_MAXIMUM)
        voltage = -VOLTAGE_MAXIMUM;

    // 设定PWM
    if (voltage > 0) // 正压
    {
        TIM_SetCompare1(TIM3, voltage);
        TIM_SetCompare2(TIM3, 0);
    }
    else // 负压
    {
        TIM_SetCompare1(TIM3, 0);
        TIM_SetCompare2(TIM3, -voltage);
    }
}

void motor_control(void)
{
    // 测速
    measured_motor_speed = encoder_num;  // 对编码器值采样
    encoder_num = 0;    // 清零，用于下次计数

    // PID计算
    pid_calculate(&pid_motor_speed, measured_motor_speed, target_motor_speed);
    set_motor_voltage(pid_motor_speed.out);
}

void set_motor_voltage_1(float voltage)
{
    // 限制取值范围
    if (voltage > VOLTAGE_MAXIMUM)
        voltage = VOLTAGE_MAXIMUM;
    else if (voltage < -VOLTAGE_MAXIMUM)
        voltage = -VOLTAGE_MAXIMUM;

    // 设定PWM
    if (voltage > 0) // 正压
    {
        TIM_SetCompare3(TIM3, voltage);
        TIM_SetCompare4(TIM3, 0);
    }
    else // 负压
    {
        TIM_SetCompare3(TIM3, 0);
        TIM_SetCompare4(TIM3, -voltage);
    }
}

void motor_control_1(void)
{
    // 测速
    measured_motor_speed_1 = encoder_num_1;  // 对编码器值采样
    encoder_num_1 = 0;    // 清零，用于下次计数

    // PID计算
    pid_calculate(&pid_motor_speed_1, measured_motor_speed_1, target_motor_speed_1);
    set_motor_voltage_1(pid_motor_speed_1.out);
}

void set_motor_voltage_2(float voltage)
{
    // 限制取值范围
    if (voltage > VOLTAGE_MAXIMUM)
        voltage = VOLTAGE_MAXIMUM;
    else if (voltage < -VOLTAGE_MAXIMUM)
        voltage = -VOLTAGE_MAXIMUM;

    // 设定PWM
    if (voltage > 0) // 正压
    {
        TIM_SetCompare1(TIM4, voltage);
        TIM_SetCompare2(TIM4, 0);
    }
    else // 负压
    {
        TIM_SetCompare1(TIM4, 0);
        TIM_SetCompare2(TIM4, -voltage);
    }
}

void motor_control_2(void)
{
    // 测速
    measured_motor_speed_2 = encoder_num_2;  // 对编码器值采样
    encoder_num_2 = 0;    // 清零，用于下次计数

    // PID计算
    pid_calculate(&pid_motor_speed_2, measured_motor_speed_2, target_motor_speed_2);
    set_motor_voltage_2(pid_motor_speed_2.out);
}

void set_motor_voltage_3(float voltage)
{
    // 限制取值范围
    if (voltage > VOLTAGE_MAXIMUM)
        voltage = VOLTAGE_MAXIMUM;
    else if (voltage < -VOLTAGE_MAXIMUM)
        voltage = -VOLTAGE_MAXIMUM;

    // 设定PWM
    if (voltage > 0) // 正压
    {
        TIM_SetCompare3(TIM4, voltage);
        TIM_SetCompare4(TIM4, 0);
    }
    else // 负压
    {
        TIM_SetCompare3(TIM4, 0);
        TIM_SetCompare4(TIM4, -voltage);
    }
}

void motor_control_3(void)
{
    // 测速
    measured_motor_speed_3 = encoder_num_3;  // 对编码器值采样
    encoder_num_3 = 0;    // 清零，用于下次计数

    // PID计算
    pid_calculate(&pid_motor_speed_3, measured_motor_speed_3, target_motor_speed_3);
    set_motor_voltage_3(pid_motor_speed_3.out);
}



void motor_control_4(void)
{
	TIM_SetCompare4(TIM5,target_motor_speed_4);
}
*/
