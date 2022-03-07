/*   
		  ���ݴ�ѧ ���15 ���ٳ�          
		
	 LED �̵��� ���� �������������Ƴ���        

	        2019/4 - 2019/6             */

#include "led&control.h"  

// ������LED/CONTROL  IO�ڳ�ʼ��
//
void LED_CONTROL_Init(void)
{		
	GPIO_InitTypeDef GPIO_InitStructure; //����ṹ��
	RCC_AHB1PeriphClockCmd ( RCC_AHB1Periph_GPIOG, ENABLE); 	//��ʼ��GPIOGʱ��	
	RCC_AHB1PeriphClockCmd ( RCC_AHB1Periph_GPIOD, ENABLE); 	//��ʼ��GPIODʱ��	
	RCC_AHB1PeriphClockCmd ( RCC_AHB1Periph_GPIOB, ENABLE); 	//��ʼ��GPIOBʱ��	
	RCC_AHB1PeriphClockCmd ( RCC_AHB1Periph_GPIOH, ENABLE); 	//��ʼ��GPIOHʱ��	
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;		//���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		//�������
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;		//����
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;	//�ٶ�ѡ��
	
	//��ʼ�� LED1 ����
	GPIO_InitStructure.GPIO_Pin = LED1_PIN;	 
	GPIO_Init(LED1_PORT, &GPIO_InitStructure);	
	
	//��ʼ�� LED2 ����								   
	GPIO_InitStructure.GPIO_Pin = LED2_PIN;	
	GPIO_Init(LED2_PORT, &GPIO_InitStructure);	
	
	//��ʼ�� FEN_CONTROL ����								   
	GPIO_InitStructure.GPIO_Pin = FEN_CONTROL_PIN;	
	GPIO_Init(FEN_CONTROL_PORT, &GPIO_InitStructure);	
	
	//��ʼ�� CONTROL1 ����								   
	GPIO_InitStructure.GPIO_Pin = CONTROL1_PIN;	
	GPIO_Init(CONTROL1_PORT, &GPIO_InitStructure);	
	
	//��ʼ�� CONTROL2 ����								   
	GPIO_InitStructure.GPIO_Pin = CONTROL2_PIN;	
	GPIO_Init(CONTROL2_PORT, &GPIO_InitStructure);	
	
	//��ʼ�� S/H1_CONTROL ����								   
	GPIO_InitStructure.GPIO_Pin = SH1_CONTROL_PIN;	
	GPIO_Init(SH1_CONTROL_PORT, &GPIO_InitStructure);	
	
	//��ʼ�� S/H2_CONTROL ����								   
	GPIO_InitStructure.GPIO_Pin = SH2_CONTROL_PIN;	
	GPIO_Init(SH2_CONTROL_PORT, &GPIO_InitStructure);	
	
	GPIO_ResetBits(LED1_PORT,LED1_PIN);					//LED1����͵�ƽ
	GPIO_ResetBits(LED2_PORT,LED2_PIN);					//LED2����͵�ƽ
	
	GPIO_SetBits(FEN_CONTROL_PORT,FEN_CONTROL_PIN);		//FEN_CONTROL����ߵ�ƽ
	GPIO_SetBits(CONTROL1_PORT,CONTROL1_PIN);			//CONTROL1����ߵ�ƽ
	GPIO_SetBits(CONTROL2_PORT,CONTROL2_PIN);			//CONTROL2����ߵ�ƽ	
	
	GPIO_SetBits(SH1_CONTROL_PORT,SH1_CONTROL_PIN);		//SH1_CONTROL����ߵ�ƽ��δʹ��S/H	
	GPIO_SetBits(SH2_CONTROL_PORT,SH2_CONTROL_PIN);		//SH2_CONTROL����ߵ�ƽ��δʹ��S/H	
}

