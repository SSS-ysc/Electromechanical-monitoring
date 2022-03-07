/*     
					扬州大学 测控15 杨寿晨          

							主程序

						2019/4 - 2019/6                         */

#include  "main.h" 

/*
 * 				注意：本程序编辑显示 Tab size = 4 ！！！！
 *				版本：
 *						核心板	反客科技 STM32F429BI
 *			  			UCOS	V3.04
 *						emWin	V5.40 ARGB for OS
 *
 *				参考来源：反客科技、野火、正点原子、安富莱	  
 */


/******************************************** 函数声明 ***********************************************/

static  void  Start_Task							(void *p_arg);		// 起始任务

static  void  SystemDatasBroadcast_Task				(void *p_arg);		// 统计任务
static  void  iwdg_Task			                	(void *p_arg);		// 看门狗 喂狗任务
static  void  emWin_Task			                (void *p_arg);		// emWin图形界面任务
static  void  Touch_Task			                (void *p_arg);		// 触摸扫描任务
static  void  LED_Task								(void *p_arg);		// LED驱动任务
static  void  ADC2_Task								(void *p_arg);		// ADC2采样触发任务
static  void  ADC3_Task								(void *p_arg);		// ADC3采样触发任务
static  void  DHT11_Task							(void *p_arg);		// DHT11通讯任务
static  void  Key_Task								(void *p_arg);		// Key按键扫描任务
static  void  DSP_Task								(void *p_arg);		// DSP数据处理任务
static  void  SD_Task								(void *p_arg);		// SD卡数据存储任务
static  void  WIFI_Task								(void *p_arg);		// WIFI通讯任务
static  void  _4G_Task								(void *p_arg);		// 4G通讯任务
static  void  _485_Task								(void *p_arg);		// 485通讯任务
static  void  GPS_Task								(void *p_arg);		// GPS数据处理任务

extern  void  MainTask								(void);           // emwin主函数定义
extern  void  DSP_FFT1024							(void);           // DSP FFT函数定义
extern  void  DSP_FIR1024							(void);           // DSP FIR函数定义

/******************************************* 任务控制块 **********************************************/

static		OS_TCB    Start_TaskTCB;

OS_TCB		SystemDatasBroadcast_TaskTCB;
OS_TCB		iwdg_TaskTCB;
OS_TCB		emWin_TaskTCB;
OS_TCB		Touch_TaskTCB;
OS_TCB		LED_TaskTCB;
OS_TCB		ADC2_TaskTCB;
OS_TCB		ADC3_TaskTCB;
OS_TCB		DHT11_TaskTCB;
OS_TCB		Key_TaskTCB;
OS_TCB		DSP_TaskTCB;
OS_TCB		SD_TaskTCB;
OS_TCB		WIFI_TaskTCB;
OS_TCB		_4G_TaskTCB;
OS_TCB		_485_TaskTCB;
OS_TCB		GPS_TaskTCB;

/******************************************* 任务堆栈 *************************************************/

static	CPU_STK   Start_TaskStk[Start_Task_STK_SIZE];

static  CPU_STK   SystemDatasBroadcast_TaskStk   [SystemDatasBroadcast_Task_STK_SIZE];
static  CPU_STK   iwdg_TaskStk                   [iwdg_Task_STK_SIZE];
static  CPU_STK   emWin_TaskStk                  [emWin_Task_STK_SIZE];
static  CPU_STK   Touch_TaskStk                  [Touch_Task_STK_SIZE];
static  CPU_STK   LED_TaskStk                    [LED_Task_STK_SIZE];
static  CPU_STK   ADC2_TaskStk                   [ADC2_Task_STK_SIZE];
static  CPU_STK   ADC3_TaskStk                   [ADC3_Task_STK_SIZE];
static  CPU_STK   DHT11_TaskStk                  [DHT11_Task_STK_SIZE];
static  CPU_STK   Key_TaskStk                    [Key_Task_STK_SIZE];
static  CPU_STK   DSP_TaskStk                    [DSP_Task_STK_SIZE];
static  CPU_STK   SD_TaskStk                     [SD_Task_STK_SIZE];
static  CPU_STK   WIFI_TaskStk                   [WIFI_Task_STK_SIZE];
static  CPU_STK   _4G_TaskStk                    [_4G_Task_STK_SIZE];
static  CPU_STK   _485_TaskStk                   [_485_Task_STK_SIZE];
static  CPU_STK   GPS_TaskStk                    [GPS_Task_STK_SIZE];

/******************************************** 全局变量 ************************************************/

uint16_t	AD_Value_CH1[1024] ={0};	//原始数据缓存区
uint16_t	AD_Value_CH2[1024] ={0};
uint16_t	AD_Value_CH3[1024] ={0};
uint16_t	AD_Value_CH4[1024] ={0};
uint16_t	AD_Value_CH7[1024] ={0};
uint16_t	AD_Value_CH8[1024] ={0};
uint16_t	AD_Value_CH9[1024] ={0};
uint16_t	AD_Value_CH10[1024]={0};

int16_t		AD_Value_FFT_CH1[1024] ={0};  //FFT处理结果缓存区
int16_t		AD_Value_FFT_CH2[1024] ={0};
int16_t		AD_Value_FFT_CH3[1024] ={0};
int16_t		AD_Value_FFT_CH4[1024] ={0};
int16_t		AD_Value_FFT_CH7[1024] ={0};
int16_t		AD_Value_FFT_CH8[1024] ={0};
int16_t		AD_Value_FFT_CH9[1024] ={0};
int16_t		AD_Value_FFT_CH10[1024]={0};
int16_t		AD_Value_FIR_CH1[1024] ={0};  //FIR处理结果缓存区
int16_t		AD_Value_FIR_CH2[1024] ={0};
int16_t		AD_Value_FIR_CH3[1024] ={0};
int16_t		AD_Value_FIR_CH4[1024] ={0};
int16_t		AD_Value_FIR_CH7[1024] ={0};
int16_t		AD_Value_FIR_CH8[1024] ={0};
int16_t		AD_Value_FIR_CH9[1024] ={0};
int16_t		AD_Value_FIR_CH10[1024]={0};
int16_t		AD_Value_CH1_VPP =0;			//各通道峰峰值
int16_t		AD_Value_CH2_VPP =0;
int16_t		AD_Value_CH3_VPP =0;
int16_t		AD_Value_CH4_VPP =0;
int16_t		AD_Value_CH7_VPP =0;
int16_t		AD_Value_CH8_VPP =0;
int16_t		AD_Value_CH9_VPP =0;
int16_t		AD_Value_CH10_VPP=0;

int16_t		AD_Value_average[1024]={0};
float32_t	AD_Value_FIR[1024]={0};

uint8_t		FIR_select =1;				//滤波系数选择

uint16_t	CH5_SPEED =0;				//转速
uint16_t	CH6_SPEED =0;

uint8_t		data_ready_display = 0;		//各标志位
uint8_t		WIFI_or_485	=0;
uint8_t		GPS_select =0;
uint8_t		SD_select =1;
uint8_t		SD_select_CH12  =1;
uint8_t		SD_select_CH34  =0;
uint8_t		SD_select_CH78  =0;
uint8_t		SD_select_CH910 =0;


uint32_t	data_longitude=11939879;	//经度纬度缓存
uint8_t		data_ewhemi=69;
uint32_t	data_latitude=3234322;
uint8_t		data_nshemi=78;

uint8_t		DHT11_humi=0;				//温度数据缓存
uint8_t		DHT11_temp=0;
uint16_t	temperature=0;

FATFS		SD_FatFs;			// SD卡文件系统对象
FRESULT		SD_FileRes;			// 操作结果 
FIL			SD_File;			// 文件对象
UINT		SD_FileCount;		// 数据数量
FSIZE_t		SD_FileSize; 		// 文件大小

u32 BMP_Buffer[1024*300]__attribute__((at(0xD0CCA000)));	// 存储从SD卡读取到的图片数据

/******************************************************************************************************
*	函 数 名: main
*	函数功能: 初始化 UCOS，并创建起始任务
*******************************************************************************************************/

