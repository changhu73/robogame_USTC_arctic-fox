/**
 * @file Chassis.hpp
 * @author yssickjgd 1345578933@qq.com
 * @brief 底盘控制
 * @version 0.1
 * @date 2022-05-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef CHASSIS_HPP
#define CHASSIS_HPP

/* Includes ------------------------------------------------------------------*/

#include "main.h"
#include "Motor.hpp"
#include "DR16.hpp"

/* Exported macros -----------------------------------------------------------*/

//轮半径, m
const float WHEEL_RADIUS = 0.050f;

//轮组满转线速度, m/s
const float WHEEL_FULL_V = (MOTOR_FULL_OMEGA * WHEEL_RADIUS);

//omega到m/s映射系数, (横轮距+纵轮距)/2, m/rad
const float OMEGA_TO_MS = ((0.482f + 0.500f) / 2);

//绝对速度限制, 任何情况不能超过
//横移速度上限, m/s
const float  X_MAX = 10000;    
//前进速度上限, m/s
const float Y_MAX = 10000;    
//旋转速度上限, rad/s
const float OMEGA_MAX = 20000; 

/* Exported types ------------------------------------------------------------*/

class Class_Chassis
{
    public:

        //底盘对应的电机
	
	//修改by changhu:先不用霍尔编码器，之前不用的版本已经测试完毕，而未测试带有霍尔编码器的初始化，在Chassis.cpp里面也需要进行改动参数
//	Class_Motor_With_Hall_Encoder Motor[4];
	
		Class_Motor Motor[4];
	
        //底盘对应的遥控器
 //     Class_DR16 DR16;

        void Init();//TIM_HandleTypeDef __Driver_PWM_TIM);/*, TIM_HandleTypeDef __Calculate_EXTI_TIM);*/
        void Changhu_velocity(SpeedTypeDef velo);
        void Set_Velocity(SpeedTypeDef __Velocity);
        //void Set_Control_Method(Enum_Control_Method __Control_Method);
        
        //void Hall_Encoder_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
        //void Calculate_TIM_PeriodElapsedCallback();
		
		SpeedTypeDef Get_Velocity();//添加获取速度的函数(by changhu)

    protected:

        //电机PWM驱动定时器
        TIM_HandleTypeDef Driver_PWM_TIM;
        //电机计算定时器中断
        //TIM_HandleTypeDef Calculate_TIM;

        //底盘控制方式
        //Enum_Control_Method Control_Method = Control_Method_OMEGA;

        //底盘速度
        SpeedTypeDef Velocity = 
        {
            1,
            0,
            0
        };

};

/* Exported variables --------------------------------------------------------*/

/* Exported function declarations --------------------------------------------*/

#endif

/************************ COPYRIGHT(C) USTC-ROBOWALKER **************************/
