#ifndef __MainTask_H
#define __MainTask_H

#include	"DIALOG.h"
#include	"GRAPH.h"
#include	"XBF_Font.h"

#include	"adc.h"
#include	"rtc.h"
#include	"DHT11.h"
#include	"4G_linking.h"
#include	"led&control.h"  

extern int16_t		AD_Value_FIR_CH1[1024] ;  //FIR处理结果缓存区
extern int16_t		AD_Value_FIR_CH2[1024] ;
extern int16_t		AD_Value_FIR_CH3[1024] ;
extern int16_t		AD_Value_FIR_CH4[1024] ;
extern int16_t		AD_Value_FIR_CH7[1024] ;
extern int16_t		AD_Value_FIR_CH8[1024] ;
extern int16_t		AD_Value_FIR_CH9[1024] ;
extern int16_t		AD_Value_FIR_CH10[1024];

extern int16_t		AD_Value_FFT_CH1[1024] ;  //FFT处理结果缓存区
extern int16_t    	AD_Value_FFT_CH2[1024] ;
extern int16_t    	AD_Value_FFT_CH3[1024] ;
extern int16_t    	AD_Value_FFT_CH4[1024] ;
extern int16_t    	AD_Value_FFT_CH7[1024] ;
extern int16_t    	AD_Value_FFT_CH8[1024] ;
extern int16_t    	AD_Value_FFT_CH9[1024] ;
extern int16_t    	AD_Value_FFT_CH10[1024];

extern int16_t		AD_Value_CH1_VPP ;			//各通道峰峰值
extern int16_t		AD_Value_CH2_VPP ;
extern int16_t		AD_Value_CH3_VPP ;
extern int16_t		AD_Value_CH4_VPP ;
extern int16_t		AD_Value_CH7_VPP ;
extern int16_t		AD_Value_CH8_VPP ;
extern int16_t		AD_Value_CH9_VPP ;
extern int16_t		AD_Value_CH10_VPP;

extern uint16_t		CH5_SPEED;					//转速
extern uint16_t		CH6_SPEED;

extern uint8_t		data_ready_display; 		//标志位
extern uint8_t		CH_select;					//通道显示选择标志位
extern uint8_t		WIFI_or_485;				//WIFI 485通讯选择标志位
extern uint8_t		GPS_select;					//GPS启用标志位
extern uint8_t		SD_select;					//SD存储允许标志位
extern uint8_t		SD_select_CH12;
extern uint8_t		SD_select_CH34;
extern uint8_t		SD_select_CH78 ;
extern uint8_t		SD_select_CH910;
extern	uint8_t		FIR_select;					//FIR Fc选择

extern uint8_t		DHT11_humi;
extern uint8_t		DHT11_temp;
extern uint16_t		temperature;
	
extern void Refresh_wave1_grid(void);
extern void Refresh_wave2_grid(void);
extern void Refresh_RTC_GPS(WM_MESSAGE * pMsg);
extern void Refresh_DHT11(WM_MESSAGE * pMsg);
extern void Refresh_SPEED(WM_MESSAGE * pMsg);
extern void Refresh_4G(WM_MESSAGE * pMsg);

extern GUI_CONST_STORAGE GUI_BITMAP bmBUTTONOFF;
extern GUI_CONST_STORAGE GUI_BITMAP bmBUTTONON;
extern GUI_CONST_STORAGE GUI_BITMAP bmsetting;
extern GUI_CONST_STORAGE GUI_BITMAP bmabout;
extern GUI_CONST_STORAGE GUI_BITMAP bmswitch;
extern GUI_CONST_STORAGE GUI_BITMAP bmwifi;
extern GUI_CONST_STORAGE GUI_BITMAP bm4G;
extern GUI_CONST_STORAGE GUI_BITMAP bmRS485;
extern GUI_CONST_STORAGE GUI_BITMAP bmSD;
extern GUI_CONST_STORAGE GUI_BITMAP bmOFF_1;
extern GUI_CONST_STORAGE GUI_BITMAP bmON_1;
extern GUI_CONST_STORAGE GUI_BITMAP bmyzu_yzu;