int  main (void)
{
	OS_ERR  err;

	OSInit(&err);    	// UCOS初始化化                                     

	OSTaskCreate((OS_TCB     *)&Start_TaskTCB,              // 创建开始任务 
				  (CPU_CHAR   *)" Task Start",
				  (OS_TASK_PTR ) Start_Task,
				  (void       *) 0,
				  (OS_PRIO     ) Start_Task_PRIO,
				  (CPU_STK    *)&Start_TaskStk[0],
				  (CPU_STK_SIZE) Start_Task_STK_SIZE / 10,
				  (CPU_STK_SIZE) Start_Task_STK_SIZE,
				  (OS_MSG_QTY  ) 5u,
				  (OS_TICK     ) 0u,
				  (void       *) 0,
				  (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
				  (OS_ERR     *)&err);

	OSStart(&err);     /* Start multitasking (i.e. give control to uC/OS-III). */
}

/******************************************************************************************************
*	函 数 名: Start_Task
*	函数功能: 起始任务
*	说    明: 初始化CPU核心、SysTick定时器，初始化底层驱动，创建其他任务
*******************************************************************************************************/

static  void	Start_Task (void *p_arg)
{
	CPU_INT32U  cpu_clk_freq;
	CPU_INT32U  cnts;
	OS_ERR      err;
  
	CPU_SR_ALLOC();
	(void)p_arg;

	CPU_Init();	
	cpu_clk_freq = BSP_CPU_ClkFreq();                           /* Determine SysTick reference freq.                    */
	cnts = cpu_clk_freq / (CPU_INT32U)OSCfg_TickRate_Hz;        /* Determine nbr SysTick increments                     */
	OS_CPU_SysTickInit(cnts);                                   /* Init uC/OS periodic time src (SysTick).              */
	Mem_Init();                                                 /* Initialize Memory Management Module                  */

	SDRAM_Init();							//  sdram       初始化
	Touch_Init();							//  触摸屏      初始化
	sFLASH_Init();							//  SPI Flash   初始化
	
	IWDG_Config(IWDG_Prescaler_128 ,625); 	//	独立看门狗	初始化	IWDG 2s 超时溢出 
	LED_CONTROL_Init();						//  LED及控制   初始化
	ADC123_Init();							//  ADC         初始化
	RTC_CLK_Config();						//  RTC实时时钟 初始化
	DHT11_GPIO_Config();					//  DHT11       初始化	
	Key_Config();							//  按键        初始化
	TIM_Config();							//  定时器      初始化
	f_mount(&SD_FatFs,"0:",1);	        	//  挂载SD卡	FatFs文件系统
	
//  Usart1_Config();						//	USART1      初始化	核心板调试串口
	Usart2_Config();						//  USART2      初始化  232  “Printf”
	Uart7_Config ();						//  UART7       初始化  485 / wifi
	GPS_Config();							//  GPS         初始化  USART1
	WiFi_Config();							//  WIFI        初始化  UART7
	_485_Config();							//  485         初始化  UART7
	_4G_linking_Config();					//  4G模块      初始化  USART6
	

#if OS_CFG_STAT_TASK_EN > 0u
    OSStatTaskCPUUsageInit(&err);                               /* Compute CPU capacity with no task running            */
#endif

#ifdef CPU_CFG_INT_DIS_MEAS_EN
    CPU_IntDisMeasMaxCurReset();
#endif

	OS_CRITICAL_ENTER();	  //进入临界区
    

    // 创建UCOS统计任务
	OSTaskCreate((OS_TCB     *)&SystemDatasBroadcast_TaskTCB,
				 (CPU_CHAR   *)"SystemDatasBroadcast Task",
				 (OS_TASK_PTR ) SystemDatasBroadcast_Task,
				 (void       *) 0,
				 (OS_PRIO     ) SystemDatasBroadcast_Task_PRIO,
				 (CPU_STK    *)&SystemDatasBroadcast_TaskStk[0],
				 (CPU_STK_SIZE) SystemDatasBroadcast_Task_STK_SIZE/10,
				 (CPU_STK_SIZE) SystemDatasBroadcast_Task_STK_SIZE,
				 (OS_MSG_QTY  ) 0,
				 (OS_TICK     ) 0,
				 (void       *) 0,
				 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR), 
				 (OS_ERR     *) &err);	
				 
    // 创建看门狗 喂狗任务
	OSTaskCreate((OS_TCB     *)&iwdg_TaskTCB,
				 (CPU_CHAR   *)"iwdg Task",
				 (OS_TASK_PTR ) iwdg_Task,
				 (void       *) 0,
				 (OS_PRIO     ) iwdg_Task_PRIO,
				 (CPU_STK    *)&iwdg_TaskStk[0],
				 (CPU_STK_SIZE) iwdg_Task_STK_SIZE/10,
				 (CPU_STK_SIZE) iwdg_Task_STK_SIZE,
				 (OS_MSG_QTY  ) 0,
				 (OS_TICK     ) 0,
				 (void       *) 0,
				 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR), 
				 (OS_ERR     *) &err);
				 
	// 创建emWin图形界面任务
    OSTaskCreate((OS_TCB     *)&emWin_TaskTCB,               
                 (CPU_CHAR   *)"emWin Task ",
                 (OS_TASK_PTR ) emWin_Task,
                 (void       *) 0,
                 (OS_PRIO     ) emWin_Task_PRIO,
                 (CPU_STK    *)&emWin_TaskStk[0],
                 (CPU_STK_SIZE) emWin_Task_STK_SIZE / 10,
                 (CPU_STK_SIZE) emWin_Task_STK_SIZE,
                 (OS_MSG_QTY  ) 5u,
                 (OS_TICK     ) 0u,
                 (void       *) 0,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR | OS_OPT_TASK_SAVE_FP),
                 (OS_ERR     *)&err);
	 
	// 创建触摸扫描任务
	OSTaskCreate((OS_TCB     *)&Touch_TaskTCB,               
                 (CPU_CHAR   *)"Touch Task ",
                 (OS_TASK_PTR ) Touch_Task,
                 (void       *) 0,
                 (OS_PRIO     ) Touch_Task_PRIO,
                 (CPU_STK    *)&Touch_TaskStk[0],
                 (CPU_STK_SIZE) Touch_Task_STK_SIZE / 10,
                 (CPU_STK_SIZE) Touch_Task_STK_SIZE,
                 (OS_MSG_QTY  ) 5u,
                 (OS_TICK     ) 0u,
                 (void       *) 0,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR     *)&err);
								 
	// 创建key按键扫描任务
	OSTaskCreate((OS_TCB     *)&Key_TaskTCB,               
                 (CPU_CHAR   *)"Key Task ",
                 (OS_TASK_PTR ) Key_Task,
                 (void       *) 0,
                 (OS_PRIO     ) Key_Task_PRIO,
                 (CPU_STK    *)&Key_TaskStk[0],
                 (CPU_STK_SIZE) Key_Task_STK_SIZE / 10,
                 (CPU_STK_SIZE) Key_Task_STK_SIZE,
                 (OS_MSG_QTY  ) 5u,
                 (OS_TICK     ) 0u,
                 (void       *) 0,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR     *)&err);
								 
	// 创建LED驱动任务
    OSTaskCreate((OS_TCB     *)&LED_TaskTCB,                	
                 (CPU_CHAR   *)"Led Task ",
                 (OS_TASK_PTR ) LED_Task,
                 (void       *) 0, 
                 (OS_PRIO     ) LED_Task_PRIO,
                 (CPU_STK    *)&LED_TaskStk[0],
                 (CPU_STK_SIZE) LED_Task_STK_SIZE / 10,
                 (CPU_STK_SIZE) LED_Task_STK_SIZE,
                 (OS_MSG_QTY  ) 5u,
                 (OS_TICK     ) 0u,
                 (void       *) 0,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR     *)&err);

    // 创建ADC2驱动任务
	OSTaskCreate((OS_TCB     *)&ADC2_TaskTCB,               	
                 (CPU_CHAR   *)"ADC2 Task ",
                 (OS_TASK_PTR ) ADC2_Task,
                 (void       *) 0, 
                 (OS_PRIO     ) ADC2_Task_PRIO,
                 (CPU_STK    *)&ADC2_TaskStk[0],
                 (CPU_STK_SIZE) ADC2_Task_STK_SIZE / 10,
                 (CPU_STK_SIZE) ADC2_Task_STK_SIZE,
                 (OS_MSG_QTY  ) 5u,
                 (OS_TICK     ) 0u,
                 (void       *) 0,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR | OS_OPT_TASK_SAVE_FP ),
                 (OS_ERR     *)&err);

	// 创建ADC3驱动任务
	OSTaskCreate((OS_TCB     *)&ADC3_TaskTCB,               	
                 (CPU_CHAR   *)"ADC3 Task ",
                 (OS_TASK_PTR ) ADC3_Task,
                 (void       *) 0, 
                 (OS_PRIO     ) ADC3_Task_PRIO,
                 (CPU_STK    *)&ADC3_TaskStk[0],
                 (CPU_STK_SIZE) ADC3_Task_STK_SIZE / 10,
                 (CPU_STK_SIZE) ADC3_Task_STK_SIZE,
                 (OS_MSG_QTY  ) 5u,
                 (OS_TICK     ) 0u,
                 (void       *) 0,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR | OS_OPT_TASK_SAVE_FP ),
                 (OS_ERR     *)&err);
								 
	// 创建DSP数据处理任务
	OSTaskCreate((OS_TCB     *)&DSP_TaskTCB,               	
                 (CPU_CHAR   *)"DSP Task ",
                 (OS_TASK_PTR ) DSP_Task,
                 (void       *) 0, 
                 (OS_PRIO     ) DSP_Task_PRIO,
                 (CPU_STK    *)&DSP_TaskStk[0],
                 (CPU_STK_SIZE) DSP_Task_STK_SIZE / 10,
                 (CPU_STK_SIZE) DSP_Task_STK_SIZE,
                 (OS_MSG_QTY  ) 5u,
                 (OS_TICK     ) 0u,
                 (void       *) 0,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR | OS_OPT_TASK_SAVE_FP ),
                 (OS_ERR     *)&err);
						 
	// 创建SD卡数据存储任务
	OSTaskCreate((OS_TCB     *)&SD_TaskTCB,               	
                 (CPU_CHAR   *)"SD Task ",
                 (OS_TASK_PTR ) SD_Task,
                 (void       *) 0, 
                 (OS_PRIO     ) SD_Task_PRIO,
                 (CPU_STK    *)&SD_TaskStk[0],
                 (CPU_STK_SIZE) SD_Task_STK_SIZE / 10,
                 (CPU_STK_SIZE) SD_Task_STK_SIZE,
                 (OS_MSG_QTY  ) 5u,
                 (OS_TICK     ) 0u,
                 (void       *) 0,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR ),
                 (OS_ERR     *)&err);

	// 创建GPS数据处理任务
	OSTaskCreate((OS_TCB     *)&GPS_TaskTCB,               	
                 (CPU_CHAR   *)"GPS Task ",
                 (OS_TASK_PTR ) GPS_Task,
                 (void       *) 0, 
                 (OS_PRIO     ) GPS_Task_PRIO,
                 (CPU_STK    *)&GPS_TaskStk[0],
                 (CPU_STK_SIZE) GPS_Task_STK_SIZE / 10,
                 (CPU_STK_SIZE) GPS_Task_STK_SIZE,
                 (OS_MSG_QTY  ) 5u,
                 (OS_TICK     ) 0u,
                 (void       *) 0,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR | OS_OPT_TASK_SAVE_FP),
                 (OS_ERR     *)&err); 
								 
	// 创建DHT11通讯任务
	OSTaskCreate((OS_TCB     *)&DHT11_TaskTCB,                	
                 (CPU_CHAR   *)"DHT11 Task ",
                 (OS_TASK_PTR ) DHT11_Task,
                 (void       *) 0, 
                 (OS_PRIO     ) DHT11_Task_PRIO,
                 (CPU_STK    *)&DHT11_TaskStk[0],
                 (CPU_STK_SIZE) DHT11_Task_STK_SIZE / 10,
                 (CPU_STK_SIZE) DHT11_Task_STK_SIZE,
                 (OS_MSG_QTY  ) 5u,
                 (OS_TICK     ) 0u,
                 (void       *) 0,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR | OS_OPT_TASK_SAVE_FP ),
                 (OS_ERR     *)&err);

	// 创建WIFI通讯任务
	OSTaskCreate((OS_TCB     *)&WIFI_TaskTCB,               	
                 (CPU_CHAR   *)"WIFI Task ",
                 (OS_TASK_PTR ) WIFI_Task,
                 (void       *) 0, 
                 (OS_PRIO     ) WIFI_Task_PRIO,
                 (CPU_STK    *)&WIFI_TaskStk[0],
                 (CPU_STK_SIZE) WIFI_Task_STK_SIZE / 10,
                 (CPU_STK_SIZE) WIFI_Task_STK_SIZE,
                 (OS_MSG_QTY  ) 5u,
                 (OS_TICK     ) 0u,
                 (void       *) 0,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR  ),
                 (OS_ERR     *)&err);	
				 
	// 创建4G模块通讯任务
	OSTaskCreate((OS_TCB     *)&_4G_TaskTCB,               	
                 (CPU_CHAR   *)"_4G Task ",
                 (OS_TASK_PTR ) _4G_Task,
                 (void       *) 0, 
                 (OS_PRIO     ) _4G_Task_PRIO,
                 (CPU_STK    *)&_4G_TaskStk[0],
                 (CPU_STK_SIZE) _4G_Task_STK_SIZE / 10,
                 (CPU_STK_SIZE) _4G_Task_STK_SIZE,
                 (OS_MSG_QTY  ) 5u,
                 (OS_TICK     ) 0u,
                 (void       *) 0,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR  ),
                 (OS_ERR     *)&err);	

	// 创建485通讯任务
	OSTaskCreate((OS_TCB     *)&_485_TaskTCB,               	
                 (CPU_CHAR   *)"_485 Task ",
                 (OS_TASK_PTR ) _485_Task,
                 (void       *) 0, 
                 (OS_PRIO     ) _485_Task_PRIO,
                 (CPU_STK    *)&_485_TaskStk[0],
                 (CPU_STK_SIZE) _485_Task_STK_SIZE / 10,
                 (CPU_STK_SIZE) _485_Task_STK_SIZE,
                 (OS_MSG_QTY  ) 5u,
                 (OS_TICK     ) 0u,
                 (void       *) 0,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR  ),
                 (OS_ERR     *)&err);				 

	OS_CRITICAL_EXIT();  //退出临界区
    
	OSTaskDel ( & Start_TaskTCB, & err ); //删除起始任务本身，该任务不再运行
}


