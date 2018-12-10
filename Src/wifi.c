#include "usart.h"
#include "wifi.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


#define	wifi_USART huart3

uint8_t OK[] = "OK";
uint8_t AT[] = "AT\r\n\n";
uint8_t AT_RST[] = "AT+RST\r\n\n";
uint8_t AT_CWMODE[] = "AT+CWMODE=1\r\n\n";
uint8_t AT_CWJAP[] = "AT+CWJAP=\"Qianli’s iPhone XSMax\",\"233333333\"\r\n\n";
uint8_t AT_CIPSTART[] = "AT+CIPSTART=\"TCP\",\"73.103.73.130\",8687\r\n\n";
uint8_t AT_CIPSEND[] = "AT+CIPSEND=112\r\n\n";
uint8_t AT_CIPCLOSE[] = "AT+CIPCLOSE=0\r\n\n";
uint8_t send_message[112];

uint8_t RST_RSV[526];
uint8_t JAP_RSV[126];
uint8_t START_RSV[100];
uint8_t CIPMUX_RSV[32];
uint8_t CIPSERVER_RSV[38];
bool reset_OK = false;
uint8_t HTTP_RSV[50];
uint8_t TCP_RSV[5];
bool TCP_signal = false;
int TCP_RSV_count = 0;
uint8_t TCP_temp;
uint8_t SEND_RSV[50];
uint8_t rcv_message[3];

bool send_ok = false;
bool send_ready = false;

uint8_t temp[30];
int temp_num = 0;

void wifi_Init(void)
{
	  HAL_UART_Transmit(&wifi_USART, AT, sizeof(AT), 1000);
	  HAL_UART_Transmit(&wifi_USART, AT_RST, sizeof(AT_RST), 1000);
	  HAL_UART_Receive(&wifi_USART, RST_RSV,sizeof(RST_RSV),1000);
	  if(strstr(RST_RSV,OK)!=NULL){
		  reset_OK = true;
	  }
	  HAL_Delay(1000);
	  HAL_UART_Transmit(&wifi_USART, AT_CWMODE, sizeof(AT_CWMODE), 1000);
	  HAL_Delay(3000);
	  HAL_UART_Transmit(&wifi_USART, AT_CWJAP, sizeof(AT_CWJAP), 1000);
	  HAL_UART_Receive(&wifi_USART, JAP_RSV,sizeof(JAP_RSV),8000);
	  HAL_UART_Transmit(&wifi_USART, AT_CIPSTART, sizeof(AT_CIPSTART), 1000);
	  HAL_UART_Receive(&wifi_USART, START_RSV,sizeof(START_RSV),1000);
}

void wifi_RxCpltCallback(void)
{
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

void format_msg(void){
	strcpy(send_message, GPS_message);
	strcat(send_message, ",");
	uint8_t x_string[5], y_string[5];
	sprintf(x_string, "%0+4d", x_value);
	sprintf(y_string, "%0+4d", y_value);
	strcat(send_message, x_string);
	strcat(send_message, ",");
	strcat(send_message, y_string);
	strcat(send_message, ",");
	int i;
	for (i = 0; i < 14; i++){
		uint8_t ADC_string[5];
		sprintf(ADC_string, "%04d", ADC_value[i]);
		strcat(send_message, ADC_string);
		strcat(send_message, ",");
	}
}

void wifi_Check(void)
{
	HAL_UART_Receive_IT(&wifi_USART, &TCP_temp,sizeof(TCP_temp));
	if(send_ready){
		char lspeedstr[3];
		char rspeedstr[3];
		memcpy(lspeedstr, TCP_RSV, 2);
		memcpy(rspeedstr, TCP_RSV+2, 2);
		lspeed = atoi(lspeedstr);
		rspeed = atoi(rspeedstr);
		if(TCP_RSV[4] == '1'){
			  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_10,GPIO_PIN_SET);
		}else{
			  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_10,GPIO_PIN_RESET);
		}
		HAL_UART_Transmit(&wifi_USART, AT_CIPSEND, sizeof(AT_CIPSEND), 1000);
		HAL_Delay(1000);
		format_msg();
		HAL_UART_Transmit(&wifi_USART, send_message, sizeof(send_message), 1000);
		HAL_UART_Receive(&wifi_USART, SEND_RSV,sizeof(SEND_RSV),1000);
		send_ready = false;
	}
}
