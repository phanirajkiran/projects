#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#include "delay.h"
#include "Usart.h"
#include "Rs485.h"	
#include "ADC.h"

/**
************************************************************
************************************************************
************************************************************
*
*	作者： 		重庆八城科技
*
*	日期： 		2018-01-01
*
*	版本： 		V1.0
*
*	说明： 		人体红外库函数操作实验-HAL库版本
*
*	修改记录：	
************************************************************
************************************************************
************************************************************
**/
uint32_t Light_AD = 0; 							//存放AD采样值

int main(void)
{ 
  HAL_Init();             					//初始化HAL库  
	UART1_Init(115200);								//初始化串口
	Rs485_Init();   									//初始化485
	MY_ADC_Init();                  	//初始化ADC1通道1
	
	while(1)
	{	
		Light_AD = Get_Adc_Average(ADC_CHANNEL_0,50);	//获取通道0的转换值，50次取平均
		
		Rs485_Config(1); 															//485发送模式
		printf("pir->led%d\r\n",Light_AD);						//将数据发送给LED
		HAL_Delay(10);
		Rs485_Config(0);					 										//485接收模式 
	  HAL_Delay(100);
	}
}

