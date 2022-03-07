/*   
      ���ݴ�ѧ ���15 ���ٳ�          
		
		   ADC ���� ����         

	    2019/4 - 2019/6                */

#include "adc.h"

__IO uint16_t ADC_ConvertedValue[CH_Number]={0};
__IO uint16_t ADC_Speed_ConvertedValue[CH_Speed_Number]={0};


// ��ʼ��ADC�������
//
void ADC_GPIO_Config (void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOC|RCC_AHB1Periph_GPIOF, ENABLE);		// ��ʼ��ADC IO��ʱ��

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;				//	ģ�⸴��ģʽ
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;			//	����������
	
	GPIO_InitStructure.GPIO_Pin  = ADC_CH1_PIN;			        //  ADC CH1ͨ��
	GPIO_Init(ADC_CH1_PORT, &GPIO_InitStructure);		        //  ��ʼ��ADC_CH1����
	
	GPIO_InitStructure.GPIO_Pin  = ADC_CH2_PIN;			        //  ADC CH2ͨ��
	GPIO_Init(ADC_CH2_PORT, &GPIO_InitStructure);		        //  ��ʼ��ADC_CH2����
	
	GPIO_InitStructure.GPIO_Pin  = ADC_CH3_PIN;			        //  ADC CH3ͨ��
	GPIO_Init(ADC_CH3_PORT, &GPIO_InitStructure);		        //  ��ʼ��ADC_CH3����
	
	GPIO_InitStructure.GPIO_Pin  = ADC_CH4_PIN;			        //  ADC CH4ͨ��
	GPIO_Init(ADC_CH4_PORT, &GPIO_InitStructure);		        //  ��ʼ��ADC_CH4����
	
	GPIO_InitStructure.GPIO_Pin  = ADC_CH5_PIN;			        //  ADC CH5ͨ��
	GPIO_Init(ADC_CH5_PORT, &GPIO_InitStructure);		        //  ��ʼ��ADC_CH5����
	
	GPIO_InitStructure.GPIO_Pin  = ADC_CH6_PIN;			        //  ADC CH6ͨ��
	GPIO_Init(ADC_CH6_PORT, &GPIO_InitStructure);		        //  ��ʼ��ADC_CH6����
	
	GPIO_InitStructure.GPIO_Pin  = ADC_CH7_PIN;			        //  ADC CH7ͨ��
	GPIO_Init(ADC_CH7_PORT, &GPIO_InitStructure);		        //  ��ʼ��ADC_CH7����
	
	GPIO_InitStructure.GPIO_Pin  = ADC_CH8_PIN;			        //  ADC CH8ͨ��
	GPIO_Init(ADC_CH8_PORT, &GPIO_InitStructure);		        //  ��ʼ��ADC_CH8����
	
	GPIO_InitStructure.GPIO_Pin  = ADC_CH9_PIN;			        //  ADC CH9ͨ��
	GPIO_Init(ADC_CH9_PORT, &GPIO_InitStructure);		        //  ��ʼ��ADC_CH9����
	
	GPIO_InitStructure.GPIO_Pin  = ADC_CH10_PIN;				//  ADC CH10ͨ��
	GPIO_Init(ADC_CH10_PORT, &GPIO_InitStructure);				//  ��ʼ��ADC_CH10����

}

/******************************************************************************************************
*	�� �� ��: ADC1_Init
*	��������: ��ʼ��ADC1
*	˵    ��: ���ڲɼ��ڲ��¶ȴ�����/VBAT
*******************************************************************************************************/

void ADC1_Init(void)
{
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	ADC_InitTypeDef       ADC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);				            // ����ADCʱ��			
	
	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;						// ����ת��ģʽ
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div8; 					// 8��Ƶ
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled; 		// ��ʹ��DMA
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;	// ��������
	ADC_CommonInit(&ADC_CommonInitStructure);

	ADC_InitStructure.ADC_NbrOfConversion = 1;					// ����ת��						
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;				// ��ʹ��ɨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;		  	// ��ʹ������ת��
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;		// 12λ���ݳ���
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;		// �Ҷ���
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;	// ��ʹ���ⲿͨ������
	ADC_InitStructure.ADC_ExternalTrigConv     = ADC_ExternalTrigConv_T1_CC1;		
	ADC_Init(ADC1, &ADC_InitStructure);

	ADC_TempSensorVrefintCmd(ENABLE);		// ʹ���ڲ��¶ȴ�����
	ADC_Cmd(ADC1, ENABLE);					// ʹ��ADC1
}


