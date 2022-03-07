/*   
		  扬州大学 测控15 杨寿晨          
		
	 LED 继电器 风扇 采样保持器控制程序        

	        2019/4 - 2019/6             */

#include "led&control.h"  

// 函数：LED/CONTROL  IO口初始化
//
void LED_CONTROL_Init(void)
{		
	GPIO_InitTypeDef GPIO_InitStructure; //定义结构体
	RCC_AHB1PeriphClockCmd ( RCC_AHB1Periph_GPIOG, ENABLE); 	//初始化GPIOG时钟	
	RCC_AHB1PeriphClockCmd ( RCC_AHB1Periph_GPIOD, ENABLE); 	//初始化GPIOD时钟	
	RCC_AHB1PeriphClockCmd ( RCC_AHB1Periph_GPIOB, ENABLE); 	//初始化GPIOB时钟	
	RCC_AHB1PeriphClockCmd ( RCC_AHB1Periph_GPIOH, ENABLE); 	//初始化GPIOH时钟	
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;		//输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		//推挽输出
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;		//上拉
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;	//速度选择
	
	//初始化 LED1 引脚
	GPIO_InitStructure.GPIO_Pin = LED1_PIN;	 
	GPIO_Init(LED1_PORT, &GPIO_InitStructure);	
	
	//初始化 LED2 引脚								   
	GPIO_InitStructure.GPIO_Pin = LED2_PIN;	
	GPIO_Init(LED2_PORT, &GPIO_InitStructure);	
	
	//初始化 FEN_CONTROL 引脚								   
	GPIO_InitStructure.GPIO_Pin = FEN_CONTROL_PIN;	
	GPIO_Init(FEN_CONTROL_PORT, &GPIO_InitStructure);	
	
	//初始化 CONTROL1 引脚								   
	GPIO_InitStructure.GPIO_Pin = CONTROL1_PIN;	
	GPIO_Init(CONTROL1_PORT, &GPIO_InitStructure);	
	
	//初始化 CONTROL2 引脚								   
	GPIO_InitStructure.GPIO_Pin = CONTROL2_PIN;	
	GPIO_Init(CONTROL2_PORT, &GPIO_InitStructure);	
	
	//初始化 S/H1_CONTROL 引脚								   
	GPIO_InitStructure.GPIO_Pin = SH1_CONTROL_PIN;	
	GPIO_Init(SH1_CONTROL_PORT, &GPIO_InitStructure);	
	
	//初始化 S/H2_CONTROL 引脚								   
	GPIO_InitStructure.GPIO_Pin = SH2_CONTROL_PIN;	
	GPIO_Init(SH2_CONTROL_PORT, &GPIO_InitStructure);	
	
	GPIO_ResetBits(LED1_PORT,LED1_PIN);					//LED1输出低电平
	GPIO_ResetBits(LED2_PORT,LED2_PIN);					//LED2输出低电平
	
	GPIO_SetBits(FEN_CONTROL_PORT,FEN_CONTROL_PIN);		//FEN_CONTROL输出高电平
	GPIO_SetBits(CONTROL1_PORT,CONTROL1_PIN);			//CONTROL1输出高电平
	GPIO_SetBits(CONTROL2_PORT,CONTROL2_PIN);			//CONTROL2输出高电平	
	
	GPIO_SetBits(SH1_CONTROL_PORT,SH1_CONTROL_PIN);		//SH1_CONTROL输出高电平，未使用S/H	
	GPIO_SetBits(SH2_CONTROL_PORT,SH2_CONTROL_PIN);		//SH2_CONTROL输出高电平，未使用S/H	
}

