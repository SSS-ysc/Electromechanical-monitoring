/*   
      ���ݴ�ѧ ���15  ���ٳ�       
		
		���� 4Gģ�����         
		USART6  PC6 PC7        			

	    2019/4 - 2019/6                  */

#include "4G_linking.h"


// ������usart_4G IO�ڳ�ʼ��
//
void USART6_GPIO_Config	(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd ( USART6_TX_CLK|USART6_RX_CLK, ENABLE); 	//IO��ʱ������

	//IO����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;		//����ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		//����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;		//����
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;	//�ٶȵȼ�

	//��ʼ�� TX	����
	GPIO_InitStructure.GPIO_Pin = USART6_TX_PIN;	 
	GPIO_Init(USART6_TX_PORT, &GPIO_InitStructure);	
	//��ʼ�� RX ����													   
	GPIO_InitStructure.GPIO_Pin = USART6_RX_PIN;	
	GPIO_Init(USART6_RX_PORT, &GPIO_InitStructure);		
	
	//IO���ã����õ�USART6
	GPIO_PinAFConfig(USART6_TX_PORT,USART6_TX_PinSource,GPIO_AF_USART6); 
	GPIO_PinAFConfig(USART6_RX_PORT,USART6_RX_PinSource,GPIO_AF_USART6);	
}

//����4G ʹ�õĴ����ж�
//                                                     //��δʹ��
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

// ������USART6 �ڳ�ʼ��
//
void Usart6_Config(void)
{		
	USART_InitTypeDef USART_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);
	
	// IO�ڳ�ʼ��
	USART6_GPIO_Config();
		 
	// ���ô��ڸ������
	USART_InitStructure.USART_BaudRate 	 	= USART6_BaudRate;		//������
	USART_InitStructure.USART_WordLength 	= USART_WordLength_8b;	//����λ8λ
	USART_InitStructure.USART_StopBits   	= USART_StopBits_1;		//ֹͣλ1λ
	USART_InitStructure.USART_Parity     	= USART_Parity_No ;		//��У��
	USART_InitStructure.USART_Mode			= USART_Mode_Rx | USART_Mode_Tx;			//���ͺͽ���ģʽ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;		// ��ʹ��Ӳ��������
	
	USART_Init(USART6,&USART_InitStructure);	//��ʼ������6
	USART_Cmd(USART6,ENABLE);					//ʹ�ܴ���6
}



// ������4G ��ʼ��
//
void _4G_linking_Config(void)
{ 
	GPIO_InitTypeDef GPIO_InitStructure; 
		
	RCC_APB1PeriphClockCmd( RCC_AHB1Periph_GPIOG, ENABLE ); 

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;	    		
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	
	GPIO_InitStructure.GPIO_Pin = _4G_LED_WORK_PIN;		//����״̬���� ����
	GPIO_Init(_4G_LED_WORK_PORT, &GPIO_InitStructure); 

	GPIO_InitStructure.GPIO_Pin = _4G_LED_NET_PIN;		//������������ ����
	GPIO_Init(_4G_LED_NET_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = _4G_LINKA_PIN;		//��·A����״̬���� ����
	GPIO_Init(_4G_LINKA_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = _4G_LINKB_PIN;		//��·B����״̬���� ����
	GPIO_Init(_4G_LINKB_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;	  	//���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;    	//�������
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL; 	//����	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz; 	//�ٶ�ѡ��
	
	GPIO_InitStructure.GPIO_Pin   = _4G_POWER_KEY_PIN;	//ʹ������ ���
	GPIO_Init(_4G_POWER_KEY_PORT, &GPIO_InitStructure);
	  
	USART6_GPIO_Config();
	Usart6_Config();
	GPIO_SetBits(_4G_POWER_KEY_PORT,_4G_POWER_KEY_PIN);	//4Gģ�鿪��
}


void _4G_SendByte(  uint8_t ch )
{
	/* ����һ���ֽ����ݵ�USART6 */
	USART_SendData(USART6,ch);
		
	/* �ȴ�������� */
	while (USART_GetFlagStatus(USART6, USART_FLAG_TXE) == RESET);	
	
}


