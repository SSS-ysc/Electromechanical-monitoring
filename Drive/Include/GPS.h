#ifndef __GPS_H
#define	__GPS_H

#include "stm32f4xx.h"
#include <string.h>
#include <stdio.h>

/* GPS接口配置 使用不同的串口时，要修改对应的接口 */
#define  GPS_USART                USART1

#define  USART_GPS_BaudRate       9600

#define  USART_GPS_TX_PIN		  GPIO_Pin_6			 // TX 引脚
#define	 USART_GPS_TX_PORT		  GPIOB					 // TX 引脚端口
#define	 USART_GPS_TX_CLK		  RCC_AHB1Periph_GPIOB	 // TX 引脚时钟
#define  USART_GPS_TX_PinSource   GPIO_PinSource6	     // 引脚源

#define  USART_GPS_RX_PIN		  GPIO_Pin_7             // RX 引脚
#define	 USART_GPS_RX_PORT		  GPIOB                  // RX 引脚端口
#define	 USART_GPS_RX_CLK		  RCC_AHB1Periph_GPIOB   // RX 引脚时钟
#define  USART_GPS_RX_PinSource   GPIO_PinSource7        // 引脚源

#define  GPS_RBUFF_SIZE           1024                   //串口接收缓冲区大小


//UTC时间信息
__packed typedef struct  
{										    
 	u16 year;	//年份
	u8 month;	//月份
	u8 date;	//日期
	u8 hour; 	//小时
	u8 min; 	//分钟
	u8 sec; 	//秒钟
}nmea_utc_time; 

//NMEA 0183 协议解析后数据存放结构体
__packed typedef struct  
{		
	nmea_utc_time utc;			//UTC时间
	u32 latitude;				//纬度 分扩大100000倍,实际要除以100000
	u8 nshemi;					//北纬/南纬,N:北纬;S:南纬				  
	u32 longitude;			    //经度 分扩大100000倍,实际要除以100000
	u8 ewhemi;					//东经/西经,E:东经;W:西经
}nmea_msg;


void GPS_Config(void);
void NMEA_GNRMC_Analysis(nmea_msg *gpsx,u8 *buf);

#endif 
