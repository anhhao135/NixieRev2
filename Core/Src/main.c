/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define PCF85363A_I2C_ADDR (0x51 << 1) //1010001 in binary, 9.3.1 in datasheet, left bit shift to allow RW LSB

#define IMU_I2C_ADDR (0b1101000 << 1)
#define IMU_REG_DEVICE_CONFIG 0x01
#define IMU_REG_DRIVE_CONFIG2 0x04
#define IMU_REG_WHOAMI 0x75
#define IMU_REG_TEMP_DATA1 0x09
#define IMU_REG_TEMP_DATA2 0x0A





#define PCF85363A_REG_BATSWITCH 0x26
#define PCF85363A_REG_FUNCTION 0x28
#define PCF85363A_REG_RESETS 0x2F


//RTC MODE

#define PCF85363A_REG_100THSECS 0x00
#define PCF85363A_REG_SECS 0x01
#define PCF85363A_REG_MINS 0x02
#define PCF85363A_REG_HOURS 0x03
#define PCF85363A_REG_DAYS 0x04
#define PCF85363A_REG_WEEKDAYS 0x05
#define PCF85363A_REG_MONTHS 0x06
#define PCF85363A_REG_YEARS 0x07
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */


int GetSeconds(){
	uint8_t data;
	HAL_I2C_Mem_Read(&hi2c1, PCF85363A_I2C_ADDR, PCF85363A_REG_SECS, I2C_MEMADD_SIZE_8BIT, &data, 1, HAL_MAX_DELAY);

	uint8_t tens = (data & 0b01110000) >> 4;
	uint8_t digits = data & 0b00001111;
	return tens * 10 + digits;
}

int IMURead(){
	uint8_t data;
	HAL_I2C_Mem_Read(&hi2c1, IMU_I2C_ADDR, IMU_REG_WHOAMI, I2C_MEMADD_SIZE_8BIT, &data, 1, HAL_MAX_DELAY);

	return data;
}

double GetIMUTemp(){

	uint8_t data1;
	HAL_I2C_Mem_Read(&hi2c1, IMU_I2C_ADDR, IMU_REG_TEMP_DATA1, I2C_MEMADD_SIZE_8BIT, &data1, 1, HAL_MAX_DELAY);
	uint8_t data0;
	HAL_I2C_Mem_Read(&hi2c1, IMU_I2C_ADDR, IMU_REG_TEMP_DATA0, I2C_MEMADD_SIZE_8BIT, &data0, 1, HAL_MAX_DELAY);

	return data;
}



