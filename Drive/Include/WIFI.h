#ifndef __WIFI_H
#define __WIFI_H

#include "stm32f4xx.h"
#include "usart.h"


#define     Usart_WIFI( fmt, ... )              USART_printf ( UART7, fmt, ##__VA_ARGS__ )  

void	WiFi_Config (void);
void	_WIFI_SendByte(  uint8_t ch );
	
#endif

