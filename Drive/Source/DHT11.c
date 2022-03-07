/*   
      扬州大学 测控15 杨寿晨          
		
		    温湿度DHT11 程序        

	     2019/4 - 2019/6               */

#include "DHT11.h"
#include "delay.h"

// 函数名：DHT11_GPIO_Config
// 描述  ：配置DHT11用到的I/O口
//
void DHT11_GPIO_Config(void)
{		
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(DHT11_CLK, ENABLE); 	
		
	GPIO_InitStructure.GPIO_Pin = DHT11_PIN;	
	/*设置引脚模式为通用推挽输出*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;   
	/*设置引脚的输出类型为推挽输出*/
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	/*设置引脚为上拉模式*/
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	/*设置引脚速率为50MHz */   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	/*调用库函数，初始化DHT11_PORT*/
	GPIO_Init(DHT11_PORT, &GPIO_InitStructure); 
}

// 函数名：DHT11_Mode_IPU
// 描述  ：使DHT11-DATA引脚变为上拉输入模式
//
void DHT11_Mode_IPU(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	/*选择要控制的DHT11_PORT引脚*/	
	GPIO_InitStructure.GPIO_Pin = DHT11_PIN;
	/*设置引脚模式为浮空输入模式*/ 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN ; 
    /*设置引脚为复用推挽*/
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	/*设置引脚速率为50MHz */   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	/*调用库函数，初始化DHT11_PORT*/
	GPIO_Init(DHT11_PORT, &GPIO_InitStructure);	 
}

// 函数名：DHT11_Mode_Out_PP
// 描述  ：使DHT11-DATA引脚变为推挽输出模式
//
void DHT11_Mode_Out_PP(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	/*选择要控制的DHT11_PORT引脚*/
	GPIO_InitStructure.GPIO_Pin = DHT11_PIN;
	/*设置引脚模式为通用推挽输出*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	/*设置引脚的输出类型为推挽输出*/
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	/*设置引脚为上拉模式*/
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	/*设置引脚速率为50MHz */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	/*调用库函数，初始化DHT11_PORT*/
	GPIO_Init(DHT11_PORT, &GPIO_InitStructure);
}


// 从DHT11读取一个字节，MSB先行
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
		/* 等待数据1的高电平结束 */
		Delay_us(40); 
		retry=0;
		while(DHT11_DATA_IN()&&retry<100)
		{				retry++; Delay_us(1); 	
		}	
		temp|=(uint8_t)(0x01<<(7-i));  //把第7-i位置1，MSB先行 
		}
		else 
		temp&=(uint8_t)~(0x01<<(7-i)); //把第7-i位置0，MSB先行return 0;   
		}
		return temp;
}


// 一次完整的数据传输为40bit，高位先出
// 8bit 湿度整数 + 8bit 湿度小数 + 8bit 温度整数 + 8bit 温度小数 + 8bit 校验和 
//
uint8_t Read_DHT11(DHT11_Data_TypeDef *DHT11_Data)
{ 
	uint16_t count_DHT11;
	/*输出模式*/
	DHT11_Mode_Out_PP();
	/*主机拉低*/
	DHT11_DATA_OUT(DHT11_LOW);
	/*延时20ms*/
	Delay_us(20000);
	/*总线拉高*/
	DHT11_DATA_OUT(DHT11_HIGH); 
	/*延时30us*/
	Delay_us(30);  

	/*输入模式*/ 
	DHT11_Mode_IPU();

	/*判断从机是否有低电平响应信号*/   
	if(DHT11_DATA_IN()==Bit_RESET)     
	{
		count_DHT11=0;
		/*轮询直到从机发出 的80us 低电平 响应信号结束*/  
		while(DHT11_DATA_IN()==Bit_RESET)
		{
		  count_DHT11++;
		  if(count_DHT11>100)  return 0;
		  Delay_us(1); }
	   
		count_DHT11=0;
		/*轮询直到从机发出的 80us 高电平 标置信号结束*/
		while(DHT11_DATA_IN()==Bit_SET)
		{
		  count_DHT11++;
		  if(count_DHT11>100)  return 0;
		  Delay_us(1); } 

		/*开始接收数据*/   
		DHT11_Data->humi_int  = Read_Byte();

		DHT11_Data->humi_deci = Read_Byte();

		DHT11_Data->temp_int  = Read_Byte();

		DHT11_Data->temp_deci = Read_Byte();

		DHT11_Data->check_sum = Read_Byte();

		/*读取结束，引脚改为输出模式*/
		DHT11_Mode_Out_PP();
		/*主机拉高*/
		DHT11_DATA_OUT(DHT11_HIGH);

		/*检查读取的数据是否正确*/
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