/*		主信息对话框控件		*/
#define ID_WINDOW_0              		(GUI_ID_USER + 0x00)
#define ID_TimerTime             		(GUI_ID_USER + 0x01)
#define ID_TEXT_0                		(GUI_ID_USER + 0x02)
#define ID_TEXT_1                		(GUI_ID_USER + 0x03)
#define ID_TEXT_2                		(GUI_ID_USER + 0x04)
#define ID_TEXT_3                		(GUI_ID_USER + 0x05)
#define ID_TEXT_4                		(GUI_ID_USER + 0x06)
#define ID_TEXT_5                		(GUI_ID_USER + 0x07)
#define ID_TEXT_6                		(GUI_ID_USER + 0x08)
#define ID_TEXT_7                		(GUI_ID_USER + 0x09)
#define ID_TEXT_8                		(GUI_ID_USER + 0x0A)
#define ID_TEXT_9                		(GUI_ID_USER + 0x0B)
#define ID_TEXT_10               		(GUI_ID_USER + 0x0C)
#define ID_TEXT_11               		(GUI_ID_USER + 0x0D)
#define ID_TEXT_12               		(GUI_ID_USER + 0x0E)
#define ID_TEXT_13               		(GUI_ID_USER + 0x0F)
#define ID_BUTTON_0              		(GUI_ID_USER + 0x10)
#define ID_BUTTON_1              		(GUI_ID_USER + 0x11)
#define ID_BUTTON_2              		(GUI_ID_USER + 0x12)
#define ID_IMAGE_0              		(GUI_ID_USER + 0x13)

/*		设置 对话框控件		*/
#define ID_FRAMEWIN_0            		(GUI_ID_USER + 0x30)
#define ID_MULTIPAGE_0					(GUI_ID_USER + 0x31)

#define ID_WINDOW_option_page1			(GUI_ID_USER + 0x32)
#define ID_TEXT_option_page1_0			(GUI_ID_USER + 0x33)
#define ID_TEXT_option_page1_1			(GUI_ID_USER + 0x34)
#define ID_TEXT_option_page1_2			(GUI_ID_USER + 0x35)
#define ID_TEXT_option_page1_3			(GUI_ID_USER + 0x36)
#define ID_TEXT_option_page1_4			(GUI_ID_USER + 0x37)
#define ID_TEXT_option_page1_5			(GUI_ID_USER + 0x38)
#define ID_TEXT_option_page1_6			(GUI_ID_USER + 0x39)
#define ID_TEXT_option_page1_7			(GUI_ID_USER + 0x3A)
#define ID_TEXT_option_page1_8			(GUI_ID_USER + 0x3B)
#define ID_TEXT_option_page1_9			(GUI_ID_USER + 0x3C)
#define ID_TEXT_option_page1_10			(GUI_ID_USER + 0x3D)
#define ID_BUTTON_option_page1_0		(GUI_ID_USER + 0x3E)

#define ID_WINDOW_option_page2			(GUI_ID_USER + 0x40)
#define ID_TEXT_option_page2_0			(GUI_ID_USER + 0x41)
#define ID_TEXT_option_page2_1			(GUI_ID_USER + 0x42)
#define ID_TEXT_option_page2_2			(GUI_ID_USER + 0x43)
#define ID_TEXT_option_page2_3			(GUI_ID_USER + 0x44)
#define ID_TEXT_option_page2_4			(GUI_ID_USER + 0x45)
#define ID_TEXT_option_page2_5			(GUI_ID_USER + 0x46)
#define ID_TEXT_option_page2_6			(GUI_ID_USER + 0x47)
#define ID_BUTTON_option_page2_0		(GUI_ID_USER + 0x48)
#define ID_TimerTime_option_page2		(GUI_ID_USER + 0x49)

#define ID_WINDOW_option_page3			(GUI_ID_USER + 0x4A)
#define ID_TEXT_option_page3_0			(GUI_ID_USER + 0x4B)
#define ID_TEXT_option_page3_1			(GUI_ID_USER + 0x4C)
#define ID_TEXT_option_page3_2			(GUI_ID_USER + 0x4D)
#define ID_TEXT_option_page3_3			(GUI_ID_USER + 0x4E)
#define ID_TEXT_option_page3_4			(GUI_ID_USER + 0x4F)
#define ID_TEXT_option_page3_5			(GUI_ID_USER + 0x50)
#define ID_TEXT_option_page3_6			(GUI_ID_USER + 0x51)
#define ID_TEXT_option_page3_7			(GUI_ID_USER + 0x52)
#define ID_TEXT_option_page3_8			(GUI_ID_USER + 0x53)
#define ID_BUTTON_option_page3_0		(GUI_ID_USER + 0x54)
#define ID_BUTTON_option_page3_1		(GUI_ID_USER + 0x55)
#define ID_BUTTON_option_page3_2		(GUI_ID_USER + 0x56)