void writeNixie1Number(int number){

	switch(number%10){
		case 0:
			HAL_GPIO_WritePin(GPIOA, IN_17_1_A_Pin, 0);
			HAL_GPIO_WritePin(GPIOA, IN_17_1_B_Pin, 0);
			HAL_GPIO_WritePin(GPIOA, IN_17_1_C_Pin, 0);
			HAL_GPIO_WritePin(GPIOA, IN_17_1_D_Pin, 0);
			break;
		case 1:
			HAL_GPIO_WritePin(GPIOA, IN_17_1_A_Pin, 1);
			HAL_GPIO_WritePin(GPIOA, IN_17_1_B_Pin, 0);
			HAL_GPIO_WritePin(GPIOA, IN_17_1_C_Pin, 0);
			HAL_GPIO_WritePin(GPIOA, IN_17_1_D_Pin, 0);
			break;
		case 2:
			HAL_GPIO_WritePin(GPIOA, IN_17_1_A_Pin, 0);
			HAL_GPIO_WritePin(GPIOA, IN_17_1_B_Pin, 1);
			HAL_GPIO_WritePin(GPIOA, IN_17_1_C_Pin, 0);
			HAL_GPIO_WritePin(GPIOA, IN_17_1_D_Pin, 0);
			break;
		case 3:
			HAL_GPIO_WritePin(GPIOA, IN_17_1_A_Pin, 1);
			HAL_GPIO_WritePin(GPIOA, IN_17_1_B_Pin, 1);
			HAL_GPIO_WritePin(GPIOA, IN_17_1_C_Pin, 0);
			HAL_GPIO_WritePin(GPIOA, IN_17_1_D_Pin, 0);
			break;
		case 4:
			HAL_GPIO_WritePin(GPIOA, IN_17_1_A_Pin, 0);
			HAL_GPIO_WritePin(GPIOA, IN_17_1_B_Pin, 0);
			HAL_GPIO_WritePin(GPIOA, IN_17_1_C_Pin, 1);
			HAL_GPIO_WritePin(GPIOA, IN_17_1_D_Pin, 0);
			break;
		case 5:
			HAL_GPIO_WritePin(GPIOA, IN_17_1_A_Pin, 1);
			HAL_GPIO_WritePin(GPIOA, IN_17_1_B_Pin, 0);
			HAL_GPIO_WritePin(GPIOA, IN_17_1_C_Pin, 1);
			HAL_GPIO_WritePin(GPIOA, IN_17_1_D_Pin, 0);
			break;
		case 6:
			HAL_GPIO_WritePin(GPIOA, IN_17_1_A_Pin, 0);
			HAL_GPIO_WritePin(GPIOA, IN_17_1_B_Pin, 1);
			HAL_GPIO_WritePin(GPIOA, IN_17_1_C_Pin, 1);
			HAL_GPIO_WritePin(GPIOA, IN_17_1_D_Pin, 0);
			break;
		case 7:
			HAL_GPIO_WritePin(GPIOA, IN_17_1_A_Pin, 1);
			HAL_GPIO_WritePin(GPIOA, IN_17_1_B_Pin, 1);
			HAL_GPIO_WritePin(GPIOA, IN_17_1_C_Pin, 1);
			HAL_GPIO_WritePin(GPIOA, IN_17_1_D_Pin, 0);
			break;
		case 8:
			HAL_GPIO_WritePin(GPIOA, IN_17_1_A_Pin, 0);
			HAL_GPIO_WritePin(GPIOA, IN_17_1_B_Pin, 0);
			HAL_GPIO_WritePin(GPIOA, IN_17_1_C_Pin, 0);
			HAL_GPIO_WritePin(GPIOA, IN_17_1_D_Pin, 1);
			break;
		case 9:
			HAL_GPIO_WritePin(GPIOA, IN_17_1_A_Pin, 1);
			HAL_GPIO_WritePin(GPIOA, IN_17_1_B_Pin, 0);
			HAL_GPIO_WritePin(GPIOA, IN_17_1_C_Pin, 0);
			HAL_GPIO_WritePin(GPIOA, IN_17_1_D_Pin, 1);
			break;
		default:
			HAL_GPIO_WritePin(GPIOA, IN_17_1_A_Pin, 1);
			HAL_GPIO_WritePin(GPIOA, IN_17_1_B_Pin, 1);
			HAL_GPIO_WritePin(GPIOA, IN_17_1_C_Pin, 1);
			HAL_GPIO_WritePin(GPIOA, IN_17_1_D_Pin, 1);
			break;

	}

}