/******************************************************************************************************
*	函 数 名: emWin_Task
*	函数功能: emWin图形界面任务
*******************************************************************************************************/

static	void	emWin_Task (void *p_arg)
{	
	OS_ERR      err;
	(void)p_arg;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CRC, ENABLE);	// 使能CRC时钟，用于emwin验证	
	#if GUI_SUPPORT_MEMDEV
    WM_SetCreateFlags(WM_CF_MEMDEV);					// 使能emwin内存设备
	#endif
	GUI_Init();
	WM_MULTIBUF_Enable(1);								// 窗口管理器自动使用多缓冲，可以让动态绘图更加流畅	
//	LCD_PWMinit(90);									// LCD背光PWM初始化,用于调节背光亮度         TIM4

	WM_SetDesktopColor(GUI_BLACK);

	
/************************* 显示开机画面 从SD卡中加载 **************************/	
	
	int BMP_XSize = 0;	        	// 图片 X 尺寸
	int BMP_YSize = 0;	        	// 图片 Y 尺寸
	GUI_MEMDEV_Handle	 hMem_BMP;	// 存储设备句柄
					
	if(	f_open( &SD_File,"4.bmp",FA_OPEN_EXISTING | FA_READ ) == FR_OK )			// 打开文件
	{
		SD_FileSize = f_size( &SD_File);											// 获取文件大小	
		f_read( &SD_File,BMP_Buffer,SD_FileSize,&SD_FileCount); 					// 读取数据	
		BMP_XSize = GUI_BMP_GetXSize(BMP_Buffer);									// 获取图片 X 尺寸
		BMP_YSize = GUI_BMP_GetYSize(BMP_Buffer);									// 获取图片 Y 尺寸
		hMem_BMP  = GUI_MEMDEV_CreateEx(0, 0, BMP_XSize, BMP_YSize, GUI_MEMDEV_HASTRANS);	// 创建相应大小的存储设备
		GUI_MEMDEV_Select(hMem_BMP);					// 选择该存储设备
		GUI_BMP_Draw(BMP_Buffer,0, 0);					// 将图片解码到存储设备中
		GUI_MEMDEV_Select(0);				    		// 解码完毕，取消激活该存储设备
		f_close(&SD_File);								// 关闭文件
		GUI_MEMDEV_WriteOpaqueAt(hMem_BMP, 0, 0);		// 显示存储设备	hMem_BMP 的图片
				
		OSTimeDlyHMSM(0,0,5,0,(OS_OPT)OS_OPT_TIME_DLY,(OS_ERR*)&err);		// 显示 5 秒
//		while(GPIO_ReadInputDataBit(KEYconfirm_INT_GPIO_PORT ,KEYconfirm_INT_GPIO_PIN)==0);		//等待“确认”按键进入主界面
	}

	GUI_UC_SetEncodeUTF8();	// 使能UTF8编码	
	GUI_XBF_CreateFont(&XBF_Font16,&XBF_Data16,GUI_XBF_TYPE_PROP,_cbGetData_XBF16,&XBF_file16);			// 创建XBF 宋体16点阵字体    				         						    					     	
	GUI_XBF_CreateFont(&XBF_Font24,&XBF_Data24,GUI_XBF_TYPE_PROP,_cbGetData_XBF24,&XBF_file24);			// 创建XBF 宋体24点阵字体                 	
	GUI_XBF_CreateFont(&XBF_Font32,&XBF_Data32,GUI_XBF_TYPE_PROP_EXT,_cbGetData_XBF32,&XBF_file32);		// 创建XBF 宋体32点阵字体 

	GUI_CURSOR_Show();       		//显示光标
	GUI_SetColor(GUI_WHITE);		//设置画笔色
	GUI_SetBkColor(GUI_BLACK);		//设置背景色
	GUI_Clear();
	
	MainTask();
}

/******************************************************************************************************
*	函 数 名: iwdg_Task
*	函数功能: 看门狗 喂狗任务
*	说    明: 周期 600ms
*******************************************************************************************************/

static	void	iwdg_Task (void *p_arg)
 {
	OS_ERR      err;
	(void)p_arg;
	
	while(DEF_TRUE)
	{	
		IWDG_Feed();  //1s内喂狗，否则发生复位
		OSTimeDlyHMSM(0,0,0,600,(OS_OPT)OS_OPT_TIME_DLY,(OS_ERR*)&err);	
	}
}

/******************************************************************************************************
*	函 数 名: Touch_Task
*	函数功能: 触摸扫描任务
*	说    明: 扫描周期 20ms
*******************************************************************************************************/

