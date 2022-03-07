/*    
		  扬州大学 测控15 杨寿晨          
		
		       中断服务函数 
  
	          2019/4 - 2019/6                         */
						

#include  "stm32f4xx_it.h"

static uint16_t		data_count;

uint16_t		speed_CH5_count1=0;
uint16_t		speed_CH5_count2=0;
uint16_t		speed_CH5_Value1=0;
uint16_t		speed_CH5_Value2=0;

uint16_t		speed_CH6_count1=0;
uint16_t		speed_CH6_count2=0;
uint16_t		speed_CH6_Value1=0;
uint16_t		speed_CH6_Value2=0;

uint8_t			speed_CH5_NEW=0;
uint8_t			speed_CH6_NEW=0;

u16 GPS_count=0;

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}


/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f4xx.s).                                               */
/******************************************************************************/

extern void LTDC_ISR_Handler(void);

//	函数:LTDC中断服务函数
//
void LTDC_IRQHandler(void)
{ 
	CPU_SR_ALLOC();        //进入中断

	CPU_CRITICAL_ENTER();  
	OSIntEnter();
	CPU_CRITICAL_EXIT();
	
	LTDC_ISR_Handler();
	
	OSIntExit();
}


//	SD卡全局中断
//
void SDIO_IRQHandler(void)
{ 
	CPU_SR_ALLOC();        

	CPU_CRITICAL_ENTER();  
	OSIntEnter();
	CPU_CRITICAL_EXIT();
	
	/* Process All SDIO Interrupt Sources */
	SD_ProcessIRQSrc();
	
	OSIntExit();   
}

//	DMA2 Stream3  SD卡DMA中断
//
void SD_SDIO_DMA_IRQHANDLER(void)
{ 
	CPU_SR_ALLOC();       

	CPU_CRITICAL_ENTER();  
	OSIntEnter();
	CPU_CRITICAL_EXIT();
	
	/* Process DMA2 Stream3 Interrupt Sources */
	SD_ProcessDMAIRQ();
	OSIntExit();    
}


//	DMA2 Stream1 中断 用于处理ADC3 2路测速通道
//
void  DMA2_Stream1_IRQHandler (void)
{ 
	CPU_SR_ALLOC();

	CPU_CRITICAL_ENTER();  
	OSIntEnter();
	CPU_CRITICAL_EXIT();
	
	if ( DMA_GetITStatus( RHEOSTAT_ADC3_DMA_STREAM , DMA_IT_TCIF1) != RESET ) 
	{	  
		DMA_ClearITPendingBit( RHEOSTAT_ADC3_DMA_STREAM , DMA_IT_TCIF1); 
		
		if(speed_CH5_NEW ==0)		//CH5测速，检测上升沿，计数采样周期count，转速 = 60 / count * 采样间隔 r/min
		{
			speed_CH5_Value1 = ADC_Speed_ConvertedValue[0];
			speed_CH5_count1++;
			if(speed_CH5_Value1<1500 && speed_CH5_Value2>=1500 && speed_CH5_count2==0)
				{ speed_CH5_count2=speed_CH5_count1;		}
			if((speed_CH5_Value1<1500 && speed_CH5_Value2>=1500 && speed_CH5_count2 !=0 && (speed_CH5_count1-speed_CH5_count2)>1 )||speed_CH5_count1>4096)
				{ 	if(speed_CH5_count1==4097)
						CH5_SPEED=0;
					else
					{	CH5_SPEED = (int) (60 * 4000 / (speed_CH5_count1-speed_CH5_count2));}
					speed_CH5_NEW=1;
				}
			speed_CH5_Value2 = speed_CH5_Value1;	
		}
		
		if(speed_CH6_NEW ==0)		//CH6测速，检测上升沿，计数采样周期count，转速 = 60 / count * 采样间隔 r/min
		{
			speed_CH6_Value1 = ADC_Speed_ConvertedValue[1];
			speed_CH6_count1++;
			if(speed_CH6_Value1<1500 && speed_CH6_Value2>=1500 && speed_CH6_count2==0)
				{ speed_CH6_count2=speed_CH6_count1;		}
			if((speed_CH6_Value1<1500 && speed_CH6_Value2>=1500 && speed_CH6_count2 !=0 && (speed_CH6_count1-speed_CH6_count2)>1 )||speed_CH6_count1>4096)
				{   if(speed_CH6_count1==4097)
						CH6_SPEED=0;
					else
					{	CH6_SPEED = (int) (60 * 4000 / (speed_CH6_count1-speed_CH6_count2));}
					speed_CH6_NEW=1;
				}
			speed_CH6_Value2 = speed_CH6_Value1;	
		}	
		
		if(speed_CH5_NEW==1 && speed_CH6_NEW==1)	//CH5、CH6 采样结束，或无信号
		{	
			speed_CH5_count1=0;
			speed_CH5_count2=0;
			speed_CH5_Value1=0;
			speed_CH5_Value2=0;
		
			speed_CH6_count1=0;
			speed_CH6_count2=0;
			speed_CH6_Value1=0;
			speed_CH6_Value2=0;
			
			speed_CH5_NEW=0;
			speed_CH6_NEW=0;
			TIM_Cmd(TIM5, DISABLE);
			DMA_Cmd(RHEOSTAT_ADC3_DMA_STREAM, DISABLE);
			TIM_CtrlPWMOutputs(TIM5, DISABLE);
		}
	}
	OSIntExit();   
}



