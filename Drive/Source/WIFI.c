/*   
      ���ݴ�ѧ ���15 ���ٳ�       
		
	   ����WIFI232-B2  WIFI ����    (ESP8266���������ߣ���Ϊ����ģ��)	   
          UART7  PF7 PF6       	

	      2019/4 - 2019/6                  */

#include "WIFI.h"


// WIFI��ʼ��
//
void WiFi_Config( void )
{
	
}


void _WIFI_SendByte(  uint8_t ch )
{
	/* ����һ���ֽ����ݵ�UART7 */
	USART_SendData(UART7,ch);
		
	/* �ȴ�������� */
	while (USART_GetFlagStatus(UART7, USART_FLAG_TXE) == RESET);	
	
}
