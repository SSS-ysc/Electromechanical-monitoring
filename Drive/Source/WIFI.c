/*   
      扬州大学 测控15 杨寿晨       
		
	   有人WIFI232-B2  WIFI 程序    (ESP8266无外置天线，改为有人模块)	   
          UART7  PF7 PF6       	

	      2019/4 - 2019/6                  */

#include "WIFI.h"


// WIFI初始化
//
void WiFi_Config( void )
{
	
}


void _WIFI_SendByte(  uint8_t ch )
{
	/* 发送一个字节数据到UART7 */
	USART_SendData(UART7,ch);
		
	/* 等待发送完毕 */
	while (USART_GetFlagStatus(UART7, USART_FLAG_TXE) == RESET);	
	
}
