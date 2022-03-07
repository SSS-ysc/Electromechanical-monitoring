/*   
      ���ݴ�ѧ ���15 ���ٳ�      
		
	     TIM��ʱ�� ����         

		2019/4 - 2019/6          */

#include "tim.h"

#define Sampling_rate     2000  		//��λ Hz   ����������ʿɵ���Ϊ 1 - 1M Hz  ��Ϊ1M������


/******************************************************************************
		HCLK = SYSCLK / 1      (AHB1Periph)
		PCLK2 = HCLK  / 2      (APB2Periph)
		PCLK1 = HCLK  / 4      (APB1Periph)

		APB1 prescaler != 1,  APB1�ϵ�TIMxCLK = PCLK1 x 2 = SystemCoreClock / 2;
		APB2 prescaler != 1,  APB2�ϵ�TIMxCLK = PCLK2 x 2 = SystemCoreClock;

		APB1 ��ʱ���� TIM2, TIM3 ,TIM4, TIM5, TIM6, TIM7, TIM12, TIM13, TIM14
		APB2 ��ʱ���� TIM1, TIM8 ,TIM9, TIM10, TIM11
					
		TIMx ���������� = TIMxCLK / ��TIM_Period + 1��/��TIM_Prescaler + 1��
*******************************************************************************/

// �� �� ��: TIM5_Config
// ����˵��: ���ö�ʱ��5�����ڴ���ADC3
// ˵    ����TIM_Period��TIM_Prescaler�ɵ���TIM��ʱʱ�䣬�Ӷ����Ʋ����ٶ�
//
static void TIM5_Config(void)
{   TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef        TIM_OCInitStructure;
	
	/* ʹ�ܶ�ʱ��5 */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);	

	/* �Ƚ��������� */
    TIM_Cmd(TIM5, DISABLE);	
	
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure); 	          //��ʼ����ʱ��1�ļĴ���Ϊ��λֵ
    TIM_TimeBaseStructure.TIM_Period = 250 - 1;					  //ARR�Զ���װ�ؼĴ������ڵ�ֵ(��ʱʱ�䣩������Ƶ�ʺ���������»����ж�(Ҳ��˵��ʱʱ�䵽)
    TIM_TimeBaseStructure.TIM_Prescaler = 90-1;   		          //PSCʱ��Ԥ��Ƶ�� ���磺ʱ��Ƶ��=TIM1CLK/(ʱ��Ԥ��Ƶ+1)
    TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;    	          //CR1->CKDʱ��ָ�ֵ
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   //CR1->CMS[1:0]��DIR��ʱ��ģʽ ���ϼ���	
    TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);	
	
	/**************ADC3�Ĵ���***********************************************/
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 				  
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;     
    TIM_OCInitStructure.TIM_Pulse = TIM_TimeBaseStructure.TIM_Period/2;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 		
    TIM_OC1Init(TIM5, &TIM_OCInitStructure);

	//���ﲻʹ��TIM ��ADC3_Task��ʹ��
}
	
// �� �� ��: TIM8_Config
// ����˵��: ���ö�ʱ��8�����ڴ���ADC2
// ˵    ����TIM_Period��TIM_Prescaler�ɵ���TIM��ʱʱ�䣬�Ӷ����Ʋ����ٶ�
//
static void TIM8_Config(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef        TIM_OCInitStructure;
    
	/* ʹ�ܶ�ʱ��1 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);	
    
	/* �Ƚ��������� */
    TIM_Cmd(TIM8, DISABLE);	
	  
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure); 	            		//��ʼ����ʱ��1�ļĴ���Ϊ��λֵ
    TIM_TimeBaseStructure.TIM_Period = ( 1000000 / Sampling_rate ) - 1;		//ARR�Զ���װ�ؼĴ������ڵ�ֵ(��ʱʱ�䣩������Ƶ�ʺ���������»����ж�(Ҳ��˵��ʱʱ�䵽)
    TIM_TimeBaseStructure.TIM_Prescaler = 180-1;   		            		//PSCʱ��Ԥ��Ƶ�� ���磺ʱ��Ƶ��=TIM1CLK/(ʱ��Ԥ��Ƶ+1)
    TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;							//CR1->CKDʱ��ָ�ֵ
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;				//CR1->CMS[1:0]��DIR��ʱ��ģʽ ���ϼ���
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0000;					/* TIM1 �� TIM8 �������� */	
    TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);

    /**************ADC2�Ĵ���***********************************************/
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 						//CCMR2�����ϼ���ʱ��һ��TIMx_CNT<TIMx_CCR1ʱͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;			//CCER ���ʹ��          
    TIM_OCInitStructure.TIM_Pulse = TIM_TimeBaseStructure.TIM_Period/2;		//CCR3ͬ������TIMx_CNT�ıȽϣ�����OC1�˿��ϲ�������ź� 
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;				//CCER�����������
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;			/* only for TIM1 and TIM8. �˴����������Ų�ͬ */	
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;				/* only for TIM1 and TIM8. */		 
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;			/* only for TIM1 and TIM8. */
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;			/* only for TIM1 and TIM8. */	
	TIM_OC1Init(TIM8, &TIM_OCInitStructure);

    //���ﲻʹ��TIM ��ADC2_Task��ʹ��
}


//��ʼ����ʱ��
//
void TIM_Config(void)
{
	TIM5_Config();
	TIM8_Config();
}


