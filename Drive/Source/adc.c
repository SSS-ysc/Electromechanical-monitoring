/*   
      扬州大学 测控15 杨寿晨          
		
		   ADC 采样 程序         

	    2019/4 - 2019/6                */

#include "adc.h"

__IO uint16_t ADC_ConvertedValue[CH_Number]={0};
__IO uint16_t ADC_Speed_ConvertedValue[CH_Speed_Number]={0};


// 初始化ADC相关引脚
//
void ADC_GPIO_Config (void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOC|RCC_AHB1Periph_GPIOF, ENABLE);		// 初始化ADC IO口时钟

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;				//	模拟复用模式
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;			//	不带上下拉
	
	GPIO_InitStructure.GPIO_Pin  = ADC_CH1_PIN;			        //  ADC CH1通道
	GPIO_Init(ADC_CH1_PORT, &GPIO_InitStructure);		        //  初始化ADC_CH1引脚
	
	GPIO_InitStructure.GPIO_Pin  = ADC_CH2_PIN;			        //  ADC CH2通道
	GPIO_Init(ADC_CH2_PORT, &GPIO_InitStructure);		        //  初始化ADC_CH2引脚
	
	GPIO_InitStructure.GPIO_Pin  = ADC_CH3_PIN;			        //  ADC CH3通道
	GPIO_Init(ADC_CH3_PORT, &GPIO_InitStructure);		        //  初始化ADC_CH3引脚
	
	GPIO_InitStructure.GPIO_Pin  = ADC_CH4_PIN;			        //  ADC CH4通道
	GPIO_Init(ADC_CH4_PORT, &GPIO_InitStructure);		        //  初始化ADC_CH4引脚
	
	GPIO_InitStructure.GPIO_Pin  = ADC_CH5_PIN;			        //  ADC CH5通道
	GPIO_Init(ADC_CH5_PORT, &GPIO_InitStructure);		        //  初始化ADC_CH5引脚
	
	GPIO_InitStructure.GPIO_Pin  = ADC_CH6_PIN;			        //  ADC CH6通道
	GPIO_Init(ADC_CH6_PORT, &GPIO_InitStructure);		        //  初始化ADC_CH6引脚
	
	GPIO_InitStructure.GPIO_Pin  = ADC_CH7_PIN;			        //  ADC CH7通道
	GPIO_Init(ADC_CH7_PORT, &GPIO_InitStructure);		        //  初始化ADC_CH7引脚
	
	GPIO_InitStructure.GPIO_Pin  = ADC_CH8_PIN;			        //  ADC CH8通道
	GPIO_Init(ADC_CH8_PORT, &GPIO_InitStructure);		        //  初始化ADC_CH8引脚
	
	GPIO_InitStructure.GPIO_Pin  = ADC_CH9_PIN;			        //  ADC CH9通道
	GPIO_Init(ADC_CH9_PORT, &GPIO_InitStructure);		        //  初始化ADC_CH9引脚
	
	GPIO_InitStructure.GPIO_Pin  = ADC_CH10_PIN;				//  ADC CH10通道
	GPIO_Init(ADC_CH10_PORT, &GPIO_InitStructure);				//  初始化ADC_CH10引脚

}

/******************************************************************************************************
*	函 数 名: ADC1_Init
*	函数功能: 初始化ADC1
*	说    明: 用于采集内部温度传感器/VBAT
*******************************************************************************************************/

void ADC1_Init(void)
{
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	ADC_InitTypeDef       ADC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);				            // 开启ADC时钟			
	
	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;						// 独立转换模式
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div8; 					// 8分频
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled; 		// 不使用DMA
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;	// 采样周期
	ADC_CommonInit(&ADC_CommonInitStructure);

	ADC_InitStructure.ADC_NbrOfConversion = 1;					// 单次转换						
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;				// 不使用扫描模式
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;		  	// 不使用连续转换
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;		// 12位数据长度
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;		// 右对齐
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;	// 不使用外部通道触发
	ADC_InitStructure.ADC_ExternalTrigConv     = ADC_ExternalTrigConv_T1_CC1;		
	ADC_Init(ADC1, &ADC_InitStructure);

	ADC_TempSensorVrefintCmd(ENABLE);		// 使能内部温度传感器
	ADC_Cmd(ADC1, ENABLE);					// 使能ADC1
}


