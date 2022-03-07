/*   
		���ݴ�ѧ ���15 ���ٳ�        
	 
   ����   USART1������ PA9/PA10 ���İ� 
		  USART2������ PD5/PD6  232
		  UART7������  PF7/PF6  485/WIFI        

	           2019/4 - 2019/6                  */

#include "usart.h"  

// ������usart1 IO�ڳ�ʼ��
//
void  USART1_GPIO_Config	(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd ( USART1_TX_CLK, ENABLE); 	//IO��ʱ������

	//IO����
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;		//����ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		//����
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;		//����
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶȵȼ�

	//��ʼ�� TX	����
	GPIO_InitStructure.GPIO_Pin = USART1_TX_PIN;	 
	GPIO_Init(USART1_TX_PORT, &GPIO_InitStructure);		
	
	//��ʼ�� RX	����
	GPIO_InitStructure.GPIO_Pin = USART1_RX_PIN;	 
	GPIO_Init(USART1_RX_PORT, &GPIO_InitStructure);		
	
	//IO���ã����õ�USART1
	GPIO_PinAFConfig(USART1_TX_PORT,USART1_TX_PinSource,GPIO_AF_USART1); 
	GPIO_PinAFConfig(USART1_RX_PORT,USART1_RX_PinSource,GPIO_AF_USART1); 
}

// ������USART1 ��ʼ��
//
void Usart1_Config(void)
{		
	USART_InitTypeDef USART_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	// IO�ڳ�ʼ��
	USART1_GPIO_Config();
		 
	// ���ô��ڸ������
	USART_InitStructure.USART_BaudRate 	 = USART1_BaudRate;     //������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; //����λ8λ
	USART_InitStructure.USART_StopBits   = USART_StopBits_1;    //ֹͣλ1λ
	USART_InitStructure.USART_Parity     = USART_Parity_No ;    //��У��
	USART_InitStructure.USART_Mode 	     = USART_Mode_Rx | USART_Mode_Tx;           // ���ͺͽ���ģʽ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // ��ʹ��Ӳ��������
	
	USART_Init(USART1,&USART_InitStructure); //��ʼ������1
	USART_Cmd(USART1,ENABLE);	//ʹ�ܴ���1
}

/***************************************************************************************************************/

// ������usart2 IO�ڳ�ʼ��
//
void  USART2_GPIO_Config	(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd ( USART2_TX_CLK|USART2_RX_CLK, ENABLE); 	//IO��ʱ������

	//IO����
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;		//����ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		//����
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;		//����
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;	//�ٶȵȼ�

	//��ʼ�� TX	����
	GPIO_InitStructure.GPIO_Pin = USART2_TX_PIN;	 
	GPIO_Init(USART2_TX_PORT, &GPIO_InitStructure);	
	//��ʼ�� RX ����													   
	GPIO_InitStructure.GPIO_Pin = USART2_RX_PIN;	
	GPIO_Init(USART2_RX_PORT, &GPIO_InitStructure);		
	
	//IO���ã����õ�USART2
	GPIO_PinAFConfig(USART2_TX_PORT,USART2_TX_PinSource,GPIO_AF_USART2); 
	GPIO_PinAFConfig(USART2_RX_PORT,USART2_RX_PinSource,GPIO_AF_USART2);	
}

// ������USART2 ��ʼ��
//
void Usart2_Config(void)
{		
	USART_InitTypeDef USART_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	
	// IO�ڳ�ʼ��
	USART2_GPIO_Config();
		 
	// ���ô��ڸ������
	USART_InitStructure.USART_BaudRate 	 = USART2_BaudRate;     //������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; //����λ8λ
	USART_InitStructure.USART_StopBits   = USART_StopBits_1;    //ֹͣλ1λ
	USART_InitStructure.USART_Parity     = USART_Parity_No ;    //��У��
	USART_InitStructure.USART_Mode 	    = USART_Mode_Rx | USART_Mode_Tx;            // ���ͺͽ���ģʽ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // ��ʹ��Ӳ��������
	
	USART_Init(USART2,&USART_InitStructure); //��ʼ������2
	USART_Cmd(USART2,ENABLE);	//ʹ�ܴ���2
}

/***************************************************************************************************************/

