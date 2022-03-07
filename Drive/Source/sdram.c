/***
	***************************************************************************
	*	@file  	sdram.c
	*	@brief   sdram初始化，本代码移植于官方stm32f429discovery例程，
	*				并作出相应修改
	*				
   ******************************************************************************
   *  
	* 
	* 
	* 
	***************************************************************************
***/
  
#include "sdram.h"   

/******************************************************************************************************
*	函 数 名: SDRAM_delay
*	入口参数: 无
*	返 回 值: 无
*	函数功能: 简易延时函数，单位约为5ms
*	说    明: 无
*******************************************************************************************************/

void SDRAM_delay(__IO uint32_t nCount)
{
  __IO uint32_t index = 0; 
  for(index = (100000 * nCount); index != 0; index--)
  {
  }
}

/******************************************************************************************************
*	函 数 名: SDRAM_GPIO_Config
*	入口参数: 无
*	返 回 值: 无
*	函数功能: 配置GPIO
*	说    明: 无
*******************************************************************************************************/

void SDRAM_GPIO_Config(void)
{		
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE |       
	RCC_AHB1Periph_GPIOF | RCC_AHB1Periph_GPIOG | RCC_AHB1Periph_GPIOH | RCC_AHB1Periph_GPIOI,ENABLE); 	

	//IO口配置
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;       //配置为复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;   
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽输出
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;   

	//地址线 
	GPIO_PinAFConfig(FMC_A0_PORT,  FMC_A0_PINSOURCE ,  FMC_A0_AF);	
	GPIO_PinAFConfig(FMC_A1_PORT,  FMC_A1_PINSOURCE ,  FMC_A1_AF);	
	GPIO_PinAFConfig(FMC_A2_PORT,  FMC_A2_PINSOURCE ,  FMC_A2_AF);	
	GPIO_PinAFConfig(FMC_A3_PORT,  FMC_A3_PINSOURCE ,  FMC_A3_AF);  
	GPIO_PinAFConfig(FMC_A4_PORT,  FMC_A4_PINSOURCE ,  FMC_A4_AF);  
	GPIO_PinAFConfig(FMC_A5_PORT,  FMC_A5_PINSOURCE ,  FMC_A5_AF);  
	GPIO_PinAFConfig(FMC_A6_PORT,  FMC_A6_PINSOURCE ,  FMC_A6_AF);  
	GPIO_PinAFConfig(FMC_A7_PORT,  FMC_A7_PINSOURCE ,  FMC_A7_AF);	
	GPIO_PinAFConfig(FMC_A8_PORT,  FMC_A8_PINSOURCE ,  FMC_A8_AF);
	GPIO_PinAFConfig(FMC_A9_PORT,  FMC_A9_PINSOURCE ,  FMC_A9_AF);
	GPIO_PinAFConfig(FMC_A10_PORT, FMC_A10_PINSOURCE , FMC_A10_AF);
	GPIO_PinAFConfig(FMC_A11_PORT, FMC_A11_PINSOURCE , FMC_A11_AF);	 

	GPIO_InitStructure.GPIO_Pin = FMC_A0_PIN; 
	GPIO_Init(FMC_A0_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_A1_PIN; 
	GPIO_Init(FMC_A1_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_A2_PIN; 
	GPIO_Init(FMC_A2_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_A3_PIN; 
	GPIO_Init(FMC_A3_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_A4_PIN; 
	GPIO_Init(FMC_A4_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_A5_PIN; 
	GPIO_Init(FMC_A5_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_A6_PIN; 
	GPIO_Init(FMC_A6_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_A7_PIN; 
	GPIO_Init(FMC_A7_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_A8_PIN; 
	GPIO_Init(FMC_A8_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_A9_PIN; 
	GPIO_Init(FMC_A9_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_A10_PIN; 
	GPIO_Init(FMC_A10_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_A11_PIN; 
	GPIO_Init(FMC_A11_PORT, &GPIO_InitStructure);

   //数据线
	GPIO_PinAFConfig(FMC_D0_PORT,  FMC_D0_PINSOURCE ,  FMC_D0_AF);  
	GPIO_PinAFConfig(FMC_D1_PORT,  FMC_D1_PINSOURCE ,  FMC_D1_AF);
	GPIO_PinAFConfig(FMC_D2_PORT,  FMC_D2_PINSOURCE ,  FMC_D2_AF);
	GPIO_PinAFConfig(FMC_D3_PORT,  FMC_D3_PINSOURCE ,  FMC_D3_AF);	 
	GPIO_PinAFConfig(FMC_D4_PORT,  FMC_D4_PINSOURCE ,  FMC_D4_AF);	 
	GPIO_PinAFConfig(FMC_D5_PORT,  FMC_D5_PINSOURCE ,  FMC_D5_AF);	 
	GPIO_PinAFConfig(FMC_D6_PORT,  FMC_D6_PINSOURCE ,  FMC_D6_AF);
	GPIO_PinAFConfig(FMC_D7_PORT,  FMC_D7_PINSOURCE ,  FMC_D7_AF);  
	GPIO_PinAFConfig(FMC_D8_PORT,  FMC_D8_PINSOURCE ,  FMC_D8_AF);  
	GPIO_PinAFConfig(FMC_D9_PORT,  FMC_D9_PINSOURCE ,  FMC_D9_AF);  
	GPIO_PinAFConfig(FMC_D10_PORT, FMC_D10_PINSOURCE , FMC_D10_AF);
	GPIO_PinAFConfig(FMC_D11_PORT, FMC_D11_PINSOURCE , FMC_D11_AF);
	GPIO_PinAFConfig(FMC_D12_PORT, FMC_D12_PINSOURCE , FMC_D12_AF);
	GPIO_PinAFConfig(FMC_D13_PORT, FMC_D13_PINSOURCE , FMC_D13_AF);
	GPIO_PinAFConfig(FMC_D14_PORT, FMC_D14_PINSOURCE , FMC_D14_AF);
	GPIO_PinAFConfig(FMC_D15_PORT, FMC_D15_PINSOURCE , FMC_D15_AF);
	GPIO_PinAFConfig(FMC_D16_PORT, FMC_D16_PINSOURCE , FMC_D16_AF);
	GPIO_PinAFConfig(FMC_D17_PORT, FMC_D17_PINSOURCE , FMC_D17_AF);  
	GPIO_PinAFConfig(FMC_D18_PORT, FMC_D18_PINSOURCE , FMC_D18_AF);  
	GPIO_PinAFConfig(FMC_D19_PORT, FMC_D19_PINSOURCE , FMC_D19_AF); 
	GPIO_PinAFConfig(FMC_D20_PORT, FMC_D20_PINSOURCE , FMC_D20_AF);  
	GPIO_PinAFConfig(FMC_D21_PORT, FMC_D21_PINSOURCE , FMC_D21_AF);  
	GPIO_PinAFConfig(FMC_D22_PORT, FMC_D22_PINSOURCE , FMC_D22_AF); 
	GPIO_PinAFConfig(FMC_D23_PORT, FMC_D23_PINSOURCE , FMC_D23_AF);
	GPIO_PinAFConfig(FMC_D24_PORT, FMC_D24_PINSOURCE , FMC_D24_AF);
	GPIO_PinAFConfig(FMC_D25_PORT, FMC_D25_PINSOURCE , FMC_D25_AF);
	GPIO_PinAFConfig(FMC_D26_PORT, FMC_D26_PINSOURCE , FMC_D26_AF); 
	GPIO_PinAFConfig(FMC_D27_PORT, FMC_D27_PINSOURCE , FMC_D27_AF);	
	GPIO_PinAFConfig(FMC_D28_PORT, FMC_D28_PINSOURCE , FMC_D28_AF);  
   GPIO_PinAFConfig(FMC_D29_PORT, FMC_D29_PINSOURCE , FMC_D29_AF);	
	GPIO_PinAFConfig(FMC_D30_PORT, FMC_D30_PINSOURCE , FMC_D30_AF);  
	GPIO_PinAFConfig(FMC_D31_PORT, FMC_D31_PINSOURCE , FMC_D31_AF);      
  
	GPIO_InitStructure.GPIO_Pin = FMC_D0_PIN; 
	GPIO_Init(FMC_D0_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_D1_PIN; 
	GPIO_Init(FMC_D1_PORT, &GPIO_InitStructure);
	 
	GPIO_InitStructure.GPIO_Pin = FMC_D2_PIN; 
	GPIO_Init(FMC_D2_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_D3_PIN; 
	GPIO_Init(FMC_D3_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_D4_PIN; 
	GPIO_Init(FMC_D4_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_D5_PIN; 
	GPIO_Init(FMC_D5_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_D6_PIN; 
	GPIO_Init(FMC_D6_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_D7_PIN; 
	GPIO_Init(FMC_D7_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_D8_PIN; 
	GPIO_Init(FMC_D8_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_D9_PIN; 
	GPIO_Init(FMC_D9_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_D10_PIN; 
	GPIO_Init(FMC_D10_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_D11_PIN; 
	GPIO_Init(FMC_D11_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_D12_PIN; 
	GPIO_Init(FMC_D12_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_D13_PIN; 
	GPIO_Init(FMC_D13_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_D14_PIN; 
	GPIO_Init(FMC_D14_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_D15_PIN; 
	GPIO_Init(FMC_D15_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_D16_PIN; 
	GPIO_Init(FMC_D16_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_D17_PIN; 
	GPIO_Init(FMC_D17_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_D18_PIN; 
	GPIO_Init(FMC_D18_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_D19_PIN; 
	GPIO_Init(FMC_D19_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_D20_PIN; 
	GPIO_Init(FMC_D20_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_D21_PIN; 
	GPIO_Init(FMC_D21_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_D22_PIN; 
	GPIO_Init(FMC_D22_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_D23_PIN; 
	GPIO_Init(FMC_D23_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_D24_PIN; 
	GPIO_Init(FMC_D24_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_D25_PIN; 
	GPIO_Init(FMC_D25_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_D26_PIN; 
	GPIO_Init(FMC_D26_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_D27_PIN; 
	GPIO_Init(FMC_D27_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_D28_PIN; 
	GPIO_Init(FMC_D28_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_D29_PIN; 
	GPIO_Init(FMC_D29_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_D30_PIN; 
	GPIO_Init(FMC_D30_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_D31_PIN; 
	GPIO_Init(FMC_D31_PORT, &GPIO_InitStructure);
  
   //控制线
	GPIO_PinAFConfig(FMC_CS_PORT, FMC_CS_PINSOURCE , FMC_CS_AF);  
	GPIO_PinAFConfig(FMC_BA0_PORT, FMC_BA0_PINSOURCE , FMC_BA0_AF); 
	GPIO_PinAFConfig(FMC_BA1_PORT, FMC_BA1_PINSOURCE , FMC_BA1_AF);	
	GPIO_PinAFConfig(FMC_WE_PORT, FMC_WE_PINSOURCE , FMC_WE_AF);	
	GPIO_PinAFConfig(FMC_RAS_PORT, FMC_RAS_PINSOURCE , FMC_RAS_AF); 
	GPIO_PinAFConfig(FMC_CAS_PORT, FMC_CAS_PINSOURCE , FMC_CAS_AF);  
	GPIO_PinAFConfig(FMC_CLK_PORT, FMC_CLK_PINSOURCE , FMC_CLK_AF);  
	GPIO_PinAFConfig(FMC_CKE_PORT, FMC_CKE_PINSOURCE , FMC_CKE_AF);
	GPIO_PinAFConfig(FMC_UDQM_PORT, FMC_UDQM_PINSOURCE , FMC_UDQM_AF);  
	GPIO_PinAFConfig(FMC_LDQM_PORT, FMC_LDQM_PINSOURCE , FMC_LDQM_AF);  
	GPIO_PinAFConfig(FMC_NBL2_PORT, FMC_NBL2_PINSOURCE , FMC_NBL2_AF);  
	GPIO_PinAFConfig(FMC_NBL3_PORT, FMC_NBL3_PINSOURCE , FMC_NBL3_AF);     
  
  
	GPIO_InitStructure.GPIO_Pin = FMC_CS_PIN; 
	GPIO_Init(FMC_CS_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_BA0_PIN; 
	GPIO_Init(FMC_BA0_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_BA1_PIN;
	GPIO_Init(FMC_BA1_PORT, &GPIO_InitStructure);
	 
	GPIO_InitStructure.GPIO_Pin = FMC_WE_PIN; 
	GPIO_Init(FMC_WE_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_RAS_PIN; 
	GPIO_Init(FMC_RAS_PORT, &GPIO_InitStructure);
	 
	GPIO_InitStructure.GPIO_Pin = FMC_CAS_PIN; 
	GPIO_Init(FMC_CAS_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_CLK_PIN; 
	GPIO_Init(FMC_CLK_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_CKE_PIN; 
	GPIO_Init(FMC_CKE_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_UDQM_PIN; 
	GPIO_Init(FMC_UDQM_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_LDQM_PIN; 
	GPIO_Init(FMC_LDQM_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_NBL2_PIN; 
	GPIO_Init(FMC_NBL2_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FMC_NBL3_PIN; 
	GPIO_Init(FMC_NBL3_PORT, &GPIO_InitStructure);

}

/******************************************************************************************************
*	函 数 名: SDRAM_InitSequence
*	入口参数: 无
*	返 回 值: 无
*	函数功能: SDRAM 参数配置
*	说    明: 配置SDRAM相关时序和控制方式
*******************************************************************************************************/

void SDRAM_InitSequence(void)
{
	FMC_SDRAMCommandTypeDef FMC_SDRAMCommandStructure;
	u32 Reg = 0;	// 定义寄存器变量

	FMC_SDRAMCommandStructure.FMC_CommandMode            = FMC_Command_Mode_CLK_Enabled;	// 开启SDRAM时钟 
	FMC_SDRAMCommandStructure.FMC_CommandTarget          = FMC_COMMAND_TARGET_BANK;			// 选择要控制的区域
	FMC_SDRAMCommandStructure.FMC_AutoRefreshNumber      = 1;
	FMC_SDRAMCommandStructure.FMC_ModeRegisterDefinition = 0;
	while(FMC_GetFlagStatus(FMC_BANK_SDRAM, FMC_FLAG_Busy) != RESET);  //等待SDRAM空闲 
	FMC_SDRAMCmdConfig(&FMC_SDRAMCommandStructure);  						 // 配置SDRAM
	SDRAM_delay(1); //延时5ms 
	 

	FMC_SDRAMCommandStructure.FMC_CommandMode 			  = FMC_Command_Mode_PALL;			// 预充电命令
	FMC_SDRAMCommandStructure.FMC_CommandTarget 			  = FMC_COMMAND_TARGET_BANK;		// 选择要控制的区域
	FMC_SDRAMCommandStructure.FMC_AutoRefreshNumber		  = 1;
	FMC_SDRAMCommandStructure.FMC_ModeRegisterDefinition = 0;
	while(FMC_GetFlagStatus(FMC_BANK_SDRAM, FMC_FLAG_Busy) != RESET)	//等待SDRAM空闲 
	FMC_SDRAMCmdConfig(&FMC_SDRAMCommandStructure);							// 配置SDRAM
	SDRAM_delay(1); //延时5ms 
	
	//自动刷新配置 
	FMC_SDRAMCommandStructure.FMC_CommandMode				  = FMC_Command_Mode_AutoRefresh; // 使用自动刷新
	FMC_SDRAMCommandStructure.FMC_CommandTarget			  = FMC_COMMAND_TARGET_BANK; 		 // 选择要控制的区域
	FMC_SDRAMCommandStructure.FMC_AutoRefreshNumber 	  = 8;									 // 自动刷新次数
	FMC_SDRAMCommandStructure.FMC_ModeRegisterDefinition = 0;    
	while(FMC_GetFlagStatus(FMC_BANK_SDRAM, FMC_FLAG_Busy) != RESET);	//等待SDRAM空闲 
	FMC_SDRAMCmdConfig(&FMC_SDRAMCommandStructure);							// 配置SDRAM

	//寄存器配置 
	Reg  =   (u32)SDRAM_MODEREG_BURST_LENGTH_2     |		
				SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL   |
				SDRAM_MODEREG_CAS_LATENCY_3           |		
				SDRAM_MODEREG_OPERATING_MODE_STANDARD |
				SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;

	FMC_SDRAMCommandStructure.FMC_CommandMode				  = FMC_Command_Mode_LoadMode;	// 加载模式寄存器命令
	FMC_SDRAMCommandStructure.FMC_CommandTarget          = FMC_COMMAND_TARGET_BANK;		// 选择要控制的区域
	FMC_SDRAMCommandStructure.FMC_AutoRefreshNumber		  = 1;
	FMC_SDRAMCommandStructure.FMC_ModeRegisterDefinition = Reg;									// 寄存器值
	while(FMC_GetFlagStatus(FMC_BANK_SDRAM, FMC_FLAG_Busy) != RESET);	//等待SDRAM空闲 
	FMC_SDRAMCmdConfig(&FMC_SDRAMCommandStructure);							// 配置SDRAM

	FMC_SetRefreshCount(1386);	// 设置刷新计数器 
	while(FMC_GetFlagStatus(FMC_BANK_SDRAM, FMC_FLAG_Busy) != RESET);	//等待SDRAM空闲 
}

/******************************************************************************************************
*	函 数 名: SDRAM_Init
*	入口参数: 无
*	返 回 值: 无
*	函数功能: SDRAM初始化
*	说    明: 初始化FMC和SDRAM配置
*******************************************************************************************************/

void SDRAM_Init(void)
{
	u32 i = 0;	// 计数变量
	
	FMC_SDRAMInitTypeDef  FMC_SDRAMInitStructure;
	FMC_SDRAMTimingInitTypeDef  FMC_SDRAMTimingInitStructure; 

	RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FMC, ENABLE);	// 开启FMC时钟
	SDRAM_GPIO_Config();												// 初始化IO口

	FMC_SDRAMTimingInitStructure.FMC_LoadToActiveDelay    = 2;  // TMRD: min=12ns (2x11.11ns)  
	FMC_SDRAMTimingInitStructure.FMC_ExitSelfRefreshDelay = 7;  // TXSR: min=72ns (7x11.11ns)  
	FMC_SDRAMTimingInitStructure.FMC_SelfRefreshTime      = 4;  // TRAS: min=42ns (4x11.11ns)    
	FMC_SDRAMTimingInitStructure.FMC_RowCycleDelay        = 6;  // TRC:  min=60ns (6x11.11ns)   
	FMC_SDRAMTimingInitStructure.FMC_WriteRecoveryTime    = 2;  // TWR:  2 Tck 
	FMC_SDRAMTimingInitStructure.FMC_RPDelay              = 2;  // TRP:  18ns => 2x11.11ns             
	FMC_SDRAMTimingInitStructure.FMC_RCDDelay             = 2;  // TRCD: 12ns => 2x11.11ns 

	FMC_SDRAMInitStructure.FMC_Bank 						= FMC_BANK_SDRAM; 					// 选择BANK区
	FMC_SDRAMInitStructure.FMC_ColumnBitsNumber 		= FMC_ColumnBits_Number_8b; 		// 行地址宽度
	FMC_SDRAMInitStructure.FMC_RowBitsNumber 			= FMC_RowBits_Number_12b;			// 列地址线宽度
	FMC_SDRAMInitStructure.FMC_SDMemoryDataWidth 	= FMC_SDMemory_Width_32b; 			// 数据宽度  
	FMC_SDRAMInitStructure.FMC_InternalBankNumber 	= FMC_InternalBank_Number_4;		// bank数量
	FMC_SDRAMInitStructure.FMC_CASLatency 				= FMC_CAS_Latency_3; 				//	CAS 
	FMC_SDRAMInitStructure.FMC_WriteProtection 		= FMC_Write_Protection_Disable; 	// 禁止写保护
	FMC_SDRAMInitStructure.FMC_SDClockPeriod 			= FMC_SDClock_Period_2; 			// 分频
	FMC_SDRAMInitStructure.FMC_ReadBurst 				= FMC_Read_Burst_Enable;			// 突发模式  
	FMC_SDRAMInitStructure.FMC_ReadPipeDelay 			= FMC_ReadPipe_Delay_1; 			// 读延迟
	FMC_SDRAMInitStructure.FMC_SDRAMTimingStruct 	= &FMC_SDRAMTimingInitStructure;

	FMC_SDRAMInit(&FMC_SDRAMInitStructure); 	// 初始化FMC接口
	SDRAM_InitSequence();							//配置SDRAM
	
	// 初始化之后，将整个内存区写一遍数据，因为华邦的SDRAM刚初始化完毕时，第一次写数据存在不稳定的情况，所以先写一次数据
	for (i = 0; i < SDRAM_Size/4; i++)
	{
		*(__IO u32*) (SDRAM_BANK_ADDR + 4*i) = 0x00000000;	
	}		
}

/******************************************************************************************************
*	函 数 名: SDRAM_Test
*	入口参数: 无
*	返 回 值: SUCCESS - 成功，ERROR - 失败
*	函数功能: SDRAM测试
*	说    明: 先以32位的数据宽度写入数据，再读取出来一一进行比较，随后以8位的数据宽度写入，
*				 用以验证NBL0和NBL1两个引脚的连接是否正常。        
*******************************************************************************************************/

u8 SDRAM_Test(void)
{
	u32 i = 0;		// 计数变量
	u32 ReadData = 0; 	// 读取到的数据
	u8  ReadData_8b;
	
	printf("STM32F429 SDRAM测试\r\n");
	printf("测试开始，以32位数据宽度写入数据...\r\n");	
	for (i = 0; i < SDRAM_Size/4; i++)
	{
 		*(__IO u32*) (SDRAM_BANK_ADDR + 4*i) = i;		// 写入数据
	}
	
	printf("写入完毕，读取数据并比较...\r\n");
	for(i = 0; i < SDRAM_Size/4;i++ )
	{
		ReadData = *(__IO u32*)(SDRAM_BANK_ADDR + 4 * i );  // 从SDRAM读出数据	
		if( ReadData != i )      //检测数据，若不相等，跳出函数,返回检测失败结果。
		{
			printf("SDRAM测试失败！！\r\n");
			return ERROR;	 // 返回失败标志
		}
	}
	
	printf("32位数据宽度读写通过，以8位数据宽度写入数据\r\n");
	for (i = 0; i < 255; i++)
	{
 		*(__IO u8*) (SDRAM_BANK_ADDR + i) = i;
	}	
	printf("写入完毕，读取数据并比较...\r\n");
	for (i = 0; i < 255; i++)
	{
		ReadData_8b = *(__IO u8*) (SDRAM_BANK_ADDR + i);
		if( ReadData_8b != (u8)i )      //检测数据，若不相等，跳出函数,返回检测失败结果。
		{
			printf("8位数据宽度读写测试失败！！\r\n");
			printf("请检查NBL0和NBL1的连接\r\n");	
			return ERROR;	 // 返回失败标志
		}
	}		
	printf("8位数据宽度读写通过\r\n");
	printf("SDRAM读写测试通过，系统正常\r\n");
	return SUCCESS;	 // 返回成功标志
}