/******************************************************************************************************
*	函 数 名: ADC_GetTemp
*	返 回 值: 温度值，float型
*	函数功能: 完成单次转换，获取STM32芯片温度
*******************************************************************************************************/

double ADC_GetTemp(void)
{	
	u16 Temp_AdVaule;		// 温度AD采样值
	double	Temp_Vaule;		// 实际温度值
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_18, 1, ADC_SampleTime_480Cycles );	 // 设置转换规则
	ADC_SoftwareStartConv(ADC1);								                	 // 开启转换
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));		                         	 // 等待转换完成
	Temp_AdVaule = ADC_GetConversionValue(ADC1);			                      	 // 获取AD值
	
	Temp_Vaule = Temp_AdVaule * (3.3/4096);				      	//	计算电压值				
	Temp_Vaule = ( Temp_Vaule - 0.76f ) /0.0025f +25; 			//  计算温度值
	
	return Temp_Vaule;	  	// 返回温度值
}


// 配置ADC2使用的DMA中断 
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
*	函 数 名: ADC2_Init
*	函数功能: 初始化ADC2
*	说    明: 用于采集SH1控制的8路快变量，使用DMA数据传输，ADC2独立模式多通道采样。CH1-CH4,CH7-CH10.
*******************************************************************************************************/

void ADC2_Init(void)
{ 
	DMA_InitTypeDef       DMA_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	ADC_InitTypeDef       ADC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE);	// 初始化ADC2时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);	// 初始化DMA2时钟
  
	// ------------------DMA Init 结构体参数 初始化--------------------------
	// ADC2使用DMA2，数据流2，通道1

	// 外设基址为：ADC 数据寄存器地址
	DMA_InitStructure.DMA_PeripheralBaseAddr = RHEOSTAT_ADC2_DR_ADDR;	
	// 存储器地址，实际上就是一个内部SRAM的变量	
	DMA_InitStructure.DMA_Memory0BaseAddr = (u32)ADC_ConvertedValue;  
	// 数据传输方向为外设到存储器	
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;	
	// 缓冲区大小为，指一次传输的数据量
	DMA_InitStructure.DMA_BufferSize = CH_Number;	
	// 外设寄存器只有一个，地址不用递增
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	// 存储器地址固定
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; 
	// 外设数据大小为半字，即两个字节 
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; 
	// 存储器数据大小也为半字，跟外设数据大小相同
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;	
	// 循环传输模式
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	// DMA 传输通道优先级为高，当使用一个DMA通道时，优先级设置不影响
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	// 禁止DMA FIFO	，使用直连模式
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;  
	// FIFO 大小，FIFO模式禁止时，这个不用配置	
	DMA_InitStructure.DMA_FIFOThreshold   = DMA_FIFOThreshold_HalfFull;
	DMA_InitStructure.DMA_MemoryBurst     = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;  
	// 选择 DMA 通道，通道存在于流中
	DMA_InitStructure.DMA_Channel = RHEOSTAT_ADC2_DMA_CHANNEL; 
	// 初始化DMA流，流相当于一个大的管道，管道里面有很多通道
	DMA_Init(RHEOSTAT_ADC2_DMA_STREAM, &DMA_InitStructure);
	
	//DMA配置中断优先级
	ADC2_Interrupt_Config();
	//配置DMA发送完成后产生中断
	DMA_ITConfig(RHEOSTAT_ADC2_DMA_STREAM, DMA_IT_TC, ENABLE);  
	// 使能DMA流
	DMA_Cmd(RHEOSTAT_ADC2_DMA_STREAM, ENABLE);
	
	// -------------------ADC Common 结构体 参数 初始化------------------------
	ADC_CommonInitStructure.ADC_Mode				= ADC_Mode_Independent;			// 独立模式
	ADC_CommonInitStructure.ADC_Prescaler			= ADC_Prescaler_Div2;			// 时钟分频
	ADC_CommonInitStructure.ADC_DMAAccessMode		= ADC_DMAAccessMode_Disabled; 	// 关闭DMA直接访问模式	
	ADC_CommonInitStructure.ADC_TwoSamplingDelay	= ADC_TwoSamplingDelay_5Cycles;// 采样时间间隔，仅适用于多重采样模式
	ADC_CommonInit(&ADC_CommonInitStructure);	

	// -------------------ADC Init 结构体 参数 初始化--------------------------
	ADC_InitStructure.ADC_ScanConvMode 		   = ENABLE;						  // 扫描模式，多通道采集需要
	ADC_InitStructure.ADC_ContinuousConvMode   = DISABLE;						  // 不使用连续转换
	ADC_InitStructure.ADC_Resolution 		   = ADC_Resolution_12b;			  // ADC分辨率12位
	ADC_InitStructure.ADC_DataAlign 		   = ADC_DataAlign_Right;			  // 数据右对齐
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_Rising; // 使用TIM上升沿触发
	ADC_InitStructure.ADC_ExternalTrigConv     = ADC_ExternalTrigConv_T8_CC1;     // 外部触发通道
	ADC_InitStructure.ADC_NbrOfConversion      = CH_Number;                       // 转换通道 CH_Number 个
	ADC_Init(ADC2, &ADC_InitStructure);
  
	// 配置 ADC 规则通道转换顺序和采样时间周期
	ADC_RegularChannelConfig(ADC2, ADC_CHANNEL1, 1, ADC_SampleTime_144Cycles  );	
	ADC_RegularChannelConfig(ADC2, ADC_CHANNEL2, 2, ADC_SampleTime_144Cycles  );	
	ADC_RegularChannelConfig(ADC2, ADC_CHANNEL3, 3, ADC_SampleTime_144Cycles  );	
	ADC_RegularChannelConfig(ADC2, ADC_CHANNEL4, 4, ADC_SampleTime_144Cycles  );	
	ADC_RegularChannelConfig(ADC2, ADC_CHANNEL5, 5, ADC_SampleTime_144Cycles  );	
	ADC_RegularChannelConfig(ADC2, ADC_CHANNEL6, 6, ADC_SampleTime_144Cycles  );	
	ADC_RegularChannelConfig(ADC2, ADC_CHANNEL7, 7, ADC_SampleTime_144Cycles  );	
	ADC_RegularChannelConfig(ADC2, ADC_CHANNEL8, 8, ADC_SampleTime_144Cycles  );	

	// 使能DMA请求 after last transfer (Single-ADC mode)
	ADC_DMARequestAfterLastTransferCmd(ADC2, ENABLE);
	// 使能ADC DMA
	ADC_DMACmd(ADC2, ENABLE);
	// 使能ADC	
	ADC_Cmd(ADC2, ENABLE);
}


