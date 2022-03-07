/*   
      扬州大学 测控15 杨寿晨         
		
		GPS ATGM332D程序      
		USART1  PB6 PB7        			

	     2019/4 - 2019/6                  */

#include "GPS.h"

/* 接收缓冲  */
uint8_t gps_rbuff[GPS_RBUFF_SIZE];

/* 传输结束标志 */
__IO uint8_t GPS_TransferEnd ;


// 函数：usart_GPS IO口初始化
//
void  USART_GPS_GPIO_Config	(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd ( USART_GPS_RX_CLK, ENABLE); 	//IO口时钟配置

	//IO配置
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;     //复用模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;    //推挽
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;		  //上拉
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //速度等级

	//初始化 RX 引脚													   
	GPIO_InitStructure.GPIO_Pin = USART_GPS_RX_PIN;	
	GPIO_Init(USART_GPS_RX_PORT, &GPIO_InitStructure);		
	
	//IO复用，复用到USART1 
	GPIO_PinAFConfig(USART_GPS_RX_PORT,USART_GPS_RX_PinSource,GPIO_AF_USART1);
}

// 配置GPS使用的串口中断 
void GPS_Interrupt_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	//  Channel Interrupt ENABLE
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}


// 函数：USART_GPS 口初始化
//
void Usart_GPS_Config(void)
{		
	USART_InitTypeDef USART_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	// IO口初始化
	USART_GPS_GPIO_Config();
		 
	// 配置串口各项参数
	USART_InitStructure.USART_BaudRate 	 = USART_GPS_BaudRate;  //波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; //数据位8位
	USART_InitStructure.USART_StopBits   = USART_StopBits_1;    //停止位1位
	USART_InitStructure.USART_Parity     = USART_Parity_No ;    //无校验
	USART_InitStructure.USART_Mode 	     = USART_Mode_Rx ;      //接收模式
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 不使用硬件流控制
	
	//初始化串口
	USART_Init(GPS_USART,&USART_InitStructure); 
	
	//配置GPS使用的串口中断 NCIV
	GPS_Interrupt_Config();

	//使能串口1
	USART_Cmd(GPS_USART,ENABLE);	
}

void GPS_Config(void)
{  
	Usart_GPS_Config();
}
 

// 从buf里面得到第cx个逗号所在的位置
// 返回值:0~0XFE,代表逗号所在位置的偏移.
//       0XFF,代表不存在第cx个逗号	
//
u8 NMEA_Comma_Pos(u8 *buf,u8 cx)
{	 		    
	u8 *p=buf;
	while(cx)
	{		 
		if(*buf=='*'||*buf<' '||*buf>'z')return 0XFF;//遇到'*'或者非法字符,则不存在第cx个逗号
		if(*buf==',')cx--;
		buf++;
	}
	return buf-p;	 
}

// m^n函数
// 返回值:m^n次方
//
u32 NMEA_Pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}

// str转换为数字,以','或者'*'结束
// buf:数字存储区
// dx:小数点位数,返回给调用函数
// 返回值:转换后的数值
//
int NMEA_Str2num(u8 *buf,u8*dx)
{
	u8 *p=buf;
	u32 ires=0,fres=0;
	u8 ilen=0,flen=0,i;
	u8 mask=0;
	int res;
	while(1) //得到整数和小数的长度
	{
		if(*p=='-'){mask|=0X02;p++;}//是负数
		if(*p==','||(*p=='*'))break;//遇到结束了
		if(*p=='.'){mask|=0X01;p++;}//遇到小数点了
		else if(*p>'9'||(*p<'0'))	//有非法字符
		{	
			ilen=0;
			flen=0;
			break;
		}	
		if(mask&0X01)flen++;
		else ilen++;
		p++;
	}
	if(mask&0X02)buf++;	//去掉负号
	for(i=0;i<ilen;i++)	//得到整数部分数据
	{  
		ires+=NMEA_Pow(10,ilen-1-i)*(buf[i]-'0');
	}
	if(flen>5)flen=5;	//最多取5位小数
	*dx=flen;	 		//小数点位数
	for(i=0;i<flen;i++)	//得到小数部分数据
	{  
		fres+=NMEA_Pow(10,flen-1-i)*(buf[ilen+1+i]-'0');
	} 
	res=ires*NMEA_Pow(10,flen)+fres;
	if(mask&0X02)res=-res;		   
	return res;
}	  							 


// 分析GNRMC信息
// gpsx:nmea信息结构体
// buf:接收到的GPS数据缓冲区首地址
//
void NMEA_GNRMC_Analysis(nmea_msg *gpsx,u8 *buf)
{
	u8 *p1,dx;			 
	u8 posx;     
	u32 temp;	   
	float rs;  
	p1=(u8*)strstr((const char *)buf,"$GNRMC");  		//"$GNRMC"为首的一帧数据
	
	posx=NMEA_Comma_Pos(p1,1);							//得到UTC时间
	if(posx!=0XFF)
	{
		temp=NMEA_Str2num(p1+posx,&dx)/NMEA_Pow(10,dx);	//得到UTC时间,去掉ms
		gpsx->utc.hour=temp/10000;
		gpsx->utc.min=(temp/100)%100;
		gpsx->utc.sec=temp%100;	 	 
	}	
	
	posx=NMEA_Comma_Pos(p1,3);							//得到纬度
	if(posx!=0XFF)
	{
		temp=NMEA_Str2num(p1+posx,&dx);		 	 
		gpsx->latitude=temp/NMEA_Pow(10,dx+2);	        //得到°
		rs=temp%NMEA_Pow(10,dx+2);				        //得到'		 
		gpsx->latitude=gpsx->latitude*NMEA_Pow(10,5)+(rs*NMEA_Pow(10,5-dx))/60;//转换为° 
	}
	
	posx=NMEA_Comma_Pos(p1,4);							//南纬还是北纬 
	if(posx!=0XFF)gpsx->nshemi=*(p1+posx);					 
 	
	posx=NMEA_Comma_Pos(p1,5);							//得到经度
	if(posx!=0XFF)
	{												  
		temp=NMEA_Str2num(p1+posx,&dx);		 	 
		gpsx->longitude=temp/NMEA_Pow(10,dx+2);			//得到°
		rs=temp%NMEA_Pow(10,dx+2);				        //得到'		 
		gpsx->longitude=gpsx->longitude*NMEA_Pow(10,5)+(rs*NMEA_Pow(10,5-dx))/60;//转换为° 
	}
	
	posx=NMEA_Comma_Pos(p1,6);							//东经还是西经
	if(posx!=0XFF)gpsx->ewhemi=*(p1+posx);

	
	posx=NMEA_Comma_Pos(p1,9);							//得到UTC日期
	if(posx!=0XFF)
	{
		temp=NMEA_Str2num(p1+posx,&dx);		 			//得到UTC日期
		gpsx->utc.date=temp/10000;
		gpsx->utc.month=(temp/100)%100;
		gpsx->utc.year=2000+temp%100;	 	 
	} 
}


