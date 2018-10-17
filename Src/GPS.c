#include "usart.h"
#include "GPS.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define	GPS_USART huart1
uint8_t	GPS_Buffer[512];
extern uint8_t GPS_rcv;

extern uint8_t GPS_message[27];

void GPS_Init(void)
{
	HAL_UART_Receive_IT(&GPS_USART,GPS_Buffer,512);
}

void GPS_RxCpltCallback(void)
{
	GPS_rcv = 1;
}

void GPS_Check(void)
{
	if(GPS_rcv){
		char *str;
		str = strstr((char*)GPS_Buffer,"$GPGGA,");
		if(str!=NULL)
		{
			memcpy( GPS_message, &str[17], 26);
			GPS_message[26] = '\0';
			if(!strstr((char*)GPS_message,",N,") && !strstr((char*)GPS_message,",S,")){
				memset(GPS_message,'0',sizeof(GPS_message));
			}
		}
		memset(GPS_Buffer,0,sizeof(GPS_Buffer));
	}
	HAL_UART_Receive_IT(&GPS_USART,GPS_Buffer,512);
}
