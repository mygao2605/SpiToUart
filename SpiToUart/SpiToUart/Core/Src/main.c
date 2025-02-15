/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "Header_file.h"
#include "crc.h"

SPI_HandleTypeDef hspi1;
UART_HandleTypeDef huart3;
uint8_t spi_data[256];
uint8_t Header[6];
uint8_t uart_data[256]={0};
uint16_t checkCRC16_header;


//uint8_t sFrameRx;


void RS485Process(void)
{

	// ucChar =  USART_0_read_by#include "Data.h"te();

	while ((uint8_t)((USART3->ISR & 0x20)>>5) == 1)
	{
		uint8_t ucChar;
		ucChar = (uint8_t)(USART3->RDR);

		// Reading-----------------------------------------------
		if (sFrameRx.modbus_state == READING)
		{
			sFrameRx.u8BuffRead[sFrameRx.data_pointer++] = ucChar;
			if (sFrameRx.data_pointer == sFrameRx.byte_count)
			{
				sFrameRx.modbus_state = READING_END;
				ModbusProcess();
			}
		}

		// Check byte_count--------------------------------------
		if ((sFrameRx.u8BuffRead[3] == 0) && (sFrameRx.u8BuffRead[4] > 0))
		{
			sFrameRx.byte_count = 10 + sFrameRx.u8BuffRead[4];
		}

		// Start--------------------------------------------------
		if (sFrameRx.modbus_state == START)
		{
			if (ucChar == 0x55)
			{
				sFrameRx.data_pointer = 0;
				sFrameRx.u8BuffRead[sFrameRx.data_pointer++] = ucChar;
				sFrameRx.modbus_state = READING;

				}
				else
				{
					sFrameRx.modbus_state = START;
					sFrameRx.data_pointer = 0;
				}
			}

		}

}

void ModbusProcess(void)
{

//	sFrameRx.modbus_state = START;
//	HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, RESET);
//	for (uint8_t i = 0 ; i< 21 ; i++){
//
////		HAL_UART_Transmit(&huart3, spi_data, sizeof(spi_data), HAL_MAX_DELAY);
//		HAL_SPI_TransmitReceive(&hspi1, sFrameRx.u8BuffRead,spi_data,sizeof(spi_data), HAL_MAX_DELAY);
//		HAL_Delay(10);
//		HAL_SPI_TransmitReceive(&hspi1,uart_data,spi_data,sizeof(uart_data), HAL_MAX_DELAY);
//		HAL_UART_Transmit(&huart3, spi_data, sizeof(spi_data), HAL_MAX_DELAY);
//		sFrameRx.u8BuffRead[2]++;
//		for(int j =0; j < 6; j++)
//		{
//			Header[j] = sFrameRx.u8BuffRead[j];
//		}
//		checkCRC16_header=crc16_arc(Header, 6);
//		sFrameRx.u8BuffRead[6]=(uint8_t)(checkCRC16_header >> 8);
//		sFrameRx.u8BuffRead[7]=(uint8_t)(checkCRC16_header);
//		HAL_Delay(100);
//	}
//	HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, SET);



	sFrameRx.modbus_state = START;
		HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, RESET);
		if(sFrameRx.u8BuffRead[5] == 0x01){
		for (uint8_t i = 0 ; i< 21 ; i++){

	//		HAL_UART_Transmit(&huart3, spi_data, sizeof(spi_data), HAL_MAX_DELAY);
			HAL_SPI_TransmitReceive(&hspi1, sFrameRx.u8BuffRead,spi_data,sizeof(spi_data), HAL_MAX_DELAY);
			HAL_Delay(10);
			HAL_SPI_TransmitReceive(&hspi1,uart_data,spi_data,sizeof(uart_data), HAL_MAX_DELAY);
			HAL_UART_Transmit(&huart3, spi_data, sizeof(spi_data), HAL_MAX_DELAY);
			sFrameRx.u8BuffRead[2]++;
			for(int j =0; j < 6; j++)
			{
				Header[j] = sFrameRx.u8BuffRead[j];
			}
			checkCRC16_header=crc16_arc(Header, 6);
			sFrameRx.u8BuffRead[6]=(uint8_t)(checkCRC16_header >> 8);
			sFrameRx.u8BuffRead[7]=(uint8_t)(checkCRC16_header);
//			HAL_Delay(100);
		}
		HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, SET);
		}else if(sFrameRx.u8BuffRead[5] == 0x02){
			for (uint8_t i = 0 ; i< 16 ; i++){

				//		HAL_UART_Transmit(&huart3, spi_data, sizeof(spi_data), HAL_MAX_DELAY);
						HAL_SPI_TransmitReceive(&hspi1, sFrameRx.u8BuffRead,spi_data,sizeof(spi_data), HAL_MAX_DELAY);
						HAL_Delay(10);
						HAL_SPI_TransmitReceive(&hspi1,uart_data,spi_data,sizeof(uart_data), HAL_MAX_DELAY);
						HAL_UART_Transmit(&huart3, spi_data, sizeof(spi_data), HAL_MAX_DELAY);
						sFrameRx.u8BuffRead[2]++;
						for(int j =0; j < 6; j++)
						{
							Header[j] = sFrameRx.u8BuffRead[j];
						}
						checkCRC16_header=crc16_arc(Header, 6);
						sFrameRx.u8BuffRead[6]=(uint8_t)(checkCRC16_header >> 8);
						sFrameRx.u8BuffRead[7]=(uint8_t)(checkCRC16_header);
//						HAL_Delay(100);
					}

			HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, SET);

		}
}
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
static void MX_SPI1_Init(void);
static void MX_USART3_UART_Init(void);
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
  MX_SPI1_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
