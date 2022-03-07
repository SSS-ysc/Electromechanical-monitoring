#ifndef __IIC_H
#define __IIC_H

#include "stm32f4xx.h"

/*---------------------------------- IIC 引脚配置宏 ---------------------------------*/

#define Touch_IIC_SCL_CLK     RCC_AHB1Periph_GPIOC		// SCL 引脚时钟
#define Touch_IIC_SCL_PORT    GPIOC                 	// SCL 引脚端口
#define Touch_IIC_SCL_PIN     GPIO_Pin_13  				// SCL 引脚
         
#define Touch_IIC_SDA_CLK     RCC_AHB1Periph_GPIOB 	// SDA 引脚时钟
#define Touch_IIC_SDA_PORT    GPIOB                   // SDA 引脚端口
#define Touch_IIC_SDA_PIN     GPIO_Pin_2              // SDA 引脚

#define Touch_INT_CLK     RCC_AHB1Periph_GPIOA			// INT 引脚时钟
#define Touch_INT_PORT    GPIOA                   		// INT 引脚端口
#define Touch_INT_PIN     GPIO_Pin_15             		// INT 引脚

#define Touch_RST_CLK     RCC_AHB1Periph_GPIOI			// RST 引脚时钟
#define Touch_RST_PORT    GPIOI                   		// RST 引脚端口
#define Touch_RST_PIN     GPIO_Pin_11            		// RST 引脚

/*----------------------------------- IIC相关定义 ----------------------------------*/

#define ACK_OK  	1  			// 响应正常
#define ACK_ERR 	0				// 响应错误

// IIC通信延时，Touch_IIC_Delay()函数使用，
//	通信速度在100KHz左右，由于使用较长的FPC排线连接屏幕，不建议使用过高的速度
#define IIC_DelayVaule  20  	

/*------------------------------------ IO口操作 ------------------------------------*/   

#define Touch_IIC_SCL(a)	if (a)	\
										GPIO_SetBits(Touch_IIC_SCL_PORT,Touch_IIC_SCL_PIN);\
									else		\
										GPIO_ResetBits(Touch_IIC_SCL_PORT,Touch_IIC_SCL_PIN)		

#define Touch_IIC_SDA(a)	if (a)	\
										GPIO_SetBits(Touch_IIC_SDA_PORT,Touch_IIC_SDA_PIN);\
									else		\
										GPIO_ResetBits(Touch_IIC_SDA_PORT,Touch_IIC_SDA_PIN)		

/*------------------------------------ 函数声明 -----------------------------------*/  		
					
void 	Touch_IIC_GPIO_Config (void);			// IIC引脚初始化
void 	Touch_IIC_Delay(u32 a);					// IIC延时函数
void	Touch_INT_Out(void);						// INT数据脚配置为输出模式
void	Touch_INT_In(void);						// INT数据脚配置为输入模式								
void 	Touch_IIC_Start(void);					// 启动IIC通信
void 	Touch_IIC_Stop(void);					// IIC停止信号
void 	Touch_IIC_ACK(void);						//	发送响应信号
void 	Touch_IIC_NoACK(void);					// 发送非应答信号
u8 	Touch_IIC_WaitACK(void);				//	等待应答信号
u8	 	Touch_IIC_WriteByte(u8 IIC_Data); 	// 写字节函数
u8 	Touch_IIC_ReadByte(u8 ACK_Mode);		// 读字节函数
		
#endif //__IIC_H