// 配置ADC3使用的DMA中断 
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
*	函 数 名: ADC3_Init
*	函数功能: 初始化ADC3
*	说    明: 用于采集SH2控制的2路速度变量，使用DMA数据传输，ADC3独立模式多通道采样。CH5,CH6.
*******************************************************************************************************/

void ADC3_Init(void)
{
	DMA_InitTypeDef       DMA_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	ADC_InitTypeDef       ADC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE);	// 初始化ADC3时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);    // 初始化DMA2时钟
  
	// ------------------DMA Init 结构体参数 初始化--------------------------
	// ADC3使用DMA2，数据流1，通道2

	// 外设基址为：ADC 数据寄存器地址
	DMA_InitStructure.DMA_PeripheralBaseAddr = RHEOSTAT_ADC3_DR_ADDR;	
	// 存储器地址，实际上就是一个内部SRAM的变量	
	DMA_InitStructure.DMA_Memory0BaseAddr = (u32)ADC_Speed_ConvertedValue;  
	// 数据传输方向为外设到存储器	
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;	
	// 缓冲区大小为，指一次传输的数据量
	DMA_InitStructure.DMA_BufferSize = CH_Speed_Number;	
	// 外设寄存器只有一个，地址不用递增
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	// 存储器地址固定
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; 
	// 外设数据大小为半字，即两个字节 
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; 
	// 存储器数据大小也为半字，跟外设数据大小相同
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;	
	// 循环传输模式
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	// DMA 传输通道优先级为高，当使用一个DMA通道时，优先级设置不影响
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
	// 禁止DMA FIFO	，使用直连模式
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;  
	// FIFO 大小，FIFO模式禁止时，这个不用配置	
	DMA_InitStructure.DMA_FIFOThreshold   = DMA_FIFOThreshold_HalfFull;
	DMA_InitStructure.DMA_MemoryBurst     = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;  
	// 选择 DMA 通道，通道存在于流中
	DMA_InitStructure.DMA_Channel = RHEOSTAT_ADC3_DMA_CHANNEL; 
	// 初始化DMA流，流相当于一个大的管道，管道里面有很多通道
	DMA_Init(RHEOSTAT_ADC3_DMA_STREAM, &DMA_InitStructure);
	
	//DMA配置中断优先级
	ADC3_Interrupt_Config();
	//配置DMA发送完成后产生中断
	DMA_ITConfig(RHEOSTAT_ADC3_DMA_STREAM, DMA_IT_TC, ENABLE);  
	// 使能DMA流
	DMA_Cmd(RHEOSTAT_ADC3_DMA_STREAM, ENABLE);
	
	// -------------------ADC Common 结构体 参数 初始化------------------------
	ADC_CommonInitStructure.ADC_Mode				= ADC_Mode_Independent;			// 独立模式
	ADC_CommonInitStructure.ADC_Prescaler			= ADC_Prescaler_Div2; 			// 时钟分频
	ADC_CommonInitStructure.ADC_DMAAccessMode		= ADC_DMAAccessMode_Disabled; 	// 关闭DMA直接访问模式	
	ADC_CommonInitStructure.ADC_TwoSamplingDelay	= ADC_TwoSamplingDelay_20Cycles;// 采样时间间隔，仅适用于多重采样模式
	ADC_CommonInit(&ADC_CommonInitStructure);	

	// -------------------ADC Init 结构体 参数 初始化--------------------------
	ADC_InitStructure.ADC_ScanConvMode			= ENABLE;							// 扫描模式，多通道采集需要
	ADC_InitStructure.ADC_ContinuousConvMode	= DISABLE;							// 不使用连续转换
	ADC_InitStructure.ADC_Resolution			= ADC_Resolution_12b;				// ADC分辨率12位
	ADC_InitStructure.ADC_DataAlign				= ADC_DataAlign_Right;				// 数据右对齐
	ADC_InitStructure.ADC_ExternalTrigConvEdge	= ADC_ExternalTrigConvEdge_Rising;	// 使用TIM上升沿触发
	ADC_InitStructure.ADC_ExternalTrigConv		= ADC_ExternalTrigConv_T5_CC1;     	// 外部触发通道
	ADC_InitStructure.ADC_NbrOfConversion		= CH_Speed_Number;                 	// 转换通道 CH_Speed_Number 个
	ADC_Init(ADC3, &ADC_InitStructure);
  
	// 配置 ADC 规则通道转换顺序和采样时间周期
	ADC_RegularChannelConfig(ADC3, ADC_Speed_CHANNEL1, 1, ADC_SampleTime_144Cycles );	
	ADC_RegularChannelConfig(ADC3, ADC_Speed_CHANNEL2, 2, ADC_SampleTime_144Cycles );	

	// 使能DMA请求 after last transfer (Single-ADC mode)
	ADC_DMARequestAfterLastTransferCmd(ADC3, ENABLE);
	// 使能ADC DMA
	ADC_DMACmd(ADC3, ENABLE);
	// 使能ADC	
	ADC_Cmd(ADC3, ENABLE);
}

void ADC123_Init(void)
{	 
	ADC_GPIO_Config();	// 初始化IO口
	ADC1_Init();		// 初始化ADC1
	ADC2_Init();		// 初始化ADC2
	ADC3_Init();		// 初始化ADC3
}