static	void	Touch_Task (void *p_arg)
{
	OS_ERR      err;
	(void)p_arg;
	
	while(DEF_TRUE)
	{	
		GUI_TouchScan();		// 调用触摸检测函数
		OSTimeDly ( 20, OS_OPT_TIME_DLY, & err );	
	}
}

/******************************************************************************************************
*	函 数 名: Key_Task
*	函数功能: 按键扫描任务
*	说    明: 扫描周期 200ms 扫描方式，也可使用EXIT中断
*******************************************************************************************************/

static	void	Key_Task (void *p_arg)
{
	OS_ERR      err;
	(void)p_arg;
	
	while(DEF_TRUE)
	{	
		if(GPIO_ReadInputDataBit(KEYup_INT_GPIO_PORT      ,KEYup_INT_GPIO_PIN     )==1 )
		{	
			GUI_SendKeyMsg(GUI_KEY_UP, 1);			// 按键信息传递给emwin
		}
		if(GPIO_ReadInputDataBit(KEYdown_INT_GPIO_PORT    ,KEYdown_INT_GPIO_PIN   )==1 )
		{	
			GUI_SendKeyMsg(GUI_KEY_DOWN, 1);		// 按键信息传递给emwin
		}
		if(GPIO_ReadInputDataBit(KEYleft_INT_GPIO_PORT    ,KEYleft_INT_GPIO_PIN   )==1 )
		{	
			GUI_SendKeyMsg(GUI_KEY_LEFT, 1);		// 按键信息传递给emwin
		}	
		if(GPIO_ReadInputDataBit(KEYright_INT_GPIO_PORT   ,KEYright_INT_GPIO_PIN  )==1 )
		{	
			GUI_SendKeyMsg(GUI_KEY_RIGHT, 1);		// 按键信息传递给emwin
		}
		if(GPIO_ReadInputDataBit(KEYconfirm_INT_GPIO_PORT ,KEYconfirm_INT_GPIO_PIN)==1 )
		{	
//			GUI_SendKeyMsg(GUI_KEY_HOME, 1);		// 按键信息传递给emwin
		}
		if(GPIO_ReadInputDataBit(KEYcancel_INT_GPIO_PORT  ,KEYcancel_INT_GPIO_PIN )==1 )
		{	
//			GUI_SendKeyMsg(GUI_KEY_ENTER, 1);		// 按键信息传递给emwin
		}
		
		OSTimeDly ( 200, OS_OPT_TIME_DLY, & err );	
	}
}

/******************************************************************************************************
*	函 数 名: LED_Task
*	函数功能: 驱动LED闪烁,监测系统是否运行,监测CPU温度
*******************************************************************************************************/

static	void	LED_Task (void *p_arg)
{
	OS_ERR      err;
	(void)p_arg;
	
	while(DEF_TRUE)
	{
		GPIO_ToggleBits(LED1_PORT,LED1_PIN);
		OSTimeDly ( 300, OS_OPT_TIME_DLY, & err );
		GPIO_ToggleBits(LED1_PORT,LED1_PIN);
		OSTimeDly ( 300, OS_OPT_TIME_DLY, & err );
		GPIO_ToggleBits(LED2_PORT,LED2_PIN);
		OSTimeDly ( 200, OS_OPT_TIME_DLY, & err );
		GPIO_ToggleBits(LED2_PORT,LED2_PIN);
		OSTimeDly ( 200, OS_OPT_TIME_DLY, & err );
	}			
}


/******************************************************************************************************
*	函 数 名: ADC2_Task
*	函数功能: 驱动TIM8定时ADC采样，CH1-CH4,CH7-CH10
* 	说    明：TIM8PWM波输出上升沿驱动ADC转换，转换数据由DMA传输，DMA中断转存数据
*******************************************************************************************************/

static	void	ADC2_Task (void *p_arg)
{
	OS_ERR      err;
	(void)p_arg;

	while(DEF_TRUE)
	{	
		DMA_Cmd(RHEOSTAT_ADC2_DMA_STREAM, ENABLE);
		TIM_Cmd(TIM8, ENABLE);	
		TIM_CtrlPWMOutputs(TIM8, ENABLE);  

		OSTimeDlyHMSM(0,0,8,0,(OS_OPT)OS_OPT_TIME_DLY,(OS_ERR*)&err);			
	}
}	


/******************************************************************************************************
*	函 数 名: ADC3_Task
*	函数功能: 驱动TIM5定时ADC3采样，用于测速 CH5-CH6
* 	说    明：TIM5PWM波输出上升沿驱动ADC转换，转换数据由DMA传输，DMA中断处理数据
*******************************************************************************************************/

static	void	ADC3_Task (void *p_arg)
 {
	OS_ERR      err;
	(void)p_arg;	
	
	while(DEF_TRUE)
	{	
		DMA_Cmd(RHEOSTAT_ADC3_DMA_STREAM, ENABLE);
		TIM_Cmd(TIM5, ENABLE);	
		TIM_CtrlPWMOutputs(TIM5, ENABLE);

		OSTimeDlyHMSM(0,0,5,0,(OS_OPT)OS_OPT_TIME_DLY,(OS_ERR*)&err);			
	}
}
	
/******************************************************************************************************
*	函 数 名: DSP_Task
*	函数功能: 峰峰值、FIR、FFT处理
*******************************************************************************************************/