//  uint8_t uart_data[256] = {0x55, 0x00,c 0x01, 0x00, 0x02, 0x01, 0x59, 0xCD, 0x23, 0x35, 0x27, 0xD9};
//  uint8_t test[4]="test";
//  uint8_t spi_data[256];

//  uint8_t uart_data1[12] = {0x55, 0x00, 0x01, 0x00, 0x02, 0x02, 0x58, 0x8D, 0x24, 0x36, 0x16, 0x9B};
//  uint8_t uart_data2[50] = {0x55, 0x00, 0x02, 0x00, 0x0E, 0x03, 0xDC, 0x49, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,0x10, 0x11,0x22, 0x33,0x44, 0x8E, 0x95,0x21,0x55,
//		  0x00, 0x02, 0x00, 0x0E, 0x03, 0xDC, 0x49, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,0x10, 0x11,0x22, 0x33,0x44, 0x8E, 0x95,0x21};// 24
//  uint8_t spi_data[256]="test";
//  uint8_t uart_data_rec[256];





//  HAL_UART_Transmit(&huart3, hexStr, sizeof(hexStr), HAL_MAX_DELAY);
//  HAL_UART_Transmit(&huart3, test, sizeof(test), HAL_MAX_DELAY);

//  HAL_UART_Transmit(&huart3,test, sizeof(tesct), HAL_MAX_DELAY);
//  HAL_UART_Receive(&huart3, uart_data_rec, sizeof(uart_data_rec), HAL_MAX_DELAY);
  //status = HAL_UART_Receive(&huart3, uart_data_rec, sizeof(uart_data_rec), HAL_MAX_DELAY);
  //status = HAL_UART_Receive(&huart3, uart_data_rec, sizeof(uart_data_rec), 1000);
//  HAL_UART_Transmit(&huart3, test, sizeof(test), HAL_MAX_DELAY);
//  HAL_SPI_TransmitReceive(&hspi1, uart_data , spi_data  ,sizeof(spi_data), 1000);
//  HAL_UART_Transmit(&huart3, spi_data, sizeof(spi_data), HAL_MAX_DELAY);

  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  RS485Process();



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
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI|RCC_OSCILLATORTYPE_MSIK;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_0;
  RCC_OscInitStruct.MSIKClockRange = RCC_MSIKRANGE_4;
  RCC_OscInitStruct.MSIKState = RCC_MSIK_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLMBOOST = RCC_PLLMBOOST_DIV4;
  RCC_OscInitStruct.PLL.PLLM = 3;
  RCC_OscInitStruct.PLL.PLLN = 10;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 1;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLLVCIRANGE_1;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_PCLK3;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  SPI_AutonomousModeConfTypeDef HAL_SPI_AutonomousMode_Cfg_Struct = {0};

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 0x7;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  hspi1.Init.NSSPolarity = SPI_NSS_POLARITY_LOW;
  hspi1.Init.FifoThreshold = SPI_FIFO_THRESHOLD_01DATA;
  hspi1.Init.MasterSSIdleness = SPI_MASTER_SS_IDLENESS_00CYCLE;
  hspi1.Init.MasterInterDataIdleness = SPI_MASTER_INTERDATA_IDLENESS_00CYCLE;
  hspi1.Init.MasterReceiverAutoSusp = SPI_MASTER_RX_AUTOSUSP_DISABLE;
  hspi1.Init.MasterKeepIOState = SPI_MASTER_KEEP_IO_STATE_DISABLE;
  hspi1.Init.IOSwap = SPI_IO_SWAP_DISABLE;
  hspi1.Init.ReadyMasterManagement = SPI_RDY_MASTER_MANAGEMENT_INTERNALLY;
  hspi1.Init.ReadyPolarity = SPI_RDY_POLARITY_HIGH;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  HAL_SPI_AutonomousMode_Cfg_Struct.TriggerState = SPI_AUTO_MODE_DISABLE;
  HAL_SPI_AutonomousMode_Cfg_Struct.TriggerSelection = SPI_GRP1_GPDMA_CH0_TCF_TRG;
  HAL_SPI_AutonomousMode_Cfg_Struct.TriggerPolarity = SPI_TRIG_POLARITY_RISING;
  if (HAL_SPIEx_SetConfigAutonomousMode(&hspi1, &HAL_SPI_AutonomousMode_Cfg_Struct) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  huart3.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart3.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart3.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart3, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart3, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

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
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin : BUTTON_Pin */
  GPIO_InitStruct.Pin = BUTTON_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(BUTTON_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : CS_Pin */
  GPIO_InitStruct.Pin = CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(CS_GPIO_Port, &GPIO_InitStruct);

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
