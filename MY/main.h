#ifndef __MAIN_H
#define __MAIN_H

#include  <includes.h>
#include  "arm_math.h"
#include  "stm32_dsp.h"
  
#include  "sdram.h" 
#include  "lcd_pwm.h"
#include  "touch_070.h"
#include  "GUI.h"
#include  "GUI_Touch.h"
#include  "WM.h"
#include  "XBF_Font.h"

#include  "delay.h"
#include  "led&control.h"
#include  "usart.h"
#include  "key.h"
#include  "adc.h"
#include  "4G_linking.h"
#include  "rtc.h"
#include  "spi_flash.h"
#include  "ff.h"
#include  "DHT11.h"
#include  "GPS.h"
#include  "iwdg.h"
#include  "WIFI.h"
#include  "485.h"
#include  "tim.h"


/*---------------------- 任务优先级 ---------------------*/

#define  Start_Task_PRIO					2

#define	 iwdg_Task_PRIO		  				3
#define	 Touch_Task_PRIO		  			4
#define	 Key_Task_PRIO			    		5
#define	 ADC2_Task_PRIO			   			6
#define	 ADC3_Task_PRIO			    		7
#define	 DSP_Task_PRIO 						8

#define	 GPS_Task_PRIO			    		10
#define	 DHT11_Task_PRIO					11
#define	 LED_Task_PRIO			    		12
#define	 emWin_Task_PRIO			  		13

#define	 SD_Task_PRIO						17		//测试发现 通讯任务极其占用CPU 将其任务优先级后置
#define	 _4G_Task_PRIO						18
#define	 WIFI_Task_PRIO						19		
#define	 _485_Task_PRIO						20
#define	 SystemDatasBroadcast_Task_PRIO     21

/*--------------------- 任务堆栈大小  --------------------*/

#define  Start_Task_STK_SIZE						128

#define	 SystemDatasBroadcast_Task_STK_SIZE			128
#define	 iwdg_Task_STK_SIZE							128
#define	 LED_Task_STK_SIZE							128
#define	 ADC2_Task_STK_SIZE							128
#define	 ADC3_Task_STK_SIZE							128
#define	 Key_Task_STK_SIZE							128
#define	 DHT11_Task_STK_SIZE						128
#define	 GPS_Task_STK_SIZE							256
#define	 _4G_Task_STK_SIZE							256
#define	 _485_Task_STK_SIZE							256
#define	 WIFI_Task_STK_SIZE							256
#define	 Touch_Task_STK_SIZE						256
#define	 SD_Task_STK_SIZE							512
#define	 DSP_Task_STK_SIZE							2048
#define	 emWin_Task_STK_SIZE						4096

#endif

