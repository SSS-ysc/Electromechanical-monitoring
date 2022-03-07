#ifndef __4G_linking_H
#define __4G_linking_H

#include "stm32f4xx.h"
#include "usart.h"  

/*---------------------- 4G引脚配置宏 ------------------------*/

#define _4G_LED_WORK_PIN            GPIO_Pin_2				// LED_WORK 引脚      
#define _4G_LED_WORK_PORT           GPIOG					// LED_WORK GPIO端口

#define _4G_LED_NET_PIN             GPIO_Pin_6				// LED_NET 引脚      
#define _4G_LED_NET_PORT            GPIOG					// LED_NET GPIO端口     

#define _4G_LINKA_PIN               GPIO_Pin_9				// LINKA 引脚      
#define _4G_LINKA_PORT              GPIOG					// LINKA GPIO端口     

#define _4G_LINKB_PIN               GPIO_Pin_10				// LINKB 引脚      
#define _4G_LINKB_PORT              GPIOG					// LINKB GPIO端口     

#define _4G_POWER_KEY_PIN           GPIO_Pin_11				// POWER_KEY 引脚      
#define _4G_POWER_KEY_PORT          GPIOG					// POWER_KEY GPIO端口   


/*----------------------USART6配置宏 ------------------------*/

#define  USART6_BaudRate  115200

#define  USART6_TX_PIN				GPIO_Pin_6						// TX 引脚
#define	 USART6_TX_PORT				GPIOC							// TX 引脚端口
#define	 USART6_TX_CLK				RCC_AHB1Periph_GPIOC			// TX 引脚时钟
#define  USART6_TX_PinSource		GPIO_PinSource6					// 引脚源

#define  USART6_RX_PIN				GPIO_Pin_7						// RX 引脚
#define	 USART6_RX_PORT				GPIOC							// RX 引脚端口
#define	 USART6_RX_CLK				RCC_AHB1Periph_GPIOC			// RX 引脚时钟
#define  USART6_RX_PinSource		GPIO_PinSource7					// 引脚源


#define Usart_4G( fmt, ... )        USART_printf ( USART6, fmt, ##__VA_ARGS__ )     

void	_4G_linking_Config (void);
void	_4G_SendByte(  uint8_t ch );

#endif 

