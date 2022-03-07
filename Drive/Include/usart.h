#ifndef __USART_H
#define __USART_H


#include "stm32f4xx.h"
#include <stdio.h>
#include <stdarg.h>

/*----------------------USART1���ú� - ���İ�----------------*/

#define  USART1_BaudRate  115200

#define  USART1_TX_PIN				GPIO_Pin_9				// TX ����
#define	 USART1_TX_PORT				GPIOA					// TX ���Ŷ˿�
#define	 USART1_TX_CLK				RCC_AHB1Periph_GPIOA	// TX ����ʱ��
#define  USART1_TX_PinSource		GPIO_PinSource9			// ����Դ

#define  USART1_RX_PIN				GPIO_Pin_10            // RX ����
#define	 USART1_RX_PORT				GPIOA                  // RX ���Ŷ˿�
#define	 USART1_RX_CLK				RCC_AHB1Periph_GPIOA   // RX ����ʱ��
#define  USART1_RX_PinSource		GPIO_PinSource10       // ����Դ


/*----------------------USART2���ú� ------------------------*/

#define  USART2_BaudRate  115200

#define  USART2_TX_PIN				GPIO_Pin_5				// TX ����
#define	 USART2_TX_PORT				GPIOD					// TX ���Ŷ˿�
#define	 USART2_TX_CLK				RCC_AHB1Periph_GPIOD	// TX ����ʱ��
#define  USART2_TX_PinSource  		GPIO_PinSource5			// ����Դ

#define  USART2_RX_PIN				GPIO_Pin_6				// RX ����
#define	 USART2_RX_PORT				GPIOD					// RX ���Ŷ˿�
#define	 USART2_RX_CLK				RCC_AHB1Periph_GPIOD	// RX ����ʱ��
#define  USART2_RX_PinSource  		GPIO_PinSource6			// ����Դ


/*----------------------UART7���ú� ------------------------*/

#define  UART7_BaudRate  115200

#define  UART7_TX_PIN				GPIO_Pin_7				// TX ����
#define	 UART7_TX_PORT				GPIOF					// TX ���Ŷ˿�
#define	 UART7_TX_CLK				RCC_AHB1Periph_GPIOF	// TX ����ʱ��
#define  UART7_TX_PinSource   		GPIO_PinSource7			// ����Դ

#define  UART7_RX_PIN				GPIO_Pin_6				// RX ����
#define	 UART7_RX_PORT				GPIOF					// RX ���Ŷ˿�
#define	 UART7_RX_CLK				RCC_AHB1Periph_GPIOF	// RX ����ʱ��
#define  UART7_RX_PinSource			GPIO_PinSource6			// ����Դ


/*---------------------- �������� ----------------------------*/

void  Usart1_Config (void);	// USART1 ��ʼ������
void  Usart2_Config (void);	// USART2 ��ʼ������
void  Uart7_Config (void);	// UART7 ��ʼ������
void  USART_printf (USART_TypeDef* USARTx, char *Data, ...);	// USART printf����
	
#endif 