//	DMA2 Stream2 中断 用于处理ADC2 8路AD数据
//
void  DMA2_Stream2_IRQHandler (void)
{ 
	OS_ERR  err;
	CPU_SR_ALLOC();

	CPU_CRITICAL_ENTER();  
	OSIntEnter();
	CPU_CRITICAL_EXIT();
	
	if ( DMA_GetITStatus( RHEOSTAT_ADC2_DMA_STREAM , DMA_IT_TCIF2) != RESET ) 
	{	  
		DMA_ClearITPendingBit( RHEOSTAT_ADC2_DMA_STREAM , DMA_IT_TCIF2);  
	
		AD_Value_CH1[data_count]  =   ADC_ConvertedValue[0];	
		AD_Value_CH2[data_count]  =   ADC_ConvertedValue[1];	
		AD_Value_CH3[data_count]  =   ADC_ConvertedValue[2];
		AD_Value_CH4[data_count]  =   ADC_ConvertedValue[3];

		AD_Value_CH7[data_count]  =   ADC_ConvertedValue[4];	
		AD_Value_CH8[data_count]  =   ADC_ConvertedValue[5];	
		AD_Value_CH9[data_count]  =   ADC_ConvertedValue[6];
		AD_Value_CH10[data_count] =   ADC_ConvertedValue[7];
		data_count++;
		
		if(data_count==1024)		
		{  
			TIM_Cmd(TIM8, DISABLE);
			DMA_Cmd(RHEOSTAT_ADC2_DMA_STREAM, DISABLE);
			TIM_CtrlPWMOutputs(TIM8, DISABLE); 
			data_count=0;

			OSTaskSemPost(&DSP_TaskTCB,OS_OPT_POST_NONE,&err);		// 给DSP任务发送消息
		}
	}	
	OSIntExit();    
}




//  USART1 GPS 接收中断
//
void USART1_IRQHandler(void)
{ 
	CPU_SR_ALLOC();

	CPU_CRITICAL_ENTER();  
	OSIntEnter();
	CPU_CRITICAL_EXIT();
	
  if(USART_GetITStatus(GPS_USART,USART_IT_RXNE)!=RESET)     /* 传输完成 */
  { 
		USART_ClearITPendingBit(GPS_USART, USART_IT_RXNE);
		if(GPS_TransferEnd!=1)
		{
			gps_rbuff[GPS_count++]=USART_ReceiveData(GPS_USART);
			if(GPS_count == GPS_RBUFF_SIZE)
			{
				GPS_TransferEnd = 1;                    //设置传输完成标志位
				GPS_count=0;
				USART_ITConfig(GPS_USART, USART_IT_RXNE, DISABLE);	
			}
		}
  }
	
	OSIntExit(); 
}



//	UART7 WIFI/485接收中断
//
void UART7_IRQHandler( void )
{	
	CPU_SR_ALLOC();

	CPU_CRITICAL_ENTER();  
	OSIntEnter();
	CPU_CRITICAL_EXIT();
	
	if(WIFI_or_485 == 0)		//WIFI接收
	{
		
	}
	
	else						//485接收
	{		
		
	}
	
	USART_ClearITPendingBit(UART7, USART_IT_RXNE);
	
	OSIntExit(); 
}


