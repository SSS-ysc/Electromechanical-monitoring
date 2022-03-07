/**
  ******************************************************************************
  * @file    Project/STM32F4xx_StdPeriph_Templates/stm32f4xx_it.h 
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    06-March-2015
  * @brief   This file contains the headers of the interrupt handlers.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F4xx_IT_H
#define __STM32F4xx_IT_H

#ifdef __cplusplus
 extern "C" {
#endif 

#include  <includes.h>
#include  "main.h" 
#include "stm32f4xx.h"
#include  "GUI.h"
#include  "adc.h"
#include  "sdio_sd.h"

#include  "usart.h"
#include  "GPS.h"
#include  "WIFI.h"


void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);

#ifdef __cplusplus
}
#endif

extern uint16_t		AD_Value_CH1[1024];   		//数据缓存区
extern uint16_t		AD_Value_CH2[1024];
extern uint16_t		AD_Value_CH3[1024];
extern uint16_t		AD_Value_CH4[1024];
extern uint16_t		AD_Value_CH7[1024];
extern uint16_t		AD_Value_CH8[1024];
extern uint16_t		AD_Value_CH9[1024];
extern uint16_t		AD_Value_CH10[1024];

extern uint16_t		CH5_SPEED;					//转速
extern uint16_t		CH6_SPEED;

extern uint8_t		gps_rbuff[GPS_RBUFF_SIZE];	//GPS数据
extern uint8_t		GPS_TransferEnd ;

extern OS_TCB		DSP_TaskTCB;

extern uint8_t		WIFI_or_485;				//485\WIFI选择位


#endif /* __STM32F4xx_IT_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