static	void	DSP_Task (void *p_arg)
{
	OS_ERR      err;
	(void)p_arg;

	uint64_t   AD_Value_sum=0;
	uint16_t   AD_average=0;
	int16_t	   AD_MAX=0;
	int16_t	   AD_MIN=0;
	uint16_t   i=0;	
	
	extern	uint32_t   Mag[1024];
	
	while(DEF_TRUE)
	{

		OSTaskSemPend(0,OS_OPT_PEND_BLOCKING,0,&err);
		
/*	CH1 电涡流传感器 信号处理	*/	
			
			AD_MAX=0;AD_MIN=0;AD_Value_sum=0;
			for(i=0;i<512;i++)
			{ AD_Value_sum=AD_Value_sum+AD_Value_CH1[i];  }			//求和 
			AD_average=(int)AD_Value_sum/512;						//求平均值
			if(AD_average>100)										//判断此通道是否有数据
		    {			
				for(i=0;i<1024;i++)
				{ AD_Value_average[i]=AD_Value_CH1[i]-AD_average;}			//减去平均值
				DSP_FIR1024();												//FIR 输出浮点数据 存入AD_Value_FIR数组,并求最大最小值
				for (i = 0; i < 1024; i++)
				{	AD_Value_FIR_CH1[i] =(int) AD_Value_FIR[i];
					AD_Value_average[i] = AD_Value_FIR_CH1[i];	
					if(AD_Value_FIR_CH1[i]>=AD_MAX)	AD_MAX=AD_Value_FIR_CH1[i];
					if(AD_Value_FIR_CH1[i]<=AD_MIN)	AD_MIN=AD_Value_FIR_CH1[i];	}
				AD_Value_CH1_VPP = AD_MAX-AD_MIN;							//求峰峰值
				DSP_FFT1024();												//FFT 输出浮点数据 存入AD_Value_FIR数组
				for (i = 0; i < 1024; i++)
					{  AD_Value_FFT_CH1[i] = - (int)Mag[i]; }				//取负 显示用
			}
			else
			{	
				AD_Value_CH1_VPP = 0;
				for(i=0;i<1024;i++)
				{	AD_Value_FIR_CH1[i] = 0 ; 
					AD_Value_FFT_CH1[i] = 0 ;}
			}			
			
/*	CH2 电涡流传感器 信号处理	*/	
			
			AD_MAX=0;AD_MIN=0;AD_Value_sum=0;
			for(i=0;i<512;i++)
			{ AD_Value_sum=AD_Value_sum+AD_Value_CH2[i];  }			//求和 
			AD_average=(int)AD_Value_sum/512;						//求平均值
			if(AD_average>100)										//判断此通道是否有数据
		    {			
				for(i=0;i<1024;i++)
				{ AD_Value_average[i]=AD_Value_CH2[i]-AD_average;}			//减去平均值
				DSP_FIR1024();		                             			//FIR 输出浮点数据 存入AD_Value_FIR数组,并求最大最小值
				for (i = 0; i < 1024; i++)
				{	AD_Value_FIR_CH2[i] =(int) AD_Value_FIR[i];
					AD_Value_average[i] = AD_Value_FIR_CH2[i];
					if(AD_Value_FIR_CH2[i]>=AD_MAX)	AD_MAX=AD_Value_FIR_CH2[i];
					if(AD_Value_FIR_CH2[i]<=AD_MIN)	AD_MIN=AD_Value_FIR_CH2[i];}
				AD_Value_CH2_VPP = AD_MAX-AD_MIN;							//求峰峰值	
				DSP_FFT1024();												//FFT 输出浮点数据 存入AD_Value_FIR数组
				for (i = 0; i < 1024; i++)
				{  AD_Value_FFT_CH2[i] = - (int)Mag[i]; }					//取负 显示用
			}
			else
			{	
				AD_Value_CH2_VPP = 0;
				for(i=0;i<1024;i++)
				{	AD_Value_FIR_CH2[i] = 0 ; 
					AD_Value_FFT_CH2[i] = 0 ;}
			}
			
/*	CH3 电涡流传感器 信号处理	*/		
			
			AD_MAX=0;AD_MIN=0;AD_Value_sum=0;
			for(i=0;i<512;i++)
			{ AD_Value_sum=AD_Value_sum+AD_Value_CH3[i];  }			//求和 
			AD_average=(int)AD_Value_sum/512;						//求平均值
			if(AD_average>100)										//判断此通道是否有数据
		    {			
				for(i=0;i<1024;i++)
				{ AD_Value_average[i]=AD_Value_CH3[i]-AD_average;}			//减去平均值
				DSP_FIR1024();		                               			//FIR 输出浮点数据 存入AD_Value_FIR数组,并求最大最小值
				for (i = 0; i < 1024; i++)
				{	AD_Value_FIR_CH3[i] =(int) AD_Value_FIR[i];
					AD_Value_average[i] = AD_Value_FIR_CH3[i];
					if(AD_Value_FIR_CH3[i]>=AD_MAX)	AD_MAX=AD_Value_FIR_CH3[i];
					if(AD_Value_FIR_CH3[i]<=AD_MIN)	AD_MIN=AD_Value_FIR_CH3[i];	}
				AD_Value_CH3_VPP = AD_MAX-AD_MIN;							//求峰峰值	
				DSP_FFT1024();												//FFT 输出浮点数据 存入AD_Value_FIR数组
				for (i = 0; i < 1024; i++)
				{  AD_Value_FFT_CH3[i] = - (int)Mag[i]; }					//取负 显示用				
			}
			else
			{	
				AD_Value_CH3_VPP = 0;
				for(i=0;i<1024;i++)
				{	AD_Value_FIR_CH3[i] = 0 ; 
					AD_Value_FFT_CH3[i] = 0 ;}
			}
			
/*	CH4 电涡流传感器 信号处理	*/	
			
			AD_MAX=0;AD_MIN=0;AD_Value_sum=0;
			for(i=0;i<512;i++)
			{ AD_Value_sum=AD_Value_sum+AD_Value_CH4[i];  }			//求和 
			AD_average=(int)AD_Value_sum/512;						//求平均值
			if(AD_average>100)										//判断此通道是否有数据
		    {			
				for(i=0;i<1024;i++)
				{ AD_Value_average[i]=AD_Value_CH4[i]-AD_average;}			//减去平均值
				DSP_FIR1024();		                             			//FIR 输出浮点数据 存入AD_Value_FIR数组,并求最大最小值
				for (i = 0; i < 1024; i++)
				{	AD_Value_FIR_CH4[i] =(int) AD_Value_FIR[i];
					AD_Value_average[i] = AD_Value_FIR_CH4[i];				
					if(AD_Value_FIR_CH4[i]>=AD_MAX)	AD_MAX=AD_Value_FIR_CH4[i];
					if(AD_Value_FIR_CH4[i]<=AD_MIN)	AD_MIN=AD_Value_FIR_CH4[i];}	
				AD_Value_CH4_VPP = AD_MAX-AD_MIN;							//求峰峰值	
				DSP_FFT1024();												//FFT 输出浮点数据 存入AD_Value_FIR数组
				for (i = 0; i < 1024; i++)
				{  AD_Value_FFT_CH4[i] = - (int)Mag[i]; }					//取负 显示用							
			}
			else
			{	
				AD_Value_CH4_VPP = 0;
				for(i=0;i<1024;i++)
				{	AD_Value_FIR_CH4[i] = 0 ; 
					AD_Value_FFT_CH4[i] = 0 ;}
			}
			
/*	CH7 振动传感器 信号处理	*/	
			
			AD_MAX=0;AD_MIN=0;AD_Value_sum=0;
			for(i=0;i<512;i++)
			{ AD_Value_sum=AD_Value_sum+AD_Value_CH7[i];  }			//求和 
			AD_average=(int)AD_Value_sum/512;						//求平均值
			if(AD_average>100)										//判断此通道是否有数据
		    {			
				for(i=0;i<1024;i++)
				{ AD_Value_average[i]=AD_Value_CH7[i]-AD_average;}			//减去平均值
				DSP_FIR1024();		                              			//FIR 输出浮点数据 存入AD_Value_FIR数组,并求最大最小值
				for (i = 0; i < 1024; i++)
				{	AD_Value_FIR_CH7[i] =(int) AD_Value_FIR[i];
					AD_Value_average[i] = AD_Value_FIR_CH7[i];
					if(AD_Value_FIR_CH7[i]>=AD_MAX)	AD_MAX=AD_Value_FIR_CH7[i];
					if(AD_Value_FIR_CH7[i]<=AD_MIN)	AD_MIN=AD_Value_FIR_CH7[i];	}
				AD_Value_CH7_VPP = AD_MAX-AD_MIN;							//求峰峰值	
				DSP_FFT1024();												//FFT 输出浮点数据 存入AD_Value_FIR数组
				for (i = 0; i < 1024; i++)
				{  AD_Value_FFT_CH7[i] = - (int)Mag[i]; }					//取负 显示用			
			}
			else
			{	
				AD_Value_CH7_VPP = 0;
				for(i=0;i<1024;i++)
				{	AD_Value_FIR_CH7[i] = 0 ; 
					AD_Value_FFT_CH7[i] = 0 ;}
			}
			
/*	CH8 振动传感器 信号处理	*/	
			
			AD_MAX=0;AD_MIN=0;AD_Value_sum=0;
			for(i=0;i<512;i++)
			{ AD_Value_sum=AD_Value_sum+AD_Value_CH8[i];  }			//求和 
			AD_average=(int)AD_Value_sum/512;						//求平均值
			if(AD_average>100)										//判断此通道是否有数据
		    {
				for(i=0;i<1024;i++)
				{ AD_Value_average[i]=AD_Value_CH8[i]-AD_average;}			//减去平均值
				DSP_FIR1024();		                        				//FIR 输出浮点数据 存入AD_Value_FIR数组,并求最大最小值
				for (i = 0; i < 1024; i++)
				{	AD_Value_FIR_CH8[i] =(int) AD_Value_FIR[i];
					AD_Value_average[i] = AD_Value_FIR_CH8[i];
					if(AD_Value_FIR_CH8[i]>=AD_MAX)	AD_MAX=AD_Value_FIR_CH8[i];
					if(AD_Value_FIR_CH8[i]<=AD_MIN)	AD_MIN=AD_Value_FIR_CH8[i];	}
				AD_Value_CH8_VPP = AD_MAX-AD_MIN;							//求峰峰值		
				DSP_FFT1024();												//FFT 输出浮点数据 存入AD_Value_FIR数组
				for (i = 0; i < 1024; i++)
				{  AD_Value_FFT_CH8[i] = - (int)Mag[i]; }					//取负 显示用							
			}
			else
			{	
				AD_Value_CH8_VPP = 0;
				for(i=0;i<1024;i++)
				{	AD_Value_FIR_CH8[i] = 0 ; 
					AD_Value_FFT_CH8[i] = 0 ;}
			}
			
/*	CH9  信号处理	*/		
			
			AD_MAX=0;AD_MIN=0;AD_Value_sum=0;
			for(i=0;i<512;i++)
			{ AD_Value_sum=AD_Value_sum+AD_Value_CH9[i];  }			//求和 
			AD_average=(int)AD_Value_sum/512;						//求平均值
			if(AD_average>100)										//判断此通道是否有数据
		    {			
				for(i=0;i<1024;i++)
				{ AD_Value_average[i]=AD_Value_CH9[i]-AD_average;}			//减去平均值	
				DSP_FIR1024();		                         				//FIR 输出浮点数据 存入AD_Value_FIR数组,并求最大最小值
				for (i = 0; i < 1024; i++)
				{	AD_Value_FIR_CH9[i] =(int) AD_Value_FIR[i];
					AD_Value_average[i] = AD_Value_FIR_CH9[i];
					if(AD_Value_FIR_CH9[i]>=AD_MAX)	AD_MAX=AD_Value_FIR_CH9[i];
					if(AD_Value_FIR_CH9[i]<=AD_MIN)	AD_MIN=AD_Value_FIR_CH9[i];	}
				AD_Value_CH9_VPP = AD_MAX-AD_MIN;							//求峰峰值	
				DSP_FFT1024();												//FFT 输出浮点数据 存入AD_Value_FIR数组
				for (i = 0; i < 1024; i++)
				{  AD_Value_FFT_CH9[i] = - (int)Mag[i]; }					//取负 显示用								
			}
			else
			{	
				AD_Value_CH9_VPP = 0;
				for(i=0;i<1024;i++)
				{	AD_Value_FIR_CH9[i] = 0 ; 
					AD_Value_FFT_CH9[i] = 0 ;}
			}
			
/*	CH10  信号处理	*/		
			
			AD_MAX=0;AD_MIN=0;AD_Value_sum=0;
			for(i=0;i<512;i++)
			{ AD_Value_sum=AD_Value_sum+AD_Value_CH10[i];  }		//求和 
			AD_average=(int)AD_Value_sum/512;						//求平均值
			if(AD_average>100)										//判断此通道是否有数据
		    {
				for(i=0;i<1024;i++)
				{ AD_Value_average[i]=AD_Value_CH10[i]-AD_average;}			//减去平均值			
				DSP_FIR1024();												//FIR 输出浮点数据 存入AD_Value_FIR数组,并求最大最小值
				for (i = 0; i < 1024; i++)
				{	AD_Value_FIR_CH10[i] =(int) AD_Value_FIR[i];
					AD_Value_average[i] = AD_Value_FIR_CH10[i];
					if(AD_Value_FIR_CH10[i]>=AD_MAX) AD_MAX=AD_Value_FIR_CH10[i];
					if(AD_Value_FIR_CH10[i]<=AD_MIN) AD_MIN=AD_Value_FIR_CH10[i];	}
				AD_Value_CH10_VPP = AD_MAX-AD_MIN;							//求峰峰值		
				DSP_FFT1024();												//FFT 输出浮点数据 存入AD_Value_FIR数组
				for (i = 0; i < 1024; i++)
				{  AD_Value_FFT_CH10[i] = - (int)Mag[i]; }					//取负 显示用			
			}
			else
			{	
				AD_Value_CH10_VPP = 0;
				for(i=0;i<1024;i++)
				{	AD_Value_FIR_CH10[i] = 0 ; 
					AD_Value_FFT_CH10[i] = 0 ;}
			}
			
			data_ready_display=1;
	
			OSTaskSemPost(&WIFI_TaskTCB,OS_OPT_POST_NONE,&err);			//数据处理完成，给各任务发布消息
			OSTaskSemPost(&_4G_TaskTCB,OS_OPT_POST_NONE,&err);
			OSTaskSemPost(&SD_TaskTCB,OS_OPT_POST_NONE,&err);
			OSTaskSemPost(&_485_TaskTCB,OS_OPT_POST_NONE,&err);
			
		 OSTimeDlyHMSM(0,0,1,0,(OS_OPT)OS_OPT_TIME_DLY,(OS_ERR*)&err);			
	}
}