/******************************************************************************************************
*	�� �� ��: ADC_GetTemp
*	�� �� ֵ: �¶�ֵ��float��
*	��������: ��ɵ���ת������ȡSTM32оƬ�¶�
*******************************************************************************************************/

double ADC_GetTemp(void)
{	
	u16 Temp_AdVaule;		// �¶�AD����ֵ
	double	Temp_Vaule;		// ʵ���¶�ֵ
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_18, 1, ADC_SampleTime_480Cycles );	 // ����ת������
	ADC_SoftwareStartConv(ADC1);								                	 // ����ת��
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));		                         	 // �ȴ�ת�����
	Temp_AdVaule = ADC_GetConversionValue(ADC1);			                      	 // ��ȡADֵ
	
	Temp_Vaule = Temp_AdVaule * (3.3/4096);				      	//	�����ѹֵ				
	Temp_Vaule = ( Temp_Vaule - 0.76f ) /0.0025f +25; 			//  �����¶�ֵ
	
	return Temp_Vaule;	  	// �����¶�ֵ
}


// ����ADC2ʹ�õ�DMA�ж� 
//
void ADC2_Interrupt_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	// DMA2 Channel Interrupt ENABLE
	NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream2_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

/******************************************************************************************************
*	�� �� ��: ADC2_Init
*	��������: ��ʼ��ADC2
*	˵    ��: ���ڲɼ�SH1���Ƶ�8·�������ʹ��DMA���ݴ��䣬ADC2����ģʽ��ͨ��������CH1-CH4,CH7-CH10.
*******************************************************************************************************/

