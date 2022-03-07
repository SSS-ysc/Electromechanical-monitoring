/*   
      ���ݴ�ѧ ���15 ���ٳ�          
		
		  �ӳٺ��� ����        

	    2019/4 - 2019/6             */

#include "delay.h"
#include "includes.h"

// us����ʱʱ,�ر��������
void delay_osschedlock(void)
{
	OS_ERR err;
	OSSchedLock(&err);
}

// us����ʱʱ,�ָ��������
void delay_osschedunlock(void)
{	
	OS_ERR err; 
	OSSchedUnlock(&err);
}

// ��ʱnus
// nus:Ҫ��ʱ��us��.	
// nus:0~190887435(���ֵ22.5)	    								   
void Delay_us(u32 nus)
{		
	u32 ticks;
	u32 told,tnow,tcnt=0;
	u32 reload=SysTick->LOAD;		//LOAD��ֵ	    	 
	ticks=nus*180;					//��Ҫ�Ľ�����
	
	delay_osschedlock();			//��ֹOS���ȣ���ֹ���us��ʱ
	told=SysTick->VAL;				//�ս���ʱ�ļ�����ֵ
	while(1)
	{
		tnow=SysTick->VAL;	
		if(tnow!=told)
		{	    
			if(tnow<told)tcnt+=told-tnow;	//�ݼ��ļ�����
			else tcnt+=reload-tnow+told;	    
			told=tnow;
			if(tcnt>=ticks)break;			//ʱ�䳬��/����Ҫ�ӳٵ�ʱ��,���˳�.
		}  
	}
	delay_osschedunlock();					//�ָ�OS����											    
} 

// ��ʱnms
// nms:Ҫ��ʱ��ms��
// nms:0~65535
void Delay_ms(u16 nms)
{		
	 Delay_us((u32)(nms*1000));
}

