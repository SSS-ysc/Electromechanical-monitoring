/***
	***************************************************************************************
	*	@file  	GUI_Touch.c
	*	@version V1.0
	*  @date    2017-12-26
	*	@author  反客科技
	*	@brief   emwin触摸移植
   ***************************************************************************************
   *  @description
	*
	*	实验平台：反客STM32F429核心板 + 7寸RGB液晶屏
	*	淘宝地址：https://shop212360197.taobao.com
	*	QQ交流群：536665479
	*
	***************************************************************************************
***/

#include	"GUI_Touch.h"


GUI_PID_STATE GUI_TouchState ;	// emWin触摸参数结构体

/*****************************************************************************************
*	函 数 名: GUI_TouchScan
*	入口参数: 无
*	返 回 值: 无
*	函数功能: 传递触摸参数给emwin
*	说    明: 在SysTick中断里被调用
******************************************************************************************/

void	GUI_TouchScan(void){
	
	Touch_Scan(); //触摸扫描

	if( touchInfo.flag == 1)		// 若发生触摸
	{
		GUI_TouchState.x = touchInfo.x[0];		// x坐标
		GUI_TouchState.y = touchInfo.y[0];		// y坐标
		GUI_TouchState.Pressed = 1;				// 触摸按下标志位
		GUI_PID_StoreState(&GUI_TouchState);	// 传递触摸参数
	}
	else
	{
		GUI_TouchState.Pressed = 0;				//	无触摸发生
		GUI_PID_StoreState(&GUI_TouchState);	// 传递触摸参数
	}	
}
