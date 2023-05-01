/**
 * @file Chassis.cpp
 * @author yssickjgd 1345578933@qq.com
 * @brief 底盘控制
 * @version 0.1
 * @date 2022-05-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/* Includes ------------------------------------------------------------------*/

#include "Chassis.hpp"
#include "Motor.hpp"
#include "main.h"
#include "tim.h"

/* Private macros ------------------------------------------------------------*/

/* Private types -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function declarations ---------------------------------------------*/

/**
 * @brief 限幅函数
 * 
 * @tparam Type 
 * @param x 传入数据
 * @param Min 最小值
 * @param Max 最大值
 */
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
 * @brief 初始化底盘
 * 
 * @param __Driver_PWM_TIM 电机驱动定时器编号
 * @param __Calculate_EXTI_TIM 速度计算定时器编号
 */
void Class_Chassis::Init()//TIM_HandleTypeDef __Driver_PWM_TIM)	/*, TIM_HandleTypeDef __Calculate_EXTI_TIM)*/
{
    //Driver_PWM_TIM = __Driver_PWM_TIM;
    //Calculate_TIM = __Calculate_EXTI_TIM;
    
    //电机初始化：这里初始化当然也被改动，因为hpp定义里面被我改了
  //  Motor[0].Init(__Driver_PWM_TIM, TIM_CHANNEL_1, WHEEL_A1_Pin, WHEEL_A1_GPIO_Port, WHEEL_B1_Pin, WHEEL_B1_GPIO_Port, __Calculate_EXTI_TIM, WHEEL1_EXTI_Pin, WHEEL1_EXTI_GPIO_Port, WHEEL1_INPUT_Pin, WHEEL1_INPUT_GPIO_Port);

   // Motor[1].Init(__Driver_PWM_TIM, TIM_CHANNEL_2, WHEEL_A2_Pin, WHEEL_A2_GPIO_Port, WHEEL_B2_Pin, WHEEL_B2_GPIO_Port, __Calculate_EXTI_TIM, WHEEL2_EXTI_Pin, WHEEL2_EXTI_GPIO_Port, WHEEL2_INPUT_Pin, WHEEL2_INPUT_GPIO_Port);

   // Motor[2].Init(__Driver_PWM_TIM, TIM_CHANNEL_3, WHEEL_A3_Pin, WHEEL_A3_GPIO_Port, WHEEL_B3_Pin, WHEEL_B3_GPIO_Port, __Calculate_EXTI_TIM, WHEEL3_EXTI_Pin, WHEEL3_EXTI_GPIO_Port, WHEEL3_INPUT_Pin, WHEEL3_INPUT_GPIO_Port);
   // Motor[2].Set_Rotate_Direction_Flag(CCW);

   // Motor[3].Init(__Driver_PWM_TIM, TIM_CHANNEL_4, WHEEL_A4_Pin, WHEEL_A4_GPIO_Port, WHEEL_B4_Pin, WHEEL_B4_GPIO_Port, __Calculate_EXTI_TIM, WHEEL4_EXTI_Pin, WHEEL4_EXTI_GPIO_Port, WHEEL4_INPUT_Pin, WHEEL4_INPUT_GPIO_Port);
   // Motor[3].Set_Rotate_Direction_Flag(CCW);
	Motor[0].Init(htim3, TIM_CHANNEL_1, WHEEL_A1_Pin, WHEEL_A1_GPIO_Port, WHEEL_B1_Pin, WHEEL_B1_GPIO_Port);
	Motor[1].Init(htim3, TIM_CHANNEL_2, WHEEL_A2_Pin, WHEEL_A2_GPIO_Port, WHEEL_B2_Pin, WHEEL_B2_GPIO_Port); 
	//注意后面将2、3号轮组交换
	Motor[2].Init(htim3, TIM_CHANNEL_3, WHEEL_A3_Pin, WHEEL_A3_GPIO_Port, WHEEL_B3_Pin, WHEEL_B3_GPIO_Port);
	//Motor[2].Set_Rotate_Direction_Flag(CCW);
	
	Motor[3].Init(htim3, TIM_CHANNEL_4, WHEEL_A4_Pin, WHEEL_A4_GPIO_Port, WHEEL_B4_Pin, WHEEL_B4_GPIO_Port);
	//Motor[3].Set_Rotate_Direction_Flag(CCW);
/*
    //电机PID初始化
    for(int i = 0; i < 4; i++)
    {
        Motor[i].Omega_PID.Init(2000, 3000, 25, ULONG_MAX, ULONG_MAX);
    }
*/
    //遥控器初始化
    //DR16.Init(CHASSIS_DR16_CONTROL_UART);
}

