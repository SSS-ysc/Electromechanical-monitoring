/*   
      ���ݴ�ѧ ���15 ���ٳ�         
		
		GPS ATGM332D����      
		USART1  PB6 PB7        			

	     2019/4 - 2019/6                  */

#include "GPS.h"

/* ���ջ���  */
uint8_t gps_rbuff[GPS_RBUFF_SIZE];

/* ���������־ */
__IO uint8_t GPS_TransferEnd ;


// ������usart_GPS IO�ڳ�ʼ��
//
void  USART_GPS_GPIO_Config	(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd ( USART_GPS_RX_CLK, ENABLE); 	//IO��ʱ������

	//IO����
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;     //����ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;    //����
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;		  //����
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //�ٶȵȼ�

	//��ʼ�� RX ����													   
	GPIO_InitStructure.GPIO_Pin = USART_GPS_RX_PIN;	
	GPIO_Init(USART_GPS_RX_PORT, &GPIO_InitStructure);		
	
	//IO���ã����õ�USART1 
	GPIO_PinAFConfig(USART_GPS_RX_PORT,USART_GPS_RX_PinSource,GPIO_AF_USART1);
}

// ����GPSʹ�õĴ����ж� 
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


// ������USART_GPS �ڳ�ʼ��
//
void Usart_GPS_Config(void)
{		
	USART_InitTypeDef USART_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	// IO�ڳ�ʼ��
	USART_GPS_GPIO_Config();
		 
	// ���ô��ڸ������
	USART_InitStructure.USART_BaudRate 	 = USART_GPS_BaudRate;  //������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; //����λ8λ
	USART_InitStructure.USART_StopBits   = USART_StopBits_1;    //ֹͣλ1λ
	USART_InitStructure.USART_Parity     = USART_Parity_No ;    //��У��
	USART_InitStructure.USART_Mode 	     = USART_Mode_Rx ;      //����ģʽ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // ��ʹ��Ӳ��������
	
	//��ʼ������
	USART_Init(GPS_USART,&USART_InitStructure); 
	
	//����GPSʹ�õĴ����ж� NCIV
	GPS_Interrupt_Config();

	//ʹ�ܴ���1
	USART_Cmd(GPS_USART,ENABLE);	
}

void GPS_Config(void)
{  
	Usart_GPS_Config();
}
 

// ��buf����õ���cx���������ڵ�λ��
// ����ֵ:0~0XFE,����������λ�õ�ƫ��.
//       0XFF,�������ڵ�cx������	
//
u8 NMEA_Comma_Pos(u8 *buf,u8 cx)
{	 		    
	u8 *p=buf;
	while(cx)
	{		 
		if(*buf=='*'||*buf<' '||*buf>'z')return 0XFF;//����'*'���߷Ƿ��ַ�,�򲻴��ڵ�cx������
		if(*buf==',')cx--;
		buf++;
	}
	return buf-p;	 
}

// m^n����
// ����ֵ:m^n�η�
//
u32 NMEA_Pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}

// strת��Ϊ����,��','����'*'����
// buf:���ִ洢��
// dx:С����λ��,���ظ����ú���
// ����ֵ:ת�������ֵ
//
int NMEA_Str2num(u8 *buf,u8*dx)
{
	u8 *p=buf;
	u32 ires=0,fres=0;
	u8 ilen=0,flen=0,i;
	u8 mask=0;
	int res;
	while(1) //�õ�������С���ĳ���
	{
		if(*p=='-'){mask|=0X02;p++;}//�Ǹ���
		if(*p==','||(*p=='*'))break;//����������
		if(*p=='.'){mask|=0X01;p++;}//����С������
		else if(*p>'9'||(*p<'0'))	//�зǷ��ַ�
		{	
			ilen=0;
			flen=0;
			break;
		}	
		if(mask&0X01)flen++;
		else ilen++;
		p++;
	}
	if(mask&0X02)buf++;	//ȥ������
	for(i=0;i<ilen;i++)	//�õ�������������
	{  
		ires+=NMEA_Pow(10,ilen-1-i)*(buf[i]-'0');
	}
	if(flen>5)flen=5;	//���ȡ5λС��
	*dx=flen;	 		//С����λ��
	for(i=0;i<flen;i++)	//�õ�С����������
	{  
		fres+=NMEA_Pow(10,flen-1-i)*(buf[ilen+1+i]-'0');
	} 
	res=ires*NMEA_Pow(10,flen)+fres;
	if(mask&0X02)res=-res;		   
	return res;
}	  							 


// ����GNRMC��Ϣ
// gpsx:nmea��Ϣ�ṹ��
// buf:���յ���GPS���ݻ������׵�ַ
//
void NMEA_GNRMC_Analysis(nmea_msg *gpsx,u8 *buf)
{
	u8 *p1,dx;			 
	u8 posx;     
	u32 temp;	   
	float rs;  
	p1=(u8*)strstr((const char *)buf,"$GNRMC");  		//"$GNRMC"Ϊ�׵�һ֡����
	
	posx=NMEA_Comma_Pos(p1,1);							//�õ�UTCʱ��
	if(posx!=0XFF)
	{
		temp=NMEA_Str2num(p1+posx,&dx)/NMEA_Pow(10,dx);	//�õ�UTCʱ��,ȥ��ms
		gpsx->utc.hour=temp/10000;
		gpsx->utc.min=(temp/100)%100;
		gpsx->utc.sec=temp%100;	 	 
	}	
	
	posx=NMEA_Comma_Pos(p1,3);							//�õ�γ��
	if(posx!=0XFF)
	{
		temp=NMEA_Str2num(p1+posx,&dx);		 	 
		gpsx->latitude=temp/NMEA_Pow(10,dx+2);	        //�õ���
		rs=temp%NMEA_Pow(10,dx+2);				        //�õ�'		 
		gpsx->latitude=gpsx->latitude*NMEA_Pow(10,5)+(rs*NMEA_Pow(10,5-dx))/60;//ת��Ϊ�� 
	}
	
	posx=NMEA_Comma_Pos(p1,4);							//��γ���Ǳ�γ 
	if(posx!=0XFF)gpsx->nshemi=*(p1+posx);					 
 	
	posx=NMEA_Comma_Pos(p1,5);							//�õ�����
	if(posx!=0XFF)
	{												  
		temp=NMEA_Str2num(p1+posx,&dx);		 	 
		gpsx->longitude=temp/NMEA_Pow(10,dx+2);			//�õ���
		rs=temp%NMEA_Pow(10,dx+2);				        //�õ�'		 
		gpsx->longitude=gpsx->longitude*NMEA_Pow(10,5)+(rs*NMEA_Pow(10,5-dx))/60;//ת��Ϊ�� 
	}
	
	posx=NMEA_Comma_Pos(p1,6);							//������������
	if(posx!=0XFF)gpsx->ewhemi=*(p1+posx);

	
	posx=NMEA_Comma_Pos(p1,9);							//�õ�UTC����
	if(posx!=0XFF)
	{
		temp=NMEA_Str2num(p1+posx,&dx);		 			//�õ�UTC����
		gpsx->utc.date=temp/10000;
		gpsx->utc.month=(temp/100)%100;
		gpsx->utc.year=2000+temp%100;	 	 
	} 
}


