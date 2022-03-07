#ifndef __KEY_H
#define	__KEY_H

#include "stm32f4xx.h"

/*******************************************************/

#define KEY_INT_GPIO_PORT                GPIOI
#define KEY_INT_GPIO_PIN                 GPIO_Pin_8

#define KEYup_INT_GPIO_PORT              GPIOE
#define KEYup_INT_GPIO_PIN               GPIO_Pin_6

#define KEYdown_INT_GPIO_PORT            GPIOE
#define KEYdown_INT_GPIO_PIN             GPIO_Pin_5

#define KEYleft_INT_GPIO_PORT            GPIOE
#define KEYleft_INT_GPIO_PIN             GPIO_Pin_4

#define KEYright_INT_GPIO_PORT           GPIOE
#define KEYright_INT_GPIO_PIN            GPIO_Pin_3

#define KEYconfirm_INT_GPIO_PORT         GPIOE
#define KEYconfirm_INT_GPIO_PIN          GPIO_Pin_2

#define KEYcancel_INT_GPIO_PORT          GPIOD
#define KEYcancel_INT_GPIO_PIN           GPIO_Pin_11

/*******************************************************/

void Key_Config(void);

#endif