/******************************************************************************************************
*	函 数 名: SD_Task
*	函数功能: SD卡 存储数据
*	说    明：存储周期 3min
*******************************************************************************************************/

static	void	SD_Task (void *p_arg)
{
	OS_ERR      err;
	(void)p_arg;
	
	uint16_t	i=0;
	BYTE a[40];
	BYTE b[5];	
	
	RTC_TimeTypeDef RTC_TimeStructure;
	RTC_DateTypeDef RTC_DateStructure;

	while(DEF_TRUE)
	{	
		if(SD_select == 1)
		{
			OSTaskSemPend(0,OS_OPT_PEND_BLOCKING,0,&err);	
		
			RTC_GetTime(RTC_Format_BIN, &RTC_TimeStructure);
			RTC_GetDate(RTC_Format_BIN, &RTC_DateStructure);
			
			f_open(&SD_File, "test.txt" , FA_OPEN_ALWAYS | FA_WRITE );
		
			if( f_size(&SD_File) >= (1024*1024*1024) ) 							// 数据量大于 1GB时 覆盖文件
			{	f_close(&SD_File);
				f_open(&SD_File, "test.txt" , FA_CREATE_ALWAYS | FA_WRITE );
			}
			
			memset(a, 0, sizeof(a));											// 存储时间信息
			sprintf((char *)a, "\r\n%0.2d/%0.2d %0.2d:%0.2d:%0.2d  \r\n",
									RTC_DateStructure.RTC_Month, 
									RTC_DateStructure.RTC_Date,
									RTC_TimeStructure.RTC_Hours,
									RTC_TimeStructure.RTC_Minutes,
									RTC_TimeStructure.RTC_Seconds );
			f_lseek(&SD_File,f_size(&SD_File));
			f_write(&SD_File,a,sizeof(a),&SD_FileCount);
			
			if( SD_select_CH12 == 1 &&  CH5_SPEED !=0 )							//存储 CH1 CH2 数据							
			{	
				memset(a, 0, sizeof(a));
				sprintf((char *)a, "\r\nspeed:%d r/min \r\n",CH5_SPEED);
				f_lseek(&SD_File,f_size(&SD_File));
				f_write(&SD_File,a,sizeof(a),&SD_FileCount);
				
				memset(a, 0, sizeof(a));
				sprintf((char *)a,"CH1:\r\n");
				f_lseek(&SD_File,f_size(&SD_File));
				f_write(&SD_File,a,sizeof(a),&SD_FileCount);
				for(i=0;i<1024;i++)
				{
					memset(b, 0, sizeof(b));
					sprintf((char *)b,"%d,",AD_Value_FIR_CH1[i]);
					f_lseek(&SD_File,f_size(&SD_File));
					f_write(&SD_File,b,sizeof(b),&SD_FileCount);
				}	
				memset(a, 0, sizeof(a));
				sprintf((char *)a,"\r\nCH2:\r\n");
				f_lseek(&SD_File,f_size(&SD_File));
				f_write(&SD_File,a,sizeof(a),&SD_FileCount);	
				for(i=0;i<1024;i++)
				{
					memset(b, 0, sizeof(b));
					sprintf((char *)b,"%d,",AD_Value_FIR_CH1[i]);
					f_lseek(&SD_File,f_size(&SD_File));
					f_write(&SD_File,b,sizeof(b),&SD_FileCount);
				}
			}
			
			if( SD_select_CH34 == 1 &&  CH6_SPEED !=0 )							//存储 CH3 CH4 数据												
			{	
				memset(a, 0, sizeof(a));
				sprintf((char *)a, "\r\nspeed:%d r/min \r\n",CH6_SPEED);
				f_lseek(&SD_File,f_size(&SD_File));
				f_write(&SD_File,a,sizeof(a),&SD_FileCount);
				
				memset(a, 0, sizeof(a));
				sprintf((char *)a,"CH3:\r\n");
				f_lseek(&SD_File,f_size(&SD_File));
				f_write(&SD_File,a,sizeof(a),&SD_FileCount);
				for(i=0;i<1024;i++)
				{
					memset(b, 0, sizeof(b));
					sprintf((char *)b,"%d,",AD_Value_FIR_CH3[i]);
					f_lseek(&SD_File,f_size(&SD_File));
					f_write(&SD_File,b,sizeof(b),&SD_FileCount);
				}
				memset(a, 0, sizeof(a));
				sprintf((char *)a,"\r\nCH4:\r\n");
				f_lseek(&SD_File,f_size(&SD_File));
				f_write(&SD_File,a,sizeof(a),&SD_FileCount);	
				for(i=0;i<1024;i++)
				{
					memset(b, 0, sizeof(b));
					sprintf((char *)b,"%d,",AD_Value_FIR_CH4[i]);
					f_lseek(&SD_File,f_size(&SD_File));
					f_write(&SD_File,b,sizeof(b),&SD_FileCount);
				}
			}

			if( SD_select_CH78 == 1 )							// 存储 CH7 CH8 数据												
			{	
				memset(a, 0, sizeof(a));
				sprintf((char *)a,"\r\nCH7:\r\n");
				f_lseek(&SD_File,f_size(&SD_File));
				f_write(&SD_File,a,sizeof(a),&SD_FileCount);
				for(i=0;i<1024;i++)
				{
					memset(b, 0, sizeof(b));
					sprintf((char *)b,"%d,",AD_Value_FIR_CH7[i]);
					f_lseek(&SD_File,f_size(&SD_File));
					f_write(&SD_File,b,sizeof(b),&SD_FileCount);
				}
				memset(a, 0, sizeof(a));
				sprintf((char *)a,"\r\nCH8:\r\n");
				f_lseek(&SD_File,f_size(&SD_File));
				f_write(&SD_File,a,sizeof(a),&SD_FileCount);	
				for(i=0;i<1024;i++)
				{
					memset(b, 0, sizeof(b));
					sprintf((char *)b,"%d,",AD_Value_FIR_CH8[i]);
					f_lseek(&SD_File,f_size(&SD_File));
					f_write(&SD_File,b,sizeof(b),&SD_FileCount);
				}
			}

			if( SD_select_CH910 == 1 )							// 存储 CH9 CH10 数据												
			{	
				memset(a, 0, sizeof(a));
				sprintf((char *)a,"\r\nCH9:\r\n");
				f_lseek(&SD_File,f_size(&SD_File));
				f_write(&SD_File,a,sizeof(a),&SD_FileCount);
				for(i=0;i<1024;i++)
				{
					memset(b, 0, sizeof(b));
					sprintf((char *)b,"%d,",AD_Value_FIR_CH7[i]);
					f_lseek(&SD_File,f_size(&SD_File));
					f_write(&SD_File,b,sizeof(b),&SD_FileCount);
				}
				memset(a, 0, sizeof(a));
				sprintf((char *)a,"\r\nCH10:\r\n");
				f_lseek(&SD_File,f_size(&SD_File));
				f_write(&SD_File,a,sizeof(a),&SD_FileCount);	
				for(i=0;i<1024;i++)
				{
					memset(b, 0, sizeof(b));
					sprintf((char *)b,"%d,",AD_Value_FIR_CH8[i]);
					f_lseek(&SD_File,f_size(&SD_File));
					f_write(&SD_File,b,sizeof(b),&SD_FileCount);
				}
			}
			
			memset(a, 0, sizeof(a));							// 数据存储结束
			sprintf((char *)a,"\r\n END\r\n\r\n");
			f_lseek(&SD_File,f_size(&SD_File));
			f_write(&SD_File,a,sizeof(a),&SD_FileCount);
			f_close(&SD_File);
		}
		OSTimeDlyHMSM(0,3,0,0,(OS_OPT)OS_OPT_TIME_DLY,(OS_ERR*)&err);						
	}
}

