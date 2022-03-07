/*   
      扬州大学 测控15 杨寿晨         
		
	   485 modbus通讯程序         
        UART7  PF7 PF6       		

	      2019/4 - 2019/6                  */

#include "485.h"

// 函数：485 RE DE 引脚 初始化
//
void _485_Config(void)
{ 
	GPIO_InitTypeDef GPIO_InitStructure; 
	
	RCC_APB1PeriphClockCmd( RCC_AHB1Periph_GPIOD, ENABLE ); 
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;		//输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		//推挽输出
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;	//浮空	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;	//速度选择
	
	GPIO_InitStructure.GPIO_Pin   = _485_RE_PIN;		// 485 RE引脚初始化
	GPIO_Init(_485_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin   = _485_DE_PIN;		// 485 DE引脚初始化
	GPIO_Init(_485_PORT, &GPIO_InitStructure);

}

void _485_SendByte(  uint8_t ch )
{
	/* 发送一个字节数据到USART6 */
	USART_SendData(UART7,ch);
		
	/* 等待发送完毕 */
	while (USART_GetFlagStatus(UART7, USART_FLAG_TXE) == RESET);	
	
}


