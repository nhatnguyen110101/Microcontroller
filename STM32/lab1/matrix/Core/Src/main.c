/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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

#include "Hour_Zero_header.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  //uint8_t button_0 = 0;
  //uint8_t button_1 = 0;
  //uint8_t button_2 = 0;
  enum STATE { Hour, Minutes, Seconds };
  int counter_hour = 0;
  int counter_minutes = 0;
  enum STATE state = Hour;
  clearAllClock();
  while (1)
  {
	  switch (state){
	  case Hour:
		  state = Minutes;
		  break;
	  case Minutes:
		  if (counter_minutes == 12 ) {
			  counter_minutes = 0;
			  counter_hour++;
			  state = Hour;
		  } else {
		  	  state = Seconds;
		  }
		  break;
	  case Seconds:
		  setNumberOnClock(counter_hour,counter_minutes);
		  delay(10);
		  ++counter_minutes;
		  state = Minutes;
		  break;
	  }
	  delay(10);
  }
}




const int matrix_led[12][10] = {
		{0,1,0,0,0,0,1,1,1,1}, // 11
		{0,0,1,0,0,0,1,1,1,1}, // 12
		{0,0,0,1,0,0,1,1,1,1}, // 1
		{0,0,0,0,1,1,0,1,1,1}, // 2
		{0,0,0,0,1,1,1,0,1,1}, // 3
		{0,0,0,0,1,1,1,1,0,1}, // 4
		{0,0,0,1,0,1,1,1,1,0}, // 5
		{0,0,1,0,0,1,1,1,1,0}, // 6
		{0,1,0,0,0,1,1,1,1,0}, // 7
		{1,0,0,0,0,1,1,1,0,1}, // 8
		{1,0,0,0,0,1,1,0,1,1}, // 9
		{1,0,0,0,0,1,0,1,1,1}, // 10

};

void setNumberOnClock(int hour, int minutes){
	switch (hour){
	case 0:
		switch (minutes){
		case 0:
			Zero_0();
			break;
		case 1:
			Zero_1();
			break;
		case 2:
			Zero_2();
			break;
		case 3:
			Zero_3();
			break;
		case 4:
			Zero_4();
			break;
		case 5:
			Zero_5();
			break;
		case 6:
			Zero_6();
			break;
		case 7:
			Zero_7();
			break;
		case 8:
			Zero_8();
			break;
		case 9:
			//Zero_9();
			break;
		case 10:
			//Zero_10();
			break;
		case 11:
			//Zero_11();
			break;
		}
	}
}


void clearAllClock(){
	// CỘT
	 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,0);
	 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,0);
	 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,0);
	 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,0);
	 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,0);
	// HÀNG
  	 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_9,1);
  	 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_10,1);
  	 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_11,1);
  	 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_12,1);
  	 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_13,1);
}
void delay(unsigned int t) //hàm delay
   {
      unsigned int x,y;
      for(x=0;x<t;x++)
        {
            for(y=0;y<125;y++);
        }
   }

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7
                          |GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11
                          |GPIO_PIN_12|GPIO_PIN_13, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA4 PA5 PA6 PA7
                           PA8 PA9 PA10 PA11
                           PA12 PA13 */
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7
                          |GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11
                          |GPIO_PIN_12|GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 PB2 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
