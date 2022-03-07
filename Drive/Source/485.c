/*   
      ���ݴ�ѧ ���15 ���ٳ�         
		
	   485 modbusͨѶ����         
        UART7  PF7 PF6       		

	      2019/4 - 2019/6                  */

#include "485.h"

// ������485 RE DE ���� ��ʼ��
//
void _485_Config(void)
{ 
	GPIO_InitTypeDef GPIO_InitStructure; 
	
	RCC_APB1PeriphClockCmd( RCC_AHB1Periph_GPIOD, ENABLE ); 
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;		//���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		//�������
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;	//����	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;	//�ٶ�ѡ��
	
	GPIO_InitStructure.GPIO_Pin   = _485_RE_PIN;		// 485 RE���ų�ʼ��
	GPIO_Init(_485_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin   = _485_DE_PIN;		// 485 DE���ų�ʼ��
	GPIO_Init(_485_PORT, &GPIO_InitStructure);

}

void _485_SendByte(  uint8_t ch )
{
	/* ����һ���ֽ����ݵ�USART6 */
	USART_SendData(UART7,ch);
		
	/* �ȴ�������� */
	while (USART_GetFlagStatus(UART7, USART_FLAG_TXE) == RESET);	
	
}


