/*   
		扬州大学 测控15 杨寿晨        
	 
   串口   USART1的引脚 PA9/PA10 核心板 
		  USART2的引脚 PD5/PD6  232
		  UART7的引脚  PF7/PF6  485/WIFI        

	           2019/4 - 2019/6                  */

#include "usart.h"  

// 函数：usart1 IO口初始化
//
void  USART1_GPIO_Config	(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd ( USART1_TX_CLK, ENABLE); 	//IO口时钟配置

	//IO配置
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;		//复用模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		//推挽
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;		//上拉
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度等级

	//初始化 TX	引脚
	GPIO_InitStructure.GPIO_Pin = USART1_TX_PIN;	 
	GPIO_Init(USART1_TX_PORT, &GPIO_InitStructure);		
	
	//初始化 RX	引脚
	GPIO_InitStructure.GPIO_Pin = USART1_RX_PIN;	 
	GPIO_Init(USART1_RX_PORT, &GPIO_InitStructure);		
	
	//IO复用，复用到USART1
	GPIO_PinAFConfig(USART1_TX_PORT,USART1_TX_PinSource,GPIO_AF_USART1); 
	GPIO_PinAFConfig(USART1_RX_PORT,USART1_RX_PinSource,GPIO_AF_USART1); 
}

// 函数：USART1 初始化
//
void Usart1_Config(void)
{		
	USART_InitTypeDef USART_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	// IO口初始化
	USART1_GPIO_Config();
		 
	// 配置串口各项参数
	USART_InitStructure.USART_BaudRate 	 = USART1_BaudRate;     //波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; //数据位8位
	USART_InitStructure.USART_StopBits   = USART_StopBits_1;    //停止位1位
	USART_InitStructure.USART_Parity     = USART_Parity_No ;    //无校验
	USART_InitStructure.USART_Mode 	     = USART_Mode_Rx | USART_Mode_Tx;           // 发送和接收模式
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 不使用硬件流控制
	
	USART_Init(USART1,&USART_InitStructure); //初始化串口1
	USART_Cmd(USART1,ENABLE);	//使能串口1
}

/***************************************************************************************************************/

// 函数：usart2 IO口初始化
//
void  USART2_GPIO_Config	(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd ( USART2_TX_CLK|USART2_RX_CLK, ENABLE); 	//IO口时钟配置

	//IO配置
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;		//复用模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		//推挽
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;		//上拉
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;	//速度等级

	//初始化 TX	引脚
	GPIO_InitStructure.GPIO_Pin = USART2_TX_PIN;	 
	GPIO_Init(USART2_TX_PORT, &GPIO_InitStructure);	
	//初始化 RX 引脚													   
	GPIO_InitStructure.GPIO_Pin = USART2_RX_PIN;	
	GPIO_Init(USART2_RX_PORT, &GPIO_InitStructure);		
	
	//IO复用，复用到USART2
	GPIO_PinAFConfig(USART2_TX_PORT,USART2_TX_PinSource,GPIO_AF_USART2); 
	GPIO_PinAFConfig(USART2_RX_PORT,USART2_RX_PinSource,GPIO_AF_USART2);	
}

// 函数：USART2 初始化
//
void Usart2_Config(void)
{		
	USART_InitTypeDef USART_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	
	// IO口初始化
	USART2_GPIO_Config();
		 
	// 配置串口各项参数
	USART_InitStructure.USART_BaudRate 	 = USART2_BaudRate;     //波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; //数据位8位
	USART_InitStructure.USART_StopBits   = USART_StopBits_1;    //停止位1位
	USART_InitStructure.USART_Parity     = USART_Parity_No ;    //无校验
	USART_InitStructure.USART_Mode 	    = USART_Mode_Rx | USART_Mode_Tx;            // 发送和接收模式
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 不使用硬件流控制
	
	USART_Init(USART2,&USART_InitStructure); //初始化串口2
	USART_Cmd(USART2,ENABLE);	//使能串口2
}

/***************************************************************************************************************/

// 函数：uart7 IO口初始化
//
void  UART7_GPIO_Config	(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd ( UART7_TX_CLK|UART7_RX_CLK, ENABLE); 	//IO口时钟配置

	//IO配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;		//复用模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		//推挽
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;		//上拉
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;	//速度等级

	//初始化 TX	引脚
	GPIO_InitStructure.GPIO_Pin = UART7_TX_PIN;	 
	GPIO_Init(UART7_TX_PORT, &GPIO_InitStructure);	
	//初始化 RX 引脚													   
	GPIO_InitStructure.GPIO_Pin = UART7_RX_PIN;	
	GPIO_Init(UART7_RX_PORT, &GPIO_InitStructure);		
	
	//IO复用，复用到USART7
	GPIO_PinAFConfig(UART7_TX_PORT,UART7_TX_PinSource,GPIO_AF_UART7); 
	GPIO_PinAFConfig(UART7_RX_PORT,UART7_RX_PinSource,GPIO_AF_UART7);	
}

