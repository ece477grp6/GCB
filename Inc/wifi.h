#ifndef _wifi_H_
#define _wifi_H_

#include <stdbool.h>

extern int lspeed;
extern int rspeed;
extern uint8_t GPS_message[27];
extern uint32_t ADC_value[14];

void	wifi_Init(void);
void	wifi_RxCpltCallback(void);
void	wifi_Check(void);

#endif