void writeNixie2Number(int number){

	switch(number%10){
		case 0:
			HAL_GPIO_WritePin(GPIOA, IN_17_2_A_Pin, 0);
			HAL_GPIO_WritePin(GPIOA, IN_17_2_B_Pin, 0);
			HAL_GPIO_WritePin(GPIOA, IN_17_2_C_Pin, 0);
			HAL_GPIO_WritePin(GPIOA, IN_17_2_D_Pin, 0);
			break;
		case 1:
			HAL_GPIO_WritePin(GPIOA, IN_17_2_A_Pin, 1);
			HAL_GPIO_WritePin(GPIOA, IN_17_2_B_Pin, 0);
			HAL_GPIO_WritePin(GPIOA, IN_17_2_C_Pin, 0);
			HAL_GPIO_WritePin(GPIOA, IN_17_2_D_Pin, 0);
			break;
		case 2:
			HAL_GPIO_WritePin(GPIOA, IN_17_2_A_Pin, 0);
			HAL_GPIO_WritePin(GPIOA, IN_17_2_B_Pin, 1);
			HAL_GPIO_WritePin(GPIOA, IN_17_2_C_Pin, 0);
			HAL_GPIO_WritePin(GPIOA, IN_17_2_D_Pin, 0);
			break;
		case 3:
			HAL_GPIO_WritePin(GPIOA, IN_17_2_A_Pin, 1);
			HAL_GPIO_WritePin(GPIOA, IN_17_2_B_Pin, 1);
			HAL_GPIO_WritePin(GPIOA, IN_17_2_C_Pin, 0);
			HAL_GPIO_WritePin(GPIOA, IN_17_2_D_Pin, 0);
			break;
		case 4:
			HAL_GPIO_WritePin(GPIOA, IN_17_2_A_Pin, 0);
			HAL_GPIO_WritePin(GPIOA, IN_17_2_B_Pin, 0);
			HAL_GPIO_WritePin(GPIOA, IN_17_2_C_Pin, 1);
			HAL_GPIO_WritePin(GPIOA, IN_17_2_D_Pin, 0);
			break;
		case 5:
			HAL_GPIO_WritePin(GPIOA, IN_17_2_A_Pin, 1);
			HAL_GPIO_WritePin(GPIOA, IN_17_2_B_Pin, 0);
			HAL_GPIO_WritePin(GPIOA, IN_17_2_C_Pin, 1);
			HAL_GPIO_WritePin(GPIOA, IN_17_2_D_Pin, 0);
			break;
		case 6:
			HAL_GPIO_WritePin(GPIOA, IN_17_2_A_Pin, 0);
			HAL_GPIO_WritePin(GPIOA, IN_17_2_B_Pin, 1);
			HAL_GPIO_WritePin(GPIOA, IN_17_2_C_Pin, 1);
			HAL_GPIO_WritePin(GPIOA, IN_17_2_D_Pin, 0);
			break;
		case 7:
			HAL_GPIO_WritePin(GPIOA, IN_17_2_A_Pin, 1);
			HAL_GPIO_WritePin(GPIOA, IN_17_2_B_Pin, 1);
			HAL_GPIO_WritePin(GPIOA, IN_17_2_C_Pin, 1);
			HAL_GPIO_WritePin(GPIOA, IN_17_2_D_Pin, 0);
			break;
		case 8:
			HAL_GPIO_WritePin(GPIOA, IN_17_2_A_Pin, 0);
			HAL_GPIO_WritePin(GPIOA, IN_17_2_B_Pin, 0);
			HAL_GPIO_WritePin(GPIOA, IN_17_2_C_Pin, 0);
			HAL_GPIO_WritePin(GPIOA, IN_17_2_D_Pin, 1);
			break;
		case 9:
			HAL_GPIO_WritePin(GPIOA, IN_17_2_A_Pin, 1);
			HAL_GPIO_WritePin(GPIOA, IN_17_2_B_Pin, 0);
			HAL_GPIO_WritePin(GPIOA, IN_17_2_C_Pin, 0);
			HAL_GPIO_WritePin(GPIOA, IN_17_2_D_Pin, 1);
			break;
		default:
			HAL_GPIO_WritePin(GPIOA, IN_17_2_A_Pin, 1);
			HAL_GPIO_WritePin(GPIOA, IN_17_2_B_Pin, 1);
			HAL_GPIO_WritePin(GPIOA, IN_17_2_C_Pin, 1);
			HAL_GPIO_WritePin(GPIOA, IN_17_2_D_Pin, 1);
			break;

	}

}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

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
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */

  int seconds = 0;
  int IMUReadData = 0;

  IMUReadData = IMURead();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

	seconds = GetSeconds();
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	HAL_GPIO_WritePin(GPIOA, NIXIE_SHUTDOWN_Pin, 0);


	HAL_Delay(100);
	HAL_GPIO_TogglePin(LED_BLINK_GPIO_Port, LED_BLINK_Pin);

	if (seconds == 100){
		seconds = 0;
	}


	writeNixie2Number(seconds % 10);
	writeNixie1Number(seconds / 10);

  }
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
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV2;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x2000090E;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, IN_17_2_A_Pin|IN_17_2_D_Pin|IN_17_2_B_Pin|IN_17_2_C_Pin
                          |IN_17_1_A_Pin|IN_17_1_D_Pin|IN_17_1_B_Pin|IN_17_1_C_Pin
                          |NIXIE_SHUTDOWN_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_BLINK_GPIO_Port, LED_BLINK_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : IN_17_2_A_Pin IN_17_2_D_Pin IN_17_2_B_Pin IN_17_2_C_Pin
                           IN_17_1_A_Pin IN_17_1_D_Pin IN_17_1_B_Pin IN_17_1_C_Pin */
  GPIO_InitStruct.Pin = IN_17_2_A_Pin|IN_17_2_D_Pin|IN_17_2_B_Pin|IN_17_2_C_Pin
                          |IN_17_1_A_Pin|IN_17_1_D_Pin|IN_17_1_B_Pin|IN_17_1_C_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : LED_BLINK_Pin */
  GPIO_InitStruct.Pin = LED_BLINK_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_BLINK_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : NIXIE_SHUTDOWN_Pin */
  GPIO_InitStruct.Pin = NIXIE_SHUTDOWN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(NIXIE_SHUTDOWN_GPIO_Port, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

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
