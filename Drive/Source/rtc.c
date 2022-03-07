/*   
      扬州大学 测控15 杨寿晨          
		
		 RTC实时时钟 程序        

	     2019/4 - 2019/6              */

#include "rtc.h"

// 时间定义
unsigned int HOURS;                      // 0~23
unsigned int MINUTES;                    // 0~59
unsigned int SECONDS;                    // 0~59

// 日期定义
unsigned int DATE;                       // 1~31
unsigned int MONTH;                      // 1~12
unsigned int YEAR;                       // 0~99

//  设置时间和日期
void RTC_TimeAndDate_Set(void)
{
	RTC_TimeTypeDef RTC_TimeStructure;
	RTC_DateTypeDef RTC_DateStructure;
	
	// 初始化时间
	RTC_TimeStructure.RTC_Hours = HOURS;        
	RTC_TimeStructure.RTC_Minutes = MINUTES;      
	RTC_TimeStructure.RTC_Seconds = SECONDS;      
	RTC_SetTime(RTC_Format_BINorBCD, &RTC_TimeStructure);
	RTC_WriteBackupRegister(RTC_BKP_DRX, RTC_BKP_DATA);
	
	// 初始化日期	   
	RTC_DateStructure.RTC_Date = DATE;         
	RTC_DateStructure.RTC_Month = MONTH;         
	RTC_DateStructure.RTC_Year = YEAR;        
	RTC_SetDate(RTC_Format_BINorBCD, &RTC_DateStructure);
	RTC_WriteBackupRegister(RTC_BKP_DRX, RTC_BKP_DATA);
}


// 配置：选择RTC时钟源，设置RTC_CLK的分频系数

void RTC_CLK_Config(void)
{  
	RTC_InitTypeDef RTC_InitStructure;
	
	/*使能 PWR 时钟*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	/* PWR_CR:DBF置1，使能RTC、RTC备份寄存器和备份SRAM的访问 */
	PWR_BackupAccessCmd(ENABLE);
	/* 使能LSE */ 
	RCC_LSEConfig(RCC_LSE_ON);
	/* 等待LSE稳定 */   
	while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
	{
	}
	/* 选择LSE做为RTC的时钟源 */
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);    
	/* 使能RTC时钟 */
	RCC_RTCCLKCmd(ENABLE);
	/* 等待 RTC APB 寄存器同步 */
	RTC_WaitForSynchro();
	/* 初始化同步/异步预分频器的值   驱动日历的时钟ck_spare = LSE/[(255+1)*(127+1)] = 1HZ */
	/* 设置异步预分频器的值 */
	RTC_InitStructure.RTC_AsynchPrediv = ASYNCHPREDIV;
	/* 设置同步预分频器的值 */
	RTC_InitStructure.RTC_SynchPrediv = SYNCHPREDIV;	
	RTC_InitStructure.RTC_HourFormat = RTC_HourFormat_24; 
	/* 用RTC_InitStructure的内容初始化RTC寄存器 */
	RTC_Init(&RTC_InitStructure);
}

