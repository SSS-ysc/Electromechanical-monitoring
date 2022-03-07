#ifndef __ADC_H
#define __ADC_H	

#include "stm32f4xx.h" 

#define  CH_Number           8
#define  CH_Speed_Number     2

/*------------------------------- AD���� --------------------------------*/

#define  ADC_CH1_PIN		GPIO_Pin_0			// ADC CH1����
#define	 ADC_CH1_PORT		GPIOA				// ADC CH1�˿�
#define	 ADC_CHANNEL1   	ADC_Channel_0		// ADC CH1��������ͨ��

#define  ADC_CH2_PIN		GPIO_Pin_3			// ADC CH2����
#define	 ADC_CH2_PORT		GPIOA				// ADC CH2�˿�
#define	 ADC_CHANNEL2   	ADC_Channel_3		// ADC CH2��������ͨ��

#define  ADC_CH3_PIN		GPIO_Pin_4			// ADC CH3����
#define	 ADC_CH3_PORT		GPIOA				// ADC CH3�˿�
#define	 ADC_CHANNEL3   	ADC_Channel_4		// ADC CH3��������ͨ��

#define  ADC_CH4_PIN		GPIO_Pin_5			// ADC CH4����
#define	 ADC_CH4_PORT		GPIOA				// ADC CH4�˿�
#define	 ADC_CHANNEL4   	ADC_Channel_5		// ADC CH4��������ͨ��

#define  ADC_CH7_PIN		GPIO_Pin_6			// ADC CH7����
#define	 ADC_CH7_PORT		GPIOA				// ADC CH7�˿�
#define	 ADC_CHANNEL5   	ADC_Channel_6		// ADC CH7��������ͨ��

#define  ADC_CH8_PIN		GPIO_Pin_0			// ADC CH8����
#define	 ADC_CH8_PORT		GPIOB				// ADC CH8�˿�
#define	 ADC_CHANNEL6   	ADC_Channel_8		// ADC CH8��������ͨ��

#define  ADC_CH9_PIN		GPIO_Pin_1			// ADC CH9����
#define	 ADC_CH9_PORT		GPIOB				// ADC CH9�˿�
#define	 ADC_CHANNEL7   	ADC_Channel_9		// ADC CH9��������ͨ��

#define  ADC_CH10_PIN		GPIO_Pin_2			// ADC CH10����
#define	 ADC_CH10_PORT		GPIOC				// ADC CH10�˿�
#define	 ADC_CHANNEL8   	ADC_Channel_12		// ADC CH10��������ͨ��

//����ͨ��
#define  ADC_CH5_PIN			GPIO_Pin_10			// ADC CH5����
#define	 ADC_CH5_PORT			GPIOF				// ADC CH5�˿�
#define	 ADC_Speed_CHANNEL1		ADC_Channel_8       // ADC speed CH1��������ͨ��

#define  ADC_CH6_PIN			GPIO_Pin_9			// ADC CH6����
#define	 ADC_CH6_PORT			GPIOF				// ADC CH6�˿�
#define	 ADC_Speed_CHANNEL2		ADC_Channel_7       // ADC speed CH2��������ͨ��

/*------------------------------- ADC DMA ͨ���� --------------------------------*/

#define RHEOSTAT_ADC2_DMA_CHANNEL		DMA_Channel_1
#define RHEOSTAT_ADC2_DMA_STREAM		DMA2_Stream2

#define RHEOSTAT_ADC3_DMA_CHANNEL		DMA_Channel_2
#define RHEOSTAT_ADC3_DMA_STREAM		DMA2_Stream1

// ADC DR�Ĵ����궨�壬ADCת���������ֵ����������
#define RHEOSTAT_ADC2_DR_ADDR    ((u32)ADC2+0x4c)
#define RHEOSTAT_ADC3_DR_ADDR    ((u32)ADC3+0x4c)


// ADCת���ĵ�ѹֵͨ��MDA��ʽ����SRAM
extern __IO uint16_t ADC_ConvertedValue[CH_Number];
extern __IO uint16_t ADC_Speed_ConvertedValue[CH_Speed_Number];
	
void    ADC123_Init(void);		// ��ʼ��ADC
double  ADC_GetTemp(void);		// ����ת������ȡоƬ�¶�

#endif

