/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "motor.h"
#include "myprint.h"

#include "myusb.h"
#include "adc.h"
#include "driving_peripherals.h"
#include "effect_system.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
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
/*	  struct Effect spring_effect = {0};

	  spring_effect.condition.negative_coefficient = -0.075;
	  spring_effect.condition.positive_coefficient = 0.075;
	  spring_effect.effect_block.gain = 100;
	  spring_effect.effect_block.effect_type = ET_Spring;

	  uint16_t spring_effect_index = ES_AddEffect(spring_effect);
	  ES_StartEffect(spring_effect_index);

	  struct Effect damper_effect = {0};

	  damper_effect.condition.negative_coefficient = -0.5;
	  damper_effect.condition.positive_coefficient = 0.5;
	  damper_effect.effect_block.gain = 100;
	  damper_effect.effect_block.effect_type = ET_Damper;

	  uint16_t damper_effect_index = ES_AddEffect(damper_effect);
	  ES_StartEffect(damper_effect_index);*/

	  struct Effect constant_force_effect = {0};

	  constant_force_effect.constant_force.magnitude = 200;
	  constant_force_effect.effect_block.gain = 100;
	  constant_force_effect.effect_block.effect_type = ET_ConstantForce;

	  uint16_t constant_force_effect_index = ES_AddEffect(constant_force_effect);
	  ES_StartEffect(constant_force_effect_index);
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
  MX_USART3_UART_Init();
  MX_TIM3_Init();
  MX_TIM15_Init();
  /* USER CODE BEGIN 2 */

  //Start rotary encoder
  HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);

  Motor_Start();

  //Initialize pedals/peripherals
  ADC_Init();

  //Find zero position


  myprint("Starting USB...\n\r");
  myusb_Initialize();

  //uint8_t direction = 0; //0 = right, 1 = left
  //volatile int16_t rotation_value = 0;



  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
/*
	  rotation_value = htim3.Instance->CNT;

	  if ((int16_t)htim3.Instance->CNT < 0)
	  {
		  direction = 0;
		  rotation_value = rotation_value * -1;
	  }
	  else
	  {
		  direction = 1;
	  }

	  rotation_value = rotation_value * 0.075;

	  if (rotation_value > 600) rotation_value = 600;

	  //myprint_dec(rotation_value);

	  Motor_SetForce(rotation_value);
	  Motor_SetDirection(direction);
*/
	  report.members.steering = htim3.Instance->CNT;

	  report.members.throttle 	= Pedal_GetAxisValue(throttle);
	  report.members.brake 		= Pedal_GetAxisValue(brake);
	  report.members.clutch		= Pedal_GetAxisValue(clutch);
	  report.members.handbrake	= Pedal_GetAxisValue(handbrake);


    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART3|RCC_PERIPHCLK_TIM15
                              |RCC_PERIPHCLK_TIM34|RCC_PERIPHCLK_USB|RCC_PERIPHCLK_ADC34;
  PeriphClkInit.Usart3ClockSelection = RCC_USART3CLKSOURCE_HSI;
  PeriphClkInit.USBClockSelection = RCC_USBCLKSOURCE_PLLCLK;
  PeriphClkInit.Tim15ClockSelection = RCC_TIM15CLK_PLLCLK;
  PeriphClkInit.Tim34ClockSelection = RCC_TIM34CLK_PLLCLK;
  PeriphClkInit.Adc34ClockSelection = RCC_ADC34PLLCLK_DIV2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
//RCC_PERIPHCLK_USB | RCC_PERIPHCLK_ADC34
//PeriphClkInit.Adc34ClockSelection = RCC_ADC34PLLCLK_DIV2;





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
