/*   
      扬州大学 测控15 杨寿晨      
		
	     TIM定时器 程序         

		2019/4 - 2019/6          */

#include "tim.h"

#define Sampling_rate     2000  		//单位 Hz   定义采样速率可调整为 1 - 1M Hz  需为1M的因数


/******************************************************************************
		HCLK = SYSCLK / 1      (AHB1Periph)
		PCLK2 = HCLK  / 2      (APB2Periph)
		PCLK1 = HCLK  / 4      (APB1Periph)

		APB1 prescaler != 1,  APB1上的TIMxCLK = PCLK1 x 2 = SystemCoreClock / 2;
		APB2 prescaler != 1,  APB2上的TIMxCLK = PCLK2 x 2 = SystemCoreClock;

		APB1 定时器有 TIM2, TIM3 ,TIM4, TIM5, TIM6, TIM7, TIM12, TIM13, TIM14
		APB2 定时器有 TIM1, TIM8 ,TIM9, TIM10, TIM11
					
		TIMx 更新周期是 = TIMxCLK / （TIM_Period + 1）/（TIM_Prescaler + 1）
*******************************************************************************/

// 函 数 名: TIM5_Config
// 功能说明: 配置定时器5，用于触发ADC3
// 说    明：TIM_Period、TIM_Prescaler可调节TIM定时时间，从而控制采样速度
//
static void TIM5_Config(void)
{   TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef        TIM_OCInitStructure;
	
	/* 使能定时器5 */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);	

	/* 先禁能再配置 */
    TIM_Cmd(TIM5, DISABLE);	
	
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure); 	          //初始化定时器1的寄存器为复位值
    TIM_TimeBaseStructure.TIM_Period = 250 - 1;					  //ARR自动重装载寄存器周期的值(定时时间）到设置频率后产生个更新或者中断(也是说定时时间到)
    TIM_TimeBaseStructure.TIM_Prescaler = 90-1;   		          //PSC时钟预分频数 例如：时钟频率=TIM1CLK/(时钟预分频+1)
    TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;    	          //CR1->CKD时间分割值
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   //CR1->CMS[1:0]和DIR定时器模式 向上计数	
    TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);	
	
	/**************ADC3的触发***********************************************/
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 				  
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;     
    TIM_OCInitStructure.TIM_Pulse = TIM_TimeBaseStructure.TIM_Period/2;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 		
    TIM_OC1Init(TIM5, &TIM_OCInitStructure);

	//这里不使能TIM 在ADC3_Task中使能
}
	
// 函 数 名: TIM8_Config
// 功能说明: 配置定时器8，用于触发ADC2
// 说    明：TIM_Period、TIM_Prescaler可调节TIM定时时间，从而控制采样速度
//
static void TIM8_Config(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef        TIM_OCInitStructure;
    
	/* 使能定时器1 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);	
    
	/* 先禁能再配置 */
    TIM_Cmd(TIM8, DISABLE);	
	  
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure); 	            		//初始化定时器1的寄存器为复位值
    TIM_TimeBaseStructure.TIM_Period = ( 1000000 / Sampling_rate ) - 1;		//ARR自动重装载寄存器周期的值(定时时间）到设置频率后产生个更新或者中断(也是说定时时间到)
    TIM_TimeBaseStructure.TIM_Prescaler = 180-1;   		            		//PSC时钟预分频数 例如：时钟频率=TIM1CLK/(时钟预分频+1)
    TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;							//CR1->CKD时间分割值
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;				//CR1->CMS[1:0]和DIR定时器模式 向上计数
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0000;					/* TIM1 和 TIM8 必须设置 */	
    TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);

    /**************ADC2的触发***********************************************/
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 						//CCMR2在向上计数时，一旦TIMx_CNT<TIMx_CCR1时通道1为有效电平，否则为无效电平
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;			//CCER 输出使能          
    TIM_OCInitStructure.TIM_Pulse = TIM_TimeBaseStructure.TIM_Period/2;		//CCR3同计数器TIMx_CNT的比较，并在OC1端口上产生输出信号 
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;				//CCER输出极性设置
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;			/* only for TIM1 and TIM8. 此处和正相引脚不同 */	
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;				/* only for TIM1 and TIM8. */		 
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;			/* only for TIM1 and TIM8. */
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;			/* only for TIM1 and TIM8. */	
	TIM_OC1Init(TIM8, &TIM_OCInitStructure);

    //这里不使能TIM 在ADC2_Task中使能
}


//初始化定时器
//
void TIM_Config(void)
{
	TIM5_Config();
	TIM8_Config();
}


