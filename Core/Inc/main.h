/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stm32f4xx_it.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

//This is the timer of speed calculating unit of the chassis
#define CHASSIS_MOTOR_CALCULATE_TIM htim5
/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define TRACE_FRONT3_Pin GPIO_PIN_2
#define TRACE_FRONT3_GPIO_Port GPIOE
#define TRACE_FRONT4_Pin GPIO_PIN_3
#define TRACE_FRONT4_GPIO_Port GPIOE
#define TRACE_BACK1_Pin GPIO_PIN_4
#define TRACE_BACK1_GPIO_Port GPIOE
#define TRACE_BACK2_Pin GPIO_PIN_5
#define TRACE_BACK2_GPIO_Port GPIOE
#define TRACE_BACK3_Pin GPIO_PIN_6
#define TRACE_BACK3_GPIO_Port GPIOE
#define TRACE_BACK4_Pin GPIO_PIN_0
#define TRACE_BACK4_GPIO_Port GPIOF
#define TRACE_RIGHT1_Pin GPIO_PIN_1
#define TRACE_RIGHT1_GPIO_Port GPIOF
#define TRACE_RIGHT2_Pin GPIO_PIN_2
#define TRACE_RIGHT2_GPIO_Port GPIOF
#define TRACE_RIGHT3_Pin GPIO_PIN_3
#define TRACE_RIGHT3_GPIO_Port GPIOF
#define TRACE_RIGHT4_Pin GPIO_PIN_4
#define TRACE_RIGHT4_GPIO_Port GPIOF
#define TRACE_LEFT1_Pin GPIO_PIN_5
#define TRACE_LEFT1_GPIO_Port GPIOF
#define TRACE_LEFT2_Pin GPIO_PIN_6
#define TRACE_LEFT2_GPIO_Port GPIOF
#define TRACE_LEFT3_Pin GPIO_PIN_7
#define TRACE_LEFT3_GPIO_Port GPIOF
#define TRACE_LEFT4_Pin GPIO_PIN_9
#define TRACE_LEFT4_GPIO_Port GPIOF
#define WHEEL1_INPUT_Pin GPIO_PIN_0
#define WHEEL1_INPUT_GPIO_Port GPIOC
#define WHEEL2_INPUT_Pin GPIO_PIN_1
#define WHEEL2_INPUT_GPIO_Port GPIOC
#define WHEEL3_INPUT_Pin GPIO_PIN_2
#define WHEEL3_INPUT_GPIO_Port GPIOC
#define WHEEL4_INPUT_Pin GPIO_PIN_3
#define WHEEL4_INPUT_GPIO_Port GPIOC
#define WHEEL_A1_Pin GPIO_PIN_4
#define WHEEL_A1_GPIO_Port GPIOA
#define WHEEL_B1_Pin GPIO_PIN_5
#define WHEEL_B1_GPIO_Port GPIOA
#define WHEEL1_PWM_Pin GPIO_PIN_6
#define WHEEL1_PWM_GPIO_Port GPIOA
#define WHEEL3_PWM_Pin GPIO_PIN_7
#define WHEEL3_PWM_GPIO_Port GPIOA
#define WHEEL_A2_Pin GPIO_PIN_4
#define WHEEL_A2_GPIO_Port GPIOC
#define WHEEL_B2_Pin GPIO_PIN_5
#define WHEEL_B2_GPIO_Port GPIOC
#define WHEEL2_PWM_Pin GPIO_PIN_0
#define WHEEL2_PWM_GPIO_Port GPIOB
#define WHEEL_A3_Pin GPIO_PIN_1
#define WHEEL_A3_GPIO_Port GPIOB
#define WHEEL_B3_Pin GPIO_PIN_2
#define WHEEL_B3_GPIO_Port GPIOB
#define WHEEL1_EXTI_Pin GPIO_PIN_1
#define WHEEL1_EXTI_GPIO_Port GPIOG
#define RELAY_0_Pin GPIO_PIN_10
#define RELAY_0_GPIO_Port GPIOE
#define RELAY_1_Pin GPIO_PIN_11
#define RELAY_1_GPIO_Port GPIOE
#define RELAY_2_Pin GPIO_PIN_12
#define RELAY_2_GPIO_Port GPIOE
#define RELAY_3_Pin GPIO_PIN_13
#define RELAY_3_GPIO_Port GPIOE
#define CLAW_B2_Pin GPIO_PIN_8
#define CLAW_B2_GPIO_Port GPIOD
#define CLAW_A2_Pin GPIO_PIN_9
#define CLAW_A2_GPIO_Port GPIOD
#define CLAW_B1_Pin GPIO_PIN_10
#define CLAW_B1_GPIO_Port GPIOD
#define CLAW_A1_Pin GPIO_PIN_11
#define CLAW_A1_GPIO_Port GPIOD
#define CLAW1_PWM_Pin GPIO_PIN_12
#define CLAW1_PWM_GPIO_Port GPIOD
#define CLAW2_PWM_Pin GPIO_PIN_13
#define CLAW2_PWM_GPIO_Port GPIOD
#define WHEEL2_EXTI_Pin GPIO_PIN_2
#define WHEEL2_EXTI_GPIO_Port GPIOG
#define WHEEL3_EXTI_Pin GPIO_PIN_3
#define WHEEL3_EXTI_GPIO_Port GPIOG
#define WHEEL4_EXTI_Pin GPIO_PIN_4
#define WHEEL4_EXTI_GPIO_Port GPIOG
#define WHEEL_B4_Pin GPIO_PIN_7
#define WHEEL_B4_GPIO_Port GPIOC
#define WHEEL_A4_Pin GPIO_PIN_8
#define WHEEL_A4_GPIO_Port GPIOC
#define WHEEL4_PWM_Pin GPIO_PIN_9
#define WHEEL4_PWM_GPIO_Port GPIOC
#define HC_OUT_Pin GPIO_PIN_8
#define HC_OUT_GPIO_Port GPIOB
#define TRACE_FRONT1_Pin GPIO_PIN_0
#define TRACE_FRONT1_GPIO_Port GPIOE
#define TRACE_FRONT2_Pin GPIO_PIN_1
#define TRACE_FRONT2_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

#define TRACE_FRONT2_Pin GPIO_PIN_1
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
