/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "DR16.hpp"
#include "Motor.hpp"
#include "Chassis.hpp"
#include "Claw.hpp"
#include "Relay.hpp"
#include "trace.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
Class_Chassis Chassis;
Class_Claw Claw;
Class_Relay Relay[4]; //四个继电器
/**
 * @param Relay[0] 控制发射机构电磁阀
 * @param Relay[1] 控制真空泵 
 * @param Relay[2] 控制靠前吸盘组对应电磁阀
 * @param Relay[3] 控制靠后吸盘组对应电磁阀
 */
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

//超声波测试程序定义：
uint32_t capture_Buf[2] = {0};   //存放计数值
uint8_t capture_Cnt = 0;    //状态标志位
uint32_t high_time;   //高电平时间
uint32_t Distance;
uint32_t Distance_Calculate(uint32_t count)
{
		uint32_t Distance = 0;
		Distance = (uint32_t)(((float)count / 58) * 100);
		return Distance;
}
void HCSR04_Init_Start(void)
{
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,GPIO_PIN_SET);
	delay_us(10);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,GPIO_PIN_RESET);
}

  

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)

{
  /* USER CODE BEGIN 1 */
uint8_t trbuf[16]={2,1,1,2,184,11,0,0,0,0,0,0,0,0,3,52};
extern int colorflag;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_TIM5_Init();
  MX_TIM7_Init();
  MX_TIM9_Init();
  MX_USART2_UART_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_IC_Start_IT(&htim9, TIM_CHANNEL_1);
  
  //test_chassis:
  //底盘初始化，注意参数，详情见Chassis.cpp中的Init函数
  
  
  //, htim5);		
  
  //Chassis.Set_Control_Method(Control_Method_OPENLOOP);
  
  //使能计算时钟
  //HAL_TIM_Base_Start_IT(&CHASSIS_MOTOR_CALCULATE_TIM);
  
  //test_motor:
  /*
  Class_Motor motor1;
  Class_Motor motor2;
  Class_Motor motor3;
  Class_Motor motor4;
  */
extern int front[5];
extern int back[5];
extern int right[5];
extern int left[5];
int num1,num2,num3;
struct SpeedTypeDef v_front={0, 10000, 0};//向前
struct SpeedTypeDef v_frontlow={0, 4000, 0};//向前
struct SpeedTypeDef v_frontlowlow={0, 3000, 0};//向前
struct SpeedTypeDef v_back={0, -10000, 0};//向后
struct SpeedTypeDef v_backlow={0, -4000, 0};//向后
struct SpeedTypeDef v_backfast={0, -30000, 0};//向后
struct SpeedTypeDef v_left={10000, 0 ,0};//向左
struct SpeedTypeDef v_leftlow={4000, 0 ,0};//向左
struct SpeedTypeDef v_leftlowlow={2000, 0, 0};//向左
struct SpeedTypeDef v_right={-10000, 0 ,0};//向右
struct SpeedTypeDef v_rightlow={-4000, 0 ,0};//向右
struct SpeedTypeDef v_rightlowlow={-2000, 0, 0};//向右
struct SpeedTypeDef v_rotate={0, 0, 10000};//正转
struct SpeedTypeDef v_crotate={0, 0, -10000};//逆转
struct SpeedTypeDef v_leftass={7000, 7000, 7000};//屁股向左
struct SpeedTypeDef v_rightass={7000, 7000, -7000};//屁股向右
struct SpeedTypeDef v_leftfront={10000, 10000, 0};//左前
struct SpeedTypeDef v_rightfront={-10000, 10000, 0};//右前
struct SpeedTypeDef v_leftback={10000, -10000, 0};//左后
struct SpeedTypeDef v_rightback={-10000, -10000, 0};//右后	
struct SpeedTypeDef v_stop={0, 0 ,0};//停下
struct SpeedTypeDef v_rotatelow={0, 0, 4000};//正转
struct SpeedTypeDef v_slowfront={0, 3000, 0};//慢速向前



  struct SpeedTypeDef claw_up_rotate=  //机械臂抬升
   {
    0,0,-100
   };
     struct SpeedTypeDef claw_upup_rotate=  //机械臂抬升(快一点
   {
    0,0,-200
   };
   struct SpeedTypeDef claw_down_rotate=  //机械臂放下
   {
    0,0,50
   };
    struct SpeedTypeDef claw_downdown_rotate=  //机械臂放下(快一点
   {
    0,0,100	
   };
   
   Chassis.Init();
   Claw.Init();
   Relay[0].Init(RELAY_0_GPIO_Port,RELAY_0_Pin);
   Relay[1].Init(RELAY_1_GPIO_Port,RELAY_1_Pin);
   Relay[2].Init(RELAY_2_GPIO_Port,RELAY_2_Pin);
   Relay[3].Init(RELAY_3_GPIO_Port,RELAY_3_Pin);
 /*test_motor:
  motor1.Init(htim3, TIM_CHANNEL_1, WHEEL_A1_Pin, WHEEL_A1_GPIO_Port, WHEEL_B1_Pin, WHEEL_B1_GPIO_Port);
  motor2.Init(htim3, TIM_CHANNEL_2, WHEEL_A2_Pin, WHEEL_A2_GPIO_Port, WHEEL_B2_Pin, WHEEL_B2_GPIO_Port); 
  motor3.Init(htim3, TIM_CHANNEL_3, WHEEL_A3_Pin, WHEEL_A3_GPIO_Port, WHEEL_B3_Pin, WHEEL_B3_GPIO_Port);
  motor4.Init(htim3, TIM_CHANNEL_4, WHEEL_A4_Pin, WHEEL_A4_GPIO_Port, WHEEL_B4_Pin, WHEEL_B4_GPIO_Port);
*/
   
/*冰壶机器人算法逻辑框架---------------------*/
	int front_sum,back_sum,left_sum,right_sum;
    //穿越巡线区
	 HAL_Delay(10000);
   modified_trace_pre(19000);
	//到达第一个三岔路口
	while(!(front[2]==1 && front[3]==1)){
		left_track();  
	}
	
	Chassis.Changhu_velocity(v_stop);
	HAL_Delay(1000);
	
	//卡到位置再扫描
  HAL_UART_Transmit_DMA(&huart1,trbuf,16);	
	Chassis.Changhu_velocity(v_frontlow);
	HAL_Delay(3500);
	Chassis.Changhu_velocity(v_frontlow);
	HAL_Delay(1000);
/*  低难度第一个位置：目前在第一个三岔路口*/ 
	//这里要加一个判断//如果第一个是

 //如果第一个不是
	if(uart1_receive_buffer[1]=='0')
{
	//后退
	Chassis.Changhu_velocity(v_back);
	HAL_Delay(400);				//这个参数可能要改，看看十字校准的效果
	Chassis.Changhu_velocity(v_stop);	

	//十字校准
	read_redsense();
	while(!(left[2]==1 && left[3]==1)){
		Chassis.Changhu_velocity(v_backlow);
		HAL_Delay(20);
		read_redsense();
	}	
	
	Chassis.Changhu_velocity(v_left);
 	HAL_Delay(1000);
	Chassis.Changhu_velocity(v_stop);
	HAL_Delay(500);
	read_redsense();
	while(!(front[2]==1 && front[3]==1)){
		left_track();
	}
	Chassis.Changhu_velocity(v_stop);
	HAL_Delay(2500);
	
	Chassis.Changhu_velocity(v_frontlow);
	HAL_Delay(3500);	
}

	//前进固定距离
	Chassis.Changhu_velocity(v_backlow);
	HAL_Delay(900);/////////////////////////////////////////这个地方需要调试，先卡住然后往后退

	Chassis.Changhu_velocity(v_stop);
	//放下夹子
	Claw.Changhu_velocity(claw_downdown_rotate);
	HAL_Delay(4500);///////////////////////////////////////
	Claw.Changhu_velocity(v_stop);
	//吸起来
	Relay[1].set_Relay_output_situation(1);
	Relay[3].set_Relay_output_situation(1);
	Relay[2].set_Relay_output_situation(0);  //吸起
	HAL_Delay(5000);
	//上升
	Claw.Changhu_velocity(claw_upup_rotate);
	HAL_Delay(3600);
	Claw.Changhu_velocity(v_stop);//机械臂上升 
	//往后退，时间可能要调整
	Chassis.Changhu_velocity(v_back);//与向前进保持一样的距离，虽然可能重一点，在此之后十字校准
	HAL_Delay(500);
	Chassis.Changhu_velocity(v_stop);
	
	read_redsense();
	while(!(left[2]==1 && left[3]==1)){
		Chassis.Changhu_velocity(v_backlow);
		HAL_Delay(20);
		read_redsense();
	}
	
	//动两格就位
	read_redsense();
	while(!(back[2]==1 && back[3]==1)){
		left_track();
	}
	Chassis.Changhu_velocity(v_stop);
	HAL_Delay(500);

	//十字校准
//	trace_check_crossroad();

    //推出冰壶
	
	Claw.Changhu_velocity(claw_down_rotate);
	HAL_Delay(8000);
	Claw.Changhu_velocity(v_stop);//机械臂下降
	
	Relay[2].set_Relay_output_situation(1);//放下	
	Relay[1].set_Relay_output_situation(0);
	
	Claw.Changhu_velocity(claw_up_rotate);
	HAL_Delay(3000);
	Claw.Changhu_velocity(v_stop);//机械臂上升

	Relay[0].set_Relay_output_situation(0);
	HAL_Delay(1500);//不知道在干什么

	//前进

	Chassis.Changhu_velocity(v_frontlowlow);
	HAL_Delay(4700);//////////////////////////////
	Chassis.Changhu_velocity(v_stop);
	HAL_Delay(2000);
	/*Chassis.Changhu_velocity(v_rightlow);
	HAL_Delay(150);//////////////////////////////
	Chassis.Changhu_velocity(v_stop);
	HAL_Delay(20);
	/////////////////////////////////////////////////////////////////////////////
	Chassis.Changhu_velocity(v_leftlowlow);
	
	HAL_Delay(290);//////////////////////////////00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
	
	Chassis.Changhu_velocity(v_stop);
	HAL_Delay(500);
	*/
	Relay[0].set_Relay_output_situation(1); //此时常开（开路即断路）端闭合，电磁阀两端出现电势差，气缸将冰壶推出
	HAL_Delay(1500);
      
	Relay[0].set_Relay_output_situation(0);//气缸收回
	HAL_Delay(1500);

	//现在推完了

	Chassis.Changhu_velocity(v_back);
	HAL_Delay(400);				//这个参数可能要改，看看十字校准的效果
	Chassis.Changhu_velocity(v_stop);	

	//十字校准
	read_redsense();
	while(!(right[2]==1 && right[3]==1)){
		Chassis.Changhu_velocity(v_backlow);
		HAL_Delay(20);
		read_redsense();
	}

	Chassis.Changhu_velocity(v_left);
	HAL_Delay(300);
  read_redsense();
	while(!(back[2]==1 && back[3]==1)){
		left_track();
	}	
	Chassis.Changhu_velocity(v_stop);
	HAL_Delay(1000);

	//现在开始拿第二个低难度壶
	//前进固定距离
	Chassis.Changhu_velocity(v_frontlow);
	HAL_Delay(3500);
	Chassis.Changhu_velocity(v_stop);
	HAL_Delay(2000);
	Chassis.Changhu_velocity(v_backlow);
	HAL_Delay(900);/////////////////////////////////////////这个地方需要调试，先卡住然后往后退
	Chassis.Changhu_velocity(v_stop);
	HAL_Delay(2000);
	//放下夹子
	Claw.Changhu_velocity(claw_downdown_rotate);
	HAL_Delay(4500);/////////////////////////////////////
	Claw.Changhu_velocity(v_stop);
	//吸起来
	Relay[1].set_Relay_output_situation(1);
	Relay[3].set_Relay_output_situation(1);
	Relay[2].set_Relay_output_situation(0);  //吸起
	HAL_Delay(5000);
	//上升
	Claw.Changhu_velocity(claw_upup_rotate);
	HAL_Delay(3000);
	Claw.Changhu_velocity(v_stop);//机械臂上升 
	//往后退，时间可能要调整
	Chassis.Changhu_velocity(v_back);//与向前进保持一样的距离，虽然可能重一点，在此之后十字校准
	HAL_Delay(400);
	Chassis.Changhu_velocity(v_stop);
	
	//十字校准
	read_redsense();
	while(!(left[2]==1 && left[3]==1)){
		Chassis.Changhu_velocity(v_backlow);
		HAL_Delay(20);   
		read_redsense();
	}
	
	Chassis.Changhu_velocity(v_left);
	HAL_Delay(300);
	//动两格就位
	Chassis.Changhu_velocity(v_stop);
	HAL_Delay(500);
	read_redsense();
	while(!(back[2]==1 && back[3]==1)){
		Chassis.Changhu_velocity(v_leftlow);
		HAL_Delay(10);
		read_redsense();
	}
	Chassis.Changhu_velocity(v_left);
	HAL_Delay(20);
	Chassis.Changhu_velocity(v_stop);
	HAL_Delay(1000);

	//十字校准
//	trace_check_crossroad();

    //推出冰壶

	Claw.Changhu_velocity(claw_down_rotate);
	HAL_Delay(8000);
	Claw.Changhu_velocity(v_stop);//机械臂下降
	
	Relay[2].set_Relay_output_situation(1);//放下	
	Relay[1].set_Relay_output_situation(0);
	
	Claw.Changhu_velocity(claw_up_rotate);
	HAL_Delay(3000);
	Claw.Changhu_velocity(v_stop);//机械臂上升

	Relay[0].set_Relay_output_situation(0);
	HAL_Delay(1500);//不知道在干什么

	//前进

	Chassis.Changhu_velocity(v_frontlowlow);
	HAL_Delay(4700);
	Chassis.Changhu_velocity(v_stop);
	HAL_Delay(2000);
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Chassis.Changhu_velocity(v_rightlowlow);
	HAL_Delay(290);//////////////////////////////
	Chassis.Changhu_velocity(v_stop);
	HAL_Delay(500);
	
	Relay[0].set_Relay_output_situation(1); //此时常开（开路即断路）端闭合，电磁阀两端出现电势差，气缸将冰壶推出
	HAL_Delay(1500);
      
	Relay[0].set_Relay_output_situation(0);//气缸收回
	HAL_Delay(1500);

	//现在第二个也推完了，定位到高难度初始位置
	Chassis.Changhu_velocity(v_back);
	HAL_Delay(800);				//这个参数可能要改，看看十字校准的效果
	Chassis.Changhu_velocity(v_stop);	

	//十字校准
	read_redsense();
	while(!(left[2]==1 && left[3]==1)){
		Chassis.Changhu_velocity(v_backlow);
		HAL_Delay(20);
		read_redsense();
	}

	Chassis.Changhu_velocity(v_rotate);//旋转180度
	HAL_Delay(5200);//先旋转个大概然后再慢慢对上
	//trace_xuanzhuan();

	//十字定位
	trace_check_crossroad();
	Claw.Changhu_velocity(claw_up_rotate);
	HAL_Delay(1500);
	 HAL_UART_Transmit_DMA(&huart1,trbuf,16);
	Chassis.Changhu_velocity(v_front);
	HAL_Delay(1000);
	Chassis.Changhu_velocity(v_slowfront);
	HAL_Delay(2000);
//！！注意，这是高难度区第一次用视觉，在此判断，如果是己方的话
	if(uart1_receive_buffer[1]=='1')
{
	/*Chassis.Changhu_velocity(v_slowfront);
	HAL_Delay(8000);
	Chassis.Changhu_velocity(v_stop);						//往高难度取壶区走
	*/
	Claw.Changhu_velocity(claw_downdown_rotate);
	HAL_Delay(6000);
	Claw.Changhu_velocity(v_stop);//机械臂下降
	
	Relay[1].set_Relay_output_situation(1);
	Relay[2].set_Relay_output_situation(1);
	Relay[3].set_Relay_output_situation(0);  //吸起
	HAL_Delay(5000);
	
	Claw.Changhu_velocity(claw_upup_rotate);
	HAL_Delay(2000);
	Claw.Changhu_velocity(v_stop);//机械臂上升
	
	Chassis.Changhu_velocity(v_back);
	HAL_Delay(1000);
	Chassis.Changhu_velocity(v_stop);					//往后走点，这个还没测/////////////////////////////////////////////////0000000000000000000000000000000000000
	
	Chassis.Changhu_velocity(v_rotate);//旋转180度
	HAL_Delay(5400);
	trace_xuanzhuan();
	
	//十字定位
	trace_check_crossroad();
	
	Chassis.Changhu_velocity(v_front);
	HAL_Delay(1500);
	Chassis.Changhu_velocity(v_stop);
	
	Claw.Changhu_velocity(claw_down_rotate);
	HAL_Delay(7000);
	Claw.Changhu_velocity(v_stop);//机械臂下降
	
	Relay[3].set_Relay_output_situation(1);//放下
	Relay[1].set_Relay_output_situation(0);
	
	Claw.Changhu_velocity(claw_up_rotate);
	HAL_Delay(3000);
	Claw.Changhu_velocity(v_stop);//机械臂上升
	
	Relay[0].set_Relay_output_situation(0);
	HAL_Delay(1500);//这个地方应该是要在初始定义中写，我认为不是在这里加
	
	Chassis.Changhu_velocity(v_slowfront);
	HAL_Delay(200);
	Chassis.Changhu_velocity(v_stop);				//走一丢丢
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Chassis.Changhu_velocity(v_rightlowlow);
	HAL_Delay(300);//////////////////////////////
	
	Relay[0].set_Relay_output_situation(1); //此时常开（开路即断路）端闭合，电磁阀两端出现电势差，气缸将冰壶推出
	HAL_Delay(1500);
      
	Relay[0].set_Relay_output_situation(0);//气缸收回
	HAL_Delay(1500);

//在此结束了第一个推的过程
//掉头识别第二个

	Chassis.Changhu_velocity(v_back);
	HAL_Delay(1100);				//这个参数可能要改，看看十字校准的效果
	Chassis.Changhu_velocity(v_stop);
	
HAL_Delay(5200);//先旋转个大概然后再慢慢对上
	trace_xuanzhuan();
	trace_check_crossroad();
	
	
}

Chassis.Changhu_velocity(v_back);
	HAL_Delay(1000);
	Chassis.Changhu_velocity(v_stop);					//往后走点，这个还没测/////////////////////////////////////////////////0000000000000000000000000000000000000

Chassis.Changhu_velocity(v_left);
	HAL_Delay(300);
  read_redsense();
	while(!(front[2]==1 && front[3]==1)){
		right_track();
	}
	Chassis.Changhu_velocity(v_stop);
	HAL_Delay(2000);
	
 HAL_UART_Transmit_DMA(&huart1,trbuf,16);
	Chassis.Changhu_velocity(v_front);
	HAL_Delay(1000);
	Chassis.Changhu_velocity(v_slowfront);
	HAL_Delay(2000);
//高难度第二次识别（如果判断不是己方：直接右移开始第二个推，第二个和第三个都是自己的，可以直接推）
if(uart1_receive_buffer[1]=='1')
{
	/*Chassis.Changhu_velocity(v_slowfront);
	HAL_Delay(8000);
	Chassis.Changhu_velocity(v_stop);						//往高难度取壶区走
	*/
	Claw.Changhu_velocity(claw_downdown_rotate);
	HAL_Delay(6000);
	Claw.Changhu_velocity(v_stop);//机械臂下降
	
	Relay[1].set_Relay_output_situation(1);
	Relay[2].set_Relay_output_situation(1);
	Relay[3].set_Relay_output_situation(0);  //吸起
	HAL_Delay(5000);
	
	Claw.Changhu_velocity(claw_upup_rotate);
	HAL_Delay(2000);
	Claw.Changhu_velocity(v_stop);//机械臂上升
	
	Chassis.Changhu_velocity(v_back);
	HAL_Delay(1000);
	Chassis.Changhu_velocity(v_stop);					//往后走点，这个还没测
	
	Chassis.Changhu_velocity(v_rotate);//旋转180度
	HAL_Delay(5400);//
	trace_xuanzhuan();
	//十字定位
	trace_check_crossroad();
	
	Chassis.Changhu_velocity(v_right);
	HAL_Delay(300);
	read_redsense();
	while(!(front[2]==1 && front[3]==1)){
		right_track();
	}
	Chassis.Changhu_velocity(v_stop);
	HAL_Delay(2000);
	
	Chassis.Changhu_velocity(v_front);
	HAL_Delay(1500);
	Chassis.Changhu_velocity(v_stop);
	
	Claw.Changhu_velocity(claw_down_rotate);
	HAL_Delay(7000);
	Claw.Changhu_velocity(v_stop);//机械臂下降
	
	Relay[3].set_Relay_output_situation(1);//放下
	Relay[1].set_Relay_output_situation(0);
	
	Claw.Changhu_velocity(claw_up_rotate);
	HAL_Delay(3000);
	Claw.Changhu_velocity(v_stop);//机械臂上升
	
	Relay[0].set_Relay_output_situation(0);
	HAL_Delay(1500);//这个地方应该是要在初始定义中写，我认为不是在这里加
	
	Chassis.Changhu_velocity(v_slowfront);
	HAL_Delay(200);
	Chassis.Changhu_velocity(v_stop);				//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Chassis.Changhu_velocity(v_leftlowlow);
	HAL_Delay(200);//////////////////////////////
	Relay[0].set_Relay_output_situation(1); //此时常开（开路即断路）端闭合，电磁阀两端出现电势差，气缸将冰壶推出
	HAL_Delay(1500);
      
	Relay[0].set_Relay_output_situation(0);//气缸收回
	HAL_Delay(1500);
	
	//完成第二个推壶过程，往后走到十字区
	Chassis.Changhu_velocity(v_back);
	HAL_Delay(1100);
	Chassis.Changhu_velocity(v_stop);	
	trace_check_crossroad();
	Chassis.Changhu_velocity(v_rotate);//旋转180度
	HAL_Delay(5200);//先旋转个大概然后再慢慢对上
	trace_xuanzhuan();
	trace_check_crossroad();
}else {
	Chassis.Changhu_velocity(v_back);
	HAL_Delay(1000);
	Chassis.Changhu_velocity(v_stop);					//往后走点，这个还没测/////////////////////////////////////////////////0000000000000000000000000000000000000

  Chassis.Changhu_velocity(v_right);
	HAL_Delay(300);
	read_redsense();
	while(!(front[2]==1 && front[3]==1)){
		right_track();
	}
	Chassis.Changhu_velocity(v_stop);
	HAL_Delay(2000);
}
HAL_UART_Transmit_DMA(&huart1,trbuf,16);
Chassis.Changhu_velocity(v_front);
	HAL_Delay(1000);
	Chassis.Changhu_velocity(v_slowfront);
	HAL_Delay(2000);
if(uart1_receive_buffer[1]=='1'){
	/*Chassis.Changhu_velocity(v_slowfront);
	HAL_Delay(8000);
	Chassis.Changhu_velocity(v_stop);						//往高难度取壶区走
	*/
	Claw.Changhu_velocity(claw_downdown_rotate);
	HAL_Delay(6000);
	Claw.Changhu_velocity(v_stop);//机械臂下降
	
	Relay[1].set_Relay_output_situation(1);
	Relay[2].set_Relay_output_situation(1);
	Relay[3].set_Relay_output_situation(0);  //吸起
	HAL_Delay(5000);
	
	Claw.Changhu_velocity(claw_upup_rotate);
	HAL_Delay(2000);
	Claw.Changhu_velocity(v_stop);//机械臂上升
	
	Chassis.Changhu_velocity(v_back);
	HAL_Delay(1000);
	Chassis.Changhu_velocity(v_stop);					//往后走点，这个还没测
	
	Chassis.Changhu_velocity(v_rotate);//旋转180度
	HAL_Delay(5400);
	trace_xuanzhuan();
	
	//十字定位
	trace_check_crossroad();
	
	Chassis.Changhu_velocity(v_front);
	HAL_Delay(1500);
	Chassis.Changhu_velocity(v_stop);
	
	Claw.Changhu_velocity(claw_down_rotate);
	HAL_Delay(7000);
	Claw.Changhu_velocity(v_stop);//机械臂下降
	
	Relay[3].set_Relay_output_situation(1);//放下
	Relay[1].set_Relay_output_situation(0);
	
	Claw.Changhu_velocity(claw_up_rotate);
	HAL_Delay(3000);
	Claw.Changhu_velocity(v_stop);//机械臂上升
	
	Relay[0].set_Relay_output_situation(0);
	HAL_Delay(1500);//这个地方应该是要在初始定义中写，我认为不是在这里加
	
	Chassis.Changhu_velocity(v_slowfront);
	HAL_Delay(200);
	Chassis.Changhu_velocity(v_stop);				//走一丢丢
	
	Relay[0].set_Relay_output_situation(1); //此时常开（开路即断路）端闭合，电磁阀两端出现电势差，气缸将冰壶推出
	HAL_Delay(1500);
      
	Relay[0].set_Relay_output_situation(0);//气缸收回
	HAL_Delay(1500);
}


  /*机器人运动结束--------------------------*/

  

  
	
  
  
 


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  /*while(1){
   

*/
    
   
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

  

 
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	
	if(TIM9 == htim->Instance)
	{
		switch(capture_Cnt){
			case 1:
				capture_Buf[0] = HAL_TIM_ReadCapturedValue(&htim9,TIM_CHANNEL_1);//获取当前的捕获值.
				__HAL_TIM_SET_CAPTUREPOLARITY(&htim9,TIM_CHANNEL_1,TIM_ICPOLARITY_FALLING);  //设置为下降沿捕获
				capture_Cnt++;
				break;
			case 2:
				capture_Buf[1] = HAL_TIM_ReadCapturedValue(&htim9,TIM_CHANNEL_1);//获取当前的捕获值.
				HAL_TIM_IC_Stop_IT(&htim9,TIM_CHANNEL_1); //停止捕获   或者: __HAL_TIM_DISABLE(&htim9);
				capture_Cnt++;    
		}
	
	}
	
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
	  
	  
	  
	  
	  
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
