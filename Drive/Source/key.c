/*   
      ���ݴ�ѧ ���15 ���ٳ�          
		
		   ���� ����        

	   2019/4 - 2019/6           */

#include "key.h"

void Key_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
  
	/*��������GPIO�ڵ�ʱ��*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOD|RCC_AHB1Periph_GPIOE|RCC_AHB1Periph_GPIOI,ENABLE);
	
	/* ��������Ϊ����ģʽ */ 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;	    		
	/* ������������ */
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	
	/* ��ʼ�����İ尴��KEY */ 
	GPIO_InitStructure.GPIO_Pin = KEY_INT_GPIO_PIN;
	GPIO_Init(KEY_INT_GPIO_PORT, &GPIO_InitStructure); 

	/* �������Ų�����Ҳ������ */
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;  
	
	/* ��ʼ������up */ 
	GPIO_InitStructure.GPIO_Pin = KEYup_INT_GPIO_PIN;
	GPIO_Init(KEYup_INT_GPIO_PORT, &GPIO_InitStructure); 
	
	/* ��ʼ������down */ 
	GPIO_InitStructure.GPIO_Pin = KEYdown_INT_GPIO_PIN;  
	GPIO_Init(KEYdown_INT_GPIO_PORT, &GPIO_InitStructure); 
	
	/* ��ʼ������left */ 
	GPIO_InitStructure.GPIO_Pin = KEYleft_INT_GPIO_PIN;  
	GPIO_Init(KEYleft_INT_GPIO_PORT, &GPIO_InitStructure);  
	
	/* ��ʼ������right */ 
	GPIO_InitStructure.GPIO_Pin = KEYright_INT_GPIO_PIN;  
	GPIO_Init(KEYright_INT_GPIO_PORT, &GPIO_InitStructure);  
	
	/* ��ʼ������confirm */ 
	GPIO_InitStructure.GPIO_Pin = KEYconfirm_INT_GPIO_PIN;  
	GPIO_Init(KEYconfirm_INT_GPIO_PORT, &GPIO_InitStructure); 
 	
	/* ��ʼ������cancel */ 
	GPIO_InitStructure.GPIO_Pin = KEYcancel_INT_GPIO_PIN;  
	GPIO_Init(KEYcancel_INT_GPIO_PORT, &GPIO_InitStructure);    	
}

