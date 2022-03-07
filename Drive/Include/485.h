#ifndef __485_H
#define __485_H

#include "stm32f4xx.h"
#include "usart.h"  

#define _485_RE_PIN              	GPIO_Pin_3			// 485_RE Òý½Å      
#define _485_DE_PIN              	GPIO_Pin_4			// 485_DE Òý½Å   
#define _485_PORT                	GPIOD				// 485_RE 485_DE GPIO¶Ë¿Ú
  
#define Usart_485( fmt, ... )        USART_printf ( UART7, fmt, ##__VA_ARGS__ )     

void _485_Config (void);
void	_485_SendByte(  uint8_t ch );

#endif

