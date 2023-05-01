#include "Claw.hpp"
#include "tim.h"
const float CLAW_OMEGA_MAX = 20000; //by jintai: 机械臂最大角速度
template <typename Type>
void Math_Constrain(Type *x, Type Min, Type Max)
{
    if (*x < Min)
    {
        *x = Min;
    }
    else if (*x > Max)
    {
        *x = Max;
    }
}
/**
 * @brief 求绝对值
 * 
 * @tparam Type 
 * @param x 传入数据
 * @return Type x的绝对值
 */
template <typename Type>
Type Math_Abs(Type x)
{
    return((x > 0) ? x : -x); 
}

/**
 * @brief 初始化机械臂
 * 
 * @param __Driver_PWM_TIM 电机驱动定时器编号
 * 
 */

void Class_Claw::Init()
{
	Motor[0].Init(htim4, TIM_CHANNEL_1, CLAW_A1_Pin, CLAW_A1_GPIO_Port, CLAW_B1_Pin, CLAW_B1_GPIO_Port);
	Motor[1].Init(htim4, TIM_CHANNEL_2, CLAW_A2_Pin, CLAW_A2_GPIO_Port, CLAW_B2_Pin, CLAW_B2_GPIO_Port); 
}

/**
 * @brief 设定机械臂速度
 * 
 * @param __Velocity 机械臂转动速度
 */


void Class_Claw::Set_Velocity(SpeedTypeDef __Velocity)
{
    Velocity = __Velocity;
}

//获取速度的函数
SpeedTypeDef Class_Claw::Get_Velocity()
{
    return(Velocity);
}


void Class_Claw::Changhu_velocity(SpeedTypeDef velo)
{  
    Math_Constrain(&velo.Omega,-CLAW_OMEGA_MAX,CLAW_OMEGA_MAX);   //看门狗，机械臂最大转速不能超过设定的CLAW_OMEGA_MAX
    Motor[0].Set_Out(velo.Omega);	
	Motor[0].Output();
	Motor[1].Set_Out(-velo.Omega);	
	Motor[1].Output();
}
