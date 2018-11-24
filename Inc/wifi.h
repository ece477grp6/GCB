#ifndef _wifi_H_
#define _wifi_H_

#include <stdbool.h>

extern int lspeed;
extern int rspeed;
extern uint8_t GPS_message[28];
extern uint32_t ADC_value[14];
extern int x_value;
extern int y_value;

void	wifi_Init(void);
void	wifi_RxCpltCallback(void);
void	wifi_Check(void);

#endif