// 配置NVIC中的UART7中断
//
void UART7_Interrupt_Config( void )
{
	NVIC_InitTypeDef NVIC_InitStructure; 
	 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	NVIC_InitStructure.NVIC_IRQChannel = UART7_IRQn;	 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}


// 函数：UART7 初始化
//
void Uart7_Config(void)
{		
	USART_InitTypeDef USART_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART7, ENABLE);
	
	// IO口初始化
	UART7_GPIO_Config();
		 
	// 配置串口各项参数
	USART_InitStructure.USART_BaudRate 	 = UART7_BaudRate;      //波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; //数据位8位
	USART_InitStructure.USART_StopBits   = USART_StopBits_1;    //停止位1位
	USART_InitStructure.USART_Parity     = USART_Parity_No ;    //无校验
	USART_InitStructure.USART_Mode 	     = USART_Mode_Rx | USART_Mode_Tx; //发送和接收模式
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 不使用硬件流控制
	
	USART_Init(UART7,&USART_InitStructure); 	//初始化串口7
	
	UART7_Interrupt_Config();					//中断初始化
	
	USART_ITConfig(UART7, USART_IT_RXNE, ENABLE);/* 使能串口7接收中断 */
	USART_Cmd(UART7,ENABLE);	//使能串口7
}






/************************************************************************************

							USART_printf 函数 

***********************************************************************************/

// 重定向c库函数printf到USART2 232
//
int fputc(int c, FILE *fp)
{
	// 发送单字节数据
	USART_SendData( USART2,(u8)c );
	//等待发送完毕 
	while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);	
	//返回字符
	return (c); 
}


/*
 * 函数名：itoa
 * 描述  ：将整形数据转换成字符串
 * 输入  ：-radix =10 表示10进制，其他结果为0
 *         -value 要转换的整形数
 *         -buf 转换后的字符串
 *         -radix = 10
 * 调用  ：被USART_printf()调用
 */
static char *itoa( int value, char *string, int radix )
{
    int     i, d;
    int     flag = 0;
    char    *ptr = string;

    /* This implementation only works for decimal numbers. */
    if (radix != 10)
    {	*ptr = 0;
        return string;}

    if (!value)
    {   *ptr++ = 0x30;
        *ptr = 0;
        return string;}

    /* if this is a negative value insert the minus sign. */
    if (value < 0)
    {  *ptr++ = '-';
        /* Make the value positive. */
        value *= -1;}
    
    for (i = 10000; i > 0; i /= 10)
    {	d = value / i;
        if (d || flag)
        {  *ptr++ = (char)(d + 0x30);
            value -= (d * i);
            flag = 1;}
    }
    /* Null terminate the string. */
    *ptr = 0;

    return string;
} /* NCL_Itoa */

/*
 * 函数名：USART_printf
 * 描述  ：格式化输出，类似于C库中的printf，但这里没有用到C库
 * 输入  ：-USARTx 串口通道
 *		   -Data   要发送到串口的内容的指针
 *		   -...    其他参数
 * 典型应用USART_printf( USART2, "\r\n this is a demo \r\n" );
 *         USART_printf( USART3, "\r\n %d \r\n", i );
 *         USART_printf( USART4, "\r\n %s \r\n", j );
 * USARTx ：x(1,2,3,4,5,6,7） 
 */
void USART_printf( USART_TypeDef* USARTx, char *Data, ... )
{
	const char *s;
  int d;   
  char buf[16];

  va_list ap;
  va_start(ap, Data);

	while ( *Data != 0)     // 判断是否到达字符串结束符
	{				                          
		if ( *Data == 0x5c )  //'\'
		{									  
			switch ( *++Data )
			{
				case 'r':							          //回车符
					USART_SendData(USARTx, 0x0d);
					Data ++;
					break;

				case 'n':							          //换行符
					USART_SendData(USARTx, 0x0a);	
					Data ++;
					break;
				
				default:
					Data ++;
				    break;
			}			 
		}
		else if ( *Data == '%')
		{									  //
			switch ( *++Data )
			{				
				case 's':										  //字符串
					s = va_arg(ap, const char *);
					for ( ; *s; s++) 
					{	USART_SendData(USARTx,*s);
						while( USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET );}
					 Data++;			
				    break;

				case 'd':										//十进制
					d = va_arg(ap, int);
					itoa(d, buf, 10);
					for (s = buf; *s; s++) 
					{	USART_SendData(USARTx,*s);
						while( USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET );}
				    Data++;
					break;	
				
				default:
					Data++;
					break;
			}		 
		} /* end of else if */
		else USART_SendData(USARTx, *Data++);
		while( USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET );
	}
}

