#ifndef __LEDCONTROL_H
#define __LEDCONTROL_H

#include "stm32f4xx.h"

/*---------------------- 配置宏 ------------------------*/

#define LED1_PIN             GPIO_Pin_7				// LED1 引脚      
#define LED1_PORT            GPIOG                  // LED1 GPIO端口     

#define LED2_PIN             GPIO_Pin_12            // LED2 引脚             
#define LED2_PORT            GPIOD                  // LED2 GPIO端口          

#define FEN_CONTROL_PIN      GPIO_Pin_7             // FEN_CONTROL 引脚             
#define FEN_CONTROL_PORT     GPIOD                  // FEN_CONTROL GPIO端口          

#define CONTROL1_PIN         GPIO_Pin_2             // CONTROL1 引脚             
#define CONTROL1_PORT        GPIOH                  // CONTROL1 GPIO端口   

#define CONTROL2_PIN         GPIO_Pin_3             // CONTROL2 引脚             
#define CONTROL2_PORT        GPIOH                  // CONTROL2 GPIO端口   

#define SH1_CONTROL_PIN      GPIO_Pin_12            // SH1_CONTROL 引脚             
#define SH1_CONTROL_PORT     GPIOB                  // SH1_CONTROL GPIO端口          
			
#define SH2_CONTROL_PIN      GPIO_Pin_13            // SH2_CONTROL 引脚             
#define SH2_CONTROL_PORT     GPIOB                  // SH2_CONTROL GPIO端口          

/*---------------------- 函数声明 ----------------------------*/

void LED_CONTROL_Init(void);	//LED初始化函数


#endif //__LED_H

