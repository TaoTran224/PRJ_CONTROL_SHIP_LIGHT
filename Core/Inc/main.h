/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "stm32f1xx_hal.h"

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
#define LIGHT_10_Pin GPIO_PIN_13
#define LIGHT_10_GPIO_Port GPIOC
#define LIGHT_11_Pin GPIO_PIN_14
#define LIGHT_11_GPIO_Port GPIOC
#define S1_Pin GPIO_PIN_15
#define S1_GPIO_Port GPIOC
#define S2_Pin GPIO_PIN_0
#define S2_GPIO_Port GPIOA
#define S3_Pin GPIO_PIN_1
#define S3_GPIO_Port GPIOA
#define S4_Pin GPIO_PIN_2
#define S4_GPIO_Port GPIOA
#define S5_Pin GPIO_PIN_3
#define S5_GPIO_Port GPIOA
#define S6_Pin GPIO_PIN_4
#define S6_GPIO_Port GPIOA
#define S7_Pin GPIO_PIN_5
#define S7_GPIO_Port GPIOA
#define LED_STT_Pin GPIO_PIN_6
#define LED_STT_GPIO_Port GPIOA
#define LED_RUN_Pin GPIO_PIN_7
#define LED_RUN_GPIO_Port GPIOA
#define SDN_Pin GPIO_PIN_0
#define SDN_GPIO_Port GPIOB
#define nIRQ_Pin GPIO_PIN_1
#define nIRQ_GPIO_Port GPIOB
#define nIRQ_EXTI_IRQn EXTI1_IRQn
#define SPI_NSS_Pin GPIO_PIN_12
#define SPI_NSS_GPIO_Port GPIOB
#define RS485_ENB_Pin GPIO_PIN_8
#define RS485_ENB_GPIO_Port GPIOA
#define LIGHT_0_Pin GPIO_PIN_11
#define LIGHT_0_GPIO_Port GPIOA
#define LIGHT_1_Pin GPIO_PIN_12
#define LIGHT_1_GPIO_Port GPIOA
#define LIGHT_2_Pin GPIO_PIN_15
#define LIGHT_2_GPIO_Port GPIOA
#define LIGHT_3_Pin GPIO_PIN_3
#define LIGHT_3_GPIO_Port GPIOB
#define LIGHT_4_Pin GPIO_PIN_4
#define LIGHT_4_GPIO_Port GPIOB
#define LIGHT_5_Pin GPIO_PIN_5
#define LIGHT_5_GPIO_Port GPIOB
#define LIGHT_6_Pin GPIO_PIN_6
#define LIGHT_6_GPIO_Port GPIOB
#define LIGHT_7_Pin GPIO_PIN_7
#define LIGHT_7_GPIO_Port GPIOB
#define LIGHT_8_Pin GPIO_PIN_8
#define LIGHT_8_GPIO_Port GPIOB
#define LIGHT_9_Pin GPIO_PIN_9
#define LIGHT_9_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
