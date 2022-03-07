/*   
		  扬州大学 测控15 杨寿晨          
		
			页面控件刷新程序        

			2019/4 - 2019/6                         */

#include  "MainTask.h"
#include  <includes.h>
#pragma		diag_suppress 870		//屏蔽warning 870

/********************************************************************
*		函 数 名: Refresh_wave1_grid
*		功能说明: 绘制 波形图1 的网格        
*/
void Refresh_wave1_grid(void)
{	
	GUI_SetColor(GUI_WHITE);	
	GUI_SetPenSize(2);					//坐标系
	GUI_DrawLine(20,0,20,239);
	GUI_DrawLine(20,120,520,120);
	GUI_DrawLine(20,238,520,238);	
	GUI_SetPenSize(1);
	
	GUI_SetColor(0xFFA9F16C);
	
	GUI_SetLineStyle(GUI_LS_DOT);
	
	GUI_DrawLine(20,30,520,30);			//网格
	GUI_DrawLine(20,60,520,60);
	GUI_DrawLine(20,90,520,90);
	GUI_DrawLine(20,150,520,150);
	GUI_DrawLine(20,180,520,180);
	GUI_DrawLine(20,210,520,210);
	
	GUI_DrawLine(70,0,70,240);
	GUI_DrawLine(120,0,120,240);
	GUI_DrawLine(170,0,170,240);
	GUI_DrawLine(220,0,220,240);
	GUI_DrawLine(270,0,270,240);
	GUI_DrawLine(320,0,320,240);
	GUI_DrawLine(370,0,370,240);
	GUI_DrawLine(420,0,420,240);
	GUI_DrawLine(470,0,470,240);
	
	GUI_SetLineStyle(GUI_LS_SOLID);

	GUI_DispDecAt(50,72,230,2);			//横向刻度值
	GUI_DispDecAt(100,122,230,3);
	GUI_DispDecAt(150,172,230,3);
	GUI_DispDecAt(200,222,230,3);
	GUI_DispDecAt(250,272,230,3);
	GUI_DispDecAt(300,322,230,3);
	GUI_DispDecAt(350,372,230,3);	
	GUI_DispDecAt(400,422,230,3);
	GUI_DispDecAt(450,472,230,3);
	
	if( CH_select==0 || CH_select==1 )
	{	
		GUI_DispDecAt(54,3, 26,2);		//刻度值
		GUI_DispDecAt(36,3, 56,2);
		GUI_DispDecAt(18,3, 86,2);

		GUI_DispDecAt(18,3,146,2);
		GUI_DispDecAt(36,3,176,2);
		GUI_DispDecAt(54,3,206,2);
		
		GUI_DispStringAt("um",5,128);
	}
	if( CH_select==2 )
	{	
		GUI_DispDecAt(54,3, 26,2);		//刻度值
		GUI_DispDecAt(36,3, 56,2);
		GUI_DispDecAt(18,3, 86,2);

		GUI_DispDecAt(18,3,146,2);
		GUI_DispDecAt(36,3,176,2);
		GUI_DispDecAt(54,3,206,2);
		
		GUI_DispStringAt("um",5,128);
	}
	if( CH_select==3 )
	{	
		GUI_DispDecAt(90,3, 26,2);		//刻度值
		GUI_DispDecAt(60,3, 56,2);
		GUI_DispDecAt(30,3, 86,2);

		GUI_DispDecAt(30,3,146,2);
		GUI_DispDecAt(60,3,176,2);
		GUI_DispDecAt(90,3,206,2);
		
		GUI_DispStringAt("**",5,128);
	}	
	
	
	GUI_SetFont(&GUI_Font8x10_ASCII);
	GUI_DispDecAt( 0,3,116,1);			// 0 刻度值	
	

}

