#ifndef  __LCD_H
#define	__LCD_H

#include "stm32f4xx.h"

/*-------------------------------------- 相关定义 ------------------------------------------------*/ 

#define LCD_CLK   25		// 定义LCD驱动时钟，这里为了方便计算数值应在10-70之间，单位为M

#define HBP  46
#define VBP  23

#define HSW  1
#define VSW  1

#define HFP  200
#define VFP  22

#define LCD_Width     	800				// LCD的像素长度
#define LCD_Height    	480				// LCD的像素宽度
#define LCD_Pixels    	800*480 			// 分辨率
#define LCD_MemoryAdd   0xD0000000 		// 显存的起始地址  

//	第二层的显存的偏移地址 
//	这里预留了emWin使用32位色格式时，三缓冲所需的空间
//	计算方法，以32位颜色格式为例，每个像素点占4字节，使用emWin三缓冲所需空间为：800*480*4*3
//
#define LCD_MemoryAdd_OFFSET    ((uint32_t)800*480*4*3)    


/*-------------------------------------- 函数声明 ------------------------------------------------*/ 

void     LCD_Init(void);

/*-------------------------------------- 引脚定义 ------------------------------------------------*/

//IO口时钟
#define LCD_GPIO_CLK	 RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOD \
							 | RCC_AHB1Periph_GPIOJ | RCC_AHB1Periph_GPIOK | RCC_AHB1Periph_GPIOI

//红色数据线
#define LTDC_R0_PORT        	GPIOI
#define LTDC_R0_PIN         	GPIO_Pin_15
#define LTDC_R0_PINSOURCE     GPIO_PinSource15

#define LTDC_R1_PORT        	GPIOJ
#define LTDC_R1_PIN         	GPIO_Pin_0
#define LTDC_R1_PINSOURCE     GPIO_PinSource0

#define LTDC_R2_PORT        	GPIOJ
#define LTDC_R2_PIN         	GPIO_Pin_1
#define LTDC_R2_PINSOURCE     GPIO_PinSource1

#define LTDC_R3_PORT        	GPIOJ
#define LTDC_R3_PIN         	GPIO_Pin_2
#define LTDC_R3_PINSOURCE     GPIO_PinSource2

#define LTDC_R4_PORT        	GPIOJ
#define LTDC_R4_PIN         	GPIO_Pin_3
#define LTDC_R4_PINSOURCE     GPIO_PinSource3

#define LTDC_R5_PORT        	GPIOJ
#define LTDC_R5_PIN         	GPIO_Pin_4
#define LTDC_R5_PINSOURCE     GPIO_PinSource4

#define LTDC_R6_PORT        	GPIOJ
#define LTDC_R6_PIN         	GPIO_Pin_5
#define LTDC_R6_PINSOURCE     GPIO_PinSource5

#define LTDC_R7_PORT        	GPIOJ
#define LTDC_R7_PIN         	GPIO_Pin_6
#define LTDC_R7_PINSOURCE     GPIO_PinSource6

//绿色数据线
#define LTDC_G0_PORT        	GPIOJ
#define LTDC_G0_PIN         	GPIO_Pin_7
#define LTDC_G0_PINSOURCE     GPIO_PinSource7

#define LTDC_G1_PORT        	GPIOJ
#define LTDC_G1_PIN         	GPIO_Pin_8
#define LTDC_G1_PINSOURCE     GPIO_PinSource8

#define LTDC_G2_PORT        	GPIOJ
#define LTDC_G2_PIN         	GPIO_Pin_9
#define LTDC_G2_PINSOURCE     GPIO_PinSource9

#define LTDC_G3_PORT        	GPIOJ
#define LTDC_G3_PIN         	GPIO_Pin_10
#define LTDC_G3_PINSOURCE     GPIO_PinSource10

#define LTDC_G4_PORT        	GPIOJ
#define LTDC_G4_PIN         	GPIO_Pin_11
#define LTDC_G4_PINSOURCE     GPIO_PinSource11

#define LTDC_G5_PORT        	GPIOK
#define LTDC_G5_PIN         	GPIO_Pin_0
#define LTDC_G5_PINSOURCE     GPIO_PinSource0

#define LTDC_G6_PORT        	GPIOK
#define LTDC_G6_PIN         	GPIO_Pin_1
#define LTDC_G6_PINSOURCE     GPIO_PinSource1

#define LTDC_G7_PORT        	GPIOK
#define LTDC_G7_PIN         	GPIO_Pin_2
#define LTDC_G7_PINSOURCE     GPIO_PinSource2

//蓝色数据线
#define LTDC_B0_PORT        	GPIOJ
#define LTDC_B0_PIN         	GPIO_Pin_12
#define LTDC_B0_PINSOURCE     GPIO_PinSource12

#define LTDC_B1_PORT       	GPIOJ
#define LTDC_B1_PIN           GPIO_Pin_13
#define LTDC_B1_PINSOURCE     GPIO_PinSource13

#define LTDC_B2_PORT        	GPIOJ
#define LTDC_B2_PIN         	GPIO_Pin_14
#define LTDC_B2_PINSOURCE     GPIO_PinSource14

#define LTDC_B3_PORT        	GPIOJ
#define LTDC_B3_PIN         	GPIO_Pin_15
#define LTDC_B3_PINSOURCE     GPIO_PinSource15

#define LTDC_B4_PORT        	GPIOK
#define LTDC_B4_PIN         	GPIO_Pin_3
#define LTDC_B4_PINSOURCE     GPIO_PinSource3

#define LTDC_B5_PORT        	GPIOK
#define LTDC_B5_PIN         	GPIO_Pin_4
#define LTDC_B5_PINSOURCE     GPIO_PinSource4

#define LTDC_B6_PORT        	GPIOK
#define LTDC_B6_PIN         	GPIO_Pin_5
#define LTDC_B6_PINSOURCE     GPIO_PinSource5

#define LTDC_B7_PORT        	GPIOK
#define LTDC_B7_PIN         	GPIO_Pin_6
#define LTDC_B7_PINSOURCE     GPIO_PinSource6

//控制信号线
#define LTDC_CLK_PORT         GPIOI					//LCD时钟引脚
#define LTDC_CLK_PIN          GPIO_Pin_14
#define LTDC_CLK_PINSOURCE    GPIO_PinSource14

#define LTDC_HSYNC_PORT       GPIOI					//行同步
#define LTDC_HSYNC_PIN        GPIO_Pin_12
#define LTDC_HSYNC_PINSOURCE  GPIO_PinSource12

#define LTDC_VSYNC_PORT       GPIOI					//帧同步
#define LTDC_VSYNC_PIN        GPIO_Pin_13
#define LTDC_VSYNC_PINSOURCE  GPIO_PinSource13

#define LTDC_DE_PORT          GPIOK					//数据使能
#define LTDC_DE_PIN           GPIO_Pin_7
#define LTDC_DE_PINSOURCE     GPIO_PinSource7
	
#define LTDC_Black_PORT       GPIOD					//背光
#define LTDC_Black_PIN        GPIO_Pin_13

#endif 
