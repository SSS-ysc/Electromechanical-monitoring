/*   
      ���ݴ�ѧ ���15 ���ٳ�          
		
		 RTCʵʱʱ�� ����        

	     2019/4 - 2019/6              */

#include "rtc.h"

// ʱ�䶨��
unsigned int HOURS;                      // 0~23
unsigned int MINUTES;                    // 0~59
unsigned int SECONDS;                    // 0~59

// ���ڶ���
unsigned int DATE;                       // 1~31
unsigned int MONTH;                      // 1~12
unsigned int YEAR;                       // 0~99

//  ����ʱ�������
void RTC_TimeAndDate_Set(void)
{
	RTC_TimeTypeDef RTC_TimeStructure;
	RTC_DateTypeDef RTC_DateStructure;
	
	// ��ʼ��ʱ��
	RTC_TimeStructure.RTC_Hours = HOURS;        
	RTC_TimeStructure.RTC_Minutes = MINUTES;      
	RTC_TimeStructure.RTC_Seconds = SECONDS;      
	RTC_SetTime(RTC_Format_BINorBCD, &RTC_TimeStructure);
	RTC_WriteBackupRegister(RTC_BKP_DRX, RTC_BKP_DATA);
	
	// ��ʼ������	   
	RTC_DateStructure.RTC_Date = DATE;         
	RTC_DateStructure.RTC_Month = MONTH;         
	RTC_DateStructure.RTC_Year = YEAR;        
	RTC_SetDate(RTC_Format_BINorBCD, &RTC_DateStructure);
	RTC_WriteBackupRegister(RTC_BKP_DRX, RTC_BKP_DATA);
}


// ���ã�ѡ��RTCʱ��Դ������RTC_CLK�ķ�Ƶϵ��

void RTC_CLK_Config(void)
{  
	RTC_InitTypeDef RTC_InitStructure;
	
	/*ʹ�� PWR ʱ��*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	/* PWR_CR:DBF��1��ʹ��RTC��RTC���ݼĴ����ͱ���SRAM�ķ��� */
	PWR_BackupAccessCmd(ENABLE);
	/* ʹ��LSE */ 
	RCC_LSEConfig(RCC_LSE_ON);
	/* �ȴ�LSE�ȶ� */   
	while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
	{
	}
	/* ѡ��LSE��ΪRTC��ʱ��Դ */
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);    
	/* ʹ��RTCʱ�� */
	RCC_RTCCLKCmd(ENABLE);
	/* �ȴ� RTC APB �Ĵ���ͬ�� */
	RTC_WaitForSynchro();
	/* ��ʼ��ͬ��/�첽Ԥ��Ƶ����ֵ   ����������ʱ��ck_spare = LSE/[(255+1)*(127+1)] = 1HZ */
	/* �����첽Ԥ��Ƶ����ֵ */
	RTC_InitStructure.RTC_AsynchPrediv = ASYNCHPREDIV;
	/* ����ͬ��Ԥ��Ƶ����ֵ */
	RTC_InitStructure.RTC_SynchPrediv = SYNCHPREDIV;	
	RTC_InitStructure.RTC_HourFormat = RTC_HourFormat_24; 
	/* ��RTC_InitStructure�����ݳ�ʼ��RTC�Ĵ��� */
	RTC_Init(&RTC_InitStructure);
}