// ������uart7 IO�ڳ�ʼ��
//
void  UART7_GPIO_Config	(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd ( UART7_TX_CLK|UART7_RX_CLK, ENABLE); 	//IO��ʱ������

	//IO����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;		//����ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		//����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;		//����
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;	//�ٶȵȼ�

	//��ʼ�� TX	����
	GPIO_InitStructure.GPIO_Pin = UART7_TX_PIN;	 
	GPIO_Init(UART7_TX_PORT, &GPIO_InitStructure);	
	//��ʼ�� RX ����													   
	GPIO_InitStructure.GPIO_Pin = UART7_RX_PIN;	
	GPIO_Init(UART7_RX_PORT, &GPIO_InitStructure);		
	
	//IO���ã����õ�USART7
	GPIO_PinAFConfig(UART7_TX_PORT,UART7_TX_PinSource,GPIO_AF_UART7); 
	GPIO_PinAFConfig(UART7_RX_PORT,UART7_RX_PinSource,GPIO_AF_UART7);	
}

// ����NVIC�е�UART7�ж�
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


// ������UART7 ��ʼ��
//
void Uart7_Config(void)
{		
	USART_InitTypeDef USART_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART7, ENABLE);
	
	// IO�ڳ�ʼ��
	UART7_GPIO_Config();
		 
	// ���ô��ڸ������
	USART_InitStructure.USART_BaudRate 	 = UART7_BaudRate;      //������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; //����λ8λ
	USART_InitStructure.USART_StopBits   = USART_StopBits_1;    //ֹͣλ1λ
	USART_InitStructure.USART_Parity     = USART_Parity_No ;    //��У��
	USART_InitStructure.USART_Mode 	     = USART_Mode_Rx | USART_Mode_Tx; //���ͺͽ���ģʽ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // ��ʹ��Ӳ��������
	
	USART_Init(UART7,&USART_InitStructure); 	//��ʼ������7
	
	UART7_Interrupt_Config();					//�жϳ�ʼ��
	
	USART_ITConfig(UART7, USART_IT_RXNE, ENABLE);/* ʹ�ܴ���7�����ж� */
	USART_Cmd(UART7,ENABLE);	//ʹ�ܴ���7
}






/************************************************************************************

							USART_printf ���� 

***********************************************************************************/

// �ض���c�⺯��printf��USART2 232
//
int fputc(int c, FILE *fp)
{
	// ���͵��ֽ�����
	USART_SendData( USART2,(u8)c );
	//�ȴ�������� 
	while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);	
	//�����ַ�
	return (c); 
}


/*
 * ��������itoa
 * ����  ������������ת�����ַ���
 * ����  ��-radix =10 ��ʾ10���ƣ��������Ϊ0
 *         -value Ҫת����������
 *         -buf ת������ַ���
 *         -radix = 10
 * ����  ����USART_printf()����
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
 * ��������USART_printf
 * ����  ����ʽ�������������C���е�printf��������û���õ�C��
 * ����  ��-USARTx ����ͨ��
 *		   -Data   Ҫ���͵����ڵ����ݵ�ָ��
 *		   -...    ��������
 * ����Ӧ��USART_printf( USART2, "\r\n this is a demo \r\n" );
 *         USART_printf( USART3, "\r\n %d \r\n", i );
 *         USART_printf( USART4, "\r\n %s \r\n", j );
 * USARTx ��x(1,2,3,4,5,6,7�� 
 */
void USART_printf( USART_TypeDef* USARTx, char *Data, ... )
{
	const char *s;
  int d;   
  char buf[16];

  va_list ap;
  va_start(ap, Data);

	while ( *Data != 0)     // �ж��Ƿ񵽴��ַ���������
	{				                          
		if ( *Data == 0x5c )  //'\'
		{									  
			switch ( *++Data )
			{
				case 'r':							          //�س���
					USART_SendData(USARTx, 0x0d);
					Data ++;
					break;

				case 'n':							          //���з�
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
				case 's':										  //�ַ���
					s = va_arg(ap, const char *);
					for ( ; *s; s++) 
					{	USART_SendData(USARTx,*s);
						while( USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET );}
					 Data++;			
				    break;

				case 'd':										//ʮ����
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

