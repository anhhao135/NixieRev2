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
#include "stm32g0xx_hal.h"

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
#define IN_17_2_A_Pin GPIO_PIN_0
#define IN_17_2_A_GPIO_Port GPIOA
#define IN_17_2_D_Pin GPIO_PIN_1
#define IN_17_2_D_GPIO_Port GPIOA
#define IN_17_2_B_Pin GPIO_PIN_2
#define IN_17_2_B_GPIO_Port GPIOA
#define IN_17_2_C_Pin GPIO_PIN_3
#define IN_17_2_C_GPIO_Port GPIOA
#define IN_17_1_A_Pin GPIO_PIN_4
#define IN_17_1_A_GPIO_Port GPIOA
#define IN_17_1_D_Pin GPIO_PIN_5
#define IN_17_1_D_GPIO_Port GPIOA
#define IN_17_1_B_Pin GPIO_PIN_6
#define IN_17_1_B_GPIO_Port GPIOA
#define IN_17_1_C_Pin GPIO_PIN_7
#define IN_17_1_C_GPIO_Port GPIOA
#define LED_BLINK_Pin GPIO_PIN_11
#define LED_BLINK_GPIO_Port GPIOA
#define NIXIE_SHUTDOWN_Pin GPIO_PIN_12
#define NIXIE_SHUTDOWN_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
