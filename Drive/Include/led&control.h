#ifndef __LEDCONTROL_H
#define __LEDCONTROL_H

#include "stm32f4xx.h"

/*---------------------- ���ú� ------------------------*/

#define LED1_PIN             GPIO_Pin_7				// LED1 ����      
#define LED1_PORT            GPIOG                  // LED1 GPIO�˿�     

#define LED2_PIN             GPIO_Pin_12            // LED2 ����             
#define LED2_PORT            GPIOD                  // LED2 GPIO�˿�          

#define FEN_CONTROL_PIN      GPIO_Pin_7             // FEN_CONTROL ����             
#define FEN_CONTROL_PORT     GPIOD                  // FEN_CONTROL GPIO�˿�          

#define CONTROL1_PIN         GPIO_Pin_2             // CONTROL1 ����             
#define CONTROL1_PORT        GPIOH                  // CONTROL1 GPIO�˿�   

#define CONTROL2_PIN         GPIO_Pin_3             // CONTROL2 ����             
#define CONTROL2_PORT        GPIOH                  // CONTROL2 GPIO�˿�   

#define SH1_CONTROL_PIN      GPIO_Pin_12            // SH1_CONTROL ����             
#define SH1_CONTROL_PORT     GPIOB                  // SH1_CONTROL GPIO�˿�          
			
#define SH2_CONTROL_PIN      GPIO_Pin_13            // SH2_CONTROL ����             
#define SH2_CONTROL_PORT     GPIOB                  // SH2_CONTROL GPIO�˿�          

/*---------------------- �������� ----------------------------*/

void LED_CONTROL_Init(void);	//LED��ʼ������


#endif //__LED_H

