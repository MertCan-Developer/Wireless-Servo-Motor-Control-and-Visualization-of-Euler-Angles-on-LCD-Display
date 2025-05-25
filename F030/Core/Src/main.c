/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "string.h"
#include "BNO055.h"
#include "bno055_port.h"
#include "Parser.h"

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
I2C_HandleTypeDef hi2c1;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
char RxBuff[13] = {0};
uint8_t RxChar = 0;
char Global_Receive_Buff[31];
uint8_t indeks = 0;
char temp[5] = {0};
struct bno055_t bno055_ = {0};

s32 comres = BNO055_ERROR;

u8 power_mode = BNO055_INIT_VALUE;

s16 accel_datax = BNO055_INIT_VALUE;

s16 accel_datay = BNO055_INIT_VALUE;

s16 accel_dataz = BNO055_INIT_VALUE;

struct bno055_accel_t accel_xyz;

s16 mag_datax = BNO055_INIT_VALUE;

s16 mag_datay = BNO055_INIT_VALUE;

s16 mag_dataz = BNO055_INIT_VALUE;

struct bno055_mag_t mag_xyz;

s16 gyro_datax = BNO055_INIT_VALUE;

s16 gyro_datay = BNO055_INIT_VALUE;

s16 gyro_dataz = BNO055_INIT_VALUE;

struct bno055_gyro_t gyro_xyz;

struct bno055_euler_t euler_hrp;

struct bno055_quaternion_t quaternion_wxyz;

struct bno055_linear_accel_t linear_acce_xyz;

struct bno055_gravity_t gravity_xyz;

struct bno055_accel_double_t d_accel_xyz;

struct bno055_mag_double_t d_mag_xyz;

struct bno055_gyro_double_t d_gyro_xyz;

struct bno055_euler_double_t d_euler_hpr;

struct bno055_linear_accel_double_t d_linear_accel_xyz;

struct bno055_gravity_double_t d_gravity_xyz;

struct bno055_data_double_t bno055_data = {0};

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_I2C1_Init(void);
/* USER CODE BEGIN PFP */
void RS485_TransmitData(char* buffer);

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
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
  HAL_UART_Receive_IT(&huart2, &RxChar, 1);

  bno055_.dev_addr = 0x28U;
  bno055_.delay_msec = bno055_delay;
  bno055_.bus_read = bno055_read;
  bno055_.bus_write = bno055_write;

  if(bno055_init(&bno055_) != BNO055_SUCCESS)
  {
	  Error_Handler();
  }

  power_mode = BNO055_POWER_MODE_NORMAL;

  comres += bno055_set_power_mode(power_mode);

  comres += bno055_set_operation_mode(BNO055_OPERATION_MODE_NDOF);

  Global_Receive_Buff[0] = '$';
  strcpy(&Global_Receive_Buff[1], ";S:");
  Global_Receive_Buff[8] = ',';
  Global_Receive_Buff[13] = ',';
  strcpy(&Global_Receive_Buff[18], ";M:");
  Global_Receive_Buff[24] = ',';
  strcpy(&Global_Receive_Buff[28], ";!");

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	  comres += bno055_read_accel_xyz(&accel_xyz);
	  comres += bno055_read_mag_xyz(&mag_xyz);
	  comres += bno055_read_gyro_xyz(&gyro_xyz);
	  comres += bno055_read_gravity_xyz(&gravity_xyz);
	  comres += bno055_read_euler_hrp(&euler_hrp);

	  //Datas converted to double
	  comres += bno055_convert_double_accel_xyz_mg(&d_accel_xyz);
	  comres += bno055_convert_double_mag_xyz_uT(&d_mag_xyz);
	  comres += bno055_convert_double_gyro_xyz_dps(&d_gyro_xyz);
	  comres += bno055_convert_double_gravity_xyz_msq(&d_gravity_xyz);
	  comres += bno055_convert_double_euler_hpr_deg(&d_euler_hpr);

	  sprintf(temp, "%04d", (int)d_euler_hpr.r);
	  memcpy(&Global_Receive_Buff[4], temp, 4);

	  sprintf(temp, "%04d", (int)d_euler_hpr.p);
	  memcpy(&Global_Receive_Buff[9], temp, 4);

	  sprintf(temp, "%04d", (int)d_euler_hpr.h);
	  memcpy(&Global_Receive_Buff[14], temp, 4);

	  memset(&Global_Receive_Buff[21], '-', 3);
	  memset(&Global_Receive_Buff[25], '-', 3);
	  HAL_UART_Transmit(&huart1, (uint8_t*)&Global_Receive_Buff, 31, 100);
	  HAL_Delay(100);
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL12;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_I2C1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_HSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
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
  hi2c1.Init.Timing = 0x00201D2B;
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
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(RS_485_GPIO_GPIO_Port, RS_485_GPIO_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : LED_Pin */
  GPIO_InitStruct.Pin = LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : RS_485_GPIO_Pin */
  GPIO_InitStruct.Pin = RS_485_GPIO_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(RS_485_GPIO_GPIO_Port, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

	//İndex değerinin buffer boyutundan küçük olup olmadığı kontrol edilir
	if(indeks <= 13)
	{
		RxBuff[indeks++] = RxChar;

		if((RxChar == '!') && (RxBuff[0] == '$'))
		{
			//Buffer'a gelen Servo-2 verilerini gönderilecek genel buffer'a kaydet
			for(uint8_t i=0; i<3; i++)
			{
				Global_Receive_Buff[21+i] = RxBuff[2+i];
			}

			//Buffer'a gelen Servo-1 verilerini gönderilecek genel buffer'a kaydet
			for(uint8_t i=0; i<3; i++)
			{
				Global_Receive_Buff[25+i] = RxBuff[6+i];
			}
		}

		//Bitiş karakteri geldiğinde bu bloğa gir
		if(RxChar == '!')
		{
			//Buffer'da toplanan paketi ayrıştır, format yanlışsa Error_Handler'a gir
			if(ParsePacket(RxBuff) != HAL_OK)
			{
				memset(&RxBuff, 0, 13);
				Error_Handler();
			}

			//Toplanan paketi gönder
			RS485_TransmitData(Global_Receive_Buff);

			//Buffer'ı sıfırla
			memset(&RxBuff, 0, 13);
		}
		//'\r' veya '\n' karakterleri gelmişse bu bloğa gir. İndeksi sıfırla ve tekrar kesme bekle
		else if(RxChar == '\r' || RxChar == '\n')
		{
			indeks = 0;
			HAL_UART_Receive_IT(&huart2, &RxChar, 1);
			return;
		}
	}
	HAL_UART_Receive_IT(&huart2, &RxChar, 1);
}

void RS485_TransmitData(char* buffer)
{
	HAL_GPIO_WritePin(RS_485_GPIO_GPIO_Port, RS_485_GPIO_Pin, GPIO_PIN_SET);
	HAL_UART_Transmit(&huart1, (uint8_t*)&Global_Receive_Buff, 31, 1000);
	HAL_GPIO_WritePin(RS_485_GPIO_GPIO_Port, RS_485_GPIO_Pin, GPIO_PIN_RESET);
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
