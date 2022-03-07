#ifndef __RTC_H__
#define __RTC_H__

#include "stm32f4xx.h"    

// 异步分频因子
#define ASYNCHPREDIV         0X7F
// 同步分频因子
#define SYNCHPREDIV          0XFF
// 时间格式宏定义
#define RTC_Format_BINorBCD  RTC_Format_BIN
// 备份域寄存器宏定义
#define RTC_BKP_DRX          RTC_BKP_DR0
// 写入到备份寄存器的数据宏定义
#define RTC_BKP_DATA         0X32F2
                                  
void RTC_CLK_Config(void);
void RTC_TimeAndDate_Set(void);

#endif // __RTC_H__
