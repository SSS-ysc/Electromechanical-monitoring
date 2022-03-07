/*   
      ���ݴ�ѧ ���15 ���ٳ�          
		
		    ��ʪ��DHT11 ����        

	     2019/4 - 2019/6               */

#include "DHT11.h"
#include "delay.h"

// ��������DHT11_GPIO_Config
// ����  ������DHT11�õ���I/O��
//
void DHT11_GPIO_Config(void)
{		
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(DHT11_CLK, ENABLE); 	
		
	GPIO_InitStructure.GPIO_Pin = DHT11_PIN;	
	/*��������ģʽΪͨ���������*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;   
	/*�������ŵ��������Ϊ�������*/
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	/*��������Ϊ����ģʽ*/
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	/*������������Ϊ50MHz */   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	/*���ÿ⺯������ʼ��DHT11_PORT*/
	GPIO_Init(DHT11_PORT, &GPIO_InitStructure); 
}

// ��������DHT11_Mode_IPU
// ����  ��ʹDHT11-DATA���ű�Ϊ��������ģʽ
//
void DHT11_Mode_IPU(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	/*ѡ��Ҫ���Ƶ�DHT11_PORT����*/	
	GPIO_InitStructure.GPIO_Pin = DHT11_PIN;
	/*��������ģʽΪ��������ģʽ*/ 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN ; 
    /*��������Ϊ��������*/
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	/*������������Ϊ50MHz */   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	/*���ÿ⺯������ʼ��DHT11_PORT*/
	GPIO_Init(DHT11_PORT, &GPIO_InitStructure);	 
}

// ��������DHT11_Mode_Out_PP
// ����  ��ʹDHT11-DATA���ű�Ϊ�������ģʽ
//
void DHT11_Mode_Out_PP(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	/*ѡ��Ҫ���Ƶ�DHT11_PORT����*/
	GPIO_InitStructure.GPIO_Pin = DHT11_PIN;
	/*��������ģʽΪͨ���������*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	/*�������ŵ��������Ϊ�������*/
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	/*��������Ϊ����ģʽ*/
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	/*������������Ϊ50MHz */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	/*���ÿ⺯������ʼ��DHT11_PORT*/
	GPIO_Init(DHT11_PORT, &GPIO_InitStructure);
}


// ��DHT11��ȡһ���ֽڣ�MSB����
//
static uint8_t Read_Byte(void)
{
	u8 retry,i, temp=0;
	for(i=0;i<8;i++)    
	{
	  while(DHT11_DATA_IN()&&retry<100)//wait become Low level
	  {
	   retry++;
	   Delay_us(1);
	  }
	   retry=0;
	  while(!DHT11_DATA_IN()&&retry<100)//wait become High level
	  {
	   retry++;
	   Delay_us(1);
	  }
			
	   Delay_us(30);//wait 30us
			
	  if(DHT11_DATA_IN()==Bit_SET)
	  { 
		/* �ȴ�����1�ĸߵ�ƽ���� */
		Delay_us(40); 
		retry=0;
		while(DHT11_DATA_IN()&&retry<100)
		{				retry++; Delay_us(1); 	
		}	
		temp|=(uint8_t)(0x01<<(7-i));  //�ѵ�7-iλ��1��MSB���� 
		}
		else 
		temp&=(uint8_t)~(0x01<<(7-i)); //�ѵ�7-iλ��0��MSB����return 0;   
		}
		return temp;
}


// һ�����������ݴ���Ϊ40bit����λ�ȳ�
// 8bit ʪ������ + 8bit ʪ��С�� + 8bit �¶����� + 8bit �¶�С�� + 8bit У��� 
//
uint8_t Read_DHT11(DHT11_Data_TypeDef *DHT11_Data)
{ 
	uint16_t count_DHT11;
	/*���ģʽ*/
	DHT11_Mode_Out_PP();
	/*��������*/
	DHT11_DATA_OUT(DHT11_LOW);
	/*��ʱ20ms*/
	Delay_us(20000);
	/*��������*/
	DHT11_DATA_OUT(DHT11_HIGH); 
	/*��ʱ30us*/
	Delay_us(30);  

	/*����ģʽ*/ 
	DHT11_Mode_IPU();

	/*�жϴӻ��Ƿ��е͵�ƽ��Ӧ�ź�*/   
	if(DHT11_DATA_IN()==Bit_RESET)     
	{
		count_DHT11=0;
		/*��ѯֱ���ӻ����� ��80us �͵�ƽ ��Ӧ�źŽ���*/  
		while(DHT11_DATA_IN()==Bit_RESET)
		{
		  count_DHT11++;
		  if(count_DHT11>100)  return 0;
		  Delay_us(1); }
	   
		count_DHT11=0;
		/*��ѯֱ���ӻ������� 80us �ߵ�ƽ �����źŽ���*/
		while(DHT11_DATA_IN()==Bit_SET)
		{
		  count_DHT11++;
		  if(count_DHT11>100)  return 0;
		  Delay_us(1); } 

		/*��ʼ��������*/   
		DHT11_Data->humi_int  = Read_Byte();

		DHT11_Data->humi_deci = Read_Byte();

		DHT11_Data->temp_int  = Read_Byte();

		DHT11_Data->temp_deci = Read_Byte();

		DHT11_Data->check_sum = Read_Byte();

		/*��ȡ���������Ÿ�Ϊ���ģʽ*/
		DHT11_Mode_Out_PP();
		/*��������*/
		DHT11_DATA_OUT(DHT11_HIGH);

		/*����ȡ�������Ƿ���ȷ*/
		if(DHT11_Data->check_sum == DHT11_Data->humi_int + DHT11_Data->humi_deci + DHT11_Data->temp_int+ DHT11_Data->temp_deci)
			return 1;
		else 
			return 0;	
	}
	else
	{			
		return 0;
	}  
}


