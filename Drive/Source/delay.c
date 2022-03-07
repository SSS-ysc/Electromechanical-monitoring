/*   
      扬州大学 测控15 杨寿晨          
		
		  延迟函数 程序        

	    2019/4 - 2019/6             */

#include "delay.h"
#include "includes.h"

// us级延时时,关闭任务调度
void delay_osschedlock(void)
{
	OS_ERR err;
	OSSchedLock(&err);
}

// us级延时时,恢复任务调度
void delay_osschedunlock(void)
{	
	OS_ERR err; 
	OSSchedUnlock(&err);
}

// 延时nus
// nus:要延时的us数.	
// nus:0~190887435(最大值22.5)	    								   
void Delay_us(u32 nus)
{		
	u32 ticks;
	u32 told,tnow,tcnt=0;
	u32 reload=SysTick->LOAD;		//LOAD的值	    	 
	ticks=nus*180;					//需要的节拍数
	
	delay_osschedlock();			//阻止OS调度，防止打断us延时
	told=SysTick->VAL;				//刚进入时的计数器值
	while(1)
	{
		tnow=SysTick->VAL;	
		if(tnow!=told)
		{	    
			if(tnow<told)tcnt+=told-tnow;	//递减的计数器
			else tcnt+=reload-tnow+told;	    
			told=tnow;
			if(tcnt>=ticks)break;			//时间超过/等于要延迟的时间,则退出.
		}  
	}
	delay_osschedunlock();					//恢复OS调度											    
} 

// 延时nms
// nms:要延时的ms数
// nms:0~65535
void Delay_ms(u16 nms)
{		
	 Delay_us((u32)(nms*1000));
}

