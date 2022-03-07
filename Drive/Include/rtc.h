#ifndef __RTC_H__
#define __RTC_H__

#include "stm32f4xx.h"    

// �첽��Ƶ����
#define ASYNCHPREDIV         0X7F
// ͬ����Ƶ����
#define SYNCHPREDIV          0XFF
// ʱ���ʽ�궨��
#define RTC_Format_BINorBCD  RTC_Format_BIN
// ������Ĵ����궨��
#define RTC_BKP_DRX          RTC_BKP_DR0
// д�뵽���ݼĴ��������ݺ궨��
#define RTC_BKP_DATA         0X32F2
                                  
void RTC_CLK_Config(void);
void RTC_TimeAndDate_Set(void);

#endif // __RTC_H__