/******************************************************************************************************
*	函 数 名: WIFI_Task
*	函数功能: WIFI通讯，传输数据
*******************************************************************************************************/

static	void	WIFI_Task (void *p_arg)
{
	OS_ERR      err;
	(void)p_arg;
	uint16_t	i;
	
	RTC_TimeTypeDef RTC_TimeStructure;
	RTC_DateTypeDef RTC_DateStructure;
	
	while(DEF_TRUE)
	{		
		if(WIFI_or_485 == 0)
		{
			OSTaskSemPend(0,OS_OPT_PEND_BLOCKING,0,&err);
				
			RTC_GetTime(RTC_Format_BIN, &RTC_TimeStructure);
			RTC_GetDate(RTC_Format_BIN, &RTC_DateStructure);
			
			Usart_WIFI("\r\n%d/%d %d:%d:%d",
						RTC_DateStructure.RTC_Month, 
						RTC_DateStructure.RTC_Date,
						RTC_TimeStructure.RTC_Hours,
						RTC_TimeStructure.RTC_Minutes,
						RTC_TimeStructure.RTC_Seconds );
			
			if(AD_Value_CH1_VPP !=0 &&AD_Value_CH2_VPP !=0)
			{
				Usart_WIFI("\r\n speed : %d r/min", CH5_SPEED );
				Usart_WIFI("\r\nCH1: ");
				for(i=0;i<1024;i++)
				{	
					Usart_WIFI("%d,",AD_Value_CH1[i]);
				}
				
				Usart_WIFI("\r\nCH2: ");
				for(i=0;i<1024;i++)
				{	
					Usart_WIFI("%d,",AD_Value_CH2[i]);
				}
			}
			
			if(AD_Value_CH3_VPP !=0 &&AD_Value_CH4_VPP !=0)
			{
				Usart_WIFI("\r\n speed : %d r/min", CH6_SPEED );
				Usart_WIFI("\r\nCH3: ");
				for(i=0;i<1024;i++)
				{	
					Usart_WIFI("%d,",AD_Value_CH3[i]);
				}
				
				Usart_WIFI("\r\nCH4: ");
				for(i=0;i<1024;i++)
				{	
					Usart_WIFI("%d,",AD_Value_CH4[i]);
				}
			}			

			if(AD_Value_CH7_VPP !=0)
			{
				Usart_WIFI("\r\nCH7: ");
				for(i=0;i<1024;i++)
				{	
					Usart_WIFI("%d,",AD_Value_CH7[i]);
				}		
			}
			
			if(AD_Value_CH8_VPP !=0)
			{
				Usart_WIFI("\r\nCH8: ");
				for(i=0;i<1024;i++)
				{	
					Usart_WIFI("%d,",AD_Value_CH8[i]);
				}	
			}
				
			if(AD_Value_CH9_VPP !=0)
			{
				Usart_WIFI("\r\nCH9: ");
				for(i=0;i<1024;i++)
				{	
					Usart_WIFI("%d,",AD_Value_CH9[i]);
				}		
			}
			
			if(AD_Value_CH10_VPP !=0)
			{
				Usart_WIFI("\r\nCH10: ");
				for(i=0;i<1024;i++)
				{	
					Usart_WIFI("%d,",AD_Value_CH10[i]);
				}				
			}
			
			Usart_WIFI("\r\nALLEND\r\n");
		}

		OSTimeDlyHMSM(0,0,5,0,(OS_OPT)OS_OPT_TIME_DLY,(OS_ERR*)&err);						
	}
}

/******************************************************************************************************
*	函 数 名: _4G_Task
*	函数功能: 4G模块通讯，传输数据
*******************************************************************************************************/

static	void	_4G_Task (void *p_arg)
{
	OS_ERR      err;
	(void)p_arg;

	while(DEF_TRUE)
	{	
		OSTaskSemPend(0,OS_OPT_PEND_BLOCKING,0,&err);
		
		if(GPIO_ReadInputDataBit(_4G_LINKA_PORT,_4G_LINKA_PIN)== 1 )
		{	
			uint16_t	i;
			int8_t		send;
			
			if(AD_Value_CH1_VPP != 0 && AD_Value_CH2_VPP != 0)
			{	
				send=0x68;
				_4G_SendByte(send);
				
				send=(int)(CH5_SPEED%10)+48; 
				_4G_SendByte(send);				
				send=(int)((CH5_SPEED%100)/10)+48;
				_4G_SendByte(send);	
				send=(int)((CH5_SPEED%1000)/100)+48;
				_4G_SendByte(send);	
				send=(int)(CH5_SPEED/1000)+48;
				_4G_SendByte(send);
	
				for(i=0;i<1024;i++)
				{	send = AD_Value_CH1[i];
					_4G_SendByte(send);
					send = AD_Value_CH1[i]>>8;
					_4G_SendByte(send);
				}
				
				for(i=0;i<1024;i++)
				{	send = AD_Value_CH2[i];
					_4G_SendByte(send);
					send = AD_Value_CH2[i]>>8;
					_4G_SendByte(send);
				}
			}
		}
		
		OSTimeDlyHMSM(0,0,5,0,(OS_OPT)OS_OPT_TIME_DLY,(OS_ERR*)&err);						
	}
}

/******************************************************************************************************
*	函 数 名: _485_Task
*	函数功能: 485 Modbus通讯，传输数据，Modbus的相关功能未实现
*******************************************************************************************************/

static	void	_485_Task (void *p_arg)
{
	OS_ERR      err;
	(void)p_arg;
	
	uint16_t	i;
	
	RTC_TimeTypeDef RTC_TimeStructure;
	RTC_DateTypeDef RTC_DateStructure;
	while(DEF_TRUE)
	{	
		if(	WIFI_or_485 == 1)
		{	
			OSTaskSemPend(0,OS_OPT_PEND_BLOCKING,0,&err);
			
			GPIO_SetBits(_485_PORT,_485_DE_PIN);		// 使能发送数据
			GPIO_SetBits(_485_PORT,_485_RE_PIN);		
			
			OSTimeDlyHMSM(0,0,0,200,(OS_OPT)OS_OPT_TIME_DLY,(OS_ERR*)&err);
			
			RTC_GetTime(RTC_Format_BIN, &RTC_TimeStructure);
			RTC_GetDate(RTC_Format_BIN, &RTC_DateStructure);
			
			Usart_485("\r\n%d/%d %d:%d:%d",
						RTC_DateStructure.RTC_Month, 
						RTC_DateStructure.RTC_Date,
						RTC_TimeStructure.RTC_Hours,
						RTC_TimeStructure.RTC_Minutes,
						RTC_TimeStructure.RTC_Seconds );

			if(AD_Value_CH1_VPP !=0 &&AD_Value_CH2_VPP !=0)
			{			
				Usart_485("\r\n speed : %d r/min", CH5_SPEED );
				Usart_485("\r\nCH1: ");
				for(i=0;i<1024;i++)
				{	
					Usart_485("%d,",AD_Value_CH1[i]);
				}
				
				Usart_485("\r\nCH2: ");
				for(i=0;i<1024;i++)
				{	
					Usart_485("%d,",AD_Value_CH2[i]);
				}
			}

			if(AD_Value_CH3_VPP !=0 &&AD_Value_CH4_VPP !=0)
			{
				Usart_485("\r\n speed : %d r/min", CH6_SPEED );
				Usart_485("\r\nCH3: ");
				for(i=0;i<1024;i++)
				{	
					Usart_485("%d,",AD_Value_CH3[i]);
				}
				
				Usart_485("\r\nCH4: ");
				for(i=0;i<1024;i++)
				{	
					Usart_WIFI("%d,",AD_Value_CH4[i]);
				}				
			}

			if(AD_Value_CH7_VPP !=0)
			{			
				Usart_485("\r\nCH7: ");
				for(i=0;i<1024;i++)
				{	
					Usart_485("%d,",AD_Value_CH7[i]);
				}	
			}			

			if(AD_Value_CH8_VPP !=0)
			{			
				Usart_485("\r\nCH8: ");
				for(i=0;i<1024;i++)
				{	
					Usart_485("%d,",AD_Value_CH8[i]);
				}	
			}	
			
			if(AD_Value_CH9_VPP !=0)
			{			
				Usart_485("\r\nCH9: ");
				for(i=0;i<1024;i++)
				{	
					Usart_485("%d,",AD_Value_CH9[i]);
				}		
			}
			
			if(AD_Value_CH10_VPP !=0)
			{			
				Usart_WIFI("\r\nCH10: ");
				for(i=0;i<1024;i++)
				{	
					Usart_485("%d,",AD_Value_CH10[i]);
				}				
			}
			Usart_485("\r\nALLEND\r\n");
			
			GPIO_ResetBits(_485_PORT,_485_DE_PIN);		// 使能接收数据
			GPIO_ResetBits(_485_PORT,_485_RE_PIN);
		}

		OSTimeDlyHMSM(0,0,5,0,(OS_OPT)OS_OPT_TIME_DLY,(OS_ERR*)&err);						
	}
}

