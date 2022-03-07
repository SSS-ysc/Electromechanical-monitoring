#ifndef __4G_linking_H
#define __4G_linking_H

#include "stm32f4xx.h"
#include "usart.h"  

/*---------------------- 4G�������ú� ------------------------*/

#define _4G_LED_WORK_PIN            GPIO_Pin_2				// LED_WORK ����      
#define _4G_LED_WORK_PORT           GPIOG					// LED_WORK GPIO�˿�

#define _4G_LED_NET_PIN             GPIO_Pin_6				// LED_NET ����      
#define _4G_LED_NET_PORT            GPIOG					// LED_NET GPIO�˿�     

#define _4G_LINKA_PIN               GPIO_Pin_9				// LINKA ����      
#define _4G_LINKA_PORT              GPIOG					// LINKA GPIO�˿�     

#define _4G_LINKB_PIN               GPIO_Pin_10				// LINKB ����      
#define _4G_LINKB_PORT              GPIOG					// LINKB GPIO�˿�     

#define _4G_POWER_KEY_PIN           GPIO_Pin_11				// POWER_KEY ����      
#define _4G_POWER_KEY_PORT          GPIOG					// POWER_KEY GPIO�˿�   


/*----------------------USART6���ú� ------------------------*/

#define  USART6_BaudRate  115200

#define  USART6_TX_PIN				GPIO_Pin_6						// TX ����
#define	 USART6_TX_PORT				GPIOC							// TX ���Ŷ˿�
#define	 USART6_TX_CLK				RCC_AHB1Periph_GPIOC			// TX ����ʱ��
#define  USART6_TX_PinSource		GPIO_PinSource6					// ����Դ

#define  USART6_RX_PIN				GPIO_Pin_7						// RX ����
#define	 USART6_RX_PORT				GPIOC							// RX ���Ŷ˿�
#define	 USART6_RX_CLK				RCC_AHB1Periph_GPIOC			// RX ����ʱ��
#define  USART6_RX_PinSource		GPIO_PinSource7					// ����Դ


#define Usart_4G( fmt, ... )        USART_printf ( USART6, fmt, ##__VA_ARGS__ )     

void	_4G_linking_Config (void);
void	_4G_SendByte(  uint8_t ch );

#endif 