#define ID_WINDOW_option_page4			(GUI_ID_USER + 0x5A)
#define ID_TEXT_option_page4_0			(GUI_ID_USER + 0x5B)
#define ID_TEXT_option_page4_1			(GUI_ID_USER + 0x5C)
#define ID_TEXT_option_page4_2			(GUI_ID_USER + 0x5D)
#define ID_TEXT_option_page4_3			(GUI_ID_USER + 0x5E)
#define ID_TEXT_option_page4_4			(GUI_ID_USER + 0x5F)
#define ID_TEXT_option_page4_5			(GUI_ID_USER + 0x60)
#define ID_CHECKBOX_option_page4_0		(GUI_ID_USER + 0x62)
#define ID_CHECKBOX_option_page4_1		(GUI_ID_USER + 0x63)
#define ID_CHECKBOX_option_page4_2		(GUI_ID_USER + 0x64)
#define ID_CHECKBOX_option_page4_3		(GUI_ID_USER + 0x65)
#define ID_BUTTON_option_page4_0		(GUI_ID_USER + 0x66)

#define ID_WINDOW_option_page5			(GUI_ID_USER + 0x67)
#define ID_TEXT_option_page5_0			(GUI_ID_USER + 0x68)
#define ID_TEXT_option_page5_1			(GUI_ID_USER + 0x69)
#define ID_TEXT_option_page5_2			(GUI_ID_USER + 0x6A)
#define ID_TEXT_option_page5_3			(GUI_ID_USER + 0x6B)
#define ID_TEXT_option_page5_4			(GUI_ID_USER + 0x6C)
#define ID_BUTTON_option_page5_0		(GUI_ID_USER + 0x6D)
#define ID_TimerTime_option_page5		(GUI_ID_USER + 0x6E)
#define ID_GRAPH_option_page5_0			(GUI_ID_USER + 0x6F)
#define ID_GRAPH_option_page5_1			(GUI_ID_USER + 0x70)

/*		关于 对话框控件		*/
#define ID_FRAMEWIN_1					(GUI_ID_USER + 0x76)
#define ID_TEXT_about_0					(GUI_ID_USER + 0x77)
#define ID_TEXT_about_1					(GUI_ID_USER + 0x78)
#define ID_TEXT_about_2					(GUI_ID_USER + 0x79)
#define ID_TEXT_about_3					(GUI_ID_USER + 0x7A)
#define ID_TEXT_about_4					(GUI_ID_USER + 0x7B)
#define ID_TEXT_about_5					(GUI_ID_USER + 0x7C)
#define ID_TEXT_about_6					(GUI_ID_USER + 0x7D)

/*		波形显示1对话框控件		*/
#define ID_WINDOW_1						(GUI_ID_USER + 0x7E)

/*		波形显示2对话框控件		*/
#define ID_WINDOW_2						(GUI_ID_USER + 0x7F)

/*		波形显示2对话框控件		*/
#define ID_WINDOW_3						(GUI_ID_USER + 0x80)
#define ID_TimerTime_VPP				(GUI_ID_USER + 0x81)
#define ID_TEXT_VPP_0					(GUI_ID_USER + 0x82)	 
#define ID_TEXT_VPP_1					(GUI_ID_USER + 0x83)
#define ID_TEXT_VPP_2					(GUI_ID_USER + 0x84)
#define ID_TEXT_VPP_3					(GUI_ID_USER + 0x85)
#define ID_TEXT_VPP_4					(GUI_ID_USER + 0x86)
#define ID_TEXT_VPP_5					(GUI_ID_USER + 0x87)
#define ID_TEXT_VPP_6					(GUI_ID_USER + 0x88)
#define ID_TEXT_VPP_7					(GUI_ID_USER + 0x89)

#define ID_TEXT_VPP_00					(GUI_ID_USER + 0x8A)
#define ID_TEXT_VPP_01					(GUI_ID_USER + 0x8B)
#define ID_TEXT_VPP_02					(GUI_ID_USER + 0x8C)
#define ID_TEXT_VPP_03					(GUI_ID_USER + 0x8D)
#define ID_TEXT_VPP_04					(GUI_ID_USER + 0x8E)
#define ID_TEXT_VPP_05					(GUI_ID_USER + 0x8F)
#define ID_TEXT_VPP_06					(GUI_ID_USER + 0x90)
#define ID_TEXT_VPP_07					(GUI_ID_USER + 0x91)

#define ID_TEXT_VPP_10					(GUI_ID_USER + 0x92)
#define ID_TEXT_VPP_11					(GUI_ID_USER + 0x93)
#define ID_TEXT_VPP_12					(GUI_ID_USER + 0x94)
#define ID_TEXT_VPP_13					(GUI_ID_USER + 0x95)
#define ID_TEXT_VPP_14					(GUI_ID_USER + 0x96)
#define ID_TEXT_VPP_15					(GUI_ID_USER + 0x97)
#define ID_TEXT_VPP_16					(GUI_ID_USER + 0x98)
#define ID_TEXT_VPP_17					(GUI_ID_USER + 0x99)

#endif

