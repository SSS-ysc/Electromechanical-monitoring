#ifndef __ADC_H
#define __ADC_H	

#include "stm32f4xx.h" 

#define  CH_Number           8
#define  CH_Speed_Number     2

/*------------------------------- AD引脚 --------------------------------*/

#define  ADC_CH1_PIN		GPIO_Pin_0			// ADC CH1引脚
#define	 ADC_CH1_PORT		GPIOA				// ADC CH1端口
#define	 ADC_CHANNEL1   	ADC_Channel_0		// ADC CH1采样输入通道

#define  ADC_CH2_PIN		GPIO_Pin_3			// ADC CH2引脚
#define	 ADC_CH2_PORT		GPIOA				// ADC CH2端口
#define	 ADC_CHANNEL2   	ADC_Channel_3		// ADC CH2采样输入通道

#define  ADC_CH3_PIN		GPIO_Pin_4			// ADC CH3引脚
#define	 ADC_CH3_PORT		GPIOA				// ADC CH3端口
#define	 ADC_CHANNEL3   	ADC_Channel_4		// ADC CH3采样输入通道

#define  ADC_CH4_PIN		GPIO_Pin_5			// ADC CH4引脚
#define	 ADC_CH4_PORT		GPIOA				// ADC CH4端口
#define	 ADC_CHANNEL4   	ADC_Channel_5		// ADC CH4采样输入通道

#define  ADC_CH7_PIN		GPIO_Pin_6			// ADC CH7引脚
#define	 ADC_CH7_PORT		GPIOA				// ADC CH7端口
#define	 ADC_CHANNEL5   	ADC_Channel_6		// ADC CH7采样输入通道

#define  ADC_CH8_PIN		GPIO_Pin_0			// ADC CH8引脚
#define	 ADC_CH8_PORT		GPIOB				// ADC CH8端口
#define	 ADC_CHANNEL6   	ADC_Channel_8		// ADC CH8采样输入通道

#define  ADC_CH9_PIN		GPIO_Pin_1			// ADC CH9引脚
#define	 ADC_CH9_PORT		GPIOB				// ADC CH9端口
#define	 ADC_CHANNEL7   	ADC_Channel_9		// ADC CH9采样输入通道

#define  ADC_CH10_PIN		GPIO_Pin_2			// ADC CH10引脚
#define	 ADC_CH10_PORT		GPIOC				// ADC CH10端口
#define	 ADC_CHANNEL8   	ADC_Channel_12		// ADC CH10采样输入通道

//测速通道
#define  ADC_CH5_PIN			GPIO_Pin_10			// ADC CH5引脚
#define	 ADC_CH5_PORT			GPIOF				// ADC CH5端口
#define	 ADC_Speed_CHANNEL1		ADC_Channel_8       // ADC speed CH1采样输入通道

#define  ADC_CH6_PIN			GPIO_Pin_9			// ADC CH6引脚
#define	 ADC_CH6_PORT			GPIOF				// ADC CH6端口
#define	 ADC_Speed_CHANNEL2		ADC_Channel_7       // ADC speed CH2采样输入通道

/*------------------------------- ADC DMA 通道宏 --------------------------------*/

#define RHEOSTAT_ADC2_DMA_CHANNEL		DMA_Channel_1
#define RHEOSTAT_ADC2_DMA_STREAM		DMA2_Stream2

#define RHEOSTAT_ADC3_DMA_CHANNEL		DMA_Channel_2
#define RHEOSTAT_ADC3_DMA_STREAM		DMA2_Stream1

// ADC DR寄存器宏定义，ADC转换后的数字值则存放在这里
#define RHEOSTAT_ADC2_DR_ADDR    ((u32)ADC2+0x4c)
#define RHEOSTAT_ADC3_DR_ADDR    ((u32)ADC3+0x4c)


// ADC转换的电压值通过MDA方式传到SRAM
extern __IO uint16_t ADC_ConvertedValue[CH_Number];
extern __IO uint16_t ADC_Speed_ConvertedValue[CH_Speed_Number];
	
void    ADC123_Init(void);		// 初始化ADC
double  ADC_GetTemp(void);		// 单次转换，获取芯片温度

#endif