/**
 * @brief 设定底盘速度
 * 
 * @param __Velocity 底盘速度
 */


void Class_Chassis::Set_Velocity(SpeedTypeDef __Velocity)
{
    Velocity = __Velocity;
}

/**
 * @brief 设定底盘控制方式
 * 
 * @param __Control_Method 底盘控制方式
 */

/*
void Class_Chassis::Set_Control_Method(Enum_Control_Method __Control_Method)
{
    Control_Method = __Control_Method;

    for(int i = 0; i < 4; i++)
    {
        Motor[i].Set_Control_Method(__Control_Method);
    }
}
*/

/**
 * @brief 底盘电机霍尔编码器触发中断处理函数
 * 
 */
/*
void Class_Chassis::Hall_Encoder_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    //判断中断源, 并指向电机的中断处理函数
    if(GPIO_Pin == WHEEL1_EXTI_Pin)
    {
        Motor[0].Hall_Encoder_GPIO_EXTI_Callback();
    }
    else if(GPIO_Pin == WHEEL2_EXTI_Pin)
    {
        Motor[1].Hall_Encoder_GPIO_EXTI_Callback();
    }
    else if(GPIO_Pin == WHEEL3_EXTI_Pin)
    {
        Motor[2].Hall_Encoder_GPIO_EXTI_Callback();
    }
    else if(GPIO_Pin == WHEEL4_EXTI_Pin)
    {
        Motor[3].Hall_Encoder_GPIO_EXTI_Callback();
    }
}
*/

//获取速度的函数
SpeedTypeDef Class_Chassis::Get_Velocity()
{
    return(Velocity);
}

/**
 * @brief 定时器中断处理函数
 * 
 */

/*
void Class_Chassis::Calculate_TIM_PeriodElapsedCallback()
{			//main函数定义参数，遥控器的传参直接删除即可。
    //遥控器处理
    //DR16.Process_TIM_PeriodElapsedCallback();
    //Velocity = //DR16.Get_Velocity();
	//修改
	Velocity = Get_Velocity();
	
    //速度解算
    Math_Constrain(&Velocity.X, -X_MAX, X_MAX);
    Math_Constrain(&Velocity.Y, -Y_MAX, Y_MAX);
    Math_Constrain(&Velocity.Omega, -OMEGA_MAX, OMEGA_MAX);

    //Motor[0].Set_Omega_Target((-OMEGA_TO_MS * Velocity.Omega + Velocity.X - Velocity.Y) / WHEEL_RADIUS * ((Motor[0].Get_Rotate_Direction_Flag() == CW)?1:(-1)));
    //Motor[1].Set_Omega_Target((-OMEGA_TO_MS * Velocity.Omega - Velocity.X - Velocity.Y) / WHEEL_RADIUS * ((Motor[1].Get_Rotate_Direction_Flag() == CW)?1:(-1)));
    //Motor[2].Set_Omega_Target((OMEGA_TO_MS * Velocity.Omega + Velocity.X - Velocity.Y) / WHEEL_RADIUS * ((Motor[2].Get_Rotate_Direction_Flag() == CW)?1:(-1)));
    //Motor[3].Set_Omega_Target((OMEGA_TO_MS * Velocity.Omega - Velocity.X - Velocity.Y) / WHEEL_RADIUS * ((Motor[3].Get_Rotate_Direction_Flag() == CW)?1:(-1)));
	
	
    //电机输出值设定并输出
    for(int i = 0; i < 4; i++)
    {
//		Motor[i].Calculate_TIM_PeriodElapsedCallback();
        Motor[i].Output();
    }
    
}

*/

