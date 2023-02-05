/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Sensor_Timer_A_Pin GPIO_PIN_5
#define Sensor_Timer_A_GPIO_Port GPIOE
#define Sensor_Timer_B_Pin GPIO_PIN_6
#define Sensor_Timer_B_GPIO_Port GPIOE
#define Left_Encoder_A_Pin GPIO_PIN_9
#define Left_Encoder_A_GPIO_Port GPIOE
#define Left_Encoder_B_Pin GPIO_PIN_11
#define Left_Encoder_B_GPIO_Port GPIOE
#define SW_U_Pin GPIO_PIN_12
#define SW_U_GPIO_Port GPIOE
#define SW_D_Pin GPIO_PIN_13
#define SW_D_GPIO_Port GPIOE
#define SW_L_Pin GPIO_PIN_14
#define SW_L_GPIO_Port GPIOE
#define SW_R_Pin GPIO_PIN_15
#define SW_R_GPIO_Port GPIOE
#define SEN_0_8_Pin GPIO_PIN_8
#define SEN_0_8_GPIO_Port GPIOD
#define SEN_1_9_Pin GPIO_PIN_9
#define SEN_1_9_GPIO_Port GPIOD
#define SEN_2_10_Pin GPIO_PIN_10
#define SEN_2_10_GPIO_Port GPIOD
#define SEN_3_11_Pin GPIO_PIN_11
#define SEN_3_11_GPIO_Port GPIOD
#define SEN_4_12_Pin GPIO_PIN_12
#define SEN_4_12_GPIO_Port GPIOD
#define SEN_5_13_Pin GPIO_PIN_13
#define SEN_5_13_GPIO_Port GPIOD
#define SEN_6_14_Pin GPIO_PIN_14
#define SEN_6_14_GPIO_Port GPIOD
#define SEN_7_15_Pin GPIO_PIN_15
#define SEN_7_15_GPIO_Port GPIOD
#define Right_Encoder_A_Pin GPIO_PIN_6
#define Right_Encoder_A_GPIO_Port GPIOC
#define Right_Encoder_B_Pin GPIO_PIN_7
#define Right_Encoder_B_GPIO_Port GPIOC
#define VFD_DATA_Pin GPIO_PIN_0
#define VFD_DATA_GPIO_Port GPIOD
#define VFD_RS_Pin GPIO_PIN_1
#define VFD_RS_GPIO_Port GPIOD
#define VFD_CE_Pin GPIO_PIN_2
#define VFD_CE_GPIO_Port GPIOD
#define VFD_CLK_Pin GPIO_PIN_3
#define VFD_CLK_GPIO_Port GPIOD
#define right_motor_pwm_Pin GPIO_PIN_5
#define right_motor_pwm_GPIO_Port GPIOB
#define Motor_Timer_A_Pin GPIO_PIN_6
#define Motor_Timer_A_GPIO_Port GPIOB
#define Motor_Timer_B_Pin GPIO_PIN_7
#define Motor_Timer_B_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
