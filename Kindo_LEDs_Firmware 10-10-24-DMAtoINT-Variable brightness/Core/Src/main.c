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


/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

UART_HandleTypeDef huart2;

#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
set to ‘Yes? calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

/**
* @brief Retargets the C library printf function to the USART.
* @param None
* @retval None
*/
PUTCHAR_PROTOTYPE
{
/* Place your implementation of fputc here */
/* e.g. write a character to the USART */
HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1,10);
return ch;
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
I2C_HandleTypeDef hi2c1;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim3;
DMA_HandleTypeDef hdma_tim3_ch1;
DMA_HandleTypeDef hdma_tim3_ch2;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */


float bred=0,bgreen=0,bblue=0;
uint8_t state_cup=0;
uint8_t state_gate=0;
//#define PWM_HI (74)
//#define PWM_LO (32)
 uint8_t rxbuf[10];
uint8_t rx_data;
uint8_t location=255;
uint8_t pattern_strip;
uint8_t pattern_cup;
uint8_t pattern_gate;
uint8_t red_cup;
uint8_t green_cup;
uint8_t blue_cup;
uint8_t red_gate;
uint8_t green_gate;
uint8_t blue_gate;
uint8_t rx_complete=0;
uint8_t state_protocol =0;
uint8_t cup_blink =0;
uint8_t gate_blink =0;
uint32_t start_time_gate;
uint32_t start_time_cup;
uint32_t current_time_gate;
uint32_t current_time_cup;
int Cup_Brightness = 45;
int Gate_Brightness = 45;
uint8_t strip_brightness = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_TIM1_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_TIM3_Init(void);
static void MX_I2C1_Init(void);
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
  MX_DMA_Init();
  MX_TIM1_Init();
  MX_USART2_UART_Init();
  MX_TIM3_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
	printf("Firmware Version Compute Board : v1.0 \r\n");
//for(int i=0;i<25;i++)
//		{
//			Set_LED(i,245 ,65, 170);
//		}

		//Set_Brightness(45);
	//	WS2812_Send();
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1,1-1);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3,1-1);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4,1-1);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
	
	Set_LED_GATE(0,0,0,0);
	Set_LED_GATE(1,0,0,0);
		Set_Brightness_GATE(Gate_Brightness);
		WS2812_Send(GATE);
		
		Set_LED_CUP(0,0,0,0);
	Set_LED_CUP(1,0,0,0);
	Set_Brightness_CUP(Cup_Brightness);
		WS2812_Send(CUP);
	
	
	HAL_UART_Receive_IT(&huart2,  &rx_data, 1);
	 //HAL_UARTEx_ReceiveToIdle_DMA(&huart2,  rxbuf, 10);
	 //__HAL_DMA_DISABLE_IT(&hdma_usart2_rx, DMA_IT_HT);
