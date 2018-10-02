/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_hal.h"
#include "adc.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */
#include<stdbool.h>
#include "GPS.h"

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
int time = 1;
int escLimit = 7;
uint8_t OK[] = "OK";
uint8_t AT[] = "AT\r\n\n";
uint8_t AT_RST[] = "AT+RST\r\n\n";
uint8_t AT_CIPMUX[] = "AT+CIPMUX=1\r\n\n";
uint8_t AT_CIPSERVER[] = "AT+CIPSERVER=1\r\n\n";
uint8_t AT_CIPSEND[] = "AT+CIPSEND=0,25\r\n\n";
uint8_t AT_CIPCLOSE[] = "AT+CIPCLOSE=0\r\n\n";
//uint8_t send_message[] = "<html><head><title></title></head><body>Happy Mid Autumn Festival</body></html>";
uint8_t send_message[] = "Happy Mid Autumn Festival";
uint8_t RST_RSV[526];
uint8_t CIPMUX_RSV[32];
uint8_t CIPSERVER_RSV[38];
bool reset_OK = false;
uint8_t HTTP_RSV[50];
uint8_t TCP_RSV[5];
bool TCP_signal = false;
int TCP_RSV_count = 0;
uint8_t TCP_temp;
uint8_t SEND_RSV[40];
uint8_t rcv_message[3];

bool send_ok = false;
bool send_ready = false;

uint8_t temp[30];
int temp_num = 0;

uint8_t GPS_message[27];

bool ADC_flag = false;
uint32_t ADC_value[5];

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
void HAL_TIM_PeriodElapsedCallback (TIM_HandleTypeDef *htim){
	if( htim->Instance==TIM1 ){

		if((100-TIM2->CCR1)<escLimit){
			TIM2->CCR1 -= 1;
		}
		else if((100-TIM2->CCR1)>escLimit){
			TIM2->CCR1 += 1;
		}
		else{}
		if(time>0){
			time--;
		}
		else{
			HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_15);
			time = 1;
			ADC_flag = true;
		}
		if(!strcmp(rcv_message,"low")){
			escLimit = 8;
		}
		if(!strcmp(rcv_message,"hig")){
			escLimit = 9;
		}
		if(!strcmp(rcv_message,"sto")){
			escLimit = 5;
		}
	}
}
void HAL_UART_RxCpltCallback (UART_HandleTypeDef *huart){
  if(huart->Instance==USART1){
	  GPS_RxCpltCallback();
  }
  if(huart->Instance==USART2){
	  	temp[temp_num] = TCP_temp;
		temp_num++;
		if(temp_num>29){
			temp_num = 0;
		}
		if(TCP_signal && TCP_RSV_count<5){
			TCP_RSV[TCP_RSV_count] = TCP_temp;
			TCP_RSV_count +=1;
			if(TCP_RSV_count==5){
				send_ready = true;
				TCP_signal = false;
			}
		}
		if(TCP_temp==':'){
			TCP_signal = true;
			TCP_RSV_count = 0;
		}
	}
}

/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

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
  MX_USART2_UART_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_USART1_UART_Init();
  MX_ADC1_Init();

  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim1);
  HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);

  HAL_ADC_Start_DMA(&hadc1,ADC_value, 5);

  TIM2->CCR1 = 100;

  GPS_Init();

  HAL_UART_Transmit(&huart2, AT, sizeof(AT), 1000);
  HAL_Delay(1000);
  HAL_UART_Transmit(&huart2, AT_RST, sizeof(AT_RST), 1000);
  HAL_UART_Receive(&huart2, RST_RSV,sizeof(RST_RSV),1000);
  if(strstr(RST_RSV,OK)!=NULL){
	  reset_OK = true;
  }
  HAL_Delay(1000);
  HAL_UART_Transmit(&huart2, AT_CIPMUX, sizeof(AT_CIPMUX), 1000);
  HAL_UART_Receive(&huart2, CIPMUX_RSV,sizeof(CIPMUX_RSV),1000);
  HAL_Delay(1000);
  HAL_UART_Transmit(&huart2, AT_CIPSERVER, sizeof(AT_CIPSERVER), 1000);
  HAL_UART_Receive(&huart2, CIPSERVER_RSV,sizeof(CIPSERVER_RSV),1000);
  HAL_Delay(1000);


//  HAL_UART_Transmit(&huart2, AT_CIPMUX, sizeof(AT_CIPMUX), 1000);
//  HAL_UART_Transmit(&huart2, AT_CIPSERVER, sizeof(AT_CIPSERVER), 1000);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
	  HAL_UART_Receive_IT(&huart2, &TCP_temp,sizeof(TCP_temp));
	  GPS_Check();

	  if(send_ready){
		  HAL_UART_Transmit(&huart2, AT_CIPSEND, sizeof(AT_CIPSEND), 1000);
		  HAL_Delay(1000);
		  HAL_UART_Transmit(&huart2, GPS_message, sizeof(GPS_message), 1000);
		  HAL_UART_Receive(&huart2, SEND_RSV,sizeof(SEND_RSV),1000);
		  send_ready = false;
	  }


  }
  /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Configure the main internal regulator output voltage 
    */
  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 50;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV8;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV4;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void _Error_Handler(char * file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler_Debug */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