void ADC2_Init(void)
{ 
	DMA_InitTypeDef       DMA_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	ADC_InitTypeDef       ADC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE);	// ��ʼ��ADC2ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);	// ��ʼ��DMA2ʱ��
  
	// ------------------DMA Init �ṹ����� ��ʼ��--------------------------
	// ADC2ʹ��DMA2��������2��ͨ��1

	// �����ַΪ��ADC ���ݼĴ�����ַ
	DMA_InitStructure.DMA_PeripheralBaseAddr = RHEOSTAT_ADC2_DR_ADDR;	
	// �洢����ַ��ʵ���Ͼ���һ���ڲ�SRAM�ı���	
	DMA_InitStructure.DMA_Memory0BaseAddr = (u32)ADC_ConvertedValue;  
	// ���ݴ��䷽��Ϊ���赽�洢��	
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;	
	// ��������СΪ��ָһ�δ����������
	DMA_InitStructure.DMA_BufferSize = CH_Number;	
	// ����Ĵ���ֻ��һ������ַ���õ���
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	// �洢����ַ�̶�
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; 
	// �������ݴ�СΪ���֣��������ֽ� 
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; 
	// �洢�����ݴ�СҲΪ���֣����������ݴ�С��ͬ
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;	
	// ѭ������ģʽ
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	// DMA ����ͨ�����ȼ�Ϊ�ߣ���ʹ��һ��DMAͨ��ʱ�����ȼ����ò�Ӱ��
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	// ��ֹDMA FIFO	��ʹ��ֱ��ģʽ
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;  
	// FIFO ��С��FIFOģʽ��ֹʱ�������������	
	DMA_InitStructure.DMA_FIFOThreshold   = DMA_FIFOThreshold_HalfFull;
	DMA_InitStructure.DMA_MemoryBurst     = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;  
	// ѡ�� DMA ͨ����ͨ������������
	DMA_InitStructure.DMA_Channel = RHEOSTAT_ADC2_DMA_CHANNEL; 
	// ��ʼ��DMA�������൱��һ����Ĺܵ����ܵ������кܶ�ͨ��
	DMA_Init(RHEOSTAT_ADC2_DMA_STREAM, &DMA_InitStructure);
	
	//DMA�����ж����ȼ�
	ADC2_Interrupt_Config();
	//����DMA������ɺ�����ж�
	DMA_ITConfig(RHEOSTAT_ADC2_DMA_STREAM, DMA_IT_TC, ENABLE);  
	// ʹ��DMA��
	DMA_Cmd(RHEOSTAT_ADC2_DMA_STREAM, ENABLE);
	
	// -------------------ADC Common �ṹ�� ���� ��ʼ��------------------------
	ADC_CommonInitStructure.ADC_Mode				= ADC_Mode_Independent;			// ����ģʽ
	ADC_CommonInitStructure.ADC_Prescaler			= ADC_Prescaler_Div2;			// ʱ�ӷ�Ƶ
	ADC_CommonInitStructure.ADC_DMAAccessMode		= ADC_DMAAccessMode_Disabled; 	// �ر�DMAֱ�ӷ���ģʽ	
	ADC_CommonInitStructure.ADC_TwoSamplingDelay	= ADC_TwoSamplingDelay_5Cycles;// ����ʱ�������������ڶ��ز���ģʽ
	ADC_CommonInit(&ADC_CommonInitStructure);	

	// -------------------ADC Init �ṹ�� ���� ��ʼ��--------------------------
	ADC_InitStructure.ADC_ScanConvMode 		   = ENABLE;						  // ɨ��ģʽ����ͨ���ɼ���Ҫ
	ADC_InitStructure.ADC_ContinuousConvMode   = DISABLE;						  // ��ʹ������ת��
	ADC_InitStructure.ADC_Resolution 		   = ADC_Resolution_12b;			  // ADC�ֱ���12λ
	ADC_InitStructure.ADC_DataAlign 		   = ADC_DataAlign_Right;			  // �����Ҷ���
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_Rising; // ʹ��TIM�����ش���
	ADC_InitStructure.ADC_ExternalTrigConv     = ADC_ExternalTrigConv_T8_CC1;     // �ⲿ����ͨ��
	ADC_InitStructure.ADC_NbrOfConversion      = CH_Number;                       // ת��ͨ�� CH_Number ��
	ADC_Init(ADC2, &ADC_InitStructure);
  
	// ���� ADC ����ͨ��ת��˳��Ͳ���ʱ������
	ADC_RegularChannelConfig(ADC2, ADC_CHANNEL1, 1, ADC_SampleTime_144Cycles  );	
	ADC_RegularChannelConfig(ADC2, ADC_CHANNEL2, 2, ADC_SampleTime_144Cycles  );	
	ADC_RegularChannelConfig(ADC2, ADC_CHANNEL3, 3, ADC_SampleTime_144Cycles  );	
	ADC_RegularChannelConfig(ADC2, ADC_CHANNEL4, 4, ADC_SampleTime_144Cycles  );	
	ADC_RegularChannelConfig(ADC2, ADC_CHANNEL5, 5, ADC_SampleTime_144Cycles  );	
	ADC_RegularChannelConfig(ADC2, ADC_CHANNEL6, 6, ADC_SampleTime_144Cycles  );	
	ADC_RegularChannelConfig(ADC2, ADC_CHANNEL7, 7, ADC_SampleTime_144Cycles  );	
	ADC_RegularChannelConfig(ADC2, ADC_CHANNEL8, 8, ADC_SampleTime_144Cycles  );	

	// ʹ��DMA���� after last transfer (Single-ADC mode)
	ADC_DMARequestAfterLastTransferCmd(ADC2, ENABLE);
	// ʹ��ADC DMA
	ADC_DMACmd(ADC2, ENABLE);
	// ʹ��ADC	
	ADC_Cmd(ADC2, ENABLE);
}


// ����ADC3ʹ�õ�DMA�ж� 
//
void ADC3_Interrupt_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	// DMA2 Channel Interrupt ENABLE
	NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream1_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 5;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

/******************************************************************************************************
*	�� �� ��: ADC3_Init
*	��������: ��ʼ��ADC3
*	˵    ��: ���ڲɼ�SH2���Ƶ�2·�ٶȱ�����ʹ��DMA���ݴ��䣬ADC3����ģʽ��ͨ��������CH5,CH6.
*******************************************************************************************************/

