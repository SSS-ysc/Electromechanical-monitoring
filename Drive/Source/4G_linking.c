/*   
      扬州大学 测控15  杨寿晨       
		
		有人 4G模块程序         
		USART6  PC6 PC7        			

	    2019/4 - 2019/6                  */

#include "4G_linking.h"


// 函数：usart_4G IO口初始化
//
void USART6_GPIO_Config	(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd ( USART6_TX_CLK|USART6_RX_CLK, ENABLE); 	//IO口时钟配置

	//IO配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;		//复用模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		//推挽
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;		//上拉
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;	//速度等级

	//初始化 TX	引脚
	GPIO_InitStructure.GPIO_Pin = USART6_TX_PIN;	 
	GPIO_Init(USART6_TX_PORT, &GPIO_InitStructure);	
	//初始化 RX 引脚													   
	GPIO_InitStructure.GPIO_Pin = USART6_RX_PIN;	
	GPIO_Init(USART6_RX_PORT, &GPIO_InitStructure);		
	
	//IO复用，复用到USART6
	GPIO_PinAFConfig(USART6_TX_PORT,USART6_TX_PinSource,GPIO_AF_USART6); 
	GPIO_PinAFConfig(USART6_RX_PORT,USART6_RX_PinSource,GPIO_AF_USART6);	
}

//配置4G 使用的串口中断
//                                                     //暂未使用
void _4G_Interrupt_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	//  Channel Interrupt ENABLE
	NVIC_InitStructure.NVIC_IRQChannel = USART6_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

// 函数：USART6 口初始化
//
void Usart6_Config(void)
{		
	USART_InitTypeDef USART_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);
	
	// IO口初始化
	USART6_GPIO_Config();
		 
	// 配置串口各项参数
	USART_InitStructure.USART_BaudRate 	 	= USART6_BaudRate;		//波特率
	USART_InitStructure.USART_WordLength 	= USART_WordLength_8b;	//数据位8位
	USART_InitStructure.USART_StopBits   	= USART_StopBits_1;		//停止位1位
	USART_InitStructure.USART_Parity     	= USART_Parity_No ;		//无校验
	USART_InitStructure.USART_Mode			= USART_Mode_Rx | USART_Mode_Tx;			//发送和接收模式
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;		// 不使用硬件流控制
	
	USART_Init(USART6,&USART_InitStructure);	//初始化串口6
	USART_Cmd(USART6,ENABLE);					//使能串口6
}



// 函数：4G 初始化
//
void _4G_linking_Config(void)
{ 
	GPIO_InitTypeDef GPIO_InitStructure; 
		
	RCC_APB1PeriphClockCmd( RCC_AHB1Periph_GPIOG, ENABLE ); 

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;	    		
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	
	GPIO_InitStructure.GPIO_Pin = _4G_LED_WORK_PIN;		//工作状态引脚 输入
	GPIO_Init(_4G_LED_WORK_PORT, &GPIO_InitStructure); 

	GPIO_InitStructure.GPIO_Pin = _4G_LED_NET_PIN;		//网络类型引脚 输入
	GPIO_Init(_4G_LED_NET_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = _4G_LINKA_PIN;		//链路A链接状态引脚 输入
	GPIO_Init(_4G_LINKA_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = _4G_LINKB_PIN;		//链路B链接状态引脚 输入
	GPIO_Init(_4G_LINKB_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;	  	//输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;    	//推挽输出
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL; 	//浮空	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz; 	//速度选择
	
	GPIO_InitStructure.GPIO_Pin   = _4G_POWER_KEY_PIN;	//使能引脚 输出
	GPIO_Init(_4G_POWER_KEY_PORT, &GPIO_InitStructure);
	  
	USART6_GPIO_Config();
	Usart6_Config();
	GPIO_SetBits(_4G_POWER_KEY_PORT,_4G_POWER_KEY_PIN);	//4G模块开机
}


void _4G_SendByte(  uint8_t ch )
{
	/* 发送一个字节数据到USART6 */
	USART_SendData(USART6,ch);
		
	/* 等待发送完毕 */
	while (USART_GetFlagStatus(USART6, USART_FLAG_TXE) == RESET);	
	
}


