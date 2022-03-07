/*   
      扬州大学 测控15 杨寿晨          
		
		   按键 程序        

	   2019/4 - 2019/6           */

#include "key.h"

void Key_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
  
	/*开启按键GPIO口的时钟*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOD|RCC_AHB1Periph_GPIOE|RCC_AHB1Periph_GPIOI,ENABLE);
	
	/* 设置引脚为输入模式 */ 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;	    		
	/* 设置引脚上拉 */
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	
	/* 初始化核心板按键KEY */ 
	GPIO_InitStructure.GPIO_Pin = KEY_INT_GPIO_PIN;
	GPIO_Init(KEY_INT_GPIO_PORT, &GPIO_InitStructure); 

	/* 设置引脚不上拉也不下拉 */
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;  
	
	/* 初始化按键up */ 
	GPIO_InitStructure.GPIO_Pin = KEYup_INT_GPIO_PIN;
	GPIO_Init(KEYup_INT_GPIO_PORT, &GPIO_InitStructure); 
	
	/* 初始化按键down */ 
	GPIO_InitStructure.GPIO_Pin = KEYdown_INT_GPIO_PIN;  
	GPIO_Init(KEYdown_INT_GPIO_PORT, &GPIO_InitStructure); 
	
	/* 初始化按键left */ 
	GPIO_InitStructure.GPIO_Pin = KEYleft_INT_GPIO_PIN;  
	GPIO_Init(KEYleft_INT_GPIO_PORT, &GPIO_InitStructure);  
	
	/* 初始化按键right */ 
	GPIO_InitStructure.GPIO_Pin = KEYright_INT_GPIO_PIN;  
	GPIO_Init(KEYright_INT_GPIO_PORT, &GPIO_InitStructure);  
	
	/* 初始化按键confirm */ 
	GPIO_InitStructure.GPIO_Pin = KEYconfirm_INT_GPIO_PIN;  
	GPIO_Init(KEYconfirm_INT_GPIO_PORT, &GPIO_InitStructure); 
 	
	/* 初始化按键cancel */ 
	GPIO_InitStructure.GPIO_Pin = KEYcancel_INT_GPIO_PIN;  
	GPIO_Init(KEYcancel_INT_GPIO_PORT, &GPIO_InitStructure);    	
}