//	 Set_LED_CUP(0,0,0,0);
//		Set_LED_CUP(1,0,0,0);
//		WS2812_Send(CUP);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
		Set_LED_GATE(0,0,0,0);
	Set_LED_GATE(1,0,0,0);
		Set_Brightness_GATE(Gate_Brightness);
		WS2812_Send(GATE);
		
		Set_LED_CUP(0,0,0,0);
	Set_LED_CUP(1,0,0,0);
	Set_Brightness_CUP(Cup_Brightness);
		WS2812_Send(CUP);
  while (1)
  {
		
		
		//printf("Hello \r\n");
		if (pattern_strip ==11)
		{
			BreatheWhite();
		
		}	
		else if (pattern_strip ==12)
		{
			BreatheRed();
		}
		else if (pattern_strip ==13)
		{
			BreatheGreen();
		}		
		else if (pattern_strip ==14)
		{
			BreatheBlue();
		}
		else if (pattern_strip ==15)
		{
			Whiteon();
		}
		else if (pattern_strip ==16)
		{
			Redon();
		}
		else if (pattern_strip ==17)
		{
			Greenon();
		}
		else if (pattern_strip ==18)
		{
			Blueon();
		}
		else if(pattern_strip==19)
			{
				Alloff();
		}
//		else if (pattern ==15)
//		{
//			Whiteon();
//		}
//		else if (pattern ==16)
//		{
//			Redon();
//		}
//		else if (pattern ==17)
//		{
//			Greenon();
//		}
//		else if (pattern ==18)
//		{
//			Blueon();
//		}
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
//		for (int i=0; i<46; i++)
//	  {
//		  Set_Brightness(i);
//		  WS2812_Send();
//		 // HAL_Delay (50);
//			//printf("Code Init \r\n");
//	  }

//	  for (int i=45; i>=0; i--)
//	  {
//		  Set_Brightness(i);
//		  WS2812_Send();
//		 // HAL_Delay (50);
//	  }
		 //Breathe();
		 if(gate_blink==1){
		current_time_gate = HAL_GetTick();
		if(current_time_gate-start_time_gate>1000){
			if(state_gate == 1){
				state_gate =0;
				Set_LED_GATE(0,red_gate,green_gate,blue_gate);
				Set_LED_GATE(1,red_gate, green_gate,blue_gate);
				Set_Brightness_GATE(Gate_Brightness);
				WS2812_Send(GATE);
			}
			else{
				state_gate=1;

				Set_LED_GATE(0,0,0,0);
				Set_LED_GATE(1,0,0,0);
				Set_Brightness_GATE(Gate_Brightness);
				WS2812_Send(GATE);
			}
		start_time_gate=current_time_gate;
		}
	}
	if(cup_blink==1){
		current_time_cup = HAL_GetTick();
		if(current_time_cup-start_time_cup>1000){
			if(state_cup == 1){
				state_cup =0;

				Set_LED_CUP(0,red_cup,green_cup,blue_cup);
				Set_LED_CUP(1,red_cup,green_cup,blue_cup);
				Set_Brightness_CUP(Cup_Brightness);
				WS2812_Send(CUP);
			}
			else{
				state_cup=1;
				Set_LED_CUP(0,0,0,0);
				Set_LED_CUP(1,0,0,0);
				Set_Brightness_CUP(Cup_Brightness);
				WS2812_Send(CUP);
			}
		start_time_cup=current_time_cup;
		}
	}
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
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV1;
  RCC_OscInitStruct.PLL.PLLN = 9;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV3;
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
  hi2c1.Init.Timing = 0x20303E5D;
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
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 10-1;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 256-1;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 120-1;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.Pulse = 120;
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.BreakFilter = 0;
  sBreakDeadTimeConfig.BreakAFMode = TIM_BREAK_AFMODE_INPUT;
  sBreakDeadTimeConfig.Break2State = TIM_BREAK2_DISABLE;
  sBreakDeadTimeConfig.Break2Polarity = TIM_BREAK2POLARITY_HIGH;
  sBreakDeadTimeConfig.Break2Filter = 0;
  sBreakDeadTimeConfig.Break2AFMode = TIM_BREAK_AFMODE_INPUT;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */
  HAL_TIM_MspPostInit(&htim1);

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 2-1;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 30-1;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */
  HAL_TIM_MspPostInit(&htim3);

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
  huart2.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel2_3_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel2_3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel2_3_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
  if (huart == &huart2) {
		if(rx_data==7)
		{
			
			HAL_UART_Receive(&huart2,  rxbuf, 5,100);

			location = rxbuf[0];
			if(location == CUP)
			{
			red_cup = rxbuf[2];
			green_cup = rxbuf[3];
			blue_cup = rxbuf[4];
			pattern_cup = rxbuf[1];
			//Cup_Brightness = rxbuf[5];
			//printf("cup \r\n");
			}
			else if(location == GATE)
			{
				red_gate = rxbuf[2];
				green_gate = rxbuf[3];
				blue_gate = rxbuf[4];
				pattern_gate = rxbuf[1];
				//Gate_Brightness = rxbuf[5];
				//printf("Gate \r\n");
			}
			rx_complete=1;
			switch(location)
		{
			case STRIP:
				pattern_strip = rxbuf[1];
				strip_brightness = rxbuf[5];
				//pattern =11;
				printf("STRIP \r\n");
				printf("Pattern %d \r\n", pattern_strip);
				switch (pattern_strip)
				{
					case 1:
					printf("Breathe White 1\r\n");
					pattern_strip =11;
					break;

					case 2:
						pattern_strip =12;
					break;

					case 3:
						pattern_strip =13;
					break;

					case 4:
						pattern_strip =14;
					break;

					case 5:
						pattern_strip =15;
					Whiteon();
					break;
					
					case 6:
						pattern_strip =16;
					Redon();
					break;
					
					case 7:
						pattern_strip =17;
					Greenon();
					break;
					
					case 8:
						pattern_strip =18;
					Blueon();
					break;
					
					case 9:
						Alloff();
						pattern_strip=19;
					Alloff();
					break;
					
					default:
						pattern_strip=19;
						Alloff();
					Alloff();
					break;
				}
				
				break;
		case CUP:
			//Cup_Brightness = rxbuf[5];
			//pattern_cup = rxbuf[1];
			if(pattern_cup ==1){
				//Set_Brightness_CUP(Cup_Brightness);
				Set_LED_CUP(0,red_cup,green_cup,blue_cup);
				Set_LED_CUP(1,red_cup,green_cup,blue_cup);
				Set_Brightness_CUP(45);
				WS2812_Send(CUP);
		printf("Cup \r\n");
				cup_blink=0;
			}
			else if(pattern_cup ==2){
				cup_blink=1;
				start_time_cup = HAL_GetTick();
			}
				break;
		case GATE:
			//Gate_Brightness = rxbuf[5];
			//pattern_gate = rxbuf[1];	
			if(pattern_gate==1){
				//Set_Brightness_CUP(Cup_Brightness);
				
				Set_LED_GATE(0,red_gate, green_gate,blue_gate);
				Set_LED_GATE(1,red_gate, green_gate,blue_gate);
				Set_Brightness_GATE(45);
				WS2812_Send(GATE);
				printf("Gate \r\n");
				printf("Gate %d, %d, %d\r\n",red_gate,green_gate, blue_gate);
				gate_blink=0;
			}
			else if(pattern_gate ==2){
				gate_blink=1;
				start_time_gate = HAL_GetTick();
			}
				break;
					
			}
			memset(rxbuf, 0x00, sizeof(rxbuf));
			//HAL_UART_Receive_DMA(&huart2,  &rx_data, 1);
		
		}
		HAL_UART_Receive_IT(&huart2,  &rx_data, 1);
			
		
		
	}
}

