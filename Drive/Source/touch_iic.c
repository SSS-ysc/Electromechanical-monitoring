/***
	***************************************************************************************
	*	@file  	touch_iic.c
	*	@version V1.1
	*  @date    2018-1-1
	*	@author  反客科技
	*	@brief   触摸屏IIC接口相关函数
   ***************************************************************************************
   *  @description
	*
	*	实验平台：反客STM32F429核心板 + 7寸RGB液晶屏(RGB070M1)
	*	淘宝地址：https://shop212360197.taobao.com
	*	QQ交流群：536665479
	*
>>>>>	V1.1版本变更：
	*	
	*	1.将IO口配置为开漏输出，无需再频繁的修改IO口模式
	*	2.增加触摸屏的INT和RST引脚初始化（只对硬件版本V1.1以及之后的版本有效）
	*		
>>>>>	文件说明：
	*
	*  1.触摸屏相关的IIC函数
	* 	2.使用模拟IIC
	*	3.通信速度默认为100KHz
	*
	***************************************************************************************
***/

#include "touch_iic.h"  


/*****************************************************************************************
*	函 数 名: Touch_IIC_GPIO_Config
*	入口参数: 无
*	返 回 值: 无
*	函数功能: 初始化IIC的GPIO口,推挽输出
*	说    明: 由于IIC通信速度不高，这里的IO口速度配置为2M即可
******************************************************************************************/

void Touch_IIC_GPIO_Config (void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(Touch_IIC_SCL_CLK | Touch_IIC_SDA_CLK | Touch_INT_CLK | Touch_RST_CLK , ENABLE);	//初始化IO口时钟

	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;   	// 输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD; 		// 开漏输出
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;	// 不带上下拉
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;	// 速度等级2M  

	GPIO_InitStructure.GPIO_Pin = Touch_IIC_SCL_PIN; 		// SCL
	GPIO_Init(Touch_IIC_SCL_PORT, &GPIO_InitStructure);				   	

	GPIO_InitStructure.GPIO_Pin = Touch_IIC_SDA_PIN; 		// SDA	
	GPIO_Init(Touch_IIC_SDA_PORT, &GPIO_InitStructure);		
	
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      	// 推挽输出
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;		 	// 上拉	
	
	GPIO_InitStructure.GPIO_Pin = Touch_INT_PIN; 		//	INT
	GPIO_Init(Touch_INT_PORT, &GPIO_InitStructure);				

	GPIO_InitStructure.GPIO_Pin = Touch_RST_PIN; 		//	RST
	GPIO_Init(Touch_RST_PORT, &GPIO_InitStructure);					   

	GPIO_SetBits(Touch_IIC_SCL_PORT,Touch_IIC_SCL_PIN);	// SCL输出高电平
	GPIO_SetBits(Touch_IIC_SDA_PORT,Touch_IIC_SDA_PIN);	// SDA输出高电平
	GPIO_ResetBits(Touch_INT_PORT,Touch_INT_PIN); 			// INT输出低电平
	GPIO_SetBits(Touch_RST_PORT,Touch_RST_PIN);				// RST输出高	电平	
}

/*****************************************************************************************
*	函 数 名: Touch_IIC_Delay
*	入口参数: a - 延时时间
*	返 回 值: 无
*	函数功能: 简单延时函数
*	说    明: 为了移植的简便性且对延时精度要求不高，所以不需要使用定时器做延时
******************************************************************************************/

void Touch_IIC_Delay(u32 a)
{
	int i;
	while (a --)				
	{
		for (i = 0; i < 10; i++);
	}
}

/*****************************************************************************************
*	函 数 名: Touch_IIC_INT_Out
*	入口参数: 无
*	返 回 值: 无
*	函数功能: 配置IIC的INT脚为输出模式
*	说    明: 无
******************************************************************************************/

void Touch_INT_Out(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;      	// 输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      	// 推挽输出
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;		 	// 上拉	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;    	// 速度等级2M 
	GPIO_InitStructure.GPIO_Pin   = Touch_INT_PIN ;  		// 初始化 INT 引脚
	
	GPIO_Init(Touch_INT_PORT, &GPIO_InitStructure);		
}

/*****************************************************************************************
*	函 数 名: Touch_IIC_INT_In
*	入口参数: 无
*	返 回 值: 无
*	函数功能: 配置IIC的INT脚为输入模式
*	说    明: 无
******************************************************************************************/

void Touch_INT_In(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;   		//	输入模式
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;		//	浮空输入
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;		//	速度等级2M
	GPIO_InitStructure.GPIO_Pin 	= Touch_INT_PIN ;  		//	初始化 INT 引脚
	
	GPIO_Init(Touch_INT_PORT, &GPIO_InitStructure);
}

/*****************************************************************************************
*	函 数 名: Touch_IIC_Start
*	入口参数: 无
*	返 回 值: 无
*	函数功能: IIC起始信号
*	说    明: 在SCL处于高电平期间，SDA由高到低跳变为起始信号
******************************************************************************************/

void Touch_IIC_Start(void)
{
	Touch_IIC_SDA(1);		
	Touch_IIC_SCL(1);
	Touch_IIC_Delay(IIC_DelayVaule);
	
	Touch_IIC_SDA(0);
	Touch_IIC_Delay(IIC_DelayVaule);
	Touch_IIC_SCL(0);
	Touch_IIC_Delay(IIC_DelayVaule);
}

