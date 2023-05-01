#include "Claw.hpp"
#include "tim.h"
const float CLAW_OMEGA_MAX = 20000; //by jintai: ��е�������ٶ�
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
 * @brief �����ֵ
 * 
 * @tparam Type 
 * @param x ��������
 * @return Type x�ľ���ֵ
 */
template <typename Type>
Type Math_Abs(Type x)
{
    return((x > 0) ? x : -x); 
}

/**
 * @brief ��ʼ����е��
 * 
 * @param __Driver_PWM_TIM ���������ʱ�����
 * 
 */

void Class_Claw::Init()
{
	Motor[0].Init(htim4, TIM_CHANNEL_1, CLAW_A1_Pin, CLAW_A1_GPIO_Port, CLAW_B1_Pin, CLAW_B1_GPIO_Port);
	Motor[1].Init(htim4, TIM_CHANNEL_2, CLAW_A2_Pin, CLAW_A2_GPIO_Port, CLAW_B2_Pin, CLAW_B2_GPIO_Port); 
}

/**
 * @brief �趨��е���ٶ�
 * 
 * @param __Velocity ��е��ת���ٶ�
 */


void Class_Claw::Set_Velocity(SpeedTypeDef __Velocity)
{
    Velocity = __Velocity;
}

//��ȡ�ٶȵĺ���
SpeedTypeDef Class_Claw::Get_Velocity()
{
    return(Velocity);
}


void Class_Claw::Changhu_velocity(SpeedTypeDef velo)
{  
    Math_Constrain(&velo.Omega,-CLAW_OMEGA_MAX,CLAW_OMEGA_MAX);   //���Ź�����е�����ת�ٲ��ܳ����趨��CLAW_OMEGA_MAX
    Motor[0].Set_Out(velo.Omega);	
	Motor[0].Output();
	Motor[1].Set_Out(-velo.Omega);	
	Motor[1].Output();
}
