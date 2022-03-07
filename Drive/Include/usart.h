#ifndef __USART_H
#define __USART_H


#include "stm32f4xx.h"
#include <stdio.h>
#include <stdarg.h>

/*----------------------USART1配置宏 - 核心板----------------*/

#define  USART1_BaudRate  115200

#define  USART1_TX_PIN				GPIO_Pin_9				// TX 引脚
#define	 USART1_TX_PORT				GPIOA					// TX 引脚端口
#define	 USART1_TX_CLK				RCC_AHB1Periph_GPIOA	// TX 引脚时钟
#define  USART1_TX_PinSource		GPIO_PinSource9			// 引脚源

#define  USART1_RX_PIN				GPIO_Pin_10            // RX 引脚
#define	 USART1_RX_PORT				GPIOA                  // RX 引脚端口
#define	 USART1_RX_CLK				RCC_AHB1Periph_GPIOA   // RX 引脚时钟
#define  USART1_RX_PinSource		GPIO_PinSource10       // 引脚源


/*----------------------USART2配置宏 ------------------------*/

#define  USART2_BaudRate  115200

#define  USART2_TX_PIN				GPIO_Pin_5				// TX 引脚
#define	 USART2_TX_PORT				GPIOD					// TX 引脚端口
#define	 USART2_TX_CLK				RCC_AHB1Periph_GPIOD	// TX 引脚时钟
#define  USART2_TX_PinSource  		GPIO_PinSource5			// 引脚源

#define  USART2_RX_PIN				GPIO_Pin_6				// RX 引脚
#define	 USART2_RX_PORT				GPIOD					// RX 引脚端口
#define	 USART2_RX_CLK				RCC_AHB1Periph_GPIOD	// RX 引脚时钟
#define  USART2_RX_PinSource  		GPIO_PinSource6			// 引脚源


/*----------------------UART7配置宏 ------------------------*/

#define  UART7_BaudRate  115200

#define  UART7_TX_PIN				GPIO_Pin_7				// TX 引脚
#define	 UART7_TX_PORT				GPIOF					// TX 引脚端口
#define	 UART7_TX_CLK				RCC_AHB1Periph_GPIOF	// TX 引脚时钟
#define  UART7_TX_PinSource   		GPIO_PinSource7			// 引脚源

#define  UART7_RX_PIN				GPIO_Pin_6				// RX 引脚
#define	 UART7_RX_PORT				GPIOF					// RX 引脚端口
#define	 UART7_RX_CLK				RCC_AHB1Periph_GPIOF	// RX 引脚时钟
#define  UART7_RX_PinSource			GPIO_PinSource6			// 引脚源


/*---------------------- 函数声明 ----------------------------*/

void  Usart1_Config (void);	// USART1 初始化函数
void  Usart2_Config (void);	// USART2 初始化函数
void  Uart7_Config (void);	// UART7 初始化函数
void  USART_printf (USART_TypeDef* USARTx, char *Data, ...);	// USART printf函数
	
#endif 