//新版速度解算
void Class_Chassis::Changhu_velocity(SpeedTypeDef velo){
	//__Velocity = Get_Velocity();
	
	Math_Constrain(&velo.X, -X_MAX, X_MAX);
    Math_Constrain(&velo.Y, -Y_MAX, Y_MAX);
    Math_Constrain(&velo.Omega, -OMEGA_MAX, OMEGA_MAX);
	/*
    Motor[0].Set_Omega_Target((-OMEGA_TO_MS * Velocity.Omega + Velocity.X - Velocity.Y) / WHEEL_RADIUS * ((Motor[0].Get_Rotate_Direction_Flag() == CW)?1:(-1)));
    Motor[1].Set_Omega_Target((-OMEGA_TO_MS * Velocity.Omega - Velocity.X - Velocity.Y) / WHEEL_RADIUS * ((Motor[1].Get_Rotate_Direction_Flag() == CW)?1:(-1)));
    Motor[2].Set_Omega_Target((OMEGA_TO_MS * Velocity.Omega + Velocity.X - Velocity.Y) / WHEEL_RADIUS * ((Motor[2].Get_Rotate_Direction_Flag() == CW)?1:(-1)));
    Motor[3].Set_Omega_Target((OMEGA_TO_MS * Velocity.Omega - Velocity.X - Velocity.Y) / WHEEL_RADIUS * ((Motor[3].Get_Rotate_Direction_Flag() == CW)?1:(-1)));
	*/
	
	//X为向左正，Y为向前正，Omega为逆时针正
	if((velo.X==0) && (velo.Y>0) && (velo.Omega==0)){
	//向前，v_front
		Motor[0].Set_Out(-velo.Y);	
		Motor[0].Output();
		Motor[2].Set_Out(-velo.Y);	
		Motor[2].Output();
		Motor[1].Set_Out(velo.Y);	
		Motor[1].Output();
		Motor[3].Set_Out(velo.Y);	
		Motor[3].Output();
}
	else if((velo.X==0) && (velo.Y<0) && (velo.Omega==0)){
		//向后，v_back,前后实际上可以合并，不过在程序里还是区分一下
		Motor[0].Set_Out(-velo.Y);	
		Motor[0].Output();
		Motor[2].Set_Out(-velo.Y);	
		Motor[2].Output();
		Motor[1].Set_Out(velo.Y);	
		Motor[1].Output(); 
		Motor[3].Set_Out(velo.Y);	
		Motor[3].Output();
}
	else if((velo.X<0) && (velo.Y==0) && (velo.Omega==0)){
	//向右，v_right
		Motor[0].Set_Out(velo.X);	
		Motor[0].Output();
		Motor[2].Set_Out(-velo.X);	
		Motor[2].Output();
		Motor[1].Set_Out(velo.X);	
		Motor[1].Output();
		Motor[3].Set_Out(-velo.X);	
		Motor[3].Output();
}
	else if((velo.X>0) && (velo.Y==0) && (velo.Omega==0)){
	//向左，v_left
		Motor[0].Set_Out(velo.X);	
		Motor[0].Output();
		Motor[2].Set_Out(-velo.X);	
		Motor[2].Output();
		Motor[1].Set_Out(velo.X);	
		Motor[1].Output();
		Motor[3].Set_Out(-velo.X);	
		Motor[3].Output();
}
	else if((velo.X==0) && (velo.Y==0) && (velo.Omega>0)){
	//顺时针旋转,v_rotate
		Motor[0].Set_Out(-velo.Omega);	
		Motor[0].Output();
		Motor[2].Set_Out(-velo.Omega);	
		Motor[2].Output();
		Motor[1].Set_Out(-velo.Omega);	
		Motor[1].Output();
		Motor[3].Set_Out(-velo.Omega);	
		Motor[3].Output();
}
	else if((velo.X==0) && (velo.Y==0) && (velo.Omega<0)){
	//逆时针旋转,v_crotate
		Motor[0].Set_Out(-velo.Omega);	
		Motor[0].Output();
		Motor[2].Set_Out(-velo.Omega);	
		Motor[2].Output();
		Motor[1].Set_Out(-velo.Omega);	
		Motor[1].Output();
		Motor[3].Set_Out(-velo.Omega);	
		Motor[3].Output();
}
	else if((velo.X>0) && (velo.Y>0) && (velo.Omega==0)){
	//左前移动,v_leftfront
		Motor[0].Set_Out(0);	
		Motor[0].Output();
		Motor[2].Set_Out(-velo.X);	
		Motor[2].Output();
		Motor[1].Set_Out(velo.X);	
		Motor[1].Output();
		Motor[3].Set_Out(0);	
		Motor[3].Output();}
			
	else if((velo.X>0) && (velo.Y<0) && (velo.Omega==0)){
	//左后移动,v_leftback
		Motor[0].Set_Out(velo.X);	
		Motor[0].Output();
		Motor[2].Set_Out(0);	
		Motor[2].Output();
		Motor[1].Set_Out(0);	
		Motor[1].Output();
		Motor[3].Set_Out(-velo.X);	
		Motor[3].Output();
				}
	else if((velo.X<0) && (velo.Y>0) && (velo.Omega==0)){
	//右前移动,v_rightfront
		Motor[0].Set_Out(velo.X);	
		Motor[0].Output();
		Motor[2].Set_Out(0);	
		Motor[2].Output();
		Motor[1].Set_Out(0);	
		Motor[1].Output();
		Motor[3].Set_Out(-velo.X);	
		Motor[3].Output();}
	else if((velo.X<0) && (velo.Y<0) && (velo.Omega==0)){
	//右后移动,v_rightback
		Motor[0].Set_Out(0);	
		Motor[0].Output();
		Motor[2].Set_Out(-velo.X);	
		Motor[2].Output();
		Motor[1].Set_Out(velo.X);	
		Motor[1].Output();
		Motor[3].Set_Out(0);	
		Motor[3].Output();}
	else if((velo.X>0) && (velo.Y>0) && (velo.Omega>0)){
	//屁股向左移动,v_leftass
		Motor[0].Set_Out(0);	
		Motor[0].Output();
		Motor[2].Set_Out(0);	
		Motor[2].Output();
		Motor[1].Set_Out(-velo.Omega);	
		Motor[1].Output();
		Motor[3].Set_Out(-velo.Omega);	
		Motor[3].Output();
		}
	else if((velo.X>0) && (velo.Y>0) && (velo.Omega<0)){
	//屁股向右移动,v_rightass
		Motor[0].Set_Out(0);	
		Motor[0].Output();
		Motor[2].Set_Out(0);	
		Motor[2].Output();
		Motor[1].Set_Out(velo.Omega);	
		Motor[1].Output();
		Motor[3].Set_Out(-velo.Omega);	
		Motor[3].Output();}
	else if((velo.X==0) && (velo.Y==0) && (velo.Omega==0)){
		//stop
		Motor[0].Set_Out(0);	
		Motor[0].Output();
		Motor[2].Set_Out(0);	
		Motor[2].Output();
		Motor[1].Set_Out(0);	
		Motor[1].Output();
		Motor[3].Set_Out(0);	
		Motor[3].Output();}
	}



/* Function prototypes -------------------------------------------------------*/

/************************ COPYRIGHT(C) USTC-ROBOWALKER **************************/