/********************************************************************
*		函 数 名: Refresh_wave2_grid
*		功能说明: 绘制 波形图2 的网格        
*/
void Refresh_wave2_grid(void)
{	
	if( CH_select==0 || CH_select==1 )
	{
		GUI_SetColor(GUI_WHITE);
		GUI_SetPenSize(2);
		
		GUI_DrawLine(20,0,20,239);			//坐标系
		GUI_DrawLine(20,120,280,120);
		GUI_DrawLine(20,238,280,238);
		
		GUI_DrawLine(20,30,25,30);			//小刻度
		GUI_DrawLine(20,60,25,60);
		GUI_DrawLine(20,90,25,90);
		GUI_DrawLine(20,150,25,150);
		GUI_DrawLine(20,180,25,180);
		GUI_DrawLine(20,210,25,210);
		
		GUI_DrawLine(70,117,70,119);		//横坐标刻度
		GUI_DrawLine(120,117,120,119);
		GUI_DrawLine(170,117,170,119);
		GUI_DrawLine(220,117,220,119);
		GUI_DrawLine(70,235,70,237);
		GUI_DrawLine(120,235,120,237);
		GUI_DrawLine(170,235,170,237);
		GUI_DrawLine(220,235,0,237);

		
		GUI_SetPenSize(1);
		
		GUI_SetColor(0xFFA9F16C);
		GUI_DrawCircle(400,130,40);			//轴心轨迹 圆
		GUI_DrawCircle(400,130,80);
		
		GUI_DispStringAt("um",496,120);
		
		GUI_SetLineStyle(GUI_LS_DOT);		//轴心轨迹坐标系		
		GUI_DrawLine(300,130,500,130);
		GUI_DrawLine(400,30,400,230);
			
		GUI_DrawLine(320,50,480,210);
		GUI_DrawLine(320,210,480,50);
		GUI_SetLineStyle(GUI_LS_SOLID);
		
		if( CH_select ==0 )
		{
			if(AD_Value_CH1_VPP *0.61 < 120 && AD_Value_CH2_VPP *0.61 < 120 )
			{
				GUI_DispDecAt(24,442, 120,2);		//轴心轨迹刻度值,自适应
				GUI_DispDecAt(48,482, 120,2);	
				GUI_DispDecAt(0, 404, 120,1);
			}
			else
			{	
				GUI_DispDecAt(48,442, 120,2);
				GUI_DispDecAt(96,482, 120,2);	
				GUI_DispDecAt(0, 404, 120,1);
			}
		}
		else
		{
			if(AD_Value_CH3_VPP *0.61 < 120 && AD_Value_CH4_VPP *0.61 < 120 )
			{
				GUI_DispDecAt(24,442, 120,2);		//轴心轨迹刻度值,自适应
				GUI_DispDecAt(48,482, 120,2);	
				GUI_DispDecAt(0, 404, 120,1);
			}
			else
			{	
				GUI_DispDecAt(48,442, 120,2);
				GUI_DispDecAt(96,482, 120,2);	
				GUI_DispDecAt(0, 404, 120,1);
			}
		}
		
		GUI_DispDecAt(54,3, 26,2);			//刻度值
		GUI_DispDecAt(36,3, 56,2);
		GUI_DispDecAt(18,3, 86,2);

		GUI_DispDecAt(54,3,146,2);			//刻度值
		GUI_DispDecAt(36,3,176,2);
		GUI_DispDecAt(18,3,206,2);

		GUI_DispStringAt("um",5,128);
		
		GUI_SetFont(&GUI_Font8x10_ASCII);	// 0 刻度值
		GUI_DispDecAt( 0,3,116,1);
		GUI_DispDecAt( 0,3,230,1);			
	}
	
	if( CH_select==2 )
	{
		GUI_SetColor(GUI_WHITE);
		GUI_SetPenSize(2);
		
		GUI_DrawLine(20,  0, 20,239);		//坐标系
		GUI_DrawLine(20,120,520,120);
		GUI_DrawLine(20,238,520,238);	
		
		GUI_DrawLine(20,30,25,30);			//小刻度
		GUI_DrawLine(20,60,25,60);
		GUI_DrawLine(20,90,25,90);
		GUI_DrawLine(20,150,25,150);
		GUI_DrawLine(20,180,25,180);
		GUI_DrawLine(20,210,25,210);
		
		GUI_SetPenSize(1);
		
		GUI_SetColor(0xFFA9F16C);
		
		GUI_DispDecAt(54,3, 26,2);			//刻度值
		GUI_DispDecAt(36,3, 56,2);
		GUI_DispDecAt(18,3, 86,2);

		GUI_DispDecAt(54,3,146,2);			//刻度值
		GUI_DispDecAt(36,3,176,2);
		GUI_DispDecAt(18,3,206,2);
		
		GUI_DispStringAt("um",5,128);
		
		GUI_SetFont(&GUI_Font8x10_ASCII);	// 0 刻度值
		GUI_DispDecAt( 0,3,116,1);
		GUI_DispDecAt( 0,3,230,1);	
	}
	
	if( CH_select==3 )
	{
		GUI_SetColor(GUI_WHITE);
		GUI_SetPenSize(2);
		
		GUI_DrawLine(20,  0, 20,239);		//坐标系
		GUI_DrawLine(20,120,520,120);
		GUI_DrawLine(20,238,520,238);	
		
		GUI_DrawLine(20,30,25,30);			//小刻度
		GUI_DrawLine(20,60,25,60);
		GUI_DrawLine(20,90,25,90);
		GUI_DrawLine(20,150,25,150);
		GUI_DrawLine(20,180,25,180);
		GUI_DrawLine(20,210,25,210);
		
		GUI_SetPenSize(1);
		
		GUI_SetColor(0xFFA9F16C);
		
		GUI_DispDecAt(90,3, 26,2);			//刻度值
		GUI_DispDecAt(60,3, 56,2);
		GUI_DispDecAt(30,3, 86,2);

		GUI_DispDecAt(90,3,146,2);			//刻度值
		GUI_DispDecAt(60,3,176,2);
		GUI_DispDecAt(30,3,206,2);
		
		GUI_DispStringAt("**",5,128);
		
		GUI_SetFont(&GUI_Font8x10_ASCII);	// 0 刻度值
		GUI_DispDecAt( 0,3,116,1);
		GUI_DispDecAt( 0,3,230,1);	
	}
}	

