#include "usart.h"
#include "GPS.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define	GPS_USART huart1
uint8_t	GPS_Buffer[512];
uint8_t	GPS_temp;
uint16_t GPS_index = 0;
uint32_t GPS_rcvTime;

extern uint8_t GPS_message[27];

void GPS_Init(void)
{
	HAL_UART_Receive_IT(&GPS_USART,&GPS_temp,1);
}

void GPS_RxCpltCallback(void)
{
	GPS_rcvTime = HAL_GetTick();
	if(GPS_index < 510)
	{
		GPS_Buffer[GPS_index] = GPS_temp;
		GPS_index++;
	}
	HAL_UART_Receive_IT(&GPS_USART,&GPS_temp,1);
}

void GPS_Check(void)
{
	if(HAL_GetTick()-GPS_rcvTime>50){
		char *str;
		str = strstr((char*)GPS_Buffer,"$GPGGA,");
		if(str!=NULL)
		{
			memcpy( GPS_message, &str[17], 26);
			GPS_message[26] = '\0';
		}
		memset(GPS_Buffer,0,sizeof(GPS_Buffer));
		GPS_index=0;
	}
}
