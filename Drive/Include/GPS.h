#ifndef __GPS_H
#define	__GPS_H

#include "stm32f4xx.h"
#include <string.h>
#include <stdio.h>

/* GPS�ӿ����� ʹ�ò�ͬ�Ĵ���ʱ��Ҫ�޸Ķ�Ӧ�Ľӿ� */
#define  GPS_USART                USART1

#define  USART_GPS_BaudRate       9600

#define  USART_GPS_TX_PIN		  GPIO_Pin_6			 // TX ����
#define	 USART_GPS_TX_PORT		  GPIOB					 // TX ���Ŷ˿�
#define	 USART_GPS_TX_CLK		  RCC_AHB1Periph_GPIOB	 // TX ����ʱ��
#define  USART_GPS_TX_PinSource   GPIO_PinSource6	     // ����Դ

#define  USART_GPS_RX_PIN		  GPIO_Pin_7             // RX ����
#define	 USART_GPS_RX_PORT		  GPIOB                  // RX ���Ŷ˿�
#define	 USART_GPS_RX_CLK		  RCC_AHB1Periph_GPIOB   // RX ����ʱ��
#define  USART_GPS_RX_PinSource   GPIO_PinSource7        // ����Դ

#define  GPS_RBUFF_SIZE           1024                   //���ڽ��ջ�������С


//UTCʱ����Ϣ
__packed typedef struct  
{										    
 	u16 year;	//���
	u8 month;	//�·�
	u8 date;	//����
	u8 hour; 	//Сʱ
	u8 min; 	//����
	u8 sec; 	//����
}nmea_utc_time; 

//NMEA 0183 Э����������ݴ�Žṹ��
__packed typedef struct  
{		
	nmea_utc_time utc;			//UTCʱ��
	u32 latitude;				//γ�� ������100000��,ʵ��Ҫ����100000
	u8 nshemi;					//��γ/��γ,N:��γ;S:��γ				  
	u32 longitude;			    //���� ������100000��,ʵ��Ҫ����100000
	u8 ewhemi;					//����/����,E:����;W:����
}nmea_msg;


void GPS_Config(void);
void NMEA_GNRMC_Analysis(nmea_msg *gpsx,u8 *buf);

#endif 