/********************************************************************
*		函 数 名: Refresh_RTC_GPS
*		功能说明: 刷新GPS、RTC信息         
*/
void Refresh_RTC_GPS(WM_MESSAGE * pMsg)
{  
	RTC_TimeTypeDef RTC_TimeStructure;
	RTC_DateTypeDef RTC_DateStructure;
	
	extern uint32_t		data_longitude;//经度纬度缓存
	extern uint8_t		data_ewhemi;
	extern uint32_t		data_latitude;
	extern uint8_t		data_nshemi;  
	float tp;	
	char buf[40];

	WM_HWIN hWin = pMsg->hWin;

	RTC_GetTime(RTC_Format_BIN, &RTC_TimeStructure);
	RTC_GetDate(RTC_Format_BIN, &RTC_DateStructure);
	
	memset(buf, 0, sizeof(buf));
	sprintf((char *)buf, "%0.2d:%0.2d:%0.2d", RTC_TimeStructure.RTC_Hours, RTC_TimeStructure.RTC_Minutes,RTC_TimeStructure.RTC_Seconds);
	TEXT_SetText(WM_GetDialogItem(hWin,ID_TEXT_0), buf);
	
 	memset(buf, 0, sizeof(buf));
	sprintf((char *)buf, "2019/%0.2d/%0.2d",  RTC_DateStructure.RTC_Month, RTC_DateStructure.RTC_Date);	//这里 year有BUG  GPS解析一直会是2021
//	sprintf((char *)buf, "20%0.2d/%0.2d/%0.2d",  RTC_DateStructure.RTC_Year, RTC_DateStructure.RTC_Month, RTC_DateStructure.RTC_Date);	
	TEXT_SetText(WM_GetDialogItem(hWin,ID_TEXT_1), buf);
	
	memset(buf, 0, sizeof(buf));
	tp=data_longitude;
	sprintf((char *)buf,"%.3f %1c ",tp/=100000,data_ewhemi);
	TEXT_SetText(WM_GetDialogItem(hWin,ID_TEXT_5), buf);	
	
	memset(buf, 0, sizeof(buf));
	tp=data_latitude;
	sprintf((char *)buf,"%.3f %1c ",tp/=100000,data_nshemi);
	TEXT_SetText(WM_GetDialogItem(hWin,ID_TEXT_6), buf);	
	
}

/********************************************************************
*		函 数 名: Refresh_4G
*		功能说明: 刷新4G通讯链接状态          
*/
void Refresh_4G(WM_MESSAGE * pMsg)
{   
	char buf[20];
	
	WM_HWIN hWin = pMsg->hWin;
	
	if(GPIO_ReadInputDataBit(_4G_LINKA_PORT,_4G_LINKA_PIN)== 1)
	{
	memset(buf, 0, sizeof(buf));   
	sprintf((char *)buf, " online ");
	TEXT_SetTextColor(WM_GetDialogItem(hWin,ID_TEXT_option_page2_6), 0xFFA8AB1D	);
	TEXT_SetText(WM_GetDialogItem(hWin,ID_TEXT_option_page2_6), buf);
	}
	else
	{
	memset(buf, 0, sizeof(buf));   
	sprintf((char *)buf, " Not online ");
	TEXT_SetTextColor(WM_GetDialogItem(hWin,ID_TEXT_option_page2_6), 0xFF404341	);
	TEXT_SetText(WM_GetDialogItem(hWin,ID_TEXT_option_page2_6), buf);
	}		

}

/********************************************************************
*		函 数 名: Refresh_DHT11
*		功能说明: 刷新DHT11温湿度         
*/
void Refresh_DHT11(WM_MESSAGE * pMsg)
{   
	char buf[60];
	
	WM_HWIN hWin = pMsg->hWin;
	
	memset(buf, 0, sizeof(buf));   
	sprintf((char *)buf, "室温: %d ℃ ", DHT11_temp);
	TEXT_SetFont(WM_GetDialogItem(hWin,ID_TEXT_2),&XBF_Font16);
	TEXT_SetText(WM_GetDialogItem(hWin,ID_TEXT_2), buf);
	
	memset(buf, 0, sizeof(buf));
	sprintf((char *)buf, "湿度: %d %%", DHT11_humi);
	TEXT_SetFont(WM_GetDialogItem(hWin,ID_TEXT_3),&XBF_Font16);
	TEXT_SetText(WM_GetDialogItem(hWin,ID_TEXT_3), buf);

}

/********************************************************************
*		函 数 名: Refresh_SPEED
*		功能说明: 刷新转速信息          
*/
void Refresh_SPEED(WM_MESSAGE * pMsg)
{   
	char buf[40];
	
	WM_HWIN hWin = pMsg->hWin;
	
	memset(buf, 0, sizeof(buf));   
	sprintf((char *)buf, "转速: %d r/min ", CH5_SPEED);
	TEXT_SetText(WM_GetDialogItem(hWin,ID_TEXT_7), buf);

	memset(buf, 0, sizeof(buf));   
	sprintf((char *)buf, "转速: %d r/min ", CH6_SPEED);
	TEXT_SetText(WM_GetDialogItem(hWin,ID_TEXT_8), buf);	
}