//void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
//{
//	if (huart->Instance == USART2)
//	{
//		printf("Message %s\r\n",rxbuf);
//		if(rxbuf[0]==7)
//		{
//			printf("true \r\n");
//			location = rxbuf[1];
//			pattern = rxbuf[2];
//			red = rxbuf[3];
//			green = rxbuf[4];
//			blue = rxbuf[5];
//			rx_complete=1;
//			switch(location)
//		{
//			case STRIP:
//				//pattern =11;
//				printf("STRIP \r\n");
//			printf("Pattern %d \r\n", pattern);
//				switch (pattern)
//				{
//					case 1:
//					printf("Breathe White 1\r\n");
//					pattern =11;
//					break;

//					case 2:
//						pattern =12;
//					break;

//					case 3:
//						pattern =13;
//					break;

//					case 4:
//						pattern =14;
//					break;

//					case 5:
//						pattern =15;
//					Whiteon();
//					break;
//					
//					case 6:
//						pattern =16;
//					Redon();
//					break;
//					
//					case 7:
//						pattern =17;
//					Greenon();
//					break;
//					
//					case 8:
//						pattern =18;
//					Blueon();
//					break;
//					
//					case 9:
//						Alloff();
//						pattern=19;
//					break;
//					
//					default:
//						pattern=19;
//						Alloff();
//					break;
//				}
//				
//				break;
//		case CUP:

//				Set_LED_CUP(0,red,green,blue);
//				Set_LED_CUP(1,red,green,blue);
//				WS2812_Send(CUP);
//		printf("Cup \r\n");
//					
//				break;
//		case GATE:
//				Set_LED_GATE(0,red,green,blue);
//				Set_LED_GATE(1,red,green,blue);
//				WS2812_Send(GATE);
//		printf("Gate \r\n");
//				break;
//					
//			}
//		}
//		memset(rxbuf, 0x00, sizeof(rxbuf));
//	}
//	HAL_UARTEx_ReceiveToIdle_DMA(&huart2, rxbuf, 10);
//	__HAL_DMA_DISABLE_IT(&hdma_usart2_rx, DMA_IT_HT);
//	
//}


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