void ADC3_Init(void)
{
	DMA_InitTypeDef       DMA_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	ADC_InitTypeDef       ADC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE);	// ��ʼ��ADC3ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);    // ��ʼ��DMA2ʱ��
  
	// ------------------DMA Init �ṹ����� ��ʼ��--------------------------
	// ADC3ʹ��DMA2��������1��ͨ��2

	// �����ַΪ��ADC ���ݼĴ�����ַ
	DMA_InitStructure.DMA_PeripheralBaseAddr = RHEOSTAT_ADC3_DR_ADDR;	
	// �洢����ַ��ʵ���Ͼ���һ���ڲ�SRAM�ı���	
	DMA_InitStructure.DMA_Memory0BaseAddr = (u32)ADC_Speed_ConvertedValue;  
	// ���ݴ��䷽��Ϊ���赽�洢��	
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;	
	// ��������СΪ��ָһ�δ����������
	DMA_InitStructure.DMA_BufferSize = CH_Speed_Number;	
	// ����Ĵ���ֻ��һ������ַ���õ���
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	// �洢����ַ�̶�
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; 
	// �������ݴ�СΪ���֣��������ֽ� 
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; 
	// �洢�����ݴ�СҲΪ���֣����������ݴ�С��ͬ
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;	
	// ѭ������ģʽ
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	// DMA ����ͨ�����ȼ�Ϊ�ߣ���ʹ��һ��DMAͨ��ʱ�����ȼ����ò�Ӱ��
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
	// ��ֹDMA FIFO	��ʹ��ֱ��ģʽ
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;  
	// FIFO ��С��FIFOģʽ��ֹʱ�������������	
	DMA_InitStructure.DMA_FIFOThreshold   = DMA_FIFOThreshold_HalfFull;
	DMA_InitStructure.DMA_MemoryBurst     = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;  
	// ѡ�� DMA ͨ����ͨ������������
	DMA_InitStructure.DMA_Channel = RHEOSTAT_ADC3_DMA_CHANNEL; 
	// ��ʼ��DMA�������൱��һ����Ĺܵ����ܵ������кܶ�ͨ��
	DMA_Init(RHEOSTAT_ADC3_DMA_STREAM, &DMA_InitStructure);
	
	//DMA�����ж����ȼ�
	ADC3_Interrupt_Config();
	//����DMA������ɺ�����ж�
	DMA_ITConfig(RHEOSTAT_ADC3_DMA_STREAM, DMA_IT_TC, ENABLE);  
	// ʹ��DMA��
	DMA_Cmd(RHEOSTAT_ADC3_DMA_STREAM, ENABLE);
	
	// -------------------ADC Common �ṹ�� ���� ��ʼ��------------------------
	ADC_CommonInitStructure.ADC_Mode				= ADC_Mode_Independent;			// ����ģʽ
	ADC_CommonInitStructure.ADC_Prescaler			= ADC_Prescaler_Div2; 			// ʱ�ӷ�Ƶ
	ADC_CommonInitStructure.ADC_DMAAccessMode		= ADC_DMAAccessMode_Disabled; 	// �ر�DMAֱ�ӷ���ģʽ	
	ADC_CommonInitStructure.ADC_TwoSamplingDelay	= ADC_TwoSamplingDelay_20Cycles;// ����ʱ�������������ڶ��ز���ģʽ
	ADC_CommonInit(&ADC_CommonInitStructure);	

	// -------------------ADC Init �ṹ�� ���� ��ʼ��--------------------------
	ADC_InitStructure.ADC_ScanConvMode			= ENABLE;							// ɨ��ģʽ����ͨ���ɼ���Ҫ
	ADC_InitStructure.ADC_ContinuousConvMode	= DISABLE;							// ��ʹ������ת��
	ADC_InitStructure.ADC_Resolution			= ADC_Resolution_12b;				// ADC�ֱ���12λ
	ADC_InitStructure.ADC_DataAlign				= ADC_DataAlign_Right;				// �����Ҷ���
	ADC_InitStructure.ADC_ExternalTrigConvEdge	= ADC_ExternalTrigConvEdge_Rising;	// ʹ��TIM�����ش���
	ADC_InitStructure.ADC_ExternalTrigConv		= ADC_ExternalTrigConv_T5_CC1;     	// �ⲿ����ͨ��
	ADC_InitStructure.ADC_NbrOfConversion		= CH_Speed_Number;                 	// ת��ͨ�� CH_Speed_Number ��
	ADC_Init(ADC3, &ADC_InitStructure);
  
	// ���� ADC ����ͨ��ת��˳��Ͳ���ʱ������
	ADC_RegularChannelConfig(ADC3, ADC_Speed_CHANNEL1, 1, ADC_SampleTime_144Cycles );	
	ADC_RegularChannelConfig(ADC3, ADC_Speed_CHANNEL2, 2, ADC_SampleTime_144Cycles );	

	// ʹ��DMA���� after last transfer (Single-ADC mode)
	ADC_DMARequestAfterLastTransferCmd(ADC3, ENABLE);
	// ʹ��ADC DMA
	ADC_DMACmd(ADC3, ENABLE);
	// ʹ��ADC	
	ADC_Cmd(ADC3, ENABLE);
}

void ADC123_Init(void)
{	 
	ADC_GPIO_Config();	// ��ʼ��IO��
	ADC1_Init();		// ��ʼ��ADC1
	ADC2_Init();		// ��ʼ��ADC2
	ADC3_Init();		// ��ʼ��ADC3
}