/******************************************************************************************************
*	函 数 名: DHT11_Task
*	函数功能: DHT11温湿度模块通讯任务
*	说    明: 通讯周期 30s
*******************************************************************************************************/

static	void	DHT11_Task (void *p_arg)
{
	OS_ERR      err;
	(void)p_arg;

	while(DEF_TRUE)
	{	
		DHT11_Data_TypeDef DHT11_Data;
		if(Read_DHT11 ( & DHT11_Data ) == SUCCESS )
		{ 
			DHT11_humi=DHT11_Data.humi_int;
			DHT11_temp=DHT11_Data.temp_int;
			if(DHT11_temp >= 30 || DHT11_humi >50 )				//30℃ 或者 50%湿度 以上开风扇
			GPIO_ResetBits(FEN_CONTROL_PORT,FEN_CONTROL_PIN);	//开风扇
			else
			GPIO_SetBits(FEN_CONTROL_PORT,FEN_CONTROL_PIN);		//关风扇
		}
	
		OSTimeDlyHMSM(0,0,30,0,(OS_OPT)OS_OPT_TIME_DLY,(OS_ERR*)&err);	
	}		
}

/******************************************************************************************************
*	函 数 名: GPS_Task
*	函数功能: GPS模块 数据处理
* 	说    明：处理周期 1min
*******************************************************************************************************/

static	void	GPS_Task (void *p_arg)
{
	OS_ERR      err;
	(void)p_arg;
	
	while(DEF_TRUE)
	{	
		if(GPS_select == 1)
		{
			nmea_msg gpsx; 											   //GPS信息
			extern  uint8_t gps_rbuff[GPS_RBUFF_SIZE];
			extern __IO uint8_t GPS_TransferEnd ;			
			extern unsigned int HOURS,MINUTES,SECONDS,DATE,MONTH,YEAR;
				
			//使能串口接收中断
			USART_ITConfig(GPS_USART, USART_IT_RXNE, ENABLE);	
				
			OSTimeDlyHMSM(0,0,5,0,(OS_OPT)OS_OPT_TIME_DLY,(OS_ERR*)&err);	//等待5s 接收数据
			
			if(GPS_TransferEnd == 1)
			{	
				NMEA_GNRMC_Analysis(&gpsx,(u8*)gps_rbuff);	
				
				GPS_TransferEnd = 0;
				
				if(gpsx.longitude != 0)
				{
					data_longitude	=gpsx.longitude;			//得到经度
					data_ewhemi		=gpsx.ewhemi;	
				}
				if(gpsx.latitude != 0)
				{
					data_latitude	=gpsx.latitude;				//得到纬度  
					data_nshemi		=gpsx.nshemi;	
				}
				
				if(gpsx.utc.year < 2050 )	//判断数据是否正确 这里 year有BUG 一直会是2021
				{					
					gpsx.utc.hour=gpsx.utc.hour+8;					//东八区
					if(gpsx.utc.hour>24)
					{	gpsx.utc.hour=gpsx.utc.hour-24;}

					//使用GPS时间信息更新RTC实时时钟
					HOURS=gpsx.utc.hour;                     // 0~23        
					MINUTES=gpsx.utc.min;                    // 0~59
					SECONDS=gpsx.utc.sec;                    // 0~59
					DATE=gpsx.utc.date;          // 1~31
					MONTH=gpsx.utc.month;        // 1~12
					YEAR=gpsx.utc.year-2000;     // 0~99
					
					RTC_TimeAndDate_Set();
				}
			}
		}
		OSTimeDlyHMSM(0,1,0,0,(OS_OPT)OS_OPT_TIME_DLY,(OS_ERR*)&err);					
	}
}

/*******************************************************************************************************
*	函 数 名: SystemDatasBroadcast
*	函数功能: 系统信息，统计tesk的堆栈占用情况，232通讯接口输出信息
*******************************************************************************************************/

static	void	SystemDatasBroadcast_Task (void *p_arg)
{
	OS_ERR err;
	CPU_STK_SIZE free,used;
	CPU_INT16U     version;
	CPU_INT32U     cpu_clk_freq;
	
	version = OSVersion(&err);                          //获取uC/OS版本号
	cpu_clk_freq = BSP_CPU_ClkFreq();                   //获取CPU时钟，时间戳是以该时钟计数
	
	RTC_TimeTypeDef RTC_TimeStructure;
	RTC_DateTypeDef RTC_DateStructure;
	
	(void)p_arg;
	
	while(DEF_TRUE)
	{	
		RTC_GetTime(RTC_Format_BIN, &RTC_TimeStructure);
		RTC_GetDate(RTC_Format_BIN, &RTC_DateStructure);
		
		printf ("\r\nYZU  Electromechanical monitoring  2019/4-2019/6\r\n");
		
		printf ("System time:%d/%d %d:%d:%d\r\n",
						RTC_DateStructure.RTC_Month, 
						RTC_DateStructure.RTC_Date,
						RTC_TimeStructure.RTC_Hours,
						RTC_TimeStructure.RTC_Minutes,
						RTC_TimeStructure.RTC_Seconds );
		//版本号
		printf ( "uC/OS: V%d.%02d.%02d\r\n", version / 10000, version % 10000 / 100, version % 100 );
		//CPU主频
		printf ( "CPU: %d MHz\r\n", cpu_clk_freq / 1000000 );  
		//CPU使用率
		printf ( "CPU Utilization rate: %d.%d%%\r\n",OSStatTaskCPUUsage / 100, OSStatTaskCPUUsage % 100 );   
		//CPU最大使用率
		printf ( "CPU Maximum utilization rate: %d.%d%%\r\n\r\n",  OSStatTaskCPUUsageMax / 100, OSStatTaskCPUUsageMax % 100 );

		OSTaskStkChk (&SystemDatasBroadcast_TaskTCB,&free,&used,&err);
		printf("SystemDatasBroadcast  usage:%d%%\r\n",(used*100)/(used+free));

		OSTaskStkChk (&iwdg_TaskTCB,&free,&used,&err);
		printf("iwdg_Task             usage:%d%%\r\n",(used*100)/(used+free));
		
		OSTaskStkChk (&LED_TaskTCB,&free,&used,&err);
		printf("LED_Task              usage:%d%%\r\n",(used*100)/(used+free));
		
		OSTaskStkChk (&Touch_TaskTCB,&free,&used,&err);
		printf("Touch_Task            usage:%d%%\r\n",(used*100)/(used+free));

		OSTaskStkChk (&Key_TaskTCB,&free,&used,&err);
		printf("Key_Task              usage:%d%%\r\n",(used*100)/(used+free));
		
		OSTaskStkChk (&emWin_TaskTCB,&free,&used,&err);
		printf("emWin_Task            usage:%d%%\r\n",(used*100)/(used+free));
			
		OSTaskStkChk (&ADC2_TaskTCB,&free,&used,&err);
		printf("ADC2_Task             usage:%d%%\r\n",(used*100)/(used+free));

		OSTaskStkChk (&ADC3_TaskTCB,&free,&used,&err);
		printf("ADC3_Task             usage:%d%%\r\n",(used*100)/(used+free));

		OSTaskStkChk (&DSP_TaskTCB,&free,&used,&err);
		printf("DSP_Task              usage:%d%%\r\n",(used*100)/(used+free));
		
		OSTaskStkChk (&DHT11_TaskTCB,&free,&used,&err);
		printf("DHT11_Task            usage:%d%%\r\n",(used*100)/(used+free));
		
		OSTaskStkChk (&SD_TaskTCB,&free,&used,&err);
		printf("SD_Task               usage:%d%%\r\n",(used*100)/(used+free));

		OSTaskStkChk (&GPS_TaskTCB,&free,&used,&err);
		printf("GPS_Task              usage:%d%%\r\n",(used*100)/(used+free));

		OSTaskStkChk (&_4G_TaskTCB,&free,&used,&err);
		printf("_4G_Task              usage:%d%%\r\n",(used*100)/(used+free));
		
		OSTaskStkChk (&_485_TaskTCB,&free,&used,&err);
		printf("_485_Task             usage:%d%%\r\n",(used*100)/(used+free));
		
		OSTaskStkChk (&WIFI_TaskTCB,&free,&used,&err);
		printf("WIFI_Task             usage:%d%%\r\n",(used*100)/(used+free));

		OSTimeDlyHMSM(0,1,0,0,(OS_OPT)OS_OPT_TIME_DLY,(OS_ERR*)&err);
   }
}

/************************************		END			***********************************************/