/*****************************************************************************************
*	函 数 名: Touch_IIC_Stop
*	入口参数: 无
*	返 回 值: 无
*	函数功能: IIC停止信号
*	说    明: 在SCL处于高电平期间，SDA由低到高跳变为起始信号
******************************************************************************************/

void Touch_IIC_Stop(void)
{
	Touch_IIC_SCL(0);
	Touch_IIC_Delay(IIC_DelayVaule);
	Touch_IIC_SDA(0);
	Touch_IIC_Delay(IIC_DelayVaule);
	
	Touch_IIC_SCL(1);
	Touch_IIC_Delay(IIC_DelayVaule);
	Touch_IIC_SDA(1);
	Touch_IIC_Delay(IIC_DelayVaule);
}

/*****************************************************************************************
*	函 数 名: Touch_IIC_ACK
*	入口参数: 无
*	返 回 值: 无
*	函数功能: IIC应答信号
*	说    明: 在SCL为高电平期间，SDA引脚输出为低电平，产生应答信号
******************************************************************************************/

void Touch_IIC_ACK(void)
{
	Touch_IIC_SCL(0);
	Touch_IIC_Delay(IIC_DelayVaule);
	Touch_IIC_SDA(0);
	Touch_IIC_Delay(IIC_DelayVaule);	
	Touch_IIC_SCL(1);
	Touch_IIC_Delay(IIC_DelayVaule);
	
	Touch_IIC_SCL(0);		// SCL输出低时，SDA应立即拉高，释放总线
	Touch_IIC_SDA(1);		
	
	Touch_IIC_Delay(IIC_DelayVaule);

}

/*****************************************************************************************
*	函 数 名: Touch_IIC_NoACK
*	入口参数: 无
*	返 回 值: 无
*	函数功能: IIC非应答信号
*	说    明: 在SCL为高电平期间，若SDA引脚为高电平，产生非应答信号
******************************************************************************************/

void Touch_IIC_NoACK(void)
{
	Touch_IIC_SCL(0);	
	Touch_IIC_Delay(IIC_DelayVaule);
	Touch_IIC_SDA(1);
	Touch_IIC_Delay(IIC_DelayVaule);
	Touch_IIC_SCL(1);
	Touch_IIC_Delay(IIC_DelayVaule);
	
	Touch_IIC_SCL(0);
	Touch_IIC_Delay(IIC_DelayVaule);
}

/*****************************************************************************************
*	函 数 名: Touch_IIC_WaitACK
*	入口参数: 无
*	返 回 值: 无
*	函数功能: 等待接收设备发出应答信号
*	说    明: 在SCL为高电平期间，若检测到SDA引脚为低电平，则接收设备响应正常
******************************************************************************************/

u8 Touch_IIC_WaitACK(void)
{
	Touch_IIC_SDA(1);
	Touch_IIC_Delay(IIC_DelayVaule);
	Touch_IIC_SCL(1);
	Touch_IIC_Delay(IIC_DelayVaule);	
	
	if( GPIO_ReadInputDataBit(Touch_IIC_SDA_PORT,Touch_IIC_SDA_PIN) != 0) //判断设备是否有做出响应		
	{
		Touch_IIC_SCL(0);	
		return ACK_ERR;	//无应答
	}
	else
	{
		Touch_IIC_SCL(0);	
		return ACK_OK;	//应答正常
	}
}

/*****************************************************************************************
*	函 数 名:	Touch_IIC_WriteByte
*	入口参数:	IIC_Data - 要写入的8位数据
*	返 回 值:	ACK_OK  - 设备响应正常
*          	ACK_ERR - 设备响应错误
*	函数功能:	写一字节数据
*	说    明:高位在前
******************************************************************************************/

u8 Touch_IIC_WriteByte(u8 IIC_Data)
{
	u8 i;

	for (i = 0; i < 8; i++)
	{
		Touch_IIC_SDA(IIC_Data & 0x80);
		
		Touch_IIC_Delay( IIC_DelayVaule );
		Touch_IIC_SCL(1);
		Touch_IIC_Delay( IIC_DelayVaule );
		Touch_IIC_SCL(0);		
		if(i == 7)
		{
			Touch_IIC_SDA(1);			
		}
		IIC_Data <<= 1;
	}

	return Touch_IIC_WaitACK(); //等待设备响应
}

/*****************************************************************************************
*	函 数 名:	Touch_IIC_ReadByte
*	入口参数:	ACK_Mode - 响应模式，输入1则发出应答信号，输入0发出非应答信号
*	返 回 值:	ACK_OK  - 设备响应正常
*          	ACK_ERR - 设备响应错误
*	函数功能:读一字节数据
*	说    明:1.高位在前
*				2.应在主机接收最后一字节数据时发送非应答信号
******************************************************************************************/

u8 Touch_IIC_ReadByte(u8 ACK_Mode)
{
	u8 IIC_Data = 0;
	u8 i = 0;
	
	for (i = 0; i < 8; i++)
	{
		IIC_Data <<= 1;
		
		Touch_IIC_SCL(1);
		Touch_IIC_Delay( IIC_DelayVaule );
		IIC_Data |= (GPIO_ReadInputDataBit(Touch_IIC_SDA_PORT,Touch_IIC_SDA_PIN) & 0x01);	
		Touch_IIC_SCL(0);
		Touch_IIC_Delay( IIC_DelayVaule );
	}
	
	if ( ACK_Mode == 1 )				//	应答信号
		Touch_IIC_ACK();
	else
		Touch_IIC_NoACK();		 	// 非应答信号
	
	return IIC_Data; 
}

/********************************************************************************************/
